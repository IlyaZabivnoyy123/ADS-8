// Copyright 2021 NNTU-CS

#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>
#include <utility>

template<typename DataType>
class BST {
private:
    struct Node {
        DataType key;
        int counter;
        Node* leftBranch;
        Node* rightBranch;

        explicit Node(DataType value) : key(value), counter(1),
                                        leftBranch(nullptr), rightBranch(nullptr) {}
    };

    Node* top;

    void placeNode(Node** branch, DataType value) {
        if (*branch == nullptr) {
            *branch = new Node(value);
            return;
        }

        if (value < (*branch)->key) {
            placeNode(&((*branch)->leftBranch), value);
        } else if (value > (*branch)->key) {
            placeNode(&((*branch)->rightBranch), value);
        } else {
            (*branch)->counter++;
        }
    }

    int lookupNode(Node* branch, DataType value) const {
        if (branch == nullptr) return 0;

        if (value == branch->key) return branch->counter;

        if (value < branch->key) return lookupNode(branch->leftBranch, value);

        return lookupNode(branch->rightBranch, value);
    }

    int measureHeight(Node* branch) const {
        if (branch == nullptr) return -1;

        int leftHeight = measureHeight(branch->leftBranch);
        int rightHeight = measureHeight(branch->rightBranch);

        return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }

    void gatherData(Node* branch, std::vector<std::pair<DataType, int>>* container) const {
        if (branch == nullptr) return;

        gatherData(branch->leftBranch, container);
        container->push_back({branch->key, branch->counter});
        gatherData(branch->rightBranch, container);
    }

    void eraseTree(Node* branch) {
        if (branch == nullptr) return;

        eraseTree(branch->leftBranch);
        eraseTree(branch->rightBranch);
        delete branch;
    }

public:
    BST() : top(nullptr) {}

    ~BST() {
        eraseTree(top);
    }

    void insert(DataType value) {
        placeNode(&top, value);
    }

    int search(DataType value) const {
        return lookupNode(top, value);
    }

    int depth() const {
        return measureHeight(top);
    }

    std::vector<std::pair<DataType, int>> getData() const {
        std::vector<std::pair<DataType, int>> result;
        gatherData(top, &result);
        return result;
    }
};

#endif  // INCLUDE_BST_H_
