#include "BigIntBase.h"	
#include "BigInt.h"	
#include <assert.h>
#include <cmath>

int main(int argc, const char * argv[]) {

	if (argc==1||argc>5) {
     	cout << "Wrong input format!" << endl;
     	BigInt test = BigInt(30);
     	cout << test << endl;
      	exit(1);
   	}
   	if (argc==2) {
    	int log10pp1 = atoi(argv[1]);
      	cout << "size of the prime: " << log10pp1 << endl;
      	cout << BigInt::randomPrime(log10pp1) << endl;
   	}
   	if (argc==3) {
      	int a = atoi(argv[1]);
      	int b = atoi(argv[2]);
      	BigIntBase *arr = new BigIntBase[2];
      	arr = BigInt::euclidExtended(a, b);
      	cout << "X: " << arr[0] << endl;
      	cout << "Y: " << arr[1] << endl;
   	}
   	if (argc==4) {
      	int e = atoi(argv[1]);
      	int p = atoi(argv[2]);
      	int q = atoi(argv[3]);
        BigIntBase ee = BigIntBase(e);
        BigIntBase pp = BigIntBase(p);
        BigIntBase qq = BigIntBase(q);
        BigIntBase phen = (pp-1)*(qq-1);
        BigIntBase phenNeg = BigIntBase(phen);
        BigInt::modInverse(phen, ee, phenNeg);
   	}
   	if (argc==5) {
      	if (argv[1][0]=='e') {
         	int e = atoi(argv[2]);
         	string n = argv[3];
         	string m = argv[4];
         	cout << BigInt::encrypt(e, n, m) << endl;
      	}
      	else if (argv[1][0]=='d'){
         	int d = atoi(argv[2]);
         	string n = argv[3];
         	string m = argv[4];
         	cout << BigInt::decrypt(d, n, m) << endl;
      	}
   	}

    return 0;
}