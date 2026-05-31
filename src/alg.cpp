// Copyright 2021 NNTU-CS

#include <iostream>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>

#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream sourceFile(filename);

    if (!sourceFile.is_open()) {
        return;
    }

    std::string buffer;
    char symbol;

    while (sourceFile.get(symbol)) {
        unsigned char ch = static_cast<unsigned char>(symbol);

        if (std::isalpha(ch)) {
            buffer += static_cast<char>(std::tolower(ch));
        } else {
            if (!buffer.empty()) {
                tree.insert(buffer);
                buffer.clear();
            }
        }
    }

    if (!buffer.empty()) {
        tree.insert(buffer);
    }

    sourceFile.close();
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> words = tree.getData();

    std::sort(words.begin(), words.end(),
        [](const std::pair<std::string, int>& first,
           const std::pair<std::string, int>& second) {
            return first.second > second.second;
        });

    std::ofstream output("result/freq.txt");

    for (const auto& entry : words) {
        std::cout << entry.first << " " << entry.second << std::endl;
        output << entry.first << " " << entry.second << std::endl;
    }

    output.close();
}
