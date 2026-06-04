package com.example.dailyplanner

import android.content.Intent
import android.os.Bundle
import android.widget.*
import androidx.appcompat.app.AlertDialog
import androidx.appcompat.app.AppCompatActivity
import java.text.SimpleDateFormat
import java.util.*

class MainActivity : AppCompatActivity() {

    private lateinit var adapter: TaskAdapter
    private val displayedTasks = mutableListOf<Task>()
    private var selectedDate: String = todayString()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        startService(Intent(this, NotificationService::class.java))

        val calendarView = findViewById<CalendarView>(R.id.calendarView)
        val listView = findViewById<ListView>(R.id.listViewTasks)
        val editSearch = findViewById<EditText>(R.id.editSearch)
        val btnAdd = findViewById<Button>(R.id.btnAdd)
        val btnSearch = findViewById<Button>(R.id.btnSearch)
        val btnClearSearch = findViewById<Button>(R.id.btnClearSearch)

        adapter = TaskAdapter(this, displayedTasks)
        listView.adapter = adapter

        // Load today's tasks initially
        loadTasksForDate(selectedDate)

        calendarView.setOnDateChangeListener { _, year, month, day ->
            selectedDate = "%04d-%02d-%02d".format(year, month + 1, day)
            editSearch.setText("")
            loadTasksForDate(selectedDate)
        }

        btnAdd.setOnClickListener {
            val intent = Intent(this, AddActivity::class.java)
            intent.putExtra("selected_date", selectedDate)
            startActivity(intent)
        }

        btnSearch.setOnClickListener {
            val keyword = editSearch.text.toString().trim()
            if (keyword.isEmpty()) {
                Toast.makeText(this, "Introdu un cuvânt cheie", Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }
            val results = XmlTaskManager.search(this, keyword)
            displayedTasks.clear()
            displayedTasks.addAll(results)
            adapter.notifyDataSetChanged()
            Toast.makeText(this, "${results.size} rezultate găsite", Toast.LENGTH_SHORT).show()
        }

        btnClearSearch.setOnClickListener {
            editSearch.setText("")
            loadTasksForDate(selectedDate)
        }

        // Tap to update
        listView.setOnItemClickListener { _, _, position, _ ->
            val task = displayedTasks[position]
            val intent = Intent(this, UpdateActivity::class.java)
            intent.putExtra("task_id", task.id)
            startActivity(intent)
        }

        // Long press to delete
        listView.setOnItemLongClickListener { _, _, position, _ ->
            val task = displayedTasks[position]
            AlertDialog.Builder(this)
                .setTitle("Șterge sarcina")
                .setMessage("Sigur vrei să ștergi \"${task.title}\"?")
                .setPositiveButton("Șterge") { _, _ ->
                    XmlTaskManager.deleteTask(this, task.id)
                    loadTasksForDate(selectedDate)
                    Toast.makeText(this, "Sarcina a fost ștearsă", Toast.LENGTH_SHORT).show()
                }
                .setNegativeButton("Anulează", null)
                .show()
            true
        }
    }

    override fun onResume() {
        super.onResume()
        loadTasksForDate(selectedDate)
    }

    private fun loadTasksForDate(date: String) {
        val tasks = XmlTaskManager.getByDate(this, date).sortedBy { it.time }
        displayedTasks.clear()
        displayedTasks.addAll(tasks)
        adapter.notifyDataSetChanged()
    }

    private fun todayString(): String {
        return SimpleDateFormat("yyyy-MM-dd", Locale.getDefault()).format(Date())
    }
}
