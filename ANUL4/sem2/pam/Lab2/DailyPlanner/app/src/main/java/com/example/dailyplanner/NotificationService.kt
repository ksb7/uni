package com.example.dailyplanner

import android.app.NotificationChannel
import android.app.NotificationManager
import android.app.PendingIntent
import android.app.Service
import android.content.Context
import android.content.Intent
import android.os.Build
import android.os.Handler
import android.os.IBinder
import android.os.Looper
import androidx.core.app.NotificationCompat
import java.text.SimpleDateFormat
import java.util.*

class NotificationService : Service() {

    private val CHANNEL_ID = "planner_channel"
    private val handler = Handler(Looper.getMainLooper())
    private val notifiedIds = mutableSetOf<String>()

    private val checkRunnable = object : Runnable {
        override fun run() {
            checkDueTasks()
            handler.postDelayed(this, 30_000) // check every 30 seconds
        }
    }

    override fun onCreate() {
        super.onCreate()
        createNotificationChannel()
        handler.post(checkRunnable)
    }

    override fun onDestroy() {
        super.onDestroy()
        handler.removeCallbacks(checkRunnable)
    }

    override fun onBind(intent: Intent?): IBinder? = null

    private fun checkDueTasks() {
        val now = Calendar.getInstance()
        val sdfDate = SimpleDateFormat("yyyy-MM-dd", Locale.getDefault())
        val sdfTime = SimpleDateFormat("HH:mm", Locale.getDefault())
        val todayStr = sdfDate.format(now.time)
        val nowHour = now.get(Calendar.HOUR_OF_DAY)
        val nowMin = now.get(Calendar.MINUTE)

        val tasks = XmlTaskManager.getByDate(this, todayStr)

        for (task in tasks) {
            if (notifiedIds.contains(task.id)) continue
            try {
                val parts = task.time.split(":")
                val taskHour = parts[0].toInt()
                val taskMin = parts[1].toInt()

                // notify if within 1 minute of task time
                val diffMin = (taskHour * 60 + taskMin) - (nowHour * 60 + nowMin)
                if (diffMin in 0..1) {
                    sendTaskNotification(task)
                    notifiedIds.add(task.id)
                }
            } catch (e: Exception) {
                e.printStackTrace()
            }
        }
    }

    private fun sendTaskNotification(task: Task) {
        val intent = Intent(this, MainActivity::class.java)
        val pendingIntent = PendingIntent.getActivity(
            this, task.id.hashCode(), intent, PendingIntent.FLAG_IMMUTABLE
        )

        val notification = NotificationCompat.Builder(this, CHANNEL_ID)
            .setSmallIcon(android.R.drawable.ic_menu_agenda)
            .setContentTitle("Sarcină: ${task.title}")
            .setContentText("Ora ${task.time} — ${task.description}")
            .setStyle(NotificationCompat.BigTextStyle()
                .bigText("${task.description}\nPrioritate: ${task.priority}"))
            .setPriority(NotificationCompat.PRIORITY_HIGH)
            .setContentIntent(pendingIntent)
            .setAutoCancel(true)
            .build()

        val mgr = getSystemService(Context.NOTIFICATION_SERVICE) as NotificationManager
        mgr.notify(task.id.hashCode(), notification)
    }

    private fun createNotificationChannel() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            val channel = NotificationChannel(
                CHANNEL_ID, "Daily Planner", NotificationManager.IMPORTANCE_HIGH
            ).apply { description = "Notificări pentru sarcinile zilnice" }
            (getSystemService(Context.NOTIFICATION_SERVICE) as NotificationManager)
                .createNotificationChannel(channel)
        }
    }
}
