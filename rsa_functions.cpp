/*****
 * Author   : karroje
 * Date     : 2011-01-20
 * Sources  : All code is original, based on standard RSA and number theoretic algorithms.
 * Purpose  : This code is designed to provide certain functions necessary for the encoding of the 
 *            RSA encyption algorithm, as assigned for Homework 02 in CSE 274.
 * Note     : DO NOT CHANGE THIS FILE!!! Students should not touch this code, and have no need to look
 *            at it save for their own curiosity.
 *****/

#include <assert.h>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>
#include <sys/types.h>
#include <iostream>
#include <math.h>
#include "rsa_functions.h"

using namespace std;
bool seedSet = false;

void precondition_assert(bool v, char* msg) {
  if (!v) {
    cerr << msg << endl;
    exit(1);
  }
}

RSAint modular_power(RSAint x, RSAint a, RSAint m) {
  precondition_assert(x >= 0 && a >= 0 && m > 1, (char*)"modular_power: bad parameters");

  if (a == 0)
    return 1;

  RSAint value = 1;
  RSAint n = (RSAint)(log((long double)a)/log((long double)2)) + 1;
  RSAint exp = x;
  RSAint mask = 1;
  for (int i=0; i <= n; i++, exp = (exp*exp) % m, mask <<= 1)
    if (a & mask) {
      assert(value*exp >= 0);
      value = (value*exp) % m;
    }

  return value;
}

void seedRand(unsigned seed) {
  seedSet = true;
  if (seed == 0) {
    srand((unsigned)time(0));
  }
  else
    srand((unsigned)seed);
}
     

RSAint randInt(RSAint max) {
  if (!seedSet)
    seedRand();

  return (RSAint)(max*(rand()*1.0)/RAND_MAX);
}

RSAint randInt(RSAint min, RSAint max) {
  precondition_assert(min <= max, (char*)"randInt: bad parameter");
  return randInt(max - min) + min;
}

bool isPrime(RSAint x) {
  precondition_assert(x > 1, (char*)"isPrime: bad parameter");
  RSAint i = 2;
  while (i*i <= x) {
    if (x % i == 0) 
      return false;
    i++;
  }
  return true;
}

RSAint gcd(RSAint a, RSAint b) {
  precondition_assert(a >= 0 && b >= 0, (char*)"gcd: bad_parameters");
  if (a < b) {
    RSAint tmp = b;
    b = a;
    a = tmp;
  }

  if (b == 0)
    return a;

  return gcd(b, a % b);
}

bool isCoPrime(RSAint x, RSAint y) {
  precondition_assert(x > 1 && y > 1, (char*)"isCoPrime: bad parameters");
  return gcd(x,y) == 1;
}



RSAint randomPrime(RSAint min, RSAint max) {
  precondition_assert(min < max, (char*)"randomPrime: min >= max");
  RSAint* vals = (RSAint*)malloc(((unsigned)(max-min))*sizeof(RSAint));
  for (RSAint i=0; i < max-min; i++)
    vals[i] = i + min;

  RSAint size = max-min;
  RSAint value;
  do {
    RSAint index = randInt(size);
    value = vals[index];
    if (index != size - 1)
      vals[index] = vals[size-1];
    size--;
  } while (size >= 0 && !isPrime(value));

  if (size < 0) {
    cerr << "randomPrime: no random number in the interval [" << min << "," << max << ")" << endl;
    exit(1);
  }

  free(vals);

  return value;
}

RSAint multiplicative_inverse(RSAint e, RSAint n) {
  precondition_assert(isCoPrime(e,n), (char*)"multiplicative inverse: arguments not co-prime");
  RSAint a = e, b = n;
  
  RSAint x = 0;
  RSAint lastx = 1;
  RSAint y = 1;
  RSAint lasty = 0;

  while (b != 0) {
    RSAint q = a / b;

    RSAint tmp_b = b;
    b = a % b;
    a = tmp_b;

    RSAint tmp_x = x;
    x = lastx - q*x;
    lastx = tmp_x;

    RSAint tmp_y = y;
    y = lasty - q*y;
    lasty = tmp_y;
  }

  while (lastx < 0)
    lastx += n;

  return lastx;
}


