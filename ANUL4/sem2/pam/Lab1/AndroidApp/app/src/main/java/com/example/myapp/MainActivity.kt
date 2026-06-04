package com.example.myapp

import android.Manifest
import android.app.NotificationChannel
import android.app.NotificationManager
import android.app.PendingIntent
import android.content.Context
import android.content.Intent
import android.content.pm.PackageManager
import android.net.Uri
import android.os.Build
import android.os.Bundle
import android.os.Handler
import android.os.Looper
import android.util.Log
import android.widget.*
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import androidx.core.app.NotificationCompat
import androidx.core.app.NotificationManagerCompat
import androidx.core.content.ContextCompat

class MainActivity : AppCompatActivity() {

    private val CHANNEL_ID = "myapp_channel"
    private val NOTIFICATION_ID = 1001
    private val REQUEST_NOTIFICATION_PERMISSION = 100

    private val presetItems = mutableListOf(
        MyItem(
            headTitle = "Planeta Pământ",
            contentOption = "A treia planetă de la Soare și singurul loc cunoscut din Univers care adăpostește viață. Are un diametru de aproximativ 12.742 km."
        ),
        MyItem(
            headTitle = "Inteligența artificială",
            contentOption = "Domeniu al informaticii care urmărește crearea de sisteme capabile să realizeze sarcini ce necesită în mod normal inteligență umană."
        ),
        MyItem(
            headTitle = "Muzica clasică",
            contentOption = "Tradiție muzicală europeană cu rădăcini în perioadele Baroc și Clasicism. Compozitori celebri includ Bach, Mozart și Beethoven."
        )
    )

    private lateinit var adapter: MyItemAdapter
    private var itemCounter = presetItems.size

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        Log.d("MYAPP", "MainActivity started OK")
        createNotificationChannel()
        requestNotificationPermissionIfNeeded()

        adapter = MyItemAdapter(this, presetItems)
        val listView = findViewById<ListView>(R.id.listViewItems)
        listView.adapter = adapter

        val editText = findViewById<EditText>(R.id.editTextSearch)

        findViewById<Button>(R.id.btnNotification).setOnClickListener {
            Toast.makeText(this, "Notificarea va apărea în 10 secunde", Toast.LENGTH_SHORT).show()
            Handler(Looper.getMainLooper()).postDelayed({ sendNotification() }, 10_000L)
        }

        findViewById<Button>(R.id.btnSearch).setOnClickListener {
            val keyword = editText.text.toString().trim()
            if (keyword.isEmpty()) {
                Toast.makeText(this, "Introdu un cuvânt cheie mai întâi", Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }
            val searchUri = Uri.parse("https://www.google.com/search?q=${Uri.encode(keyword)}")
            startActivity(Intent(Intent.ACTION_VIEW, searchUri))
        }

        findViewById<Button>(R.id.btnAddItem).setOnClickListener {
            val keyword = editText.text.toString().trim()
            itemCounter++
            val newItem = if (keyword.isNotEmpty()) {
                MyItem(
                    headTitle = keyword,
                    contentOption = "Element adăugat manual. Poziția $itemCounter în lista curentă."
                )
            } else {
                MyItem(
                    headTitle = "Element $itemCounter",
                    contentOption = "Element adăugat automat. Folosește câmpul de text pentru a-i da un nume."
                )
            }
            presetItems.add(newItem)
            adapter.notifyDataSetChanged()
            Toast.makeText(this, "Element adăugat", Toast.LENGTH_SHORT).show()
        }

        findViewById<Button>(R.id.btnClearList).setOnClickListener {
            presetItems.clear()
            itemCounter = 0
            adapter.notifyDataSetChanged()
            Toast.makeText(this, "Lista a fost golită", Toast.LENGTH_SHORT).show()
        }
    }

    private fun createNotificationChannel() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            val channel = NotificationChannel(
                CHANNEL_ID,
                "Notificări MyApp",
                NotificationManager.IMPORTANCE_HIGH
            ).apply { description = "Notificări generate de aplicație" }
            (getSystemService(Context.NOTIFICATION_SERVICE) as NotificationManager)
                .createNotificationChannel(channel)
        }
    }

    private fun requestNotificationPermissionIfNeeded() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.TIRAMISU) {
            if (ContextCompat.checkSelfPermission(this, Manifest.permission.POST_NOTIFICATIONS)
                != PackageManager.PERMISSION_GRANTED) {
                ActivityCompat.requestPermissions(
                    this,
                    arrayOf(Manifest.permission.POST_NOTIFICATIONS),
                    REQUEST_NOTIFICATION_PERMISSION
                )
            }
        }
    }

    private fun sendNotification() {
        val pendingIntent = PendingIntent.getActivity(
            this, 0,
            Intent(this, MainActivity::class.java).apply {
                flags = Intent.FLAG_ACTIVITY_NEW_TASK or Intent.FLAG_ACTIVITY_CLEAR_TASK
            },
            PendingIntent.FLAG_IMMUTABLE
        )

        val notification = NotificationCompat.Builder(this, CHANNEL_ID)
            .setSmallIcon(android.R.drawable.ic_dialog_info)
            .setContentTitle("MyApp")
            .setContentText("Notificarea a fost trimisă cu succes.")
            .setStyle(NotificationCompat.BigTextStyle()
                .bigText("Aceasta este o notificare trimisă de aplicația MyApp după un interval de 10 secunde."))
            .setPriority(NotificationCompat.PRIORITY_HIGH)
            .setContentIntent(pendingIntent)
            .setAutoCancel(true)
            .build()

        with(NotificationManagerCompat.from(this)) {
            if (ActivityCompat.checkSelfPermission(this@MainActivity, Manifest.permission.POST_NOTIFICATIONS)
                == PackageManager.PERMISSION_GRANTED || Build.VERSION.SDK_INT < Build.VERSION_CODES.TIRAMISU) {
                notify(NOTIFICATION_ID, notification)
            }
        }
    }
}
