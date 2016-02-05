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

#define CACHE = true;

using namespace std;

#ifdef CACHE
static int cache[100]; // cache array of 100 numbers
long values[526];
#endif


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
  return make_pair(i, j);
}

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {
  assert(i > 0 && j > 0);
  assert(i <= 1000000 && j <= 1000000);

  int max = 1;
  int count;

  if (i > j) { // swap if i > j
    int k = i;
    i = j;
    j = k;
  }

  if (i < (j >> 1) + 1) // drop any inputs lower than j/2+1
    i = (j >> 1) + 1;

  assert(i <= j);
  while (i <= j) { // 3n+1 algorithm
#ifdef CACHE
    if (i < 100 && cache[i] != 0) // check if i is in cache
      count = cache[i];
    else
#endif
      count = collatz_path(i);
    if (count > max)
      max = count; // max amount of jumps
    i++;
  }
  assert(i > j);
  assert(max > 0);
  return max;
}

// ------------
// collatz_path
// ------------

int collatz_path(long n) {
  int count = 1;
  while (n > 1) {
    if ((n % 2) == 0) {
      n >>= 1; // n/2 if even
      ++count;
    }
    else {
      n = (3*n + 1) >> 1; // (3n+1) if odd, n/2 because guarenteed even
      ++++count;
    }
#ifdef CACHE
    if(n < 100) {
      if (cache[n] != 0)
        return --count + cache[n]; // 
      values[count] = n;
    }
  }

  int ndx = 1;
  for(int i = count; i > 0; i--) {
    cache[values[i]] = ndx;
    ++ndx;
#endif
  }
  return count;
}

// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
  w << i << " " << j << " " << v << endl;
}

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
    collatz_print(w, i, j, v);
  }
}
