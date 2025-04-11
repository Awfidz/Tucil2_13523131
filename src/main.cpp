#include "object/Node.h"
#include "object/ImageQuadtree.h"
#include "utils/ImageLoader.h"
#include "utils/ImageMaker.h"
#include <string>
#include <iostream>
#include <chrono>
#include <filesystem> 

using namespace std;
using namespace ImageMaker;

int main() {
    cout << "====Selamat Datang di Image Compressor!!====" << endl;
    cout << "[-] Ketik \"Mulai\" untuk memulai kompresi gambar" << endl;
    cout << "-> ";

    string inputCommand;
    cin >> inputCommand;
    while (inputCommand != "Mulai") {
        cout << "[-] Ketik \"Mulai\" untuk memulai kompresi gambar" << endl;
        cout << "[-] Ketik \"Batal\" untuk keluar dari program" << endl;
        cout << "--> ";
        cin >> inputCommand;
        if (inputCommand == "Batal") {
            cout << "====Terima kasih sudah menggunakan Image Compressor!====" << endl;
            return 0;
        }
    }

    // Input alamat absolut gambar
    cout << "[-] Masukkan path gambar yang ingin dikompresi: " << endl;
    cout << "--> ";
    string imagePath;
    cin >> imagePath;

    if (!filesystem::exists(imagePath)) {
        cout << "Gambar tidak ditemukan. Silakan periksa path dan coba lagi." << endl;
        return 1;
    }

    // Input metode error measurement yang mau digunakan
    cout << "Metode apa yang akan digunakan untuk error measurement kompresi?" << endl;
    cout << "1. Variance" << endl;
    cout << "2. Mean Absolute Deviation" << endl;
    cout << "3. Maximum Pixel Difference" << endl;
    cout << "4. Entropy" << endl;
    cout << "Masukkan pilihan (1-5): ";
    cin >> inputCommand;
    while (inputCommand < "1" || inputCommand > "5") {
        cout << "[-] Pilihan tidak valid. Silakan pilih antara 1-5." << endl;
        cout << "[-] Ketik \"Batal\" untuk keluar dari program" << endl;
        cout << "--> ";
        cin >> inputCommand;
        if (inputCommand == "Batal") {
            cout << "====Terima kasih sudah menggunakan Image Compressor!====" << endl;
            return 0;
        }
    }
    
    // Input threshold
    bool validThreshold = false;
    double threshold;
    while (!validThreshold) {
        cout << "Masukkan threshold untuk kompresi: " << endl;
        cin >> threshold;

        if (inputCommand == "1" && (threshold >= 0.0 && threshold <= 1.0)) {
            validThreshold = true;
        } else if (inputCommand == "2" && (threshold >= 0.0 && threshold <= 255.0)) { 
            validThreshold = true;
        } else if (inputCommand == "3" && (threshold >= 0.0 && threshold <= 255.0)) { 
            validThreshold = true;
        } else if (inputCommand == "4" && (threshold >= 0.0 && threshold <= 8.0)) { 
            validThreshold = true;
        } else {
            cout << "Threshold tidak valid untuk metode yang dipilih. Silakan masukkan nilai yang sesuai." << endl;
        }
    }

    // Input ukuran blok minimum
    cout << "Masukkan ukuran minimum blok (pixel): " << endl;
    double minBlockSize;
    cin >> minBlockSize;

    // Input path gambar final
    cout << "Masukkan path untuk menyimpan gambar terkompresi: " << endl;
    string outputPath;
    cin >> outputPath;

    // Menampilkan ukuran awal gambar
    cout << "Memuat gambar..." << endl;
    ImageLoader imageLoader(imagePath);
    imageLoader.loadImage();
    cout << "Gambar berhasil dimuat!" << endl;
    auto originalSize = filesystem::file_size(imagePath);
    cout << "Ukuran gambar sebelum kompresi: " << originalSize << " bytes" << endl;

    // Kompresi gambar
    cout << "Memulai kompresi..." << endl;
    auto start = chrono::high_resolution_clock::now(); 
    ImageQuadtree quadtree(threshold, minBlockSize, imageLoader);
    quadtree.compressImage(quadtree.getRoot(), inputCommand, imageLoader);

    auto end = chrono::high_resolution_clock::now(); 
    chrono::duration<double> elapsed = end - start;

    // Waktu proses
    cout << "Kompresi selesai dalam " << elapsed.count() * 1000 << " ms." << endl;

    // Membuat output file dan menampilkan ukuran gambar setelah kompresi
    ImageMaker::makeImage(outputPath, imageLoader.getImageData());
    auto compressedSize = filesystem::file_size(outputPath);
    cout << "Ukuran gambar setelah kompresi: " << compressedSize << " bytes" << endl;

    // Menampilkan Persentase kompresi
    double compressionPercent = 100.0 * (1.0 - (double)compressedSize / originalSize);
    cout << "Persentase kompresi: " << compressionPercent << "%" << endl;

    // Menampilkan Kedalaman pohon
    quadtree.countMaxDepth();
    cout << "Kedalaman pohon: " << quadtree.getTreeDepth() << endl;

    // Menampilkan Banyak simpul pada pohon
    quadtree.countNumNodes(quadtree.getRoot());
    cout << "Banyak simpul pada pohon: " << quadtree.getNumNodes() << endl;

    quadtree.~ImageQuadtree();
    cout << "====Terima kasih sudah menggunakan Image Compressor!====" << endl;
    return 0;
}