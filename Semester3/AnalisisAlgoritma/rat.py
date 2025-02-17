
import sys

class MazeSolver:
    # Inisialisasi objek MazeSolver dengan file labirin sebagai input
    def __init__(self, nama_file):
        self.labirin = []  # Menyimpan representasi labirin sebagai array 2D
        self.lebar = 0  # Lebar labirin
        self.panjang = 0  # Panjang labirin
        self.solusi = []  # Menyimpan jalur solusi
        self.dilewati = []  # Menyimpan jalur yang sudah dilewati
        self.start = []  # Titik awal labirin
        self.finish = []  # Titik akhir labirin

        self.baca_maze(nama_file)  # Baca labirin dari file
        self.solve()  # Mulai mencari solusi

    # Fungsi untuk membaca file labirin dan mengubahnya menjadi array 2D
    def baca_maze(self, nama_file):
        f = open(nama_file, 'r')  # Buka file
        for baris in f:
            lst = []
            for kolom in baris:
                if kolom == '#':  # Tanda # mewakili dinding (tidak bisa dilewati)
                    lst.append(0)
                elif kolom == ' ':  # Tanda spasi mewakili jalan (bisa dilewati)
                    lst.append(1)
            self.labirin.append(lst)  # Tambahkan baris ke labirin

        self.panjang = len(self.labirin)  # Hitung panjang labirin
        self.lebar = len(self.labirin[0])  # Hitung lebar labirin
        self.cari_start()  # Cari titik awal
        self.cari_finish()  # Cari titik akhir

    # Fungsi untuk mencari titik awal di sisi kiri atau atas labirin
    def cari_start(self):
        i = 0
        # Cari titik awal di baris pertama
        for x in self.labirin[0]:
            if x == 1:  # Jika ditemukan jalan
                self.start = [0, i]  # Tetapkan titik awal
                break
            i += 1

        # Cari titik awal di kolom pertama (sisi kiri)
        i = 0
        for y in range(0, len(self.labirin)):
            if self.labirin[y][0] == 1:  # Jika ditemukan jalan
                self.start = [i, 0]
                break
            i += 1

    # Fungsi untuk mencari titik akhir di sisi kanan atau bawah labirin
    def cari_finish(self):
        i = 0
        # Cari titik akhir di baris terakhir
        for x in self.labirin[-1]:
            if x == 1:  # Jika ditemukan jalan
                self.finish = [len(self.labirin) - 1, i]
                break
            i += 1

        # Cari titik akhir di kolom terakhir
        i = 0
        for y in range(0, len(self.labirin)):
            if self.labirin[y][len(self.labirin[y]) - 1] == 1:
                self.finish = [y, len(self.labirin[y]) - 1]
                break
            i += 1

    # Fungsi untuk mencari jalur dari titik awal ke titik akhir menggunakan *backtracking*
    def cari_jalan(self, x, y):
        if [y, x] == self.finish:  # Jika sudah mencapai titik akhir
            self.solusi.append([y, x])  # Tambahkan ke solusi
            self.tampil_solusi()  # Tampilkan jalur solusi
        else:
            # Cek ke atas
            if (y - 1 > 0) and (([y - 1, x] not in self.dilewati) and (self.labirin[y - 1][x] > 0)):
                self.solusi.append([y, x])
                self.dilewati.append([y - 1, x])
                self.cari_jalan(x, y - 1)  # Pindah ke atas

            # Cek ke bawah
            elif (y + 1 < self.panjang) and (([y + 1, x] not in self.dilewati) and (self.labirin[y + 1][x] > 0)):
                self.solusi.append([y, x])
                self.dilewati.append([y + 1, x])
                self.cari_jalan(x, y + 1)  # Pindah ke bawah

            # Cek ke kanan
            elif (x + 1 < self.lebar) and (([y, x + 1] not in self.dilewati) and (self.labirin[y][x + 1] > 0)):
                self.solusi.append([y, x])
                self.dilewati.append([y, x + 1])
                self.cari_jalan(x + 1, y)  # Pindah ke kanan

            # Cek ke kiri
            elif (x - 1 > 0) and (([y, x - 1] not in self.dilewati) and (self.labirin[y][x - 1] > 0)):
                self.solusi.append([y, x])
                self.dilewati.append([y, x - 1])
                self.cari_jalan(x - 1, y)  # Pindah ke kiri

            # Jika tidak ada jalan, lakukan *backtracking*
            else:
                if len(self.solusi) > 0:
                    sebelum = self.solusi.pop()  # Kembali ke langkah sebelumnya
                    self.cari_jalan(sebelum[1], sebelum[0])  # Coba jalan lain
                else:
                    print("Solusi Tidak Ditemukan")  # Tidak ada solusi

    # Fungsi untuk memulai proses pencarian solusi dari titik awal
    def solve(self):
        start = self.start
        self.cari_jalan(start[1], start[0])

    # Fungsi untuk menampilkan solusi labirin
    def tampil_solusi(self):
        for br in range(0, self.panjang):
            for kl in range(0, self.lebar):
                if [br, kl] in self.solusi:
                    sys.stdout.write(".")  # Tampilkan "." untuk jalur solusi
                else:
                    if self.labirin[br][kl] == 0:
                        sys.stdout.write("#")  # Tampilkan "#" untuk dinding
                    elif self.labirin[br][kl] == 1:
                        sys.stdout.write(" ")  # Tampilkan " " untuk jalan
            sys.stdout.write("\n")  # Pindah ke baris berikutnya

# Inisialisasi pemecah labirin dengan file input
s = MazeSolver('maze.txt')
