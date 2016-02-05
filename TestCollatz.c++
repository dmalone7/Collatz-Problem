// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2016
// David Malone
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair

#include "gtest/gtest.h"

#include "Collatz.h"

using namespace std;

// -----------
// TestCollatz
// -----------

// ----
// read
// ----

TEST(CollatzFixture, read_1) {
    string s("1 10\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ(1, p.first);
    ASSERT_EQ(10, p.second);
}

TEST(CollatzFixture, read_2) {
    string s("1 1\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ(1, p.first);
    ASSERT_EQ(1, p.second);
}

TEST(CollatzFixture, read_3) {
    string s("999999 500000\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ(999999, p.first);
    ASSERT_EQ(500000, p.second);
}

TEST(CollatzFixture, read_4) {
    string s("1 999999\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ(     1, p.first);
    ASSERT_EQ(999999, p.second);
}

// ----
// eval
// ----

TEST(CollatzFixture, eval_1) {
    const int v = collatz_eval(1, 1);
    ASSERT_EQ(1, v);
}

TEST(CollatzFixture, eval_2) {
    const int v = collatz_eval(100, 1);
    ASSERT_EQ(119, v);
}

TEST(CollatzFixture, eval_3) {
    const int v = collatz_eval(1, 999999);
    ASSERT_EQ(525, v);
}

TEST(CollatzFixture, eval_4) {
    const int v = collatz_eval(999, 1001);
    ASSERT_EQ(143, v);
}

// ----
// path
// ----

TEST(CollatzFixture, path_1) {
    const int v = collatz_path(1);
    ASSERT_EQ(1, v);
}

TEST(CollatzFixture, path_2) {
    const int v = collatz_path(2);
    ASSERT_EQ(2, v);
}

TEST(CollatzFixture, path_3) {
    const int v = collatz_path(3);
    ASSERT_EQ(8, v);
}

TEST(CollatzFixture, path_4) {
    const int v = collatz_path(4);
    ASSERT_EQ(3, v);
}

// -----
// print
// -----

TEST(CollatzFixture, print_1) {
    ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_EQ("1 10 20\n", w.str());
}

TEST(CollatzFixture, print_2) {
    ostringstream w;
    collatz_print(w, 100, 200, 25);
    ASSERT_EQ("100 200 25\n", w.str());
}

TEST(CollatzFixture, print_3) {
    ostringstream w;
    collatz_print(w, 201, 210, 89);
    ASSERT_EQ("201 210 89\n", w.str());
}

TEST(CollatzFixture, print_4) {
    ostringstream w;
    collatz_print(w, 900, 1000, 174);
    ASSERT_EQ("900 1000 174\n", w.str());
}

// -----
// solve
// -----

TEST(CollatzFixture, solve) {
  istringstream r("1 10\n100 200\n201 210\n900 1000\n");
  ostringstream w;
  collatz_solve(r, w);
  ASSERT_EQ("1 10 20\n100 200 125\n201 210 89\n900 1000 174\n", w.str());
}

TEST(CollatzFixture, solve_large_gap) {
  istringstream r("163 1001\n161 5001\n");
  ostringstream w;
  collatz_solve(r, w);
  ASSERT_EQ("163 1001 179\n161 5001 238\n", w.str());
}

TEST(CollatzFixture, solve_reversed_set) {
    istringstream r("71 46\n95156 779\n");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("71 46 113\n95156 779 351\n", w.str());
}

/*
% g++ -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lgtest -lgtest_main -lpthread



% valgrind TestCollatz                                         >  TestCollatz.out 2>&1
% gcov -b Collatz.c++     | grep -A 5 "File 'Collatz.c++'"     >> TestCollatz.out
% gcov -b TestCollatz.c++ | grep -A 5 "File 'TestCollatz.c++'" >> TestCollatz.out



% cat TestCollatz.out
==14079== Memcheck, a memory error detector
==14079== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==14079== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
==14079== Command: ./TestCollatz
==14079== 
Running main() from gtest_main.cc
[==========] Running 17 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 17 tests from CollatzFixture
[ RUN      ] CollatzFixture.read_1
[       OK ] CollatzFixture.read_1 (13 ms)
[ RUN      ] CollatzFixture.read_2
[       OK ] CollatzFixture.read_2 (2 ms)
[ RUN      ] CollatzFixture.read_3
[       OK ] CollatzFixture.read_3 (2 ms)
[ RUN      ] CollatzFixture.read_4
[       OK ] CollatzFixture.read_4 (2 ms)
[ RUN      ] CollatzFixture.eval_1
[       OK ] CollatzFixture.eval_1 (3 ms)
[ RUN      ] CollatzFixture.eval_2
[       OK ] CollatzFixture.eval_2 (2 ms)
[ RUN      ] CollatzFixture.eval_3
[       OK ] CollatzFixture.eval_3 (1782 ms)
[ RUN      ] CollatzFixture.eval_4
[       OK ] CollatzFixture.eval_4 (2 ms)
[ RUN      ] CollatzFixture.path_1
[       OK ] CollatzFixture.path_1 (1 ms)
[ RUN      ] CollatzFixture.path_2
[       OK ] CollatzFixture.path_2 (2 ms)
[ RUN      ] CollatzFixture.path_3
[       OK ] CollatzFixture.path_3 (1 ms)
[ RUN      ] CollatzFixture.path_4
[       OK ] CollatzFixture.path_4 (2 ms)
[ RUN      ] CollatzFixture.print_1
[       OK ] CollatzFixture.print_1 (5 ms)
[ RUN      ] CollatzFixture.print_2
[       OK ] CollatzFixture.print_2 (3 ms)
[ RUN      ] CollatzFixture.print_3
[       OK ] CollatzFixture.print_3 (1 ms)
[ RUN      ] CollatzFixture.print_4
[       OK ] CollatzFixture.print_4 (2 ms)
[ RUN      ] CollatzFixture.solve
[       OK ] CollatzFixture.solve (7 ms)
[----------] 17 tests from CollatzFixture (1841 ms total)

[----------] Global test environment tear-down
[==========] 17 tests from 1 test case ran. (1865 ms total)
[  PASSED  ] 17 tests.
==14079== 
==14079== HEAP SUMMARY:
==14079==     in use at exit: 0 bytes in 0 blocks
==14079==   total heap usage: 492 allocs, 492 frees, 74,036 bytes allocated
==14079== 
==14079== All heap blocks were freed -- no leaks are possible
==14079== 
==14079== For counts of detected and suppressed errors, rerun with: -v
==14079== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
File 'Collatz.c++'
Lines executed:100.00% of 55
Branches executed:100.00% of 60
Taken at least once:70.00% of 60
Calls executed:74.07% of 27
Creating 'Collatz.c++.gcov'
File 'TestCollatz.c++'
Lines executed:100.00% of 66
Branches executed:59.81% of 418
Taken at least once:29.90% of 418
Calls executed:53.29% of 486
Creating 'TestCollatz.c++.gcov'
*/
