// -------------------------------
// Copyright (C) 2016
// David Malone
// -------------------------------

// --------
// includes
// --------

#include <iostream> // cin, cout
#include <cassert>  // assert
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair

using namespace std;

pair<int, int> collatz_read (const string& s);
int collatz_eval (int i, int j);
void collatz_print (ostream& w, int i, int j, int v);
void collatz_solve (istream& r, ostream& w);

// ----
// main
// ----

int main () {
    collatz_solve(cin, cout);
    return 0;}

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
  int c = 1;

  // swaps if i > j
  if (i > j) {
    int k = i;
    i = j;
    j = k;
  }

  // values of i < (j/2)+1 don't matter 
  if (i < (j >> 1 + 1))
    i = (j >> 1 + 1);

  while (i < j) {
    long n = i;
    int temp = 1;

    while (n > 1) {
      if ((n % 2) == 0)
        n = n >> 1;
      else
        n = n + (n << 1) + 1;
      temp++;
    }
    if (temp > c)
      c = temp;
    ++i;
  }

  return c;
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
