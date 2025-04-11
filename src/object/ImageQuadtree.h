#ifndef IMAGE_QUADTREE_H
#define IMAGE_QUADTREE_H

#include "Node.h"
#include "../utils/ImageLoader.h"
#include <vector>

using namespace std;

class ImageQuadtree {
private:
    const double treshold;
    const double minBlockSize;
    int numNodes;
    int maxDepth;
    Node* root;

public:
    ImageQuadtree(const double treshold, const double minBlockSize, ImageLoader& loader);
    ~ImageQuadtree();
    
    void compressImage(Node* root, string methodChoice, ImageLoader& loader);
    void countMaxDepth();
    int countMaxDepthHelper(Node* node, int depth);
    void countNumNodes(Node* node);
    int countNumNodesHelper(Node* node);
    Node* getRoot() const;
    int getTreeDepth() const;
    int getNumNodes() const;


};

#endif