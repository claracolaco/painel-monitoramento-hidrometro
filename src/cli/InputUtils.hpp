#pragma once
#include <iostream>
#include <string>
#include <limits>

inline int lerInt(const std::string& msg) {
    int v;
    while (true) {
        std::cout << msg;
        if (std::cin >> v) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return v;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Valor invalido. Tente de novo.\n";
    }
}

inline double lerDouble(const std::string& msg) {
    double v;
    while (true) {
        std::cout << msg;
        if (std::cin >> v) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return v;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Valor invalido. Tente de novo.\n";
    }
}

inline std::string lerLinha(const std::string& msg) {
    std::cout << msg;
    std::string s;
    std::getline(std::cin, s);
    return s;
}