// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "tree.h"

void collectPerms(Node* node, std::vector<char>& current, std::vector<std::vector<char>>& result) {
    if (!node) return;
    if (node->value != '\0') current.push_back(node->value);

    if (node->children.empty() && node->value != '\0') {
        result.push_back(current);
    } else {
        for (Node* child : node->children) {
            collectPerms(child, current, result);
        }
    }
    if (node->value != '\0') current.pop_back();
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> current;
    collectPerms(tree.getRoot(), current, result);
    return result;
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
    std::vector<std::vector<char>> perms = getAllPerms(tree);
    if (num < 1 || num > (int)perms.size()) return {};
    return perms[num - 1];
}

long long fact(int n) {
    long long res = 1;
    for (int i = 2; i <= n; ++i) res *= i;
    return res;
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
    int n = tree.getElementCount();
    long long total = fact(n);
    if (num < 1 || num > total) return {};

    std::vector<char> result;
    Node* current = tree.getRoot();
    long long idx = num - 1;

    while (current && !current->children.empty()) {
        int branch_count = current->children.size();
        long long combinations_per_branch = fact(branch_count - 1);

        long long child_idx = idx / combinations_per_branch;
        idx %= combinations_per_branch;

        current = current->children[child_idx];
        result.push_back(current->value);
    }
    return result;
}

