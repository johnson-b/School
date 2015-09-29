#include "BigInt.h"
using namespace std;

BigInt::BigInt()
	: BigIntBase() {}

BigInt::BigInt(string const& num)
	: BigIntBase(num) {}

BigInt::BigInt(IntList const& num, bool isPositive)
	: BigIntBase(num, isPositive) {}

BigInt::BigInt(int num) 
	: BigIntBase(num) {}

BigInt BigInt::random(int const& digits) {
	srand (time(NULL));
   	std::stringstream stringStream;
   	for(int i = 0; i <= digits; i++) {
      	int random = rand() % 10;
      	// Make sure the first digit isn't a 0
      	if(i == 0) {
         	while(random != 0) {
            	random = rand() % 10;
         	}
      	}
      	char digit = (char)('0'+random);
      	stringStream << digit;
   	}
   	return BigInt(stringStream.str());
}

BigIntBase BigInt::randomPrime(int const& digits) {
	srand(time(NULL));
   	BigIntBase value = BigInt::random(digits);
   
   	if(value % 2 == 0) {
      	value = value + 1;
   	}

   	while(!BigInt::fermatTest(value, 3)) {
      	value = value + 2;
   	}
   	return value;
}

BigIntBase BigInt::modExp(BigIntBase const& base, BigIntBase exponent, BigIntBase const& mod) {
	if (exponent < 0) {
    	throw new invalid_argument("Exponent may not be negative in modExp");
   	}
   	if (exponent == 0) {
     	return 1;
   	}
   	BigIntBase temp = modExp(base, exponent.half(), mod);
   	if (exponent%2 == 0) {
      	return (temp*temp)%mod;
   	} 
   	else {
      	return (((temp*temp)%mod)*base)%mod;
   	}
}

bool BigInt::fermatTest(BigIntBase value, int iterations) {
	if(value == 1 ||
      	value == 2) {
      	return true;
   	}

   	for(int i = 0; i < iterations; i++) {
      	BigInt a = BigInt(2 + i * 2);
      	if(BigInt::modExp(a, value - 1, value) != 1) {
         	return false;
      	}
   	}   
   	return true;
}

BigIntBase* BigInt::euclidExtended(int a, int b) {
	BigIntBase temp;
   	BigIntBase A = BigIntBase(a);
   	BigIntBase B = BigIntBase(b);
   
   	if(B > A) { 
      	temp = A;
      	A = B;
      	B = temp;
   	}

   	BigIntBase x = BigIntBase(0);
   	BigIntBase y = BigIntBase(1);
   	BigIntBase xRes = BigIntBase(1);
   	BigIntBase yRes = BigIntBase(0);

   	while (B != 0) {
      	BigIntBase quotRes = A / B;
      	temp = A % B;
      	A = B;
      	B = temp;
      	temp = x;
      	x = xRes - quotRes * x;
      	xRes = temp;
      	temp = y;
      	y = yRes - quotRes * y;
      	yRes = temp;
   	}

   	BigIntBase tempA = BigIntBase(a);
   	yRes = yRes < 0 ? tempA + yRes : yRes; // if y < 0, make it positive

   	BigIntBase *ret = new BigIntBase[2];
   	ret[0] = xRes;
   	ret[1] = yRes;
   
   	return ret;
}

void BigInt::modInverse(BigIntBase p, BigIntBase e, BigIntBase pn) {
    BigIntBase q,temp;
    BigIntBase x = BigIntBase(0);
    BigIntBase y = BigIntBase(1);
    BigIntBase lastx = BigIntBase(1);
    BigIntBase lasty = BigIntBase(0);
    
    if (e > p) { 
        temp = p;
        p = e;
        e = temp;
    }

    while (e != 0) {
        q = p / e;
        temp = p % e;
        p = e;
        e = temp;
        temp = x;
        x = lastx - q * x;
        lastx = temp;
        temp = y;
        y = lasty - q * y;
        lasty = temp;
    }
    lastx = lastx < 0 ? pn + lastx : lastx;
    
    cout << lasty << ", " << lastx << endl;
}

string BigInt::encrypt(int e, string n, string m) {
	const int partialSize = 3;
	const int partialCount = m.length() / partialSize;
	int *ascii = new int[partialCount];
	stringstream cypherText;
	for(int i = 0; i < m.length(); i++) {
		ascii[i] = m[i];
		BigInt base = BigInt(ascii[i]);
		BigInt exponent = BigInt(e);
		BigInt mod = BigInt(n);
		BigIntBase encrypted = BigInt::modExp(base, exponent, mod); 
		cypherText << encrypted;
	}
	return cypherText.str();
}

string BigInt::decrypt(int d, string n, string em) {
	//TODO: implement...
	return "Your original encrpted message should show up here decrypted. Oops.";
}












