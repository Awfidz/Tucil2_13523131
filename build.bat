@echo off
echo Building Image Compressor...

if not exist bin mkdir bin
if not exist bin\object mkdir bin\object
if not exist bin\utils mkdir bin\utils

g++ -Wall -std=c++17 -DSTB_IMAGE_IMPLEMENTATION -DSTB_IMAGE_WRITE_IMPLEMENTATION -c src/main.cpp -o bin/main.o
g++ -Wall -std=c++17 -c src/object/Node.cpp -o bin/object/Node.o
g++ -Wall -std=c++17 -c src/object/ImageQuadtree.cpp -o bin/object/ImageQuadtree.o

g++ bin/main.o bin/object/Node.o bin/object/ImageQuadtree.o -o image_compressor.exe

echo Build complete!