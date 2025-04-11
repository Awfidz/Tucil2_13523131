/*File: Node.cpp*/
/*Nama: Ahmad Wafi Idzharulhaqq*/

#include "Node.h"
#include <iostream>

using namespace std;

Node::Node(bool isLeaf, int x, int y, int width, int height, vector<vector<RGB>>& imageData){
    this -> isLeaf = isLeaf;
    this -> x = x;
    this -> y = y;
    this -> width = width;
    this -> height = height;
    this -> errorRate = 0.0;
    calculateAverageColor(imageData);
    for (int i = 0; i < 4; i++){
        children[i] = nullptr;
    }

}
Node::~Node(){
    for (int i = 0; i < 4; i++){
        delete children[i];
    }
}
void Node::calculateAverageColor(vector<vector<RGB>>& imageData){
    long long sumR = 0, sumG = 0, sumB = 0;
    int numPixels = this->width * this->height;
    for (int i = this->y; i < this->y + this->height; ++i) {
        for (int j = this->x; j < this->x + this->width; ++j) {
            sumR += imageData[i][j].r;
            sumG += imageData[i][j].g;
            sumB += imageData[i][j].b;
        }
    }
    
    this->avgColor.r = (uint8_t)round((double)sumR / numPixels);
    this->avgColor.g = (uint8_t)round((double)sumG / numPixels);
    this->avgColor.b = (uint8_t)round((double)sumB / numPixels);
}

void Node::calculateErrorRate(std::string methodChoice, vector<vector<RGB>>& imageData){
    if (methodChoice == "1") {
        errorRate = variance(imageData);
    } else if (methodChoice == "2") {
        errorRate = meanAbsoluteDeviation(imageData);
    } else if (methodChoice == "3") {
        errorRate = maxPixelDifference(imageData);
    } else if (methodChoice == "4") {
        errorRate = entropy(imageData);
    }
}

double Node::variance(vector<vector<RGB>>& imageData){
    double varianceR = 0, varianceG = 0, varianceB = 0;
    int numPixels = width * height;

    for (int i = y; i < y + height; ++i) {
        for (int j = x; j < x + width; ++j) {
            const RGB& pixel = imageData[i][j];
            varianceR += (pixel.r - avgColor.r) * (pixel.r - avgColor.r);
            varianceG += (pixel.g - avgColor.g) * (pixel.g - avgColor.g);
            varianceB += (pixel.b - avgColor.b) * (pixel.b - avgColor.b);
        }
    }

    varianceR /= numPixels;
    varianceG /= numPixels;
    varianceB /= numPixels;

    // Variansi total
    return (varianceR + varianceG + varianceB) / 3.0;
}

double Node::meanAbsoluteDeviation(vector<vector<RGB>>& imageData){
    double madR = 0, madG = 0, madB = 0;
    int numPixels = width * height;

    for (int i = y; i < y + height; ++i) {
        for (int j = x; j < x + width; ++j) {
            const RGB& pixel = imageData[i][j];
            madR += abs((int)pixel.r - (int)avgColor.r);
            madG += abs((int)pixel.g - (int)avgColor.g);
            madB += abs((int)pixel.b - (int)avgColor.b);
        }
    }
    madR /= numPixels;
    madG /= numPixels;
    madB /= numPixels;

    return (madR + madG + madB) / 3.0;
}

double Node::maxPixelDifference(vector<vector<RGB>>& imageData){
    int maxDiffR = 0, maxDiffG = 0, maxDiffB = 0;
    int maxR = 0, maxG = 0, maxB = 0, minR = 255, minG = 255, minB = 255;
    for (int i = y; i < y + height; ++i) {
        for (int j = x; j < x + width; ++j) {
            const RGB& pixel = imageData[i][j];
            maxR = max(maxR, (int)pixel.r);
            maxG = max(maxG, (int)pixel.g);
            maxB = max(maxB, (int)pixel.b);

            minR = min(minR, (int)pixel.r);
            minG = min(minG, (int)pixel.g);
            minB = min(minB, (int)pixel.b);
        }
    }
    maxDiffR = maxR - minR;
    maxDiffG = maxG - minG;
    maxDiffB = maxB - minB;

    return (maxDiffR + maxDiffG + maxDiffB) / 3.0;
}
double Node::entropy(vector<vector<RGB>>& imageData){
    // membuat array frekuensi tiap channel
    int freqR[256] = {0};
    int freqG[256] = {0};
    int freqB[256] = {0};

    int numPixels = width * height;

    // menghitung frekuensi nilai pixel
    for (int i = y; i < y + height; ++i) {
        for (int j = x; j < x + width; ++j) {
            const RGB& pixel = imageData[i][j];
            freqR[pixel.r]++;
            freqG[pixel.g]++;
            freqB[pixel.b]++;
        }
    }

    // menghitung entropi 
    auto calculateEntropy = [&](int freq[256]) -> double {
        double entropy = 0.0;
        for (int i = 0; i < 256; ++i) {
            if (freq[i] > 0) {
                double probability = (double)freq[i] / numPixels;
                entropy -= probability * log2(probability);
            }
        }
        return entropy;
    };

    double entropyR = calculateEntropy(freqR);
    double entropyG = calculateEntropy(freqG);
    double entropyB = calculateEntropy(freqB);

    return (entropyR + entropyG + entropyB) / 3.0;
}

RGB Node::getAvgColor() const{
    return avgColor;
}
int Node::getNodeWidth() const{
    return width;
}
int Node::getNodeHeight() const{
    return height;
}
int Node::getNodeX() const{
    return x;
}
int Node::getNodeY() const{
    return y;
}
Node* Node::getChild(int index){
    return children[index];
}
double Node::getErrorRate() const{
    return errorRate;
}
void Node::setChild(int index, Node* child){
    children[index] = child;
}
bool Node::isLeafNode() const{
    return isLeaf;
}

void Node::setAsLeaf(bool value) {
    this->isLeaf = value;
    for (int i = 0; i < 4; i++) {
        delete children[i];
        children[i] = nullptr;
    }
    
}

void Node::deleteChildren() {
    for (int i = 0; i < 4; i++) {
        if (children[i] != nullptr) {
            children[i]->deleteChildren();  
            delete children[i];
            children[i] = nullptr;
        }
    }
}

