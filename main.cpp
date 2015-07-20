#include "encrypt.h"
#include <iostream>
#include <fstream>

using namespace std;

/**
 * Add your own code to the main function below, as specified there.
 */

void test1() {
	RSAint i = chars2RSAint("ABC.", strlen("ABC.")+1);
    cout << "i: (should print 776159809) " << i << endl;
   
    char * s = (char*)malloc(strlen("ABC.")*sizeof(char) + sizeof(char));
    RSAint2chars(i, s, strlen("ABC.")+1);
    cout << "Should print ABC.: " << s << endl;
}

void test2() {
	RSAint i = chars2RSAint("ABCD.", strlen("ABCD.")+1);
    cout << "i: (should print 198713754177) " << i << endl;
   
    char * s = (char*)malloc(strlen("ABCD.")*sizeof(char) + sizeof(char));
    RSAint2chars(i, s, strlen("ABCD.")+1);
    cout << "Should print ABCD.: " << s << endl;
}

int main() {
	// for testing and grading - do not change!
	test1();
	test2();
	/**
	 * Write your code below this comment.
	 *	- Read the public key components n and e from the file keys.txt. (n is listed first.)
	 *	- Read the contents of the file encrypted.txt, containing a sequence of RSAints 
	 *		separated by spaces (which was produced by applying the encryption algorithm to a file) 
	 *		using the public key (e,n) you just read in. 
	 *	- Crack the encryption and print out the original message.
	 */

	
	string fileName = "keys.txt";
	ifstream inFile(fileName);
	RSAint e, n, d;
	inFile >> n;
	inFile >> e;
	inFile.close();

	fileName = "encrypted.txt";
	inFile = ifstream(fileName);
	bool encryptionDone = false;
	RSAint temp;
	int count = 0;
	int * newSize = (int*)malloc(sizeof(int));
	while(!inFile.eof()) {
			inFile >> temp;
			count++;
	}
	count--;
	inFile.close();
	inFile = ifstream(fileName);
	RSAint* encryptedMessage = (RSAint*)malloc(count*sizeof(RSAint));
	for(int i = 0; i < count; i++) {
		inFile >> *(encryptedMessage + i);
	}
	inFile.close();
	d = RSACracker(e, n);
	char * decodedMessage = RSAdecrypt(encryptedMessage, count, newSize, d, n); 
	for(int i = 0; i < *newSize; i++) {
		cout << *(decodedMessage + i);
	}
	
	

	return 0;
}
