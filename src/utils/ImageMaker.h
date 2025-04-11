#ifndef IMAGEMAKER_H
#define IMAGEMAKER_H

#include "stb_image_write.h"
#include "RGB.h"
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>  
#include <cctype>     
#include <iostream>

using namespace std;

namespace ImageMaker {
    vector<unsigned char> convertTo1D(const vector<vector<RGB>>& imageData) {
        int height = imageData.size();
        int width = imageData[0].size();
        vector<unsigned char> oneD(width * height * 3);  
        
        size_t idx = 0;
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                const RGB& pixel = imageData[y][x];
                oneD[idx++] = pixel.r;
                oneD[idx++] = pixel.g;
                oneD[idx++] = pixel.b;
            }
        }
        return oneD;
    }

    void makeImage(const string& outputPath, const vector<vector<RGB>>& imageData) {
        int height = imageData.size();
        int width = imageData[0].size();
        vector<unsigned char> oneD = convertTo1D(imageData);
        string ext = filesystem::path(outputPath).extension().string();
        std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

        bool success = false;
        if (ext == ".jpg" || ext == ".jpeg") {
            // Quality diset ke 50 dari percobaan dengan quality 90,50,dan 20. didapati 50 memiliki hasil lebih baik
            success = stbi_write_jpg(outputPath.c_str(), width, height, 3, oneD.data(), 50);
        } else if (ext == ".png") {
            // menggunakan kompresi maksimum untuk kompresi file png
            stbi_write_png_compression_level = 9;  
            success = stbi_write_png(outputPath.c_str(), width, height, 3, oneD.data(), width * 3);
        }

        if (!success) {
            cerr << "Error: Failed to write image to " << outputPath << endl;
        } else {
            cout << "Image successfully written to " << outputPath << endl;
        }
    }
}

#endif 
