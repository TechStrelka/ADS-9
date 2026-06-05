// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

struct Node {
    char value;
    std::vector<Node*> children;
    ~Node();
};

class PMTree {
private:
    Node* root;
    size_t element_count;
    void buildTree(Node* node, std::vector<char> elements);

public:
    PMTree(const std::vector<char>& in);
    ~PMTree();
    Node* getRoot() const;
    size_t getElementCount() const;
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);

#endif
