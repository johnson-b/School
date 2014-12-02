//
//  filter_helper.h
//  MedianFilter_SortTiming
//
//  Created by Bryan Johnson on 11/24/14.
//  Copyright (c) 2014 Bryan Johnson. All rights reserved.
//

#ifndef MedianFilter_SortTiming_filter_helper_h
#define MedianFilter_SortTiming_filter_helper_h

#include <ctime>
// ** QUICKSORT ** //
double quicksort(std::vector<int> pixel_vec, int filter, int width, int height, int max) {
    std::fstream new_img;
    std::string output = "quicksort" + std::to_string(filter) + ".pgm";
    std::clock_t start = std::clock(), end = std::clock();
    
    new_img.open(output.c_str(), std::fstream::out);
    new_img << "P2\n";
    new_img << "# ";
    new_img << output;
    new_img << "\n";
    new_img << width;
    new_img << " ";
    new_img << height;
    new_img << "\n";
    new_img << max;
    new_img << "\n";
    
    std::vector<int> window;
    std::vector<int> sorted_window;
    start = std::clock();
    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < width - 1; ++j) {
            std::vector<int> window;
            for (int k = i - 1; k < i + filter; ++k){
                for (int l = j - 1; l < j + filter; ++l){
                    if((k*width+l) > 0 && (k*width+l) < (height*width))
                        window.push_back(pixel_vec[k * width + l]);
                }
            }
            sorted_window = SortLib::quickSort(window);
            end += clock();
            new_img << SortLib::findMedian(sorted_window);
            new_img << " ";
            new_img << "\n";
            window.clear();
            sorted_window.clear();
        }
    }
    new_img.close();
    return (end - start) / (double)CLOCKS_PER_SEC/1000;    
}

// ** HEAPSORT ** //
double heapsort(std::vector<int> pixel_vec, int filter, int width, int height, int max) {
    std::fstream new_img;
    std::string output = "heapsort" + std::to_string(filter) + ".pgm";
    std::clock_t start = std::clock(), end = std::clock();
    
    new_img.open(output.c_str(), std::fstream::out);
    new_img << "P2\n";
    new_img << "# ";
    new_img << output;
    new_img << "\n";
    new_img << width;
    new_img << " ";
    new_img << height;
    new_img << "\n";
    new_img << max;
    new_img << "\n";
    
    std::vector<int> window;
    std::vector<int> sorted_window;
    // ** Quick Sort ** //
    start = std::clock();
    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < width - 1; ++j) {
            std::vector<int> window;
            for (int k = i - 1; k < i + filter; ++k){
                for (int l = j - 1; l < j + filter; ++l){
                    if((k*width+l) > 0 && (k*width+l) < (height*width))
                        window.push_back(pixel_vec[k * width + l]);
                }
            }
            sorted_window = SortLib::heapsort(window);
            end += clock();
            new_img << SortLib::findMedian(sorted_window);
            new_img << " ";
            new_img << "\n";
            window.clear();
            sorted_window.clear();
        }
    }
    new_img.close();
    return (end - start) / (double)CLOCKS_PER_SEC/1000;
}

// ** MERGESORT ** //
double mergesort(std::vector<int> pixel_vec, int filter, int width, int height, int max) {
    std::fstream new_img;
    std::string output = "mergesort" + std::to_string(filter) + ".pgm";
    std::clock_t start = std::clock(), end = std::clock();
    
    new_img.open(output.c_str(), std::fstream::out);
    new_img << "P2\n";
    new_img << "# ";
    new_img << output;
    new_img << "\n";
    new_img << width;
    new_img << " ";
    new_img << height;
    new_img << "\n";
    new_img << max;
    new_img << "\n";
    
    std::vector<int> window;
    std::vector<int> sorted_window;
    start = std::clock();
    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < width - 1; ++j) {
            std::vector<int> window;
            for (int k = i - 1; k < i + filter; ++k){
                for (int l = j - 1; l < j + filter; ++l){
                    if((k*width+l) > 0 && (k*width+l) < (height*width))
                        window.push_back(pixel_vec[k * width + l]);
                }
            }
            sorted_window = SortLib::mergeSort(window);
            end += clock();
            new_img << SortLib::findMedian(sorted_window);
            new_img << " ";
            new_img << "\n";
            window.clear();
            sorted_window.clear();
        }
    }
    new_img.close();
    return (end - start) / (double)CLOCKS_PER_SEC/1000;
}


// ** BST ** //
double bst(std::vector<int> pixel_vec, int filter, int width, int height, int max) {
    std::fstream new_img;
    std::string output = "bst" + std::to_string(filter) + ".pgm";
    std::clock_t start = std::clock(), end = std::clock();
    
    new_img.open(output.c_str(), std::fstream::out);
    new_img << "P2\n";
    new_img << "# ";
    new_img << output;
    new_img << "\n";
    new_img << width;
    new_img << " ";
    new_img << height;
    new_img << "\n";
    new_img << max;
    new_img << "\n";
    
    std::vector<int> window;
    std::vector<int> sorted_window;
    start = std::clock();
    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < width - 1; ++j) {
            std::vector<int> window;
            for (int k = i - 1; k < i + filter; ++k){
                for (int l = j - 1; l < j + filter; ++l){
                    if((k*width+l) > 0 && (k*width+l) < (height*width))
                        window.push_back(pixel_vec[k * width + l]);
                }
            }
            sorted_window = SortLib::binarySearchTree(window);
            end += clock();
            new_img << SortLib::findMedian(sorted_window);
            new_img << " ";
            new_img << "\n";
            window.clear();
            sorted_window.clear();
        }
    }
    new_img.close();
    return (end - start) / (double)CLOCKS_PER_SEC/1000;
}


#endif
