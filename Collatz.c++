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

int collatz_path(long n);

using namespace std;
long cache[500000];
long values[1000];

// ------------
// collatz_read
// ------------

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
  assert(i > 0 || j > 0);
  assert(i <= 1000000 || j <= 1000000);

  int max = 1;
  int count;

  for (int tmp = 0; tmp < 100; tmp++)
    cache[tmp] = 0;

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
  assert(i <= j);
  while (i <= j) {
    if (i < 500000 && cache[i] != 0)
      count = cache[i];
    else
      count = collatz_path(i);
    if (count > max)
      max = count;
    i++;
  }

  assert(i > j);
  assert(max > 0);
  return max;
}

int collatz_path(long n) {
  int count = 1;
  while (n > 1) {
    if ((n % 2) == 0)
      n >>= 1;
    else
      n += (n << 1) + 1;
    count++;
    if(n < 500000) {
      if (cache[n] != 0)
        return --count + cache[n];
      values[count] = n;
    }
  } 

  int ndx = 1;
  for(int i = count; i > 0; i--) {
    cache[values[i]] = ndx;
    ++ndx;
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
