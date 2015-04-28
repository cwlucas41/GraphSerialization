// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

// A collection of various macros, constants, and small functions
// used for the software examples.

// First, include all the standard headers that we need

#ifndef __Book__
#define __Book__

#include <iostream>
#include <cstdlib>
#include <time.h>  // Used by timing functions

// Now all the standard names that we use
using std::cout;
using std::endl;
using std::string;
using std::ostream;

const int defaultSize = 10; // Default size

// Return true iff "x" is even
inline bool EVEN(int x) { return (x % 2) == 0; }

// Return true iff "x" is odd
inline bool ODD(int x) { return (x % 2) != 0; }

// Assert: If "val" is false, print a message and terminate
// the program
static void Assert(bool val, string s) {
  if (!val) { // Assertion failed -- close the program
    cout << "Assertion Failed: " << s << endl;
    exit(-1);
  }
}

// Swap two elements in a generic array
template<typename E>
static inline void swap(E A[], int i, int j) {
  E temp = A[i];
  A[i] = A[j];
  A[j] = temp;
}
// Random number generator functions

static inline void Randomize() // Seed the generator
  { srand(1); }

// Return a random value in range 0 to n-1
static inline int Random(int n)
  { return rand() % (n); }


// Swap two integers
static inline void swap(int& i, int& j) {
  int temp = i;
  i = j;
  j = temp;
}

// Swap two char*'s
static inline void swap(char* i, char* j) {
  char* temp = i;
  i = j;
  j = temp;
}


// Big enough for simple testing
#define INFINITY 9999

// Timing variables and functions
static unsigned tstart = 0;  // Time at beginning of timed section

// Initialize the program timer
static void Settime() { tstart = (unsigned) clock(); }

// Return the elapsed time since the last call to Settime
static double Gettime() {
  unsigned tcurr = (unsigned) clock();
  return (double)(tcurr - tstart)/(double)CLOCKS_PER_SEC;
}

// Your basic int type as an object.
class Int {
private:
  int val;
public:
  Int(int input=0) { val = input; }
  // The following is for those times when we actually
  //   need to get a value, rather than compare objects.
  int key() const { return val; }
  // Overload = to support Int foo = 5 syntax
  Int operator= (int input) { val = input; return val; }
};

// Let us print out Ints easily
static ostream& operator<<(ostream& s, const Int& i)
  { return s << i.key(); }
static ostream& operator<<(ostream& s, const Int* i)
  { return s << i->key(); }

#endif
