//
//  UFBoard.cpp
//  union-find
//
//  Created by Bryan Johnson on 11/12/15.
//  Copyright © 2015 Bryan Johnson. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include "UFBoard.h"

UFBoard::UFBoard(int size, double probability) {
    percolateProbability = probability;
    clusterCount = 0;
}
UFBoard::UFBoard() {
    clusterCount = 0;
}

int UFBoard::find(int root, int roots[]) {
    if (roots[root] != root) {
        find(roots[root], roots);
    } else {
        return root;
    }
}

void UFBoard::Union(int a, int b, int roots[]) {
    int rootA = find(a, roots);
    int rootB = find(b, roots);
    if(rootA < rootB) {
        roots[rootB] = rootA;
    } else {
        roots[rootA] = rootB;
    }
}

bool UFBoard::canPercolate(int size) {
    int board[size][size];
    for(int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            double random = (rand() % 100 + 1) / 100.0;
            if(random <= percolateProbability) {
                board[j][i] = 1;
            } else {
                board[j][i] = 0;
            }
           // std::cout << board[j][i] << " ";
        }
       // std::cout << std::endl;
    }

    int roots[size*size];
    for (int i = 0; i < size * size; i++) {
        roots[i] = 0;
    }
    
    for (int j = 0; j < size * size; j++) {
        if(board[j % size][j / size] == 1) {
            roots[j] = j;
            
            int top = j - size;
            if(top >= 0) {
                if(board[top % size][top / size] == 1) {
                    Union(j, top, roots);
                }
                if(j % size != 0) {
                    int left = j - 1;
                    if(board[left % size][left / size] == 1) {
                        Union(j, left, roots);
                    }
                }
            }
        }
    }
    
    bool percolates = false;
    for(int k = 0; k < size; k++) {
        if(board[k][size - 1] == 1) {
            if(find((size - 1) * size + k, roots) < size) {
                percolates = true;
            }
        }
    }
    // if(percolates) {
    //     std::cout << "Percolates\n" << std::endl;
    // } else {
    //     std::cout << "Doesn't percolate\n" << std::endl;
    // }
    return percolates;
}

bool UFBoard::canPercolate(std::string fileName) {
    bool percolates = false;
    if(fileName.find(".txt") == std::string::npos) {
        std::cout << "Invalid file name" << std::endl;
        return percolates;
    } else {
        std::fstream readFile;
        std::string fileAsString, line;
        const char *character;
        int boardSize;
        readFile.open(fileName.c_str());
        if(readFile.is_open()) {
            while(getline(readFile, line, '\n')) {
                boardSize = 0;
                character = line.c_str();
                while(*character != '\0') {
                    if(*character != ' ') {
                        fileAsString += *character;
                        boardSize++;
                    }
                    character++;
                }
            }
        }
        int board[boardSize][boardSize];
        character = fileAsString.c_str();
        for(int i = 0; i < boardSize; i++) {
            for(int j = 0; j < boardSize; j++) {
                board[j][i] = *character - '0';
                character++;
                // std::cout << board[j][i] << " ";
            }
            // std::cout << std::endl;
        }
        int roots[boardSize*boardSize];
        for (int i = 0; i < boardSize * boardSize; i++) {
            roots[i] = -1;
        }
    
        for (int j = 0; j < boardSize * boardSize; j++) {
            if(board[j % boardSize][j / boardSize] == 1) {
                roots[j] = j;

                int top = j - boardSize;
                if(top >= 0) {
                    if(board[top % boardSize][top / boardSize] == 1) {
                        Union(j, top, roots);
                    }
                    if(j % boardSize != 0) {
                        int left = j - 1;
                        if(board[left % boardSize][left / boardSize] == 1) {
                            Union(j, left, roots);
                        }
                    }
                }
            }
        }
    
        for(int i = 0; i < boardSize * boardSize; i++) {
            if(roots[i] == i) {
                clusterCount++;
            }
        }

        for(int k = 0; k < boardSize; k++) {
            if(board[k][boardSize - 1] == 1) {
                if(find((boardSize - 1) * boardSize + k, roots) < boardSize) {
                    percolates = true;
                }
            }
        }
    }
    return percolates;
}
