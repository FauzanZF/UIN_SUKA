#include <bits/stdc++.h>
using namespace std;

//deklarasi arah
string direction = "DLRU";

// Array untuk perubahan baris sesuai arah (D, L, R, U)
int dr[4] = { 1, 0, 0, -1 };
// Array untuk perubahan kolom sesuai arah (D, L, R, U)
int dc[4] = { 0, -1, 1, 0 };

// Fungsi untuk memeriksa apakah sel (row, col) valid di dalam labirin
bool isValid(int row, int col, int n, vector<vector<int>>& maze)
{
    return row >= 0 && col >= 0 && row < n && col < n
           && maze[row][col] == 0;
}


void findPath(int row, int col, vector<vector<int>>& maze,
              int n, vector<string>& ans,
              string& currentPath)
{
    // Jika mencapai tujuan (pojok kanan bawah)
    if (row == n - 1 && col == n - 1) {
        ans.push_back(currentPath); 
        // Menyimpan jalur yang valid
        return;
    }
	//1=tembok
    maze[row][col] = 1; 


    for (int i = 0; i < 4; i++) {
        // Hitung baris dan kolom berikutnya berdasarkan arah
        int nextrow = row + dr[i];
        int nextcol = col + dc[i];

        // Periksa apakah sel berikutnya valid
        if (isValid(nextrow, nextcol, n, maze)) {
            currentPath += direction[i]; 
            // Tambahkan arah ke jalur saat ini
            findPath(nextrow, nextcol, maze, n, ans,
                     currentPath); 
            // Panggilan rekursif untuk menjelajahi sel berikutnya
            currentPath.pop_back(); 
            // Hapus arah terakhir untuk backtracking
        }
    }

    maze[row][col] = 0; 
}

int main()
{
	cout<< "0 1 1 1 \n";
	cout<< "0 0 1 0 \n";
	cout<< "0 0 1 1 \n";
	cout<< "1 0 0 0 \n";
	cout<< " \n";
    // Menampilkan representasi labirin awal di konsol

    vector<vector<int>> maze = {
        {0,1,1,1},
        {0,0,1,0},
        {0,0,1,1},
		{1,0,0,0}};
    // Inisialisasi labirin sebagai matriks 2D (0 = jalan, 1 = tembok)

    int n = maze.size();
    // Variabel untuk ukuran labirin (n x n)

    vector<string> result;
    // Vektor untuk menyimpan semua jalur valid dari awal ke tujuan

    string currentPath = "";
    // String untuk menyimpan jalur saat ini selama eksplorasi

    // Periksa apakah posisi awal (0, 0) dan tujuan (n-1, n-1) tidak terhalang
    if (maze[0][0] == 0 && maze[n - 1][n - 1] == 0) {
        // Memulai pencarian jalur dari (0, 0)
        findPath(0, 0, maze, n, result, currentPath);
    }

    if (result.size() == 0)
        cout << "tikus: 'jalan buntu woi'";
    // Jika tidak ada jalur valid, tampilkan pesan kegagalan
    else
        for (int i = 0; i < result.size(); i++)
            cout << result[i] << " ";
            // Menampilkan semua jalur valid yang ditemukan

    cout << endl;

    return 0;
    // Program selesai
}
