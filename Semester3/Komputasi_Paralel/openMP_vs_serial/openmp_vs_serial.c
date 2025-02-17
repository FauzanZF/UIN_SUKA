#include <stdio.h>      // Header file untuk fungsi input-output standar (seperti printf)
#include <omp.h>        // Header file OpenMP untuk pemrograman paralel
#include <stdlib.h>     // Header file untuk fungsi standar seperti malloc dan rand
#include <time.h>       // Header file untuk fungsi waktu seperti time (untuk seed pada rand)

// Fungsi untuk menghitung penjumlahan array secara serial
long serial_sum(int* arr, int size) {
    long sum = 0;  // Variabel untuk menyimpan hasil penjumlahan
    // Loop untuk menjumlahkan seluruh elemen array secara sekuensial (serial)
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;    // Mengembalikan hasil penjumlahan
}

// Fungsi untuk menghitung penjumlahan array secara paralel menggunakan OpenMP
long parallel_sum(int* arr, int size) {
    long sum = 0;  // Variabel global untuk menyimpan hasil akhir penjumlahan
    
    // Menetapkan 4 thread. Jumlah ini bisa diubah sesuai kebutuhan atau jumlah core prosesor.
    omp_set_num_threads(4);
    
    // Bagian ini akan dijalankan secara paralel
    #pragma omp paralle
    {
        long local_sum = 0;  // Variabel lokal untuk menyimpan hasil penjumlahan tiap thread
        
        // Parallel for: setiap thread akan mengerjakan bagian dari loop ini
        #pragma omp for
        for (int i = 0; i < size; i++) {
            local_sum += arr[i];  // Setiap thread menjumlahkan elemen ke dalam variabel lokal
        }

        // Atomic operation: memastikan operasi penambahan ke variabel global 'sum' aman (tanpa race condition)
        #pragma omp atomic
        sum += local_sum;  // Nilai lokal dari setiap thread digabungkan ke variabel global 'sum'
    }
    
    return sum;  // Mengembalikan hasil penjumlahan paralel
}

int main() {
    int size = 100000000;  // Ukuran array yang besar (100 juta elemen)
    int *arr = (int*) malloc(size * sizeof(int));  // Alokasi memori untuk array 'arr' secara dinamis
    
    // Mengisi array dengan nilai acak menggunakan rand()
    srand(time(NULL));  // Seed untuk generator angka acak berdasarkan waktu sekarang
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;  // Setiap elemen array adalah angka acak antara 0 dan 99
    }

    // Mengukur waktu eksekusi untuk penjumlahan serial
    double start_serial = omp_get_wtime();  // Catat waktu mulai
    long sum_serial = serial_sum(arr, size);  // Panggil fungsi serial_sum untuk menghitung penjumlahan
    double end_serial = omp_get_wtime();  // Catat waktu selesai

    // Mengukur waktu eksekusi untuk penjumlahan paralel
    double start_parallel = omp_get_wtime();  // Catat waktu mulai
    long sum_parallel = parallel_sum(arr, size);  // Panggil fungsi parallel_sum untuk menghitung penjumlahan
    double end_parallel = omp_get_wtime();  // Catat waktu selesai

    // Menampilkan hasil dan waktu eksekusi untuk penjumlahan serial dan paralel
    printf("Sum Serial: %ld, Time Serial: %f seconds\n", sum_serial, end_serial - start_serial);
    printf("Sum Parallel: %ld, Time Parallel: %f seconds\n", sum_parallel, end_parallel - start_parallel);

    // Membersihkan alokasi memori
    free(arr);  // Hapus alokasi memori untuk array 'arr'

    return 0;  // Kembalikan nilai 0, menunjukkan program selesai tanpa error
}
