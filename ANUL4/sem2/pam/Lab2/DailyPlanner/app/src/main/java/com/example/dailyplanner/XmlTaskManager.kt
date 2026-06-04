package com.example.dailyplanner

import android.content.Context
import org.xmlpull.v1.XmlPullParser
import org.xmlpull.v1.XmlPullParserFactory
import org.xmlpull.v1.XmlSerializer
import java.io.File
import java.io.FileInputStream
import java.io.FileOutputStream
import java.util.UUID

object XmlTaskManager {

    private const val FILE_NAME = "tasks.xml"

    private fun getFile(context: Context): File {
        return File(context.filesDir, FILE_NAME)
    }

    fun loadAll(context: Context): MutableList<Task> {
        val file = getFile(context)
        if (!file.exists()) return mutableListOf()

        val tasks = mutableListOf<Task>()
        try {
            val factory = XmlPullParserFactory.newInstance()
            val parser = factory.newPullParser()
            parser.setInput(FileInputStream(file), "UTF-8")

            var id = ""; var title = ""; var description = ""
            var date = ""; var time = ""; var priority = ""
            var currentTag = ""
            var eventType = parser.eventType

            while (eventType != XmlPullParser.END_DOCUMENT) {
                when (eventType) {
                    XmlPullParser.START_TAG -> currentTag = parser.name
                    XmlPullParser.TEXT -> {
                        val text = parser.text ?: ""
                        when (currentTag) {
                            "id"          -> id = text
                            "title"       -> title = text
                            "description" -> description = text
                            "date"        -> date = text
                            "time"        -> time = text
                            "priority"    -> priority = text
                        }
                    }
                    XmlPullParser.END_TAG -> {
                        if (parser.name == "task" && id.isNotEmpty()) {
                            tasks.add(Task(id, title, description, date, time, priority))
                            id = ""; title = ""; description = ""
                            date = ""; time = ""; priority = ""
                        }
                        currentTag = ""
                    }
                }
                eventType = parser.next()
            }
        } catch (e: Exception) {
            e.printStackTrace()
        }
        return tasks
    }

    fun save(context: Context, tasks: List<Task>) {
        try {
            val file = getFile(context)
            val out = FileOutputStream(file)
            val serializer: XmlSerializer = android.util.Xml.newSerializer()
            serializer.setOutput(out, "UTF-8")
            serializer.startDocument("UTF-8", true)
            serializer.startTag("", "tasks")

            for (task in tasks) {
                serializer.startTag("", "task")
                serializer.writeTag("id", task.id)
                serializer.writeTag("title", task.title)
                serializer.writeTag("description", task.description)
                serializer.writeTag("date", task.date)
                serializer.writeTag("time", task.time)
                serializer.writeTag("priority", task.priority)
                serializer.endTag("", "task")
            }

            serializer.endTag("", "tasks")
            serializer.endDocument()
            out.close()
        } catch (e: Exception) {
            e.printStackTrace()
        }
    }

    private fun XmlSerializer.writeTag(tag: String, value: String) {
        startTag("", tag)
        text(value)
        endTag("", tag)
    }

    fun addTask(context: Context, task: Task): Task {
        val tasks = loadAll(context)
        val newTask = task.copy(id = UUID.randomUUID().toString())
        tasks.add(newTask)
        save(context, tasks)
        return newTask
    }

    fun updateTask(context: Context, updated: Task) {
        val tasks = loadAll(context)
        val index = tasks.indexOfFirst { it.id == updated.id }
        if (index >= 0) tasks[index] = updated
        save(context, tasks)
    }

    fun deleteTask(context: Context, id: String) {
        val tasks = loadAll(context)
        tasks.removeAll { it.id == id }
        save(context, tasks)
    }

    fun getByDate(context: Context, date: String): List<Task> {
        return loadAll(context).filter { it.date == date }
    }

    fun search(context: Context, keyword: String): List<Task> {
        val kw = keyword.lowercase()
        return loadAll(context).filter {
            it.title.lowercase().contains(kw) || it.description.lowercase().contains(kw)
        }
    }
}
