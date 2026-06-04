package com.example.dailyplanner

import android.content.Context
import android.graphics.Color
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ArrayAdapter
import android.widget.TextView

class TaskAdapter(context: Context, private val tasks: MutableList<Task>) :
    ArrayAdapter<Task>(context, 0, tasks) {

    override fun getView(position: Int, convertView: View?, parent: ViewGroup): View {
        val view = convertView ?: LayoutInflater.from(context)
            .inflate(R.layout.list_item_task, parent, false)

        val task = tasks[position]

        view.findViewById<TextView>(R.id.tvTaskTitle).text = task.title
        view.findViewById<TextView>(R.id.tvTaskTime).text = task.time
        view.findViewById<TextView>(R.id.tvTaskDesc).text = task.description
        view.findViewById<TextView>(R.id.tvTaskDate).text = task.date

        val tvPriority = view.findViewById<TextView>(R.id.tvTaskPriority)
        tvPriority.text = task.priority
        tvPriority.setTextColor(when (task.priority) {
            "Înaltă"  -> Color.parseColor("#D32F2F")
            "Medie"   -> Color.parseColor("#F57F17")
            else      -> Color.parseColor("#388E3C")
        })

        return view
    }
}
