#include <bits/stdc++.h>
#include <chrono>  // Menyertakan chrono untuk pengukuran waktu

using namespace std;
using namespace std::chrono;  // Menyederhanakan penggunaan chrono

int countt = 0;  // Variabel global untuk menghitung total solusi

// Fungsi untuk mencetak solusi
void print(int board[][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << "-----------------\n";  // Memisahkan solusi dengan garis
}

// Fungsi untuk memeriksa apakah suatu posisi valid untuk penempatan ratu
bool isValid(int board[][8], int row, int col) {
    // Cek posisi horizontal pada baris yang sama
    for (int i = col; i >= 0; i--) {
        if (board[row][i])
            return false;  // Jika ada ratu di kiri, posisi ini tidak valid
    }
    int i = row, j = col;

    // Cek diagonal kiri atas
    while (i >= 0 && j >= 0) {
        if (board[i][j])
            return false;  // Jika ada ratu di diagonal ini, posisi tidak valid
        i--;
        j--;
    }
    i = row;
    j = col;

    // Cek diagonal kiri bawah
    while (i < 8 && j >= 0) {
        if (board[i][j])
            return false;  // Jika ada ratu di diagonal ini, posisi tidak valid
        i++;
        j--;
    }
    return true;  // Posisi ini aman untuk menempatkan ratu
}

// Fungsi untuk mencari semua solusi
void ninjaQueens(int board[][8], int currentColumn) {
    if (currentColumn >= 8)
        return;  // Jika semua kolom telah terisi, kembalikan
    
    // Perulangan untuk menempatkan ratu pada setiap baris dalam kolom saat ini
    for (int i = 0; i < 8; i++) {
        // Periksa apakah ratu dapat ditempatkan pada baris i dan kolom saat ini
        if (isValid(board, i, currentColumn)) {
            board[i][currentColumn] = 1;  // Tempatkan ratu

            // Jika mencapai kolom terakhir, cetak solusi dan hitung
            if (currentColumn == 7) {
                print(board);
                countt++;
            }

            // Rekursif untuk memeriksa kolom berikutnya
            ninjaQueens(board, currentColumn + 1);

            // Backtracking: hapus ratu untuk mencoba kemungkinan lain
            board[i][currentColumn] = 0;
        }
    }
}

int main() {
    // Inisialisasi papan kosong (0 menunjukkan tidak ada ratu)
    int board[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0}};

    // Mengukur waktu eksekusi menggunakan chrono
    auto start = high_resolution_clock::now();  // Memulai timer

    // Memanggil fungsi untuk mencari solusi mulai dari kolom 0
    ninjaQueens(board, 0);

    // Mengakhiri timer dan menghitung durasi
    auto end = high_resolution_clock::now();    
    auto duration = duration_cast<milliseconds>(end - start);  // Durasi dalam milidetik

    // Menampilkan total solusi dan waktu eksekusi
    cout << "Total solutions: " << countt << endl;
    cout << "Execution time: " << duration.count() << " ms" << endl;

    return 0;
}
