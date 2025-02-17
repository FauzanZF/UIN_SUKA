<?php
session_start();
include "database.php"; // Tambahkan ini untuk koneksi database

if (isset($_POST["logout"])) {
    session_unset();
    session_destroy();
    header('location: index.php');
}

// Fungsi untuk menambah data ke sesi dan database
function addData($date, $type, $amount, $username) {
    global $db;

    if (!isset($_SESSION['data'])) {
        $_SESSION['data'] = [];
    }
    
    // Tambah data ke sesi
    $_SESSION['data'][] = [
        'date' => $date,
        'type' => $type,
        'amount' => $amount
    ];

    // Simpan data ke database
    $stmt = $db->prepare("INSERT INTO cash_flow (username, date, type, amount) VALUES (?, ?, ?, ?)");
    $stmt->bind_param("sssi", $username, $date, $type, $amount);
    $stmt->execute();
    $stmt->close();
}

// Fungsi untuk mereset data sesi dan database
function resetData($username) {
    global $db;
    
    // Hapus data dari sesi
    unset($_SESSION['data']);

    // Hapus data dari database
    $stmt = $db->prepare("DELETE FROM cash_flow WHERE username = ?");
    $stmt->bind_param("s", $username);
    $stmt->execute();
    $stmt->close();
}

// Cek apakah form disubmit
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    if (isset($_POST['reset'])) {
        resetData($_SESSION['username']);
        header("Location: main.php"); // Tambahkan redirect setelah reset
        exit(); // Reset data jika tombol reset ditekan
    } elseif (isset($_POST['submit'])) { // Cek jika tombol tambah data ditekan
        $date = $_POST['date'];
        $type = $_POST['type'];
        $amount = $_POST['amount'];

        addData($date, $type, $amount, $_SESSION['username']);

        header("Location: main.php"); 
        exit();
    }
}

// Mengambil data untuk diagram dari database dan mengelompokkan berdasarkan tanggal
$dataPoints = [];
$stmt = $db->prepare("SELECT date, type, amount FROM cash_flow WHERE username = ?");
$stmt->bind_param("s", $_SESSION['username']);
$stmt->execute();
$result = $stmt->get_result();

// Mengelompokkan data berdasarkan tanggal
$groupedData = [];
while ($row = $result->fetch_assoc()) {
    $date = $row['date'];
    $amount = ($row['type'] === 'income') ? $row['amount'] : -$row['amount'];

    if (isset($groupedData[$date])) {
        $groupedData[$date] += $amount;
    } else {
        $groupedData[$date] = $amount;
    }
}
$stmt->close();

// Mengonversi data yang telah dikelompokkan untuk digunakan dalam diagram
foreach ($groupedData as $date => $amount) {
    $dataPoints[] = ['date' => $date, 'amount' => $amount];
}


?>


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="style.css">
    <title>Cash Flow Analysis Report</title>
</head>
<body class="body-main">
    <div class="container">
        <?php include "layout/header.html" ?>
        <h3>Good Morning <?php echo $_SESSION['username'] ?></h3>
        <?php include "layout/footer.html" ?>
    </div>
    

    <div class="container-main">
        <h1 style="font-size: 30px;">Cash Flow Analysis Report</h1>
        <form method="post">
            <label for="date">Tanggal (YYYY-MM-DD):</label>
            <input type="date" id="date" name="date" required>

            <label for="type">Pilih:</label>
            <select id="type" name="type" required>
                <option value="income">Penghasilan</option>
                <option value="expense">Pengeluaran</option>
            </select>

            <label for="amount">Nominal:</label>
            <input type="number" id="amount" name="amount" required>

            <button type="submit" name="submit">Tambah Data</button>
        </form>

        <!-- Container baru untuk diagram -->
        <div class="chart-container">
            <canvas id="myChart" width="300" height="150"></canvas> <!-- Ukuran kanvas yang lebih kecil -->
        </div>

        <form action="main.php" method="POST">
            <div class="button-container">
                <button type="submit" name="reset" class="reset-button">Reset Data</button>
                <button type="submit" name="logout" class="reset-button">Logout</button>
            </div>
        </form>
    </div>

    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
<script>
    const ctx = document.getElementById('myChart').getContext('2d');
    const dataPoints = <?php echo json_encode($dataPoints); ?>;
    
    const labels = dataPoints.map(data => new Date(data.date).toLocaleDateString());
    const values = dataPoints.map(data => data.amount);

    const myChart = new Chart(ctx, {
        type: 'line',
        data: {
            labels: labels,
            datasets: [{
                label: 'Saldo Harian (Penghasilan - Pengeluaran)',
                data: values,
                borderColor: 'rgba(65, 105, 225, 1)',
                backgroundColor: 'rgba(0, 0, 0, 0.2)',
                fill: true,
            }]
        },
        options: {
            scales: {
                x: {
                    ticks: {
                        color: 'white', // Ubah warna teks pada sumbu X menjadi putih
                    }
                },
                y: {
                    ticks: {
                        color: 'white', // Ubah warna teks pada sumbu Y menjadi putih
                    },
                    beginAtZero: true
                }
            },
            plugins: {
                legend: {
                    labels: {
                        color: 'white', // Ubah warna teks label legend menjadi putih
                    }
                },
                title: {
                    display: true,
                    text: 'Cash Flow Analysis',
                    color: 'white', // Ubah warna teks judul diagram menjadi putih
                }
            }
        }
    });
</script>

</body>
</html>

