#include <string>
#include <sys/types.h>
#include "Direction.hpp"
#include <unordered_map>
#include <iostream>

namespace ariel {
    class Board {
        uint max_row;
        uint max_column;
        uint min_row;
        uint min_column;
        std::unordered_map<size_t, char> chars;
    public:
        Board():max_row(0), max_column(0), min_row((uint)-1), min_column((uint)-1){}
        ~Board() { }
        void post(uint row, uint column, Direction direction, std::string message);
        std::string read(uint row, uint column, Direction direction, uint length);
        void show();
    };
}