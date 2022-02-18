package com.sv.vaas.api

import com.sv.vaas.model.locations
import com.sv.vaas.model.locs
import retrofit2.Call
import retrofit2.http.GET
import retrofit2.http.Query

interface vaasApi {
    @GET("feeds.json?api_key=L5WRQLFYER3Y6SP8")
    fun getList(): Call<locs>
}