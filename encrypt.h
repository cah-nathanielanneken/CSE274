/*****
 * Author   : karroje
 * Date     : 2011-01-20
 * Modified : inclezd (02/10/2015)
 * Sources  : All code is original, 
 * Purpose  : This file is designed to declare certain functions necessary for the encoding of the 
 *            RSA encyption algorithm, as assigned for Homework 02 in CSE 274.
 * Note     : DO NOT CHANGE THIS FILE!!!
 *****/
#pragma once

#include <stdlib.h>
#include <string.h>
#include "rsa_functions.h"

/***********************************************************************************/
/* Phase 01: Implement the following functions                                     */


/*
 * Purpose: Convert a string of n characters to an RSAint
 * Prameters:
 *   * A string str holding c or less characters.
 *   * An integer value c.
 * Hint: A character is an 8-bit number.  How do you fit c 8-bit
 *       numbers into a 64-bit "slot"?  If we think of each byte of
 *       our integer as a slot, we need to put one character (or --
 *       more specifically -- the ASCII value representing the 
 *       character) into a slot.  For example: if we had the string
 *       "ABC" (for c=3), we would create a number where the least
 *       significant byte has a 65 (= 'A'), the second least significant
 *       byte had a 66 (= 'B'), the third least significant byte had
 *       a 67  (= 'C') and *all* other bytes had a value of 0.
 * Comment: There are multiple ways that this can be done.  But in order to
 *          ensure that the cracker will work later on, you must do it as 
 *          described above.   (Specifically: the left-most character must
 *          go in the right-most slot.)  If what you have written works
 *          correctly with the hint in the next function, you are good.
 * Preconditions: str != NULL, 0 <= c <= sizeof(RSAint)
 */
RSAint chars2RSAint(char* str, int c);

/*
 * Purpose: Convert a RSAint to a string of c characters.
 * Comment: Take a number created by chars2RSAint and covert it
 *          into the c characters.
 * Testing: If a string of length c is used to create an RSAint
 *          in chars2RSAint, then this function should turn that
 *          number back into the same string.
 * Preconditions:  enc >= 0, c >= 0, msg != NULL
 * Assumptions: The *str has been allocated with enough space
 *              to hold the c characters.  It is not possible
 *              to enforce this as a precondition, but any errors
 *              caused by failure to comply are the user's problem.
 * Hint: The code should look exactly like this:
 *    void RSAint2chars(RSAint enc, char* str, int c) {
 *      assert(enc >= 0 && c >= 0);
 *      for (int i=0; i < c; i++) {
 *          *(str + i) = (char) enc % 256;
 *          enc = enc >> 8;
 *      }
 *    }
 * 
 */
void RSAint2chars(RSAint enc, char* str, int c);


/* 
 * Purpose: Given two large primes, generate a key set for RSA encryption
 * Comment: You need to use the random number generation functions
            (included in rsa_functions.h) to make sure you do not generate
            the same key pair every time.
 * Precondition: e != NULL, d != NULL, n != NULL, 
 *               minPrimeLimit < p < maxPrimeLimit
 *               minPrimeLimit < q < maxPrimeLimit
 *               p != q
 *               (minPrimeLimit and maxPrime Limit are constant integer
 *                values defined in rsa_functions.h)
 * Postcondition: n = p*q, e*d % ((p-1)*(q-1)) = 1, e > 10,000
 */
void generateKey(RSAint p, RSAint q, RSAint* e, RSAint* d, RSAint* n);


/*
 * Purpose: Encrypt the message in chunks of 3 characters, using the key pair (e, n),
 *          returning an integer array of the encoded values.  size is the 
 *          lengh of msg, and *newSize should be set by this function to the size of the
 *          returned array.
 * Preconditions: msg != NULL, newSize != NULL , size > 0
 */
RSAint* RSAencrypt(char* msg, int size, int* newSize, RSAint e, RSAint n);


/* Purpose: Decrypt the encoding using the key pair (d, n).  size is the size
 *          of the encoding array, while newSize will be set by this function
 *          to the size of the array created by the algorithm and returned by
 %          the function.  
 *          Assume each integer in the encoding 
 *          array represents 3 characters that can be extracted by chars2RSAint.
 * Preconditions: encoding != NULL, newSize != NULL, size > 0
 */
char* RSAdecrypt(RSAint* encoding, int size, int* newSize, RSAint d, RSAint n);



/* 
 * Purpose: Given the public key pair (e, n), returns d (thus cracking
 *          the encryption scheme and allowing you to decode messages
 *          you are not supposed to be able to read).
 * Comment: You can do this *only* because we are using small keys.  Your
 *          algorithm will be slow -- and would get exponentially worse
 *          as we increased the size of the key.
 * Hint: Find prime numbers p and q such that n = p*q. Use p, q, e, and n
 *       to compute d according to the RSA algorithm.
 */
RSAint RSACracker(RSAint e, RSAint n);


/* 
 * Don't forget to write the required code in the main function in main.cpp!!!
 */
