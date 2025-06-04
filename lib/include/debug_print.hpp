//
// Created by wired on 6/3/25.
//

#ifndef DEBUG_PRINT_HPP
#define DEBUG_PRINT_HPP
#include <iostream>
#include <string>

inline void debug_print(const std::string& msg) {
#ifndef NDEBUG
    std::cout << msg << std::endl;
#endif
}
#endif //DEBUG_PRINT_HPP
