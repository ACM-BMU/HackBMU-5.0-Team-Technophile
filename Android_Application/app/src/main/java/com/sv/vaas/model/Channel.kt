package com.sv.vaas.model

data class Channel(
    val created_at: String,
    val description: String,
    val field1: String,
    val field2: String,
    val id: Int,
    val last_entry_id: Int,
    val latitude: String,
    val longitude: String,
    val name: String,
    val updated_at: String
)