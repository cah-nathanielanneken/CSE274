/*****
 * Author   : karroje
 * Date     : 2011-01-20
 * Sources  : All code is original, based on standard RSA and number theoretic algortithms.
 * Purpose  : This class is designed to provide certain functions necessary for the encoding of the 
              RSA encyption algorithm, as assigned for Homework 02 in CSE 274.
 * Note     : DO NOT CHANGE THIS FILE!!! Students should not touch this code, 
              but they will need to understand what each function does.

 *****/
#pragma once

#include <iostream>

/* 
 * The following sets up a new type: RSAint.  This is actually just a renaming of the
 * type "long long". But since the name RSAint both makes more sence and is easier to
 * type, it makes sense to do this.
 */
typedef long long RSAint;


/*
 * Two constants defining the range that will be used for the search for primes.
 */
const int minPrimeLimit = ((RSAint) 1) << 13;
const int maxPrimeLimit = ((RSAint) 1) << 14;


/*
 * Purpose: seedRand() sets the pseudo-random number seed generator.  
 * With no argument, will seed from the clock.
 */
void seedRand(unsigned seed = 0);

/*
 * Purpose: Return a random number from the interval [min,max)
 *          Note: Notice the "half-open interval."  There is a chance
 *                that it will return min, but it will NEVER return max.
 * Preconditions: min <= max
 */
RSAint randInt(RSAint min, RSAint max);


/*
 * Purpose: Return the value of x^a % m.
 * Preconditions: x >= 0, m > 1, a >= 0
 */
RSAint modular_power(RSAint x, RSAint a, RSAint m);


/*
 * Purpose: Returns the greatest common divisor of a and b
 * Preconditions: a, b >= 0
 */
RSAint gcd(RSAint a, RSAint b);


/*
 * Purpose: Returns true if x is a prime number
 * Preconditions: p > 1
 */
bool isPrime(RSAint p);

/*
 * Purpose: Returns true if x and y are co-prime
 *          (That is, if gcd(x,y) = 1.)
 * Preconditions: x, y > 1
 */
bool isCoPrime(RSAint x, RSAint y);


/*
 * Purpose: Returns a random prime number in the interval [min,max)
 * Preconditions: min < max
 *                Note: Will terminate process if no such prime exists
 *                Comment: There is always a prime in the interval [x, 2*x)
 */
RSAint randomPrime(RSAint min, RSAint max);

/*
 * Purpose: Returns the multiplicative inverse of e for n.
 *          That is, return a where (e*a) % n == 1.
 * Preconditions: e and m are co-prime
 */
RSAint multiplicative_inverse(RSAint e, RSAint m);
