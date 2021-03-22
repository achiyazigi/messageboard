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
        Board():max_row(0), max_column(0), min_row(-1), min_column(-1){}
        ~Board() { }
        void post(int row, int column, Direction direction, std::string message);
        std::string read(int row, int column, Direction direction, int length);
        void show();
    };
}