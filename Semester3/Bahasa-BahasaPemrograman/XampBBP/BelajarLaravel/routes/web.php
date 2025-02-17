<?php

use Illuminate\Support\Facades\Route;
use App\Events\UserRegistered;


Route::get('/', function () {
    return view('welcome');
});

Route::get('/register', function () {
    event(new UserRegistered('john_doe'));
    return " Registered!!!";
});
