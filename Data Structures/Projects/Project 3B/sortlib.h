//
//  sortlib.h
//  sortlib
//
//  Created by Bryan Johnson on 11/3/14.
//  Copyright (c) 2014 Bryan Johnson. All rights reserved.
//

#ifndef sortlib_h
#define sortlib_h
#include <vector>
class SortLib {
private:
    /** QUICKSORT HELPERS **/
    static int partition(std::vector<int> &vec, int min, int max) {
        int left = min;
        int right = max;
        int val = vec[left];
        while(left < right) {
            while(vec[left] <= val)
                // move left bound to the right
                left++;
            while(vec[right] > val)
                // move right bound to the left
                right--;
            if(left < right)
                // bounds have crossed, swap values
                std::swap(vec[left], vec[right]);
        }
        std::swap(vec[min], vec[right]);
        return right;
    }
    
    static std::vector<int> quickSort(std::vector<int> &vec, int left, int right) {
        // Bad input??
        if(right <= left)
            return vec;
        int pivot = partition(vec, left, right);
        // start recursion on new pivot point (left and right)
        quickSort(vec, left, pivot-1);
        quickSort(vec, pivot+1, right);
        return vec;
    }
    /** END QUICKSORT HELPERS**/
    
    /** MERGESORT HELPERS **/
    static std::vector<int> mergeSort(std::vector<int> &vec, const std::vector<int> &left, const std::vector<int> &right) {
        std::vector<int> sorted_result;
        int left_iterator = 0;
        int right_iterator = 0;
        
        // As long as iterators are within each half of vector...
        while(left_iterator < left.size() && right_iterator < right.size()) {
            if(left[left_iterator] < right[right_iterator]) {
                sorted_result.push_back(left[left_iterator]); // Add value from left vector to sorted vector if it's
                left_iterator++;                              // less than the value in the right
            } else {
                sorted_result.push_back(right[right_iterator]); // Add value from right vector to sorted vector if it's
                right_iterator++;                               // less than the value in the left
            }
        }
        
        // Add any remaining values from left vector into sorted vector
        while(left_iterator < left.size()) {
            sorted_result.push_back(left[left_iterator]);
            left_iterator++;
        }
        
        // Add any remaining values from right vector into sorted vector
        while(right_iterator < right.size()) {
            sorted_result.push_back(right[right_iterator]);
            right_iterator++;
        }
        // Set referenced vector to the vector that is sorted
        vec = sorted_result;
        return vec;
    }
    /** END MERGESORT HELPERS **/
    
    /** BINARYSEARCHTREE HELPERS **/
    class Node{
    public:
        Node* left;
        Node* right;
        Node* next; // this is used for queues when we level traverse
        Node** parentConnection;
        int data;
        
        Node(const int& num) { data = num; left = right = next = 0; parentConnection = 0; }
    };
    
    class BinarySearchTree{
    public:
        Node* root; // the top of the tree
        int size; // to keep track of size of tree
        int index; // used to keep track where you are in tree during traversal
        
        BinarySearchTree() {
            root = 0;
            size = 0;
            index = 0;
        }
        
        void insert(Node* addThis) {
            if (!root)
            {
                root = addThis;
                root->parentConnection = &root;
                ++size;
            }
            else
                insert(addThis, root); // start the recursion from the root of the tree
        }
        
        void insert(Node* addThis, Node* subRoot) {
            if (addThis->data <= subRoot->data)
            {
                // make sure there is something to compare to in recursion call
                if (subRoot->left)
                {
                    insert(addThis, subRoot->left);
                }
                else
                {
                    subRoot->left = addThis;
                    subRoot->left->parentConnection = &(subRoot->left);
                    ++size;
                }
            }
            else
            {
                // see above
                if (subRoot->right)
                {
                    insert(addThis, subRoot->right);
                }
                else
                {
                    subRoot->right = addThis;
                    subRoot->right->parentConnection = &(subRoot->right);
                    ++size;
                }
            }
        }
        
