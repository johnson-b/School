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
    return 0;
}
