#ifndef NODE_H
#define NODE_H

#include "../utils/RGB.h"
#include <string>
#include <cmath>
#include <vector>

using namespace std;

class Node {
    private:
        bool isLeaf; // true jika node adalah leaf
        int x, y, width, height; // koordinat dan ukuran node
        double errorRate; // error rate node
        RGB avgColor; // nilai rata-rata warna node (RGB)
        Node* children[4]; // array pointer ke Node children
    
    public:
        // Constructor & Destructor
        Node(bool isLeaf, int x, int y, int width, int height,  vector<vector<RGB>>& imageData);
        ~Node();
    
        // Metode Pengukuran 
        void calculateAverageColor(vector<vector<RGB>>& imageData);
        void calculateErrorRate(std::string methodChoice, vector<vector<RGB>>& imageData);
        double variance(vector<vector<RGB>>& imageData);
        double meanAbsoluteDeviation(vector<vector<RGB>>& imageData);
        double maxPixelDifference(vector<vector<RGB>>& imageData);
        double entropy(vector<vector<RGB>>& imageData);
    
        // Getters
        RGB getAvgColor() const;
        int getNodeX() const;
        int getNodeY() const;
        int getNodeWidth() const;
        int getNodeHeight() const;
        Node* getChild(int index);
        double getErrorRate() const;
        
        // Setters
        void setChild(int index, Node* child);
        void setAsLeaf(bool value);

        bool isLeafNode() const;
        void deleteChildren();
    };

    #endif