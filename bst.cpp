#include "bst.h"
#include <queue>
#include <QThread>
#include <stack>

void BST::insert(int x) {
    if (root == nullptr) {
        root = new Node(x);
        size_++;
        return;
    }

    Node* current = root;
    Node* parent = nullptr;

    while (current != nullptr) {
        parent = current;
        if (x < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (x < parent->key) {
        parent->left = new Node(x);
    } else {
        parent->right = new Node(x);
    }

    size_++;
}

Node* BST::search(int x) {
    Node* current = root;
    while (current != nullptr && current->key != x) {
        if (x < current->key) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return current;
}

void BST::remove(int x) {
    Node* current = root;
    Node* parent = nullptr;

    while (current != nullptr && current->key != x) {
        parent = current;
        if (x < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    if (current == nullptr) {
        return;
    }

    if (current->left == nullptr && current->right == nullptr) {
        if (parent == nullptr) {
            root = nullptr;
        } else if (parent->left == current) {
            parent->left = nullptr;
        } else {
            parent->right = nullptr;
        }
        delete current;
        size_--;
        return;
    }
    else if (current->left != nullptr && current->right != nullptr) {
        Node* successor = current->right;
        parent = current;

        while (successor->left != nullptr) {
            parent = successor;
            successor = successor->left;

        }
        current->key = successor->key;
        if (parent == current) {
            parent->right = successor->right;
        } else {
            parent->left = successor->right;
        }
        delete successor;
        size_--;
        return;
    }
    else {
        Node* child = current->left ? current->left : current->right;
        if (parent == nullptr) {
            root = child;
        } else if (parent->left == current) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        delete current;
        size_--;
    }
}
int BST::calculateDepth(Node* node) {
    if (node == nullptr) return 0;
    int leftDepth = calculateDepth(node->left);
    int rightDepth = calculateDepth(node->right);
    return std::max(leftDepth, rightDepth) + 1;
}

int BST::depth() {
    return calculateDepth(root);
}


void BST::clear() {
    std::stack<Node*> Stack;
    if (root != nullptr) {
        Stack.push(root);
    }

    while (!Stack.empty()) {
        Node* current = Stack.top();
        Stack.pop();

        if (current->left) {
            Stack.push(current->left);
        }
        if (current->right) {
            Stack.push(current->right);
        }

        delete current;
    }
    root = nullptr;
    size_ = 0;
}
int BST::minimum() {
    Node* current = root;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current->key;
}

int BST::maximum() {
    Node* current = root;
    while (current->right != nullptr) {
        current = current->right;
    }
    return current->key;
}
std::vector<int> BST::inorder() {
    std::vector<int> result;
    std::vector<Node*> stack;
    Node* current = root;

    while (!stack.empty() || current != nullptr) {
        while (current != nullptr) {
            stack.push_back(current);
            current = current->left;
        }
        current = stack.back();
        stack.pop_back();

        result.push_back(current->key);
        current = current->right;
    }

    return result;
}


void BST::visualize(QGraphicsScene* scene) {
    scene->clear();

    struct NodePosition {
        Node* node;
        int x, y;
    };

    int currentLevel = 0;
    int nodesInCurrentLevel = 1;
    int nodesProcessed = 0;

    const int pt_diff_y = 70;
    const int pt_diff_x = 100;

    std::queue<NodePosition> q;
    q.push({root, 400, 50});

    while (!q.empty()) {
        NodePosition current = q.front();
        q.pop();

        int circleSize = current.node->key > 10000 ? 60 : 40;
        int circleR = circleSize / 2;

        QBrush nodecolor = Qt::white;
        QPen blackPen(Qt::black);
        blackPen.setWidth(2);

        scene->addEllipse(
            current.x - circleR,
            current.y - circleR,
            circleSize,
            circleSize,
            blackPen,
            nodecolor
            );

        QGraphicsTextItem* numberLabel = scene->addText(QString::number(current.node->key));
        numberLabel->setDefaultTextColor(Qt::black);

        QRectF textRect = numberLabel->boundingRect();
        numberLabel->setPos(current.x - (textRect.width()/2), current.y - textRect.height()/2);


        int child_decreasing_space = pt_diff_x / (currentLevel + 1);

        if (current.node->left) {
            int childX = current.x - child_decreasing_space;
            int childY = current.y + pt_diff_y;

            scene->addLine(
                current.x,
                current.y + circleR,
                childX,
                childY - circleR,
                blackPen
                );
            q.push({current.node->left, childX, childY});
        }

        if (current.node->right) {
            int childX = current.x + child_decreasing_space;
            int childY = current.y + pt_diff_y;

            scene->addLine(
                current.x,
                current.y + circleR,
                childX,
                childY - circleR,
                blackPen
                );

            q.push({current.node->right, childX, childY});
        }

        nodesProcessed++;
        if (nodesProcessed == nodesInCurrentLevel) {
            currentLevel++;
            nodesInCurrentLevel *= 2;
            nodesProcessed = 0;
        }
    }
}



