#include <iostream>   // Untuk input dan output
#include <omp.h>       // Header untuk menggunakan OpenMP

// Fungsi rekursif yang menggunakan prinsip Depth Recursion
void depth_recursion(int depth, int max_depth) {
    // Cetak informasi thread dan depth saat ini
    #pragma omp critical
    {
        std::cout << "Thread " << omp_get_thread_num() 
                  << " executing at depth " << depth << std::endl;
    }

    // Base case: jika kedalaman maksimum tercapai, berhenti
    if (depth >= max_depth) {
        return;
    }

    // Recursive case: bagi tugas secara paralel jika tidak pada kedalaman maksimum
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            depth_recursion(depth + 1, max_depth);  // Rekursi untuk cabang pertama
        }
        #pragma omp section
        {
            depth_recursion(depth + 1, max_depth);  // Rekursi untuk cabang kedua
        }
    }
}

int main() {
    // Variabel untuk kedalaman maksimum rekursi
    int max_depth = 4;

    // Set jumlah thread yang akan digunakan oleh OpenMP
    omp_set_num_threads(4);

    std::cout << "Starting depth recursion with OpenMP...\n";

    // Panggil fungsi rekursif dengan kedalaman awal 0
    #pragma omp parallel
    {
        #pragma omp single
        {
            depth_recursion(0, max_depth);  // Memulai rekursi dari kedalaman 0
        }
    }

    std::cout << "Completed depth recursion." << std::endl;

    return 0;
}
