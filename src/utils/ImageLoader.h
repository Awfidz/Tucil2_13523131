#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include "stb_image.h"
#include "RGB.h"
#include <string>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <iostream>

using namespace std;

class ImageLoader {
private:
    string absPath;                     
    int width, height;                  
    vector<vector<RGB>> imageData;

public:
    // Constructor & Destructor
    inline ImageLoader(string absPath);
    inline ~ImageLoader();

    // Load image
    inline void loadImage();

    // Print image information
    inline void printImageInfo() const;

    // Getter for image data
    inline vector<vector<RGB>>& getImageData();

    // Getters for width and height
    inline int getWidth() const;
    inline int getHeight() const;
};

ImageLoader::ImageLoader(string absPath) {
    this->absPath = absPath;
    this->width = 0;
    this->height = 0;
    this->imageData.clear();

    loadImage();
}


ImageLoader::~ImageLoader() {}


void ImageLoader::loadImage() {
    int channels;
    unsigned char* data = stbi_load(this->absPath.c_str(), &this->width, &this->height, &channels, 3); // Force RGB
    if (!data) {
        throw runtime_error("Image Load Failed: " + absPath);
    }

    imageData.resize(this->height, vector<RGB>(this->width));

    for (int y = 0; y < this->height; ++y) {
        for (int x = 0; x < this->width; ++x) {
            int idx = (y * this->width + x) * 3; 
            imageData[y][x] = {data[idx], data[idx + 1], data[idx + 2]};
        }
    }

    stbi_image_free(data);
}

void ImageLoader::printImageInfo() const {
    cout << "Source: " << absPath << endl;
    cout << "Width: " << width << ", Height: " << height << endl;
}

vector<vector<RGB>>& ImageLoader::getImageData(){
    return imageData;
}

int ImageLoader::getWidth() const {
    return width;
}

int ImageLoader::getHeight() const {
    return height;
}

#endif 