        // Alteration to inOrder traversal that adds the current element of tree to the vector
        // when it is done, you will have a sorted vector
        std::vector<int> inOrder(Node *root, std::vector<int> &vec)
        {
            Node *current, *pre;
            std::vector<int> sorted_vector;
            
            // tree is empty, vector remains empty
            if(root == NULL)
                return sorted_vector;
            
            current = root;
            while(current != NULL)
            {
                if(current->left == NULL)
                {
                    sorted_vector.push_back(current->data);
                    current = current->right;
                }
                else
                {
                    pre = current->left;
                    while(pre->right != NULL && pre->right != current)
                        pre = pre->right;
                    
                    if(pre->right == NULL)
                    {
                        pre->right = current;
                        current = current->left;
                    }
                    
                    else 
                    {
                        pre->right = NULL;
                        sorted_vector.push_back(current->data);
                        current = current->right;      
                    }
                }
            }
            return sorted_vector;
        }
        
        std::vector<int> inOrder(std::vector<int> &vec) {
            return inOrder(root, vec);
        }
    };
    /** END BINARYSEARCHTREE HELPERS**/
    
    /** HEAPSORT HELPERS **/
    static void siftDown(std::vector<int> &vec, int k, int N){
        while ( k*2 + 1 < N ) {
            
            // TODO: Is this correct??
            int child = 2*k + 1;
            
            // if two children exist, get the largest of the two
            if ((child + 1 < N) && (vec[child] < vec[child+1])) child++;
            
            // heap is out of order..
            if (vec[k] < vec[child]) {
                std::swap( vec[child], vec[k] );
                k = child;
            }
            else
                return;
        }
    }
    
    static std::vector<int> heapsort(std::vector<int> &vec, int N){
        // heapify!
        for (int k = N/2; k >= 0; k--) {
            siftDown( vec, k, N);
        }
        
        while (N-1 > 0) {
            // swap the maximum value with the last value in the heap
            std::swap(vec[N-1], vec[0]);
            // take original heap and put back in max-heap order
            siftDown(vec, 0, N-1);
            // decrease total size of heap so the previous max value will hold its placement
            N--;
        }
        return vec;
    }
    /** END HEAPSORT HELPERS **/
 
public:
    // quicksort
    static std::vector<int> quickSort(std::vector<int> vec) {
        size_t size = vec.size();
        return quickSort(vec, 0, (int)size - 1);
    }
    
    // mergesort
    static std::vector<int> mergeSort(std::vector<int> &vec){
        // Base condition, if vector only has one value, it is already sorted
        if(vec.size() == 1){
            return vec;
        }
        
        // Find middle value in vector
        std::vector<int>::iterator middle = vec.begin() + (vec.size() / 2);
        
        std::vector<int> left(vec.begin(), middle);
        std::vector<int> right(middle, vec.end());
        
        // Recursive call to mergeSort on smaller vectors of larger vector
        mergeSort(left);
        mergeSort(right);
        
        return mergeSort(vec,left, right);
    }
    
    // binarysearchtree
    static std::vector<int> binarySearchTree(std::vector<int> vec) {
        BinarySearchTree bst;
        std::vector<int> sorted_vector;
        // For each value in vector, add to binary search tree
        for (int i = 0; i < vec.size(); ++i) {
            bst.insert(new Node(vec[i]));
        }
        // return vector after it has been through inOrder traversal
        vec = bst.inOrder(sorted_vector);
        return vec;
    }
    
    // heapsort
    static std::vector<int> heapsort(std::vector<int> vec) {
        return heapsort(vec, (int)vec.size());
    }
    
    // check for sorted vector
    static bool isSorted(std::vector<int> vec) {
        for (int i = 1; i < vec.size(); i++) {
            if (vec[i - 1] > vec[i]) {
                return false;
            }
        }
        return true;
    }
    
    static int findMedian(std::vector<int> vec) {
        size_t size = vec.size();
        if(!isSorted(vec)) throw;// new std::invalid_argument("Invalid vector, vector must be sorted first");
        if(size == 0) throw;// new std::invalid_argument("Invalid vector, size of vector must be greater than 0");
        if(size == 1) return vec[0];
        if(size % 2 == 0) {
            return (vec[size/2] + vec[size/2 - 1])/2;
        } else {
            return vec[size/2];
        }
    }
};

#endif
