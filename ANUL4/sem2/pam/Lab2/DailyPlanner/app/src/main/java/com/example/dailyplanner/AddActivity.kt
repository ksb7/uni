package com.example.dailyplanner

import android.app.DatePickerDialog
import android.app.TimePickerDialog
import android.os.Bundle
import android.widget.*
import androidx.appcompat.app.AppCompatActivity
import java.util.*

class AddActivity : AppCompatActivity() {

    private var selectedDate = ""
    private var selectedTime = ""

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_add)

        selectedDate = intent.getStringExtra("selected_date") ?: todayString()

        val tvDate = findViewById<TextView>(R.id.tvSelectedDate)
        val tvTime = findViewById<TextView>(R.id.tvSelectedTime)
        val btnPickDate = findViewById<Button>(R.id.btnPickDate)
        val btnPickTime = findViewById<Button>(R.id.btnPickTime)
        val editTitle = findViewById<EditText>(R.id.editTitle)
        val editDesc = findViewById<EditText>(R.id.editDescription)
        val spinnerPriority = findViewById<Spinner>(R.id.spinnerPriority)
        val btnSave = findViewById<Button>(R.id.btnSave)
        val btnCancel = findViewById<Button>(R.id.btnCancel)

        tvDate.text = selectedDate
        selectedTime = currentTimeString()
        tvTime.text = selectedTime

        val priorities = listOf("Medie", "Înaltă", "Scăzută")
        spinnerPriority.adapter = ArrayAdapter(this, android.R.layout.simple_spinner_dropdown_item, priorities)

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
            if (selectedTime.isEmpty()) {
                Toast.makeText(this, "Selectează ora sarcinii", Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }
            val task = Task(
                id = "",
                title = title,
                description = desc,
                date = selectedDate,
                time = selectedTime,
                priority = spinnerPriority.selectedItem.toString()
            )
            XmlTaskManager.addTask(this, task)
            Toast.makeText(this, "Sarcina a fost adăugată", Toast.LENGTH_SHORT).show()
            finish()
        }

        btnCancel.setOnClickListener { finish() }
    }

    private fun todayString(): String {
        val c = Calendar.getInstance()
        return "%04d-%02d-%02d".format(c.get(Calendar.YEAR), c.get(Calendar.MONTH) + 1, c.get(Calendar.DAY_OF_MONTH))
    }

    private fun currentTimeString(): String {
        val c = Calendar.getInstance()
        return "%02d:%02d".format(c.get(Calendar.HOUR_OF_DAY), c.get(Calendar.MINUTE))
    }
}
