package com.example.dailyplanner

import android.app.DatePickerDialog
import android.app.TimePickerDialog
import android.os.Bundle
import android.widget.*
import androidx.appcompat.app.AppCompatActivity

class UpdateActivity : AppCompatActivity() {

    private var selectedDate = ""
    private var selectedTime = ""
    private lateinit var task: Task

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_add) // reuse same layout

        val taskId = intent.getStringExtra("task_id") ?: run { finish(); return }
        task = XmlTaskManager.loadAll(this).find { it.id == taskId } ?: run { finish(); return }

        selectedDate = task.date
        selectedTime = task.time

        val tvDate = findViewById<TextView>(R.id.tvSelectedDate)
        val tvTime = findViewById<TextView>(R.id.tvSelectedTime)
        val btnPickDate = findViewById<Button>(R.id.btnPickDate)
        val btnPickTime = findViewById<Button>(R.id.btnPickTime)
        val editTitle = findViewById<EditText>(R.id.editTitle)
        val editDesc = findViewById<EditText>(R.id.editDescription)
        val spinnerPriority = findViewById<Spinner>(R.id.spinnerPriority)
        val btnSave = findViewById<Button>(R.id.btnSave)
        val btnCancel = findViewById<Button>(R.id.btnCancel)

        // Pre-fill fields
        tvDate.text = selectedDate
        tvTime.text = selectedTime
        editTitle.setText(task.title)
        editDesc.setText(task.description)

        val priorities = listOf("Medie", "Înaltă", "Scăzută")
        val priorityAdapter = ArrayAdapter(this, android.R.layout.simple_spinner_dropdown_item, priorities)
        spinnerPriority.adapter = priorityAdapter
        spinnerPriority.setSelection(priorities.indexOf(task.priority).takeIf { it >= 0 } ?: 0)

        btnSave.text = "Actualizează"
        supportActionBar?.title = "Editează sarcina"

        btnPickDate.setOnClickListener {
            val parts = selectedDate.split("-")
            val y = parts[0].toInt(); val m = parts[1].toInt() - 1; val d = parts[2].toInt()
            DatePickerDialog(this, { _, year, month, day ->
                selectedDate = "%04d-%02d-%02d".format(year, month + 1, day)
                tvDate.text = selectedDate
            }, y, m, d).show()
        }

        btnPickTime.setOnClickListener {
            val parts = selectedTime.split(":")
            val h = parts[0].toInt(); val min = parts[1].toInt()
            TimePickerDialog(this, { _, hour, minute ->
                selectedTime = "%02d:%02d".format(hour, minute)
                tvTime.text = selectedTime
            }, h, min, true).show()
        }

        btnSave.setOnClickListener {
            val title = editTitle.text.toString().trim()
            val desc = editDesc.text.toString().trim()
            if (title.isEmpty()) {
                Toast.makeText(this, "Titlul este obligatoriu", Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }
            val updated = task.copy(
                title = title,
                description = desc,
                date = selectedDate,
                time = selectedTime,
                priority = spinnerPriority.selectedItem.toString()
            )
            XmlTaskManager.updateTask(this, updated)
            Toast.makeText(this, "Sarcina a fost actualizată", Toast.LENGTH_SHORT).show()
            finish()
        }

        btnCancel.setOnClickListener { finish() }
    }
}
