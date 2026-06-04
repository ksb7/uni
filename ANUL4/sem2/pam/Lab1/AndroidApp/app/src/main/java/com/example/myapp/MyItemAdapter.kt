package com.example.myapp

import android.content.Context
import android.graphics.Color
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ArrayAdapter
import android.widget.TextView

class MyItemAdapter(context: Context, private val items: List<MyItem>) :
    ArrayAdapter<MyItem>(context, 0, items) {

    // Badge colors cycling through a palette
    private val badgeColors = arrayOf(
        "#3F51B5", "#0097A7", "#388E3C", "#F57F17",
        "#AD1457", "#6A1B9A", "#00695C", "#BF360C"
    )

    override fun getView(position: Int, convertView: View?, parent: ViewGroup): View {
        val view = convertView ?: LayoutInflater.from(context)
            .inflate(R.layout.list_item, parent, false)

        val item = items[position]

        val tvIndex = view.findViewById<TextView>(R.id.tvItemIndex)
        val tvHeadTitle = view.findViewById<TextView>(R.id.tvHeadTitle)
        val tvContent = view.findViewById<TextView>(R.id.tvContentOption)

        tvIndex.text = (position + 1).toString()
        tvHeadTitle.text = item.headTitle
        tvContent.text = item.contentOption

        // Cycle through badge colors
        val colorHex = badgeColors[position % badgeColors.size]
        tvIndex.background.setTint(Color.parseColor(colorHex))

        return view
    }
}
