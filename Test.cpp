/**
 *
 * AUTHORS: <achiya zigler>
 * 
 * Date: 2020-03-23
 */
#define USE_COLOR doctest::Color::

#include "doctest.h"
#include "Board.hpp"
#include <iostream>
using namespace ariel;

#include <string>
using namespace std;

TEST_CASE("horizontal check") {
    cout << USE_COLOR Yellow << "|----------------------|" << endl;
    cout << USE_COLOR Yellow << '|' << USE_COLOR BrightGreen << " ACHIYAZIGI TESTS, V1" << USE_COLOR Yellow << " |" << endl;
    cout << USE_COLOR Yellow << "|______________________|" << USE_COLOR White << endl;
    Board board;
    CHECK_NOTHROW(board.post(100,200,Direction::Horizontal,"abcd"));
    CHECK(board.read(100,200,Direction::Horizontal,0) == "");
    CHECK(board.read(100,200,Direction::Horizontal,1) == "a");
    CHECK(board.read(100,200,Direction::Horizontal,2) == "ab");
    CHECK(board.read(100,200,Direction::Horizontal,3) == "abc");
    CHECK(board.read(100,200,Direction::Horizontal,4) == "abcd");
    CHECK(board.read(100,200,Direction::Vertical,0) == "");
    CHECK(board.read(100,200,Direction::Vertical,1) == "a");
}

TEST_CASE("vertical check") {
    Board board;
    CHECK_NOTHROW(board.post(100,200,Direction::Vertical,"abcd"));
    CHECK(board.read(100,200,Direction::Vertical,0) == "");
    CHECK(board.read(100,200,Direction::Vertical,1) == "a");
    CHECK(board.read(100,200,Direction::Vertical,2) == "ab");
    CHECK(board.read(100,200,Direction::Vertical,3) == "abc");
    CHECK(board.read(100,200,Direction::Vertical,4) == "abcd");
    CHECK(board.read(100,200,Direction::Horizontal,0) == "");
    CHECK(board.read(100,200,Direction::Horizontal,1) == "a");
}

TEST_CASE("edge cases") {
    Board board;

    board.post(0,0,Direction::Horizontal,"achiyazigi");
    CHECK_NOTHROW(board.post(0,0,Direction::Horizontal,""));
    const unsigned short achiyazigi_len = 10;
    CHECK(board.read(0,0,Direction::Horizontal,achiyazigi_len) == "achiyazigi");
}

TEST_CASE("new board") {
    Board board;
    string expected;
    size_t expected_len;

    for (uint i = 0; i <= 50; i++)
    {
        expected = string(100,'_');
        for (uint j = 0; j <= 100; j++){
            expected_len = (size_t)(100 - j);
            expected.resize(expected_len);
            CHECK(board.read(i,j,Direction::Horizontal, expected_len) == expected);
        }
    }
}

TEST_CASE("Horizontal updates on board"){
    Board board;
    bool flip = false;
    string to_post;
    string expected = "01";
    size_t to_post_len;

    for (int i = 0; i < 7; ++i)
    {
        expected += expected;
    }
    expected.resize(200);

    for (uint i = 0; i <= 200; i++)
    {
        to_post_len = (size_t)(200 - i);
        to_post = string(to_post_len, flip + '0');
        board.post(0,i,Direction::Horizontal, to_post);
        flip = !flip;
    }
    CHECK(board.read(0,0,Direction::Horizontal, 200) == expected);

}

TEST_CASE("Vertical updates on board"){
    Board board;
    bool flip = false;
    string to_post;
    string expected = "01";
    size_t to_post_len;


    for (int i = 0; i < 7; ++i)
    {
        expected += expected;
    }
    expected.resize(200);

    for (uint i = 0; i <= 200; i++)
    {
        to_post_len = (size_t)(200 - i);
        to_post = string(to_post_len, flip + '0');
        board.post(i,0,Direction::Vertical, to_post);
        flip = !flip;
    }
    CHECK(board.read(0,0,Direction::Vertical, 200) == expected);

}

TEST_CASE("The Demo Case"){
    Board board;
	board.post(100, 200, Direction::Horizontal, "abcd");
	board.post(99, 202, Direction::Vertical, "xyz");
    string res = board.read(99, 201, Direction::Vertical, 3);
    CHECK(res == "_b_");
    res = board.read(100, 200, Direction::Horizontal, 6);
    CHECK(res == "abyd__");
}
/* Add more test cases here */
