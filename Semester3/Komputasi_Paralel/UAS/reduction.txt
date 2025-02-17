#include <iostream>
#include <omp.h>
#include <vector>
using namespace std;

int main() {
    const int SIZE = 1000000;  // Ukuran array
    vector<int> numbers(SIZE);  // Vector untuk menyimpan angka
    
    // Inisialisasi array dengan angka 1-1000000
    #pragma omp parallel for
    for(int i = 0; i < SIZE; i++) {
        numbers[i] = i + 1;
    }
    
    // Variabel untuk menyimpan hasil
    long long sum = 0;
    int max_val = numbers[0];
    int min_val = numbers[0];
    
    double start_time = omp_get_wtime();  // Mulai menghitung waktu
    
    // Menggunakan reduction untuk menghitung sum, max, dan min secara parallel
    #pragma omp parallel for reduction(+:sum) reduction(max:max_val) reduction(min:min_val)
    for(int i = 0; i < SIZE; i++) {
        sum += numbers[i];          // Menjumlahkan semua elemen
        if(numbers[i] > max_val)    // Mencari nilai maksimum
            max_val = numbers[i];
        if(numbers[i] < min_val)    // Mencari nilai minimum
            min_val = numbers[i];
    }
    
    double end_time = omp_get_wtime();  // Selesai menghitung waktu
    
    // Menampilkan hasil dan waktu eksekusi
    cout << "Hasil komputasi parallel menggunakan OpenMP Reduction:\n";
    cout << "Jumlah thread yang digunakan: " << omp_get_max_threads() << endl;
    cout << "Sum  : " << sum << endl;
    cout << "Max  : " << max_val << endl;
    cout << "Min  : " << min_val << endl;
    cout << "Waktu eksekusi: " << (end_time - start_time) * 1000 << " ms" << endl;
    
    // Verifikasi hasil dengan perhitungan sequential
    long long seq_sum = 0;
    int seq_max = numbers[0];
    int seq_min = numbers[0];
    
    start_time = omp_get_wtime();
    
    for(int i = 0; i < SIZE; i++) {
        seq_sum += numbers[i];
        if(numbers[i] > seq_max)
            seq_max = numbers[i];
        if(numbers[i] < seq_min)
            seq_min = numbers[i];
    }
    
    end_time = omp_get_wtime();
    
    cout << "\nHasil komputasi sequential untuk verifikasi:\n";
    cout << "Sum  : " << seq_sum << endl;
    cout << "Max  : " << seq_max << endl;
    cout << "Min  : " << seq_min << endl;
    cout << "Waktu eksekusi: " << (end_time - start_time) * 1000 << " ms" << endl;
    
    return 0;
}