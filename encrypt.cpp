#include "rsa_functions.h"
#include <cassert>
#include <string.h>


RSAint chars2RSAint(char* str, int c) {
	assert(str != NULL && c >= 0 && c <= sizeof(RSAint));
	RSAint rsaInt = 0;
	for(int i = 0; i < c; i++) {
		rsaInt = (RSAint((*(str + i))) << (i*sizeof(char)*8)) | rsaInt;
	}
	return rsaInt;
}

void RSAint2chars(RSAint enc, char* str, int c) {
	assert(enc >= 0 && c >= 0);
	for (int i=0; i < c; i++) {
		*(str + i) = (char) enc % 256;
		enc = enc >> 8;
	}
}

void generateKey(RSAint p, RSAint q, RSAint* e, RSAint* d, RSAint* n) {
	assert(e != NULL && d != NULL && n != NULL && p > minPrimeLimit && p < maxPrimeLimit
		&& q > minPrimeLimit && q < maxPrimeLimit && p != q);

	*n = p*q;
	RSAint eFunc = (p-1)*(q-1);
	seedRand();

	*e = randomPrime(2,eFunc);
	while(gcd(*e,eFunc) != 1) {
		*e = randomPrime(2,eFunc);
	}

	*d = multiplicative_inverse(*e,eFunc);

	assert((*n == p*q) && (*e**d % ((p-1)*(q-1)) == 1) && (*e > 10000));
}

RSAint* RSAencrypt(char* msg, int size, int* newSize, RSAint e, RSAint n) {
	assert(msg != NULL && newSize != NULL && size >0);
	*newSize = size / 3;
	if(size % 3 != 0) {
		*newSize = *newSize + 1;
	}


	RSAint* codedMessage = (RSAint*)malloc(*newSize*sizeof(RSAint)+sizeof(RSAint));

	char* threeCharInt = (char*)malloc(3*sizeof(char));
	int tempCharArrayCount = 0, codedMessageCount = 0;
	for(int i = 0; i < size; i++) {
		*(threeCharInt+tempCharArrayCount) = *(msg + i);
		tempCharArrayCount++;
		if(tempCharArrayCount == 3 || (i == size - 1)) {
			*(codedMessage + codedMessageCount) = modular_power(chars2RSAint(threeCharInt, tempCharArrayCount),e,n);
			codedMessageCount++;
			tempCharArrayCount = 0;
			free(threeCharInt);
			threeCharInt = (char*)malloc(3*sizeof(char));
		}
	}
	return codedMessage;
}

char* RSAdecrypt(RSAint* encoding, int size, int* newSize, RSAint d, RSAint n) {
	assert(encoding != NULL && newSize != NULL && size > 0);
	*newSize = size*3;
	int decryptMessageCounter = 0;
	char* decryptMessage = (char*)malloc(*newSize*sizeof(char)+sizeof(char));
	for(int i = 0; i < size; i++) {
		char* tempCharHolder = (char*)malloc(3*sizeof(char));
		RSAint2chars(modular_power(*(encoding+i),d,n), tempCharHolder, 3);
		for(int g = 0; g < 3; g++) {
			*(decryptMessage+decryptMessageCounter) = *(tempCharHolder+g);
			decryptMessageCounter++;
		}
		free(tempCharHolder);
	}
	*newSize = strlen(decryptMessage);
	return decryptMessage;
}

RSAint RSACracker(RSAint e, RSAint n) {
	RSAint p=(((RSAint) 1) << 13), q;
	int i=0;
	bool foundPair = false, pIsPrime = false, qIsPrime=false;

	while(!foundPair) {
		q = (((RSAint) 1) << 13);
		qIsPrime = false;
		while(!pIsPrime) {
			if(isPrime(p)) {
				pIsPrime = true;
			}
			else {
				p++;
			}
		}
		while(!qIsPrime) {
			if(isPrime(q)) {
				if(p*q == n) {
					qIsPrime = true;
					foundPair = true;
				}
				else if(p*q < n) {
					q++;
				}
				else {
					p++;
					pIsPrime = false;
					qIsPrime = true;
				}
			}
			else if(p*q < n) {
				q++;
			}
			else {
				p++;
				pIsPrime = false;
				qIsPrime = true;
			}
		}
	}


	RSAint eFunc = (p-1)*(q-1);
	RSAint d =  multiplicative_inverse(e,eFunc);

	return d;
}