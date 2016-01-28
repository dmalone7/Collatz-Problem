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
  int temp = 0;
  while (i < j) {
    int n = i;
    int c = 1;
    while (n > 1) {
      if ((n % 2) == 0)
        n = (n / 2);
      else
        n = (3 * n) + 1;
      c++;
    }
    if (temp < c)
      temp = c;
    i++;
  }
  return temp;

/*    int v, temp;
    v = 0;
    temp = 0;

    while (i < j) {
      v = collatz_rec(i);
      if (temp < v)
        temp = v;
      i++;
    }

    return v;
}

int collatz_rec(int i) {
  if (i == 1)
    return 1;
  if (i % 2 == 0) {
    int j = collatz_rec(i / 2);
    return 1 + j;
  }
  int j = collatz_rec(i * 3 + 1);
  return 1 + j;
  */
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
