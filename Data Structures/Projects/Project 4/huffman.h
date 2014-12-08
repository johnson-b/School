
#ifndef huffman
#define huffman

#include <queue>
#include <vector>
#include <iostream>

const int MAX = 256;

// 'Base' node to hold type of node and its frequency
struct Node {
    const int freq;

    // utility for internal use when printing out string representation of Huffman tree
    enum Type {
        BASE,
        HUFF,
        LEAF
    };
    Type type;
    
    Node(int f) : freq(f) { type = BASE; }
    virtual ~Node() {}
};

// Holds the right and left value of the 'Base' node
struct HuffNode : Node {
    Node *left;
    Node *right;
    
    HuffNode(Node* l, Node* r) : Node(l->freq + r->freq), left(l), right(r) {this->type = HUFF;}
    ~HuffNode() {
        delete left;
        delete right;
    }
};

// Holds the character value of the phrase/string given
struct Leaf : Node
{
    const char character;
    
    Leaf(int freq, char c) : Node(freq), character(c) {this->type = LEAF;}
};

// Comparison used in priority queue, compare the frequency of each character in string 
struct NodeComparison {
    bool operator()(const Node* left, const Node* right) const { return left->freq > right->freq; }
};

// Builds up the Huffman Tree based on the priority queue
Node* Tree(const int (&frequencies)[MAX]) {
    std::priority_queue<Node*, std::vector<Node*>, NodeComparison> trees;
    
    // Push each frequency into a vector
    for (int i = 0; i < MAX; ++i)
    {
        if(frequencies[i] != 0)
            trees.push(new Leaf(frequencies[i], (char)i));
    }

    // Begin dequeueing the priority queue
    while (trees.size() > 1)
    {
        Node* right = trees.top();
        trees.pop();
        
        Node* left = trees.top();
        trees.pop();
        
        Node* root = new HuffNode(right, left);
        trees.push(root);
    }
    return trees.top();
}

// Generates all the necessary encoding of the inputted string/phrase
void Codes(const Node* node, const std::vector<char>& first, std::map<char, std::vector<char>>& codes) {
    if (const Leaf* l = dynamic_cast<const Leaf*>(node))
    {
        codes[l->character] = first;
    }
    else if (const HuffNode* huffnode = dynamic_cast<const HuffNode*>(node))
    {
        std::vector<char> left_or_first = first;
        left_or_first.push_back('0');
        Codes(huffnode->left, left_or_first, codes);
        
        std::vector<char> right_of_first = first;
        right_of_first.push_back('1');
        Codes(huffnode->right, right_of_first, codes);
    }
}

// Prints out the string representation of the Huffman tree
void TreeAsString(Node* root){
    if (!root) {
        return;
    }
    
    // if possible print out the current node's character, if it
    // doesn't have one, print a star
    if (root->type == Node::LEAF) {
        std::cout << dynamic_cast<Leaf*>(root)->character;
    }
    else {
        std::cout << "*";
    }
    
    // if current node has left value, start recursion on node's left
    // if not, print a forward slash
    if (root->type == Node::HUFF) {
        TreeAsString(dynamic_cast<HuffNode*>(root)->left);
    }
    else {
        std::cout << "/";
    }
    
    // if current node has right value, start recursion on node's right
    // if not, print a forward slash
    if (root->type == Node::HUFF) {
        TreeAsString(dynamic_cast<HuffNode*>(root)->right);
    }
    else {
        std::cout << "/";
    }
}

#endif