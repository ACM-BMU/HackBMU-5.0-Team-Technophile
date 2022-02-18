package com.sv.vaas

import android.content.Context
import android.content.Intent
import android.location.Geocoder
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.sv.vaas.model.Feed
import java.io.IOException
import java.util.*

class IncidentAdapter(val incidents:List<Feed>,val context: Context):
RecyclerView.Adapter<IncidentAdapter.viewHolder>(){
    inner class viewHolder(itemView: View):RecyclerView.ViewHolder(itemView){
        val time:TextView=itemView.findViewById(R.id.inci_time)
        val gforce:TextView=itemView.findViewById(R.id.gforce)
        val addressText:TextView=itemView.findViewById(R.id.address)
    }
    var result:String = ""
    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): viewHolder {
        return viewHolder(
            LayoutInflater.from(parent.context).inflate(
                R.layout.list_layout,
                parent,
                false
            )
        )
    }

    override fun onBindViewHolder(holder: viewHolder, position: Int) {

        val incident = incidents[position]
        getAddressFromLocation(
            incident.field1.toDouble(), incident.field2.toDouble(),context
        )
        Log.i("vaas", "onBindViewHolder: in binding")
        val incTime = incident.field4
        val incGf = incident.field3
        holder.time.text=incTime
        holder.gforce.text=incGf
        holder.addressText.text=result
        holder.itemView.setOnClickListener {
            val intent = Intent(it.context,MapsActivity::class.java)
                .putExtra("Lat",incident.field1)
                .putExtra("Long",incident.field2)
            it.context.startActivity(intent)
        }
    }

    override fun getItemCount(): Int {
        return incidents.size
    }

    fun getAddressFromLocation(
        latitude: Double,
        longitude: Double, context: Context
    ) {
                val geoCoder = Geocoder(
                    context,
                    Locale.getDefault()
                )
               // result= null.toString()
                try {
                    val addressList = geoCoder.getFromLocation(
                        latitude, longitude, 1
                    )
                    if ((addressList != null && addressList.size > 0)) {
                        val address = addressList.get(0)
                        val sb = StringBuilder()
                        for (i in 0 until address.maxAddressLineIndex) {
                            sb.append(address.getAddressLine(i)).append("\n")
                        }
                        sb.append(address.subLocality).append("\n")
                        sb.append(address.locality).append(", ")
                        sb.append(address.postalCode)
                        result = sb.toString()
                    }
                } catch (e: IOException) {
                    Log.e("nahh", "Unable connect to GeoCoder", e)
                }
    }

}