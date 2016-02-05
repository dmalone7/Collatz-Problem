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
static int cache[100000];
long values[1000];

pair<int, int> collatz_read (const string& s);
int collatz_eval (int i, int j);
void collatz_print (ostream& w, int i, int j, int v);
void collatz_solve (istream& r, ostream& w);
int collatz_path(long n);

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
  int max = 1;
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
  while (i <= j) {
    if (i < 100000 && cache[i] != 0)
      count = cache[i];
    else
      count = collatz_path(i);
    if (count > max)
      max = count;
    i++;
  }

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
#ifdef
    if(n < 100000) {
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
#endif
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
