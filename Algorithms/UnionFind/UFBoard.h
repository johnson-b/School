//
//  UFBoard.h
//  union-find
//
//  Created by Bryan Johnson on 11/12/15.
//  Copyright © 2015 Bryan Johnson. All rights reserved.
//

#ifndef UFBoard_h
#define UFBoard_h

#include <stdio.h>
#include <vector>

class UFBoard {
public:
    double percolateProbability;
    int clusterCount;
    UFBoard(int size, double probability);
    UFBoard();
    int find(int root, int roots[]);
    void Union(int a, int b, int roots[]);
    bool canPercolate(int size);
    bool canPercolate(std::string fileName);
};

#endif /* UFBoard_h */