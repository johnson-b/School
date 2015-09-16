/*##############################
  # written by a UA student.   #
  # all rights are reserved.   # 
  ##############################*/
  
#ifndef BIGINTBASE_H
#define	BIGINTBASE_H

#include <algorithm>
#include <iostream>
#include <list>
#include <stdexcept>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <sstream>

using namespace std;

typedef unsigned char uchar;
typedef list<uchar> IntList;

class BigIntBase {
private:
   IntList intAsList;
   bool isPositive;
public:
   BigIntBase();
   BigIntBase(string const&);
   BigIntBase(IntList const&, bool isPositive);
   BigIntBase(int);
   
   int getLength() const;
   //bool isPrime();
   
   static BigIntBase random(int const& digits);
   //static BigIntBase randomOdd(int const& digits);
   static BigIntBase randomPrime(int const& digits);
   static BigIntBase modExp(BigIntBase const& base, BigIntBase exponent, BigIntBase const& mod);
   static bool fermatTest(BigIntBase value, int iterations);
   
   friend ostream& operator<<(ostream& stream, BigIntBase const& num);
   friend ostream& operator<<(ostream& stream, int const& num);
   
   bool operator<(BigIntBase const& thatNum) const;
   bool operator<(int const& thatNum) const;
   bool operator>(BigIntBase const& thatNum) const;
   bool operator>(int const& thatNum) const;
   bool operator<=(BigIntBase const& thatNum) const;
   bool operator<=(int const& thatNum) const;
   bool operator>=(BigIntBase const& thatNum) const;
   bool operator>=(int const& thatNum) const;
   bool operator==(BigIntBase const& thatNum) const;
   bool operator==(int const& thatNum) const;
   bool operator!=(BigIntBase const& thatNum) const;
   bool operator!=(int const& thatNum) const;
   BigIntBase operator+(BigIntBase const& thatNum) const;
   BigIntBase operator+(int const& thatNum) const;
   BigIntBase operator-(BigIntBase const& thatNum) const;
   BigIntBase operator-(int const& thatNum) const;
   BigIntBase operator-() const;
   BigIntBase operator%(BigIntBase const& mod) const;
   BigIntBase operator%(int const& mod) const;
   BigIntBase operator*(BigIntBase const& thatNum) const;
   BigIntBase operator*(int const& thatNum) const;
   BigIntBase operator/(BigIntBase const& thatNum) const;
   BigIntBase operator/(int const& thatNum) const;
   BigIntBase half();
   
private:
   void borrow(IntList::reverse_iterator place) const;
   //bool fermatTest(int);  
};

#endif
