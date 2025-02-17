#include <iostream>
#include <omp.h>
using namespace std;

// Fungsi rekursif untuk menghitung factorial secara parallel
unsigned long long parallelFactorial(int n) {
    // Basis case: jika n <= 1, return 1
    if (n <= 1) return 1;
    
    unsigned long long result = 0;
    
    // Membuat task parallel hanya jika n cukup besar
    // untuk menghindari overhead yang tidak perlu
    #pragma omp task shared(result) if(n > 10)
    {
        // Menghitung factorial untuk n-1 secara rekursif
        result = n * parallelFactorial(n - 1);
    }
    
    // Menunggu semua task selesai
    #pragma omp taskwait
    
    // Jika result masih 0, artinya task belum selesai
    // maka hitung secara sequential
    if (result == 0) {
        result = n * parallelFactorial(n - 1);
    }
    
    return result;
}

int main() {
    int n = 10; // Input number untuk factorial (dikurangi untuk menghindari overflow)
    unsigned long long result;
    
    // Memulai parallel region dengan 4 thread
    #pragma omp parallel num_threads(4)
    {
        // Hanya thread master yang akan membuat task pertama
        #pragma omp single
        {
            cout << "Menghitung factorial dari " << n << " menggunakan OpenMP\n";
            cout << "Jumlah thread yang digunakan: " << omp_get_num_threads() << "\n";
            
            // Memulai perhitungan factorial
            result = parallelFactorial(n);
        }
    }
    
    // Menampilkan hasil
    cout << "Factorial dari " << n << " adalah: " << result << endl;
    
    return 0;
}