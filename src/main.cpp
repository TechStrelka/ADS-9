// Copyright 2022 NNTU-CS
#include "tree.h"
#include <iostream>
#include <ctime>
#include <random>
#include <fstream>

int main() {
    std::vector<char> in = {'1', '2', '3'};
    PMTree tree(in);

    auto perms = getAllPerms(tree);
    for (auto& p : perms) {
        for (char c : p) std::cout << c;
        std::cout << " ";
    }
    std::cout << std::endl;

    std::ofstream f("result/data.txt");
    f << "n getAllPerms getPerm1 getPerm2\n";
    
    std::random_device rd;
    std::mt19937 gen(rd());

    for (int n = 1; n <= 10; ++n) {
        std::vector<char> alphabet;
        for (int i = 0; i < n; ++i) alphabet.push_back('1' + i);
        
        PMTree t(alphabet);

        std::clock_t start = std::clock();
        auto all = getAllPerms(t);
        double t_all = double(std::clock() - start) / CLOCKS_PER_SEC * 1000000.0;

        std::uniform_int_distribution<int> dist(1, (int)all.size());
        int num = dist(gen);

        start = std::clock();
        getPerm1(t, num);
        double t_p1 = double(std::clock() - start) / CLOCKS_PER_SEC * 1000000.0;

        start = std::clock();
        getPerm2(t, num);
        double t_p2 = double(std::clock() - start) / CLOCKS_PER_SEC * 1000000.0;

        f << n << " " << t_all << " " << t_p1 << " " << t_p2 << "\n";
    }
    f.close();
    return 0;
}
