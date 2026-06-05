// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <algorithm>

struct Node {
    char value;
    std::vector<Node*> children;

    explicit Node(char v) : value(v) {}

    ~Node() {
        for (Node* child : children) {
            delete child;
        }
    }
};

class PMTree {
 private:
    Node* root;
    size_t element_count;

    void buildTree(Node* node, std::vector<char> elements) {
        if (elements.empty()) return;
        for (size_t i = 0; i < elements.size(); ++i) {
            Node* child = new Node(elements[i]);
            node->children.push_back(child);

            std::vector<char> next_elements = elements;
            next_elements.erase(next_elements.begin() + i);
            buildTree(child, next_elements);
        }
    }

 public:
    explicit PMTree(const std::vector<char>& in) {
        root = new Node('\0');
        element_count = in.size();
        std::vector<char> sorted_in = in;

        for (size_t i = 0; i < sorted_in.size(); ++i) {
            for (size_t j = i + 1; j < sorted_in.size(); ++j) {
                if (sorted_in[i] > sorted_in[j]) {
                    char temp = sorted_in[i];
                    sorted_in[i] = sorted_in[j];
                    sorted_in[j] = temp;
                }
            }
        }
        buildTree(root, sorted_in);
    }

    ~PMTree() {
        delete root;
    }

    Node* getRoot() const { return root; }
    size_t getElementCount() const { return element_count; }
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
