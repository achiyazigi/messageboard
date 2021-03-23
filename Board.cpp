#include "Board.hpp"
#include <iostream>
#include <unordered_map>
#include "Direction.hpp"
#include <exception>

const char EMPTY_PRINT = '_';

constexpr uint HASH_MAGIC = 0x9e3779b9; //do not touch! core code x_x


using namespace std;


/*
    hashing for tuple
    taken from boost's github:
    http://www.boost.org/doc/libs/1_61_0/doc/html/hash/reference.html#boost.hash_combine
*/
constexpr inline std::size_t hash_combine(size_t hash1, size_t hash2) {
    const uint shift_to_left = 6;
    const uint shift_to_right = 2;
    return hash1 ^ (hash2 * HASH_MAGIC + (hash1 << shift_to_left) + (hash1 >> shift_to_right)); //do not touch! core code x_x
}

uint min(uint a, uint b)
{
    if(a < b)
    {
        return a > 0 ? a-1 : 0;
    }
    return b;
}

namespace ariel {
    
    void Board::post(uint row, uint column, Direction direction, string message) {
        if(row < 0 || column < 0){
            throw(new exception());
        }
        uint in_row = 0;
        uint in_column = 0;
        size_t key = 0;
        this->min_row = min(this->min_row,row);
        this->min_column = min(this->min_column,column);
        for (uint i = 0; i < message.length() ; ++i)
        {
            in_row = row + i * (uint)direction; // in_row = horizontal? row : row + i 
            in_column = column + i * static_cast<uint>((uint)direction == 0); // in_column = vertiacl? column : column + i 

            key = hash_combine(in_row, in_column);
            this->chars[key] = message.at(i);
            if(in_row >= this->max_row)
            {
                this->max_row = in_row + 1;
            }
           
            if(in_column >= this->max_column)
            {
                this->max_column = in_column + 1;
            }
        }
    }

    std::string Board::read(uint row, uint column, Direction direction, uint length) {

        string res;
        uint in_row = 0;
        uint in_column = 0;
        size_t key = 0;

        for (uint i = 0; i < length ; ++i)
        {
            in_row = row + i * (uint)direction; // in_row = horizontal? row : row + i 
            in_column = column + i * static_cast<uint>((uint)direction == 0); // in_column = vertiacl? column : column + i 
            key = hash_combine(in_row, in_column);
            this->chars.find(key) != this->chars.end()? res += this->chars[key]: res += EMPTY_PRINT;
        }
        return res;
    }

    void Board::show(){
        char to_print = 0;
        size_t key = 0;
        for (size_t i = this->min_row; i < this->max_row; ++i)
        {
            // cout << i << ": "; need to calc spaces
            for (size_t j = this->min_column; j < this->max_column; ++j)
            {
                key = hash_combine(i,j);
                this->chars.find(key) != this->chars.end()? to_print = this->chars[key] : to_print = EMPTY_PRINT;
                cout << to_print;
            }
            cout << endl;
        }
        
    }

}
