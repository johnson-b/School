
#ifndef huffman
#define huffman

#include <queue>
#include <vector>
#include <map>
#include <iostream>
const int MAX = 256;

/* ============================== NODE_BEGIN ============================== */
struct Node {
    const int freq;
    
    enum Type {
        BASE,
        HUFF,
        LEAF
    };
    Type type;
    
    Node(int f) : freq(f) { type = BASE; }
    virtual ~Node() {}
};

struct HuffNode : Node {
    Node *left;
    Node *right;
    
    HuffNode(Node* l, Node* r) : Node(l->freq + r->freq), left(l), right(r) {this->type = HUFF;}
    ~HuffNode() {
        delete left;
        delete right;
    }
};

struct Leaf : Node
{
    const char character;
    
    Leaf(int freq, char c) : Node(freq), character(c) {this->type = LEAF;}
};

struct NodeComparison {
    bool operator()(const Node* left, const Node* right) const { return left->freq > right->freq; }
};
/* ============================== NODE_END ============================== */

/* ============================== HUFFMAN_BEGIN ============================== */
Node* Tree(const int (&frequencies)[MAX]) {
    std::priority_queue<Node*, std::vector<Node*>, NodeComparison> trees;
    
    for (int i = 0; i < MAX; ++i)
    {
        if(frequencies[i] != 0)
            trees.push(new Leaf(frequencies[i], (char)i));
    }
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

void Compress(const Node* node, const std::vector<char>& first, std::map<char, std::vector<char> >& codes) {
    if (const Leaf* l = dynamic_cast<const Leaf*>(node) )
    {
        codes[l->character] = first;
    }
    else if (const HuffNode* huffnode = dynamic_cast<const HuffNode*>(node))
    {
        std::vector<char> left_or_first = first;
        left_or_first.push_back('0');
        Compress(huffnode->left, left_or_first, codes);
        
        std::vector<char> right_of_first = first;
        right_of_first.push_back('1');
        Compress(huffnode->right, right_of_first, codes);
    }
}

void TreeAsStringPost(Node* root) {
    if (!root) {
        return;
    }
    
    if (root->type == Node::HUFF) {
        TreeAsStringPost(dynamic_cast<HuffNode*>(root)->left);
    }
    
    if (root->type == Node::HUFF) {
        TreeAsStringPost(dynamic_cast<HuffNode*>(root)->right);
    }
    
    if (root->type == Node::LEAF) {
        std::cout << dynamic_cast<Leaf*>(root)->character;
    } else {
        std::cout << "@";
    }
}

void PrintFrequencyTable(Node* root, std::map<char, std::vector<char> > codes) {
    if(!root) {
        return;
    }
    
    if(root->type == Node::LEAF) {
        char c = dynamic_cast<Leaf*>(root)->character;
        std::cout << c;
        std::cout << "(" << root->freq << "): ";
        
        for(size_t i = 0; i < codes.find(c)->second.size(); i++) {
            char code = codes.find(c)->second[i];
            std::cout << code;
        }
        std::cout << std::endl;
        
    }
    
    if(root->type == Node::HUFF) {
        PrintFrequencyTable(dynamic_cast<HuffNode*>(root)->left, codes);
    }
    
    
    if(root->type == Node::HUFF) {
        PrintFrequencyTable(dynamic_cast<HuffNode*>(root)->right, codes);
    }
}
/* ============================== HUFFMAN_END ============================== */
#endif