#ifndef BIGINT_H
#define	BIGINT_H

#include "BigIntBase.h"
#include <list>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <sstream>

typedef list<uchar> IntList;

class BigInt : public BigIntBase {
public:
	BigInt();
   	BigInt(string const&);
   	BigInt(IntList const&, bool isPositive);
   	BigInt(int);
   	static BigInt random(int const& digits);
   	static BigIntBase randomPrime(int const& digits);
   	static BigIntBase modExp(BigIntBase const& base, BigIntBase exponent, BigIntBase const& mod);
   	static bool fermatTest(BigIntBase value, int iterations);
   	static BigIntBase* euclidExtended(int a, int b);
   	static void modInverse(BigIntBase phen, BigIntBase ee, BigIntBase phenNeg);
   	static string encrypt(int e, string n, string m);
   	static string decrypt(int d, string n, string em);
};

#endif