// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2016
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair

#include "Collatz.h"

int collatz_path(int n);

using namespace std;

// ------------
// collatz_read
// ------------

//int collatz_rec(int i);

pair<int, int> collatz_read (const string& s) {
    istringstream sin(s);
    int i;
    int j;
    sin >> i >> j;
    return make_pair(i, j);}

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {
  //assert(i > 0 || j > 0);
  //assert(i <= 1000000 || j <= 1000000);
  
  int c = 1;
  int count;

  // swaps if i > j
  if (i > j) {
    int k = i;
    i = j;
    j = k;
  }

  // if i < (j/2)+1, drop the lower range
  if (i < (j >> 1) + 1) {
    i = (j >> 1) + 1;
  }
  
  // 3n+1 iterative algorithm
  //assert(i <= j);
  while (i <= j) {
    count = collatz_path(i);
 
    if (count > c)
      c = count;
    i++;
  }

  //assert(i > j);
  //assert(c > 0);
  return c;
}

int collatz_path(int n) {
  int count = 1;
  while (n > 1) {
    if ((n % 2) == 0)
      n >>= 1;
    else
      n += (n << 1) + 1;
    count++;
  }
  return count;
}

// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
    string s;
    while (getline(r, s)) {
        const pair<int, int> p = collatz_read(s);
        const int            i = p.first;
        const int            j = p.second;
        const int            v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}
