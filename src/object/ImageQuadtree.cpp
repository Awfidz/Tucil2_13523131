#include "ImageQuadtree.h"

ImageQuadtree::ImageQuadtree(const double treshold, const double minBlockSize, ImageLoader& imageLoader)
    : treshold(treshold), 
      minBlockSize(minBlockSize), 
      numNodes(1), 
      maxDepth(0)
{
    root = new Node(false, 0, 0, 
                   imageLoader.getWidth(), 
                   imageLoader.getHeight(), 
                   imageLoader.getImageData());
}

ImageQuadtree::~ImageQuadtree() {
    if (root != nullptr) {
        root->deleteChildren();  
        delete root;            
        root = nullptr;
    } 
}

void ImageQuadtree::compressImage(Node* root, string methodChoice, ImageLoader& imageLoader) {
    // 1. hitung error rate
    // 2. hitung ukuran
    // 3. divide? masuk ke rekursif : set semua blok di dalemnya ke avg color
    // 4. combine

    vector<vector<RGB>>& imageData = imageLoader.getImageData();
    int rootWidth = root->getNodeWidth();
    int rootHeight = root->getNodeHeight();
    int x = root->getNodeX();
    int y = root->getNodeY();

    root->calculateErrorRate(methodChoice, imageData);
    double error = root->getErrorRate();

    if (error > treshold && rootWidth > minBlockSize && rootHeight > minBlockSize && (rootWidth/2)*(rootHeight/2) >= minBlockSize) {
        int halfWidth = rootWidth / 2;
        int halfHeight = rootHeight / 2;
        numNodes += 4;

        // Buat empat anak root
        root->setChild(0, new Node(false, x, y, halfWidth, halfHeight, imageData)); // Top-left
        root->setChild(1, new Node(false, x + halfWidth, y, halfWidth, halfHeight, imageData)); // Top-right
        root->setChild(2, new Node(false, x, y + halfHeight, halfWidth, halfHeight, imageData)); // Bottom-left
        root->setChild(3, new Node(false, x + halfWidth, y + halfHeight, halfWidth, halfHeight, imageData)); // Bottom-right

        // Rekursi untuk setiap anak
        compressImage(root->getChild(0), methodChoice, imageLoader);
        compressImage(root->getChild(1), methodChoice, imageLoader);
        compressImage(root->getChild(2), methodChoice, imageLoader);
        compressImage(root->getChild(3), methodChoice, imageLoader);
    } 
    else {
        root->setAsLeaf(true);
        for (int i = y; i < y + rootHeight; ++i) {
            for (int j = x; j < x + rootWidth; ++j) {
                imageData[i][j].r = root -> getAvgColor().r;
                imageData[i][j].g = root -> getAvgColor().g;
                imageData[i][j].b = root -> getAvgColor().b;
            }
        } 
    }
}

void ImageQuadtree::countMaxDepth() {
    maxDepth = countMaxDepthHelper(root, 0);
}

// Helper function rekursif
int ImageQuadtree::countMaxDepthHelper(Node* root, int currentDepth){    
    if (root == nullptr) {
        return currentDepth;
    }

    if (root->isLeafNode()) {
        return currentDepth;
    }
    
    int maxChildDepth = currentDepth;
    for (int i = 0; i < 4; i++) {
        int childDepth = countMaxDepthHelper(root->getChild(i), currentDepth + 1);
        maxChildDepth = max(maxChildDepth, childDepth);
    }
    
    return maxChildDepth;
}

void ImageQuadtree::countNumNodes(Node* node){
    numNodes = countNumNodesHelper(node);
}

int ImageQuadtree::countNumNodesHelper(Node* node) {
    if (node == nullptr) {
        return 0;
    }

    int count = 1; // Hitung node saat ini
    for (int i = 0; i < 4; i++) {
        count += countNumNodesHelper(node->getChild(i)); // Tambahkan jumlah node anak
    }

    return count;
}

Node* ImageQuadtree::getRoot() const {
    return root;
}

int ImageQuadtree::getNumNodes() const {
    return numNodes;
}

int ImageQuadtree::getTreeDepth() const {
    return maxDepth;
}
