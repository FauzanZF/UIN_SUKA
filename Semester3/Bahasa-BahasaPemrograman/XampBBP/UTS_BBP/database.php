<?php

$hostname = "localhost";  // Menyimpan nama host server database (biasanya "localhost").
$username = "root"; // Menyimpan nama pengguna untuk koneksi database (defaultnya "root").
$password = ""; // Menyimpan kata sandi pengguna (kosong dalam kasus ini).
$database_name = "cfar"; // Menyimpan nama database yang akan digunakan ("cfar").


// Membuat koneksi ke database menggunakan hostname, username, password, dan nama database.
$db = mysqli_connect($hostname, $username, $password, $database_name);
if($db->connect_error){
    echo "database rusak"; // Menampilkan pesan "database rusak" jika terjadi kesalahan koneksi.
    die("error"); // Menghentikan eksekusi script jika terjadi error pada koneksi.
}

?>