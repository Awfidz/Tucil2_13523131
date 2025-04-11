#ifndef NODE_H
#define NODE_H

#include "../utils/RGB.h"
#include <string>
#include <cmath>
#include <vector>

using namespace std;

class Node {
    private:
        bool isLeaf;
        int x, y, width, height;
        double errorRate;
        RGB avgColor;
        Node* children[4];
    
    public:
        // Constructor & Destructor
        Node(bool isLeaf, int x, int y, int width, int height,  vector<vector<RGB>>& imageData);
        ~Node();
    
        // Calculation methods - all return double for precision
        void calculateAverageColor(vector<vector<RGB>>& imageData);
        void calculateErrorRate(std::string methodChoice, vector<vector<RGB>>& imageData);
        double variance(vector<vector<RGB>>& imageData);
        double meanAbsoluteDeviation(vector<vector<RGB>>& imageData);
        double maxPixelDifference(vector<vector<RGB>>& imageData);
        double entropy(vector<vector<RGB>>& imageData);
    
        // Getters - should be const
        RGB getAvgColor() const;
        int getNodeX() const;
        int getNodeY() const;
        int getNodeWidth() const;
        int getNodeHeight() const;
        Node* getChild(int index);
        double getErrorRate() const;
        bool isLeafNode() const;
    
        // Setters
        void setChild(int index, Node* child);
        void setAsLeaf(bool value);

        void deleteChildren();
    };

    #endif