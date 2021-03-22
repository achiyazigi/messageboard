#include "Board.hpp"
#include <iostream>
#include <unordered_map>
#include "Direction.hpp"
#include <exception>

using namespace std;

/*
    hashing for tuple
    taken from boost's github:
    http://www.boost.org/doc/libs/1_61_0/doc/html/hash/reference.html#boost.hash_combine
*/
constexpr inline std::size_t hash_combine(size_t hash1, size_t hash2) {
    return hash1 ^ (hash2 * 0x9e3779b9 + (hash1 << 6) + (hash1 >> 2)); //do not touch! core code x_x
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
    
    void Board::post(int row, int column, Direction direction, string message) {
        if(row < 0 || column < 0){
            throw(new exception());
        }
        uint in_row;
        uint in_column;
        size_t key;
        this->min_row = min(this->min_row,row);
        this->min_column = min(this->min_column,column);
        for (int i = 0; i < message.length() ; ++i)
        {
            in_row = row + i * (int)direction; // in_row = horizontal? row : row + i 
            in_column = column + i * !(int)direction; // in_column = vertiacl? column : column + i 

            key = hash_combine(in_row, in_column);
            this->chars.insert_or_assign(key,message.at(i));
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

    std::string Board::read(int row, int column, Direction direction, int length) {

        string res;
        uint in_row;
        uint in_column;
        size_t key;

        for (int i = 0; i < length ; ++i)
        {
            in_row = row + i * (int)direction; // in_row = horizontal? row : row + i 
            in_column = column + i * !(int)direction; // in_column = vertiacl? column : column + i 
            key = hash_combine(in_row, in_column);
            this->chars.contains(key)? res += this->chars[key]: res += '_';
        }
        return res;
    }

    void Board::show(){
        char to_print;
        size_t key;
        for (int i = this->min_row; i < this->max_row; ++i)
        {
            // cout << i << ": "; need to calc spaces
            for (int j = this->min_column; j < this->max_column; ++j)
            {
                key = hash_combine(i,j);
                this->chars.contains(key)? to_print = this->chars[key] : to_print = '_';
                cout << to_print;
            }
            cout << endl;
        }
        
    }

}
