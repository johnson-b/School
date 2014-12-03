//
//  main.cpp
//  C++MedianFilter
//
//  Created by Bryan Johnson on 9/30/14.
//  Copyright (c) 2014 Bryan Johnson. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "BinarySearchTree.h"

int main(int argc, const char * argv[]) {
    
    std::string importPath;// image to alter
    std::string exportPath;// output to image after being altered
    std::string ignore; // for first two lines of .pgm file not being used
    int filterBox; // length of one side of the filter box
    int width, height, pixel, max;
    std::ifstream originalPGM;
    std::ofstream newPGM;
    
    filterBox = atoi(argv[1]);
    // make sure length of filter box is odd
    if (filterBox % 2 == 0 && filterBox > 0) {
        filterBox++;
    }
    // if input of filter box length is -1
    if(filterBox < 0) {
        return 0;
    }
    
    importPath = argv[2];
    exportPath = argv[3];
    
    originalPGM.open(importPath.c_str());
    newPGM.open(exportPath.c_str());
    
    // ignore first two lines of pgm file
    getline(originalPGM, ignore);
    getline(originalPGM, ignore);
    
    originalPGM >> width; // get the width of the image
    originalPGM >> height; // get the height of the image
    originalPGM >> max; // get max value of pixel
    int index = filterBox/2; // used for left and right bounds of 2D array when added pixels to binary tree
    
    // setting up output .pgm image to correct format
    newPGM << "P2\n";
    newPGM << "# ";
    newPGM << exportPath;
    newPGM << "\n";
    newPGM << width;
    newPGM << " ";
    newPGM << height;
    newPGM << "\n";
    newPGM << max;
    newPGM << "\n";
    
    // 2D array to hold pixels of imported .pgm file
    int originalPGMArray[height][width];
    
    // put all pixels into a 2D array
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            originalPGM >> pixel;
            originalPGMArray[i][j] = pixel;
        }
    }
    originalPGM.close();
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            // create new binary tree for every pixel in original image
            BinarySearchTree *bst = new BinarySearchTree();
            for(int k = -1*index; k < index; ++k) {
                for (int l = -1*index; l < index; ++l) {
                    if(((i + k)>=0 && (i + k)<=height) && ((j+l)>=0 && (j+l)<=width)) {
                        bst->insert(new Node(originalPGMArray[i+k][j+l]));
                    }
                }
            }
            bst->setMedian(bst->root); // find median
            newPGM << bst->median; // add median to new image
            newPGM << " "; // must contain space after each pixel value
            delete bst;
        }
        newPGM << "\n";
    }
    newPGM.close();
    
    return 0;
}
