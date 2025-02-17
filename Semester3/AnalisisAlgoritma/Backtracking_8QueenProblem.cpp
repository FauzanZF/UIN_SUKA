#include <bits/stdc++.h>
#include <chrono>  // Menyertakan chrono untuk pengukuran waktu

using namespace std;
using namespace std::chrono;  // Menyederhanakan penggunaan chrono

int countt = 0;  // Variabel global untuk menghitung jumlah solusi

// Fungsi untuk mencetak solusi papan
void print(int board[][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << "-----------------\n";  // Garis pemisah antara solusi
}

// Fungsi untuk memeriksa apakah posisi (row, col) aman untuk ditempati ratu
bool isValid(int board[][8], int row, int col) {
    // Cek baris pada kolom yang lebih kiri
    for (int i = col; i >= 0; i--) {
        if (board[row][i])
            return false;  // Jika ada ratu di kiri, kembalikan false
    }
    int i = row, j = col;

    // Cek diagonal kiri atas
    while (i >= 0 && j >= 0) {
        if (board[i][j])
            return false;  // Jika ada ratu di kiri atas, kembalikan false
        i--;
        j--;
    }
    i = row;
    j = col;

    // Cek diagonal kiri bawah
    while (i < 8 && j >= 0) {
        if (board[i][j])
            return false;  // Jika ada ratu di kiri bawah, kembalikan false
        i++;
        j--;
    }
    return true;  // Posisi aman untuk menempatkan ratu
}

// Fungsi rekursif untuk mencari semua solusi
void ninjaQueens(int board[][8], int currentColumn) {
    if (currentColumn >= 8)
        return;  // Jika sudah mencapai kolom ke-8, kembali

    // Loop untuk mencoba semua baris di kolom saat ini
    for (int i = 0; i < 8; i++) {
        // Cek apakah ratu bisa ditempatkan di baris i, kolom currentColumn
        if (isValid(board, i, currentColumn)) {
            board[i][currentColumn] = 1;  // Tempatkan ratu

            // Jika mencapai kolom terakhir (kolom ke-7), cetak solusi
            if (currentColumn == 7) {
                print(board);
                countt++;  // Tambah jumlah solusi
            }

            // Rekursif untuk kolom berikutnya
            ninjaQueens(board, currentColumn + 1);

            // Backtracking: hapus ratu dan coba solusi lain
            board[i][currentColumn] = 0;
        }
    }
}

int main() {
    // Inisialisasi papan kosong (semua nilai 0)
    int board[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0}};

    // Mengukur waktu eksekusi menggunakan chrono
    auto start = high_resolution_clock::now();  // Memulai penghitungan waktu

    ninjaQueens(board, 0);  // Memulai pencarian solusi dari kolom pertama

    auto end = high_resolution_clock::now();  // Mengakhiri penghitungan waktu
    auto duration = duration_cast<milliseconds>(end - start);  // Menghitung durasi dalam milidetik

    // Mencetak total solusi yang ditemukan dan waktu eksekusi
    cout << "Total solutions: " << countt << endl;
    cout << "Execution time: " << duration.count() << " ms" << endl;

    return 0;
}
