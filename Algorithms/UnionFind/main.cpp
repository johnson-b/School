//
//  main.cpp
//  union-find
//
//  Created by Bryan Johnson on 11/10/15.
//  Copyright © 2015 Bryan Johnson. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include "UFBoard.h"

int main(int argc, const char * argv[]) {
    
    if (argc < 2) {
        std::cout << "Invalid arguments" << std::endl;
    } else {
        if(argc > 2) {
            double percolationProbability;
            int runs, boardSize;
            percolationProbability = atof(argv[1]);
            runs = atoi(argv[2]);
            boardSize = atoi(argv[3]);
            int rate = 0;
            for(int i = 0; i < runs; i++) {
                UFBoard board(boardSize, percolationProbability);
                if(board.canPercolate(boardSize)) {
                    rate++;
                }
            }
            double percolateRate = (double)rate / runs;
            std::cout << "Percolation rate: " << percolateRate * 100.0 << std::endl;
        } else {
            // text file
            UFBoard board;
            std::string fileName = argv[1];
            board.canPercolate(fileName);
            std::cout << board.clusterCount << std::endl;
            // if(board.canPercolate(fileName)) {
            //     std::cout << "Percolates" << std::endl;
            // } else {
            //     std::cout << "Doesn't percolate" << std::endl;
            // }
        }
    }
    return 0;
}
