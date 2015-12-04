//
//  main.cpp
//  seam-carving
//
//  Created by Bryan Johnson on 11/24/15.
//  Copyright © 2015 Bryan Johnson. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include "SeamCarving.h"

int main(int argc, const char * argv[]) {
    
    if(argc != 4) {
        std::cout << "Invalid arguments given" << std::endl;
        return 0;
    }
    
    std::string fileName = argv[1];
    int vSeams = atoi(argv[2]);
    int hSeams = atoi(argv[3]);
    
    // ** ROW x COLUMN **
    sc::SeamCarving seamCarving(fileName, vSeams, hSeams);
    seamCarving.processImage();
    
    
    
//    seamCarving.processImage();
//    int r = 3, c = 4;
//    std::vector<std::vector<int>> matrix;
//    int value = 1;
//    // fill matrix with data
//    for(int row = 0; row < r; row++) {
//        std::vector<int> temp;
//        for(int col = 0; col < c; col++) {
//            std::cout << value << " ";
//            temp.push_back(value++);
//        }
//        matrix.push_back(temp);
//        std::cout << std::endl;
//    }
//    
//    std::cout << std::endl;
//    // initialize matrixRotated with correct rows and columns filled with zeroes
//    std::vector<std::vector<int>> matrixRotated;
//    std::vector<int> test;
//    test.resize(r);
//    matrixRotated.resize(c, test);
//    
//    // rotate matrix 270 degrees and store values in matrixRotated
//    for(int row = 0; row < r; row++) {
//        for(int col = 0; col < c; col++) {
//            matrixRotated[c - col - 1].erase(matrixRotated[c - col - 1].begin() + row);
//            matrixRotated[c - col - 1].insert(matrixRotated[c - col - 1].begin() + row, matrix[row][col]);
//        }
//    }
//    
//    // should show rotated matrix 270 degrees
//    for(int row = 0; row < c; row++) {
//        for(int col = 0; col < r; col++) {
//            std::cout << matrixRotated[row][col] << " ";
//        }
//        std::cout << std::endl;
//    }
//    
//    std::cout << std::endl;
//    // resize matrix and clear with zeroes
//    matrix.clear();
//    test.resize(c);
//    matrix.resize(r, test);
//    
//    // rotate matrixRotated back to normal and store back in matrix
//    for(int row = 0; row < r; row++) {
//        for(int col = 0; col < c; col++) {
//            matrix[row].erase(matrix[row].begin() + (c - col - 1));
//            matrix[row].insert(matrix[row].begin() + (c - col - 1), matrixRotated[col][row]);
//        }
//    }
//
//    // should display original matrix
//    for(int row = 0; row < r; row++) {
//        for(int col = 0; col < c; col++) {
//            std::cout << matrix[row][col] << " ";
//        }
//        std::cout << std::endl;
//    }
//    return matrix[column][matrix.size() - row - 1];
//    matrix[matrix.size() - column - 1][row];
    
//    std::cout << "BREAK" << std::endl;
    

    /** ROTATES 2D ARRAY 270 DEGREES **/
//    int matrix[3][4];
//    int mirror[4][3];
//    int value = 0;
//    for (int i = 0; i < 3; i++) {
//        for (int j = 0; j < 4; j++) {
//            matrix[i][j] = ++value;
//            std::cout << value << " ";
//        }
//        std::cout << std::endl;
//    }
//    
//    std::cout << std::endl;
//    
//    for (int i = 0; i < 3; i++) {
//        for (int j = 0; j < 4; j++) {
//            mirror[4 - j - 1][i] = matrix[i][j];
//        }
//    }
//    
//    for (int i = 0; i < 4; i++) {
//        for (int j = 0; j < 3; j++) {
//            std::cout << mirror[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }
    
    return 0;
}
