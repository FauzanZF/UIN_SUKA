<?php 
    include "database.php";
    session_start();

    $register_message = "";

    if(isset($_SESSION['is_login'])){
        header("location: main.php");
    }

    if(isset($_POST["register"])){
        $username = $_POST["username"];
        $password = $_POST["password"];
        $hash_password = hash("sha256",$password);

        try{
            $sql = "INSERT INTO users (username, password) VALUES ('$username', '$hash_password')";

        
            if($db ->query($sql)){
                $register_message = "daftar akun Berhasil";
            }  else{
                $register_message = "daftar akun Gagal hahahah";
            }
        }catch(mysqli_sql_exception){
            $register_message = "Username Sudah Digunakan";
        }
        $db->close();
        
    }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <link rel="stylesheet" href="style.css">
</head>
<body class="body_HLR">
    <div class="container">
        <?php include "layout/header.html" ?>

        <h3>DAFTAR AKUN</h3>
        <i><?= $register_message ?></i>
        <form action="register.php" method="POST">
        <input type="text" placeholder="username" name="username"/>
        <input type="password" placeholder="password" name="password"/>
        <button type="submit" name="register" <?= isset($_SESSION['is_login']) ? 'disabled' : '' ?>>Daftar Sekarang</button>

        </form>

        <?php include "layout/footer.html" ?>
    </div>
</body>
</html>