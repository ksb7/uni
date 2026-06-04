package com.example.dailyplanner

data class Task(
    val id: String,
    val title: String,
    val description: String,
    val date: String,   // format: yyyy-MM-dd
    val time: String,   // format: HH:mm
    val priority: String // "Înaltă", "Medie", "Scăzută"
)
