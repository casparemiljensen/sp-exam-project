#ifndef DEBUG_PRINT_HPP
#define DEBUG_PRINT_HPP
#include <string>

inline void debug_print(const std::string& msg) {
#ifndef NDEBUG
    std::cout << msg << std::endl;
#endif
}
#endif //DEBUG_PRINT_HPP
