#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

// Fungsi untuk menghitung penjumlahan array secara serial
long serial_sum(int* arr, int size) {
    long sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

// Fungsi untuk menghitung penjumlahan array secara paralel menggunakan OpenMP
long parallel_sum(int* arr, int size) {
    long sum = 0;
    
    // Menggunakan OpenMP parallel for dengan reduction untuk menjumlahkan elemen array
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }

    return sum;
}

int main() {
    int n = 100000000; // Ukuran array yang besar untuk melihat perbedaan performa
    int *arr = (int*) malloc(n * sizeof(int));

    // Mengisi array dengan nilai acak
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }

    // --- Serial Sum ---
    double start_serial = omp_get_wtime(); // Catat waktu mulai
    long sum_serial = serial_sum(arr, n);  // Hitung jumlah array secara serial
    double end_serial = omp_get_wtime();   // Catat waktu selesai
    double serial_time = end_serial - start_serial; // Hitung waktu eksekusi serial
    printf("Sum Serial: %ld, Time Serial: %f seconds\n", sum_serial, serial_time);

    // --- Parallel Sum ---
    double start_parallel = omp_get_wtime(); // Catat waktu mulai
    long sum_parallel = parallel_sum(arr, n); // Hitung jumlah array secara paralel
    double end_parallel = omp_get_wtime(); // Catat waktu selesai
    double parallel_time = end_parallel - start_parallel; // Hitung waktu eksekusi paralel
    printf("Sum Parallel: %ld, Time Parallel: %f seconds\n", sum_parallel, parallel_time);

    // Membandingkan hasil eksekusi
    if (parallel_time < serial_time) {
        printf("Parallel execution is faster by %f seconds.\n", serial_time - parallel_time);
    } else {
        printf("Serial execution is faster by %f seconds.\n", parallel_time - serial_time);
    }

    // Membersihkan alokasi memori
    free(arr);

    return 0;
    
}
