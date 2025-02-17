<?php 

include "database.php";  // Menyertakan file database.php yang berisi koneksi ke database.
session_start(); // Memulai sesi untuk melacak informasi pengguna.

    $login_message=""; // Variabel untuk menyimpan pesan login (kosong pada awalnya).

    if(isset($_SESSION['is_login'])){
        // Mengecek apakah pengguna sudah login (variabel sesi 'is_login' sudah disetel).
        header("location: main.php"); // Jika sudah login, mengarahkan pengguna ke halaman 'main.php'.
    }

    if(isset($_POST['login'])){
        $username = $_POST['username'];
        $password = $_POST['password'];
        $hash_password = hash('sha256', $password);

        $sql = "SELECT * FROM users WHERE 
        username='$username' AND password= '$hash_password'
        ";

        $result = $db ->query($sql);

        if($result->num_rows > 0){
            $data = $result->fetch_assoc();
            $_SESSION["username"]=$data['username'];
            $_SESSION['is_login']= true;

            header("location: main.php");
 
    }else{
        $login_message= "Data lu gaada Kocak";
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="style.css">
    <title>Document</title>
</head>
<body class="body_HLR">
    <div class="container">
        <?php include "layout/header.html" ?>
        
        <h3>MASUK AKUN</h3>
        <i><?= $login_message ?></i>
        <form action="login.php" method="POST">
            <input type="text" placeholder="username" name="username"/>
            <input type="password" placeholder="password" name="password"/>
            <button type="submit" name="login">Masuk Sekarang</button>
        </form>
        
        <?php include "layout/footer.html" ?>
    </div>
</body>
</html>
