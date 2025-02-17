#include <iostream>
using namespace std;

int main() {
    double num1, num2;
    char op;
    double result;
    char choice;

    cout << "23106050047_Fauzan Zacky F \n";
    cout << "\n";

    do {
        cout << "Pilih Operator (+ : penjumlahan, - : pengurangan, * : perkalian, / : pembagian): ";
        cin >> op;

        cout << "Masukkan angka pertama bro: ";
        cin >> num1;
        cout << "Masukkan angka kedua bro: ";
        cin >> num2;

        switch (op) {
            case '+':
                result = num1 + num2;
                cout << "Hasil: " << result << endl;
                break;
            case '-':
                result = num1 - num2;
                cout << "Hasil: " << result << endl;
                break;
            case '*':
                result = num1 * num2;
                cout << "Hasil: " << result << endl;
                break;
            case '/':
                if (num2 != 0) {
                    result = num1 / num2;
                    cout << "Hasil: " << result << endl;
                } else {
                    cout << "Error: Pembagian dengan nol tidak diperbolehkan!" << endl;
                }
                break;
            default:
                cout << "Operator tidak valid!" << endl;
                break;
        }

        cout << "\nApakah ingin menghitung lagi? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    cout << "Terima kasih telah menggunakan program ini!" << endl;

    return 0;
}
