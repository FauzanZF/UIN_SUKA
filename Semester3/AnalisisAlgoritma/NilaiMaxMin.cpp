#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, num;
    int minVal, maxVal;

	cout << "Fauzan Zacky F \n";
	cout << "23106050047\n";
    cout << "Masukkan jumlah angka: ";
    cin >> n;

    if (n <= 0) {
        cout << "Jumlah angka harus lebih dari 0!" << endl;
        return 1;
    }

    cout << "Masukkan " << n << " angka:" << endl;

    // Input angka pertama
    cin >> num;
    minVal = maxVal = num;

    // Input angka berikutnya
    for (int i = 1; i < n; i++) {
        cin >> num;

        if (num < minVal) {
            minVal = num;
        }

        if (num > maxVal) {
            maxVal = num;
        }
    }

    cout << "Nilai terkecil: " << minVal << endl;
    cout << "Nilai terbesar: " << maxVal << endl;

    return 0;
}
