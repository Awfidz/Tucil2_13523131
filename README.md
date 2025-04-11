# Image Compressor with Quadtree
### Ahmad Wafi Idzharulhaqq
dibuat sebagai pemenuhan atas tugas kecil 2 mata kuliah Strategi Algoritma

## Penjelasan Singkat
Program ini adalah implementasi algoritma kompresi gambar menggunakan struktur data **Quadtree** dan pendekatan **Divide and Conquer**. Program membagi gambar menjadi blok-blok berdasarkan tingkat homogenitas warna, dan menyimpan informasi warna rata-rata untuk setiap blok. Dengan pendekatan ini, ukuran gambar dapat dikurangi tanpa kehilangan terlalu banyak detail visual.

## Requirement Program
- **Compiler**: Program ini ditulis dalam C++ dan membutuhkan compiler C++ (C++17 ke atas) terpasang

## Instalasi dan Kompilasi
1. Pastikan compiler C++ sudah terinstal.
2. Download as zip repositori ini
3. Buka terminal, masuk ke directory parent "...\Tucil2_13523131"
4. Jalankan file build.bat 
```bash
.\build.bat
```
5. Jalankan file executable file image_compressor.exe
```bash
.\image_compressor.exe
```
6. Setelah itu akan muncul tampilan program

## Melakukan Kompresi Foto
1. Masukkan absolute path gambar sumber
2. Pilih metode error measurement
3. Masukkan error treshold, dan ukuran minimum blok
4. Masukkan absolute path untuk output file

## Struktur File
```
Tucil2_13523131/
├── README.md                     # Dokumentasi proyek
├── build.bat                     # Script untuk kompilasi program
├── src/                          # Folder berisi kode sumber
│   ├── main.cpp                  # File utama program
│   ├── object/                   # Folder berisi implementasi objek
│   │   ├── ImageQuadtree.cpp     # Implementasi Quadtree
│   │   ├── ImageQuadtree.h       # Header Quadtree
│   │   ├── Node.cpp              # Implementasi Node
│   │   ├── Node.h                # Header Node
│   └── utils/                    # Folder berisi utilitas
│       ├── ImageLoader.cpp       # Implementasi pembaca gambar
│       ├── ImageLoader.h         # Header pembaca gambar
│       ├── ImageMaker.cpp        # Implementasi pembuat gambar
│       ├── ImageMaker.h          # Header pembuat gambar
├── bin/                          # Folder untuk menyimpan file .o
├── test/                         # Folder untuk menyimpan hasil tes
├── doc/                          # Folder berisi laporan
```

