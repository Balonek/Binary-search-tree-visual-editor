#ifndef BST_H
#define BST_H

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QPen>
#include <QBrush>
#include <vector>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;
    int size_;
    int calculateDepth(Node* node);

public:
    BST() : root(nullptr), size_(0) {}
    void insert(int key);
    void remove(int key);
    Node* search(int key);
    void clear();
    int size() { return size_; }
    int depth();
    int minimum();
    int maximum();
    vector<int> inorder();
    void visualize(QGraphicsScene* scene);
};

#endif // BST_H
