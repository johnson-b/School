//
//  main.cpp
//  MedianFilter_SortTiming
//
//  Created by Bryan Johnson on 11/18/14.
//  Copyright (c) 2014 Bryan Johnson. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>
#include "sortlib.h"
#include "filter_helper.h"

int main(int argc, const char * argv[]) {
    std::string input = "bears.pgm";
    std::string output = "bears3.pgm";
    std::string ignore; // for first two lines of .pgm file, not being used
    int width, height, pixel, max;
    std::fstream img;
    std::fstream new_img;
    
    img.open(input.c_str(), std::fstream::in);
    
    // ignore first two lines of pgm image
    getline(img, ignore);
    getline(img, ignore);
    
    img >> width; img >> height; img >> max;
    
    // vector to hold all pixels
    std::vector<int> pixel_vec;
    // push each pixel to vector
    for (int i = 0; i < width*height; ++i) {
        img >> pixel;
        pixel_vec.push_back(pixel);
    }
    img.close();
    
    std::cout << "// ** QUICK_SORT ** //" << std::endl;
    std::cout << "|QuickSort| 9 | " << (int)quicksort(pixel_vec, 9, width, height, max) << " ms|" << std::endl;
    std::cout << "|QuickSort| 13 | " << (int)quicksort(pixel_vec, 13, width, height, max) << " ms|" << std::endl;
    std::cout << "|QuickSort| 19 | " << (int)quicksort(pixel_vec, 19, width, height, max) << " ms|" << std::endl;
    
    /* THE TIMES ON MERGESORT ARE ABSURD, SOMETHING IS CLEARLY WRONG WITH MY MERGESORT, ENTER AT YOUR OWN RISK */
//    std::cout << "// ** MERGE_SORT ** //" << std::endl;
//    std::cout << "|MergeSort| 9 | " << (int)mergesort(pixel_vec, 9, width, height, max) << " ms|" << std::endl;
//    std::cout << "|MergeSort| 13 | " << (int)mergesort(pixel_vec, 13, width, height, max) << " ms|" << std::endl;
//    std::cout << "|MergeSort| 19 | " << (int)mergesort(pixel_vec, 19, width, height, max) << " ms|" << std::endl;
    
    std::cout << "// ** HEAP_SORT ** //" << std::endl;
    std::cout << "|HeapSort| 9 | " << (int)heapsort(pixel_vec, 9, width, height, max) << " ms|" << std::endl;
    std::cout << "|HeapSort| 13 | " << (int)heapsort(pixel_vec, 13, width, height, max) << " ms|" << std::endl;
    std::cout << "|HeapSort| 19 | " << (int)heapsort(pixel_vec, 19, width, height, max) << " ms|" << std::endl;
    
    std::cout << "// ** BST ** //" << std::endl;
    std::cout << "|BST| 9 | " << (int)bst(pixel_vec, 9, width, height, max) << " ms|" << std::endl;
    std::cout << "|BST| 13 | " << (int)bst(pixel_vec, 13, width, height, max) << " ms|" << std::endl;
    std::cout << "|BST| 19 | " << (int)bst(pixel_vec, 19, width, height, max) << " ms|" << std::endl;
    
    return 0;
}