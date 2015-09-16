/*##############################
  # written by a UA student.   #
  # all rights are reserved.   # 
  ##############################*/

#include "BigIntBase.h"
using namespace std;

BigIntBase::BigIntBase() {
   intAsList.clear();
   isPositive = true;
}
BigIntBase::BigIntBase(string const& num) {
   int start = 0;
   isPositive = true;
   if (num[0]=='-') {
      ++start;
      isPositive = false;
   }
   int end = (int)num.length();
   while(num[start]=='0') {
      // Remove leading zeros
      ++start;
   }
   for(int i=start; i<end; ++i) {
      intAsList.push_back(num[i]-'0');
   }
   if (intAsList.empty()) {
      // If all zeros were removed, or empty string, int will be 0
      intAsList.push_back(0);
      isPositive = true;
   }
}
BigIntBase::BigIntBase(IntList const& num, bool isPositive) {
   intAsList = num;
   this->isPositive = isPositive;
}
BigIntBase::BigIntBase(int num) {
   isPositive = true;
   if (num<0) {
      isPositive = false;
      num = -num;
   };
   bool isNumZero = false;
   while(!isNumZero) {
      intAsList.push_front(num%10);
      num /= 10;
      if(num == 0) {
         isNumZero = true;
      }
   }
}

int BigIntBase::getLength() const {
   return (int)this->intAsList.size();
} 

BigIntBase BigIntBase::modExp(BigIntBase const& base, BigIntBase exp, BigIntBase const& mod){
   // calculates (base^exp) % mod
   if (exp < 0) {
      throw new invalid_argument("Exponent may not be negative in modExp");
   }
   if (exp == 0) {
      return 1;
   }
   BigIntBase temp = modExp(base, exp.half(), mod);
   if (exp%2 == 0) {
      return (temp*temp)%mod;
   } 
   else {
      return (((temp*temp)%mod)*base)%mod;
   }
}

ostream& operator<<(ostream& stream, BigIntBase const& num) {
   IntList::const_iterator it;
   if(!num.isPositive) {
      stream << '-';
   }
   for(it=num.intAsList.begin(); it!=num.intAsList.end(); ++it) {
      stream << (uchar)(*it+'0');
   }
   return stream;
}
ostream& operator<<(ostream& stream, int const& num) {
   return operator<<(stream, BigIntBase(num));
}
bool BigIntBase::operator<(BigIntBase const& thatNum) const {
   if (this->isPositive && !thatNum.isPositive) {
      return false;
   }
   if (!this->isPositive && thatNum.isPositive) {
      return true;
   }
   if (!this->isPositive && !thatNum.isPositive) {
      BigIntBase copy = thatNum;
      return -(*this) > -copy;
   }
   
   int digits = (int)this->intAsList.size();
   if(digits < thatNum.intAsList.size()) {
      return true;
   } 
   if(digits > thatNum.intAsList.size()) {
      return false;
   }
   IntList::const_iterator thisIter = this->intAsList.begin();
   IntList::const_iterator thatIter = thatNum.intAsList.begin();
   for(int i = 0; i<digits; ++i) {
      if(*(thisIter) < *(thatIter)) {
         return true;
      } 
      else if(*(thisIter) > *(thatIter)) {
         return false;
      }
      ++thisIter; ++thatIter;
   }
   return false;
}
bool BigIntBase::operator<(int const& thatNum) const {
   return (*this)<(BigIntBase(thatNum));
}
bool BigIntBase::operator>(BigIntBase const& thatNum) const {
   return thatNum<(*this);
}
bool BigIntBase::operator>(int const& thatNum) const {
   return (*this)>(BigIntBase(thatNum));
}
bool BigIntBase::operator<=(BigIntBase const& thatNum) const {
   return !((*this)>thatNum);
}
bool BigIntBase::operator<=(int const& thatNum) const {
   return (*this)<=(BigIntBase(thatNum));
}
bool BigIntBase::operator>=(BigIntBase const& thatNum) const {
   return !((*this)<(thatNum));
}
bool BigIntBase::operator>=(int const& thatNum) const {
   return (*this)>=(BigIntBase(thatNum));
}
bool BigIntBase::operator==(BigIntBase const& thatNum) const {
   if( (this->isPositive && !thatNum.isPositive) || 
      (!this->isPositive && thatNum.isPositive)) {
      return false;
   }
   int digits = (int)this->intAsList.size();
   if(digits != thatNum.intAsList.size()) {
      return false;
   }
   IntList::const_iterator thisIter = this->intAsList.begin();
   IntList::const_iterator thatIter = thatNum.intAsList.begin();
   for(int i = 0; i<digits; ++i) {
      if(*(thisIter) != *(thatIter)) {
         return false;
      }
      ++thisIter; ++thatIter;
   }
   return true;
}
bool BigIntBase::operator==(int const& thatNum) const {
   return (*this)==(BigIntBase(thatNum));
}
bool BigIntBase::operator!=(BigIntBase const& thatNum) const {
   return !((*this)==(thatNum));
}
bool BigIntBase::operator!=(int const& thatNum) const {
   return (*this)!=(BigIntBase(thatNum));
}
BigIntBase BigIntBase::operator+(BigIntBase const& thatNum) const {
// gradeschool addition algorithm with carrying
   if( this->isPositive && !thatNum.isPositive) {
      return (*this)-(-thatNum);
   }
   if (!this->isPositive && thatNum.isPositive) {
      return thatNum-(-(*this));
   }
   bool resultIsPositive = this->isPositive;
   int thisDigits = (int)this->intAsList.size();
   int thatDigits = (int)thatNum.intAsList.size();
   int maxDigits = max(thisDigits, thatDigits);
   IntList result;
   uchar carry = 0;
   uchar thisPlace;
   uchar thatPlace;
   uchar sum;
   IntList::const_reverse_iterator thisIter = this->intAsList.rbegin();
   IntList::const_reverse_iterator thatIter = thatNum.intAsList.rbegin();
   for (int i=0; i<maxDigits; i++) {
      if (i<thisDigits) {
         thisPlace = *(thisIter);
         ++thisIter;
      } 
      else {
         thisPlace = 0;
      }
      if (i<thatDigits) {
         thatPlace = *(thatIter);
         ++thatIter;
      } 
      else {
         thatPlace = 0;
      }
      sum = thisPlace+thatPlace+carry;
      result.push_front(sum%10);
      carry = sum/10;
   }
   if (carry > 0) {
      result.push_front(carry);
   }
   return BigIntBase(result, resultIsPositive);
}
BigIntBase BigIntBase::operator+(int const& thatNum) const {
   return (*this)+(BigIntBase(thatNum));
}
BigIntBase BigIntBase::operator-(BigIntBase const& thatNum) const {
// gradeschool subtractioin algorithm with borrowing
   if ((*this)==(thatNum)) {
      return 0;
   }
   if (!this->isPositive && !thatNum.isPositive) {
      return (-thatNum)-(-*this);
   }
   if (this->isPositive && !thatNum.isPositive) {
      return (*this)+(-thatNum);
   }
   if (!this->isPositive && thatNum.isPositive) {
      return (*this)+(-thatNum);
   }
   
   // both numbers should be positive by this point
   if (thatNum > *this) {
      return -(thatNum-(*this));
   }
   bool resultIsPositive = true;
   int thisDigits = (int)this->intAsList.size();
   int thatDigits = (int)thatNum.intAsList.size();
   IntList thisNum = this->intAsList;
   IntList result;
   IntList::reverse_iterator thisIter = thisNum.rbegin();
   IntList::const_reverse_iterator thatIter = thatNum.intAsList.rbegin();
   uchar thisPlace, thatPlace, difference;
   
   for (int i=0; i<thisDigits; ++i) {
      thisPlace = *(thisIter);
      ++thisIter;
      if (i<thatDigits) {
         thatPlace = *(thatIter);
         ++thatIter;
      } 
      else {
         thatPlace = 0;
      }
      if (thisPlace >= thatPlace) {
         difference = thisPlace-thatPlace;
      } 
      else {
         difference = (10+thisPlace)-thatPlace;
         borrow(thisIter);
      }
      result.push_front(difference);
   }
   // remove 0's from front of resulting number
   while (result.front() == 0) {
      result.pop_front();
   }
   return BigIntBase(result, resultIsPositive);
}
BigIntBase BigIntBase::operator-(int const& thatNum) const {
   return (*this)-(BigIntBase(thatNum));
}
BigIntBase BigIntBase::operator-() const {
   return BigIntBase(this->intAsList, !this->isPositive);
}
BigIntBase BigIntBase::operator%(BigIntBase const& mod) const {
// a binary search guess/check algorithm for modulus
   if (!this->isPositive || !mod.isPositive) {
      throw new invalid_argument("Mod of negative integers not implemented.");
   }
   if (*this < mod) {
      return *this;
   }
   BigIntBase multiplier = 0;
   BigIntBase start = 0; 
   BigIntBase end = *this;
   while(start < end){
      multiplier = (start+end).half();
      if(*this >= (multiplier+1)*mod) {
         start = multiplier+1;
      } 
      else {
         end = multiplier;
      }
   }
   return (*this)-(end*mod);
}
BigIntBase BigIntBase::operator%(int const& mod) const {
   return (*this)%(BigIntBase(mod));
}
BigIntBase BigIntBase::operator*(BigIntBase const& thatNum) const {
// standard gradeschool multiplication algorithm
   if (thatNum == 0 || *this == 0) {
      return 0;
   }
   BigIntBase result = 0;
   BigIntBase multResult;
   IntList::const_reverse_iterator thisIter;
   IntList::const_reverse_iterator thatIter = thatNum.intAsList.rbegin();
   uchar carry;
   uchar product;
   for (int i=0; i<thatNum.intAsList.size(); ++i) {
      carry = 0;
      multResult.intAsList.clear();
      thisIter = intAsList.rbegin();
      for (int j=0; j<intAsList.size(); ++j) {
         product = (*thisIter) * (*thatIter) + carry;
         multResult.intAsList.push_front(product%10);
         carry = product/10;
         ++thisIter;
      }
      if (carry>0) {
         multResult.intAsList.push_front(carry);
      }
      for (int k=0; k<i; ++k) {
         multResult.intAsList.push_back(0);
      }
      result = result + multResult;
      ++thatIter;
   }
   if( (this->isPositive && !thatNum.isPositive) || 
      (!this->isPositive && thatNum.isPositive)) {
      result.isPositive = false;
   }
   return result;
}
BigIntBase BigIntBase::operator*(int const& thatNum) const {
   return (*this)*(BigIntBase(thatNum));
}
BigIntBase BigIntBase::operator/(BigIntBase const& thatNum) const {
/*  Returns quotient of division using a guess/check binary-
   search type algorithm. */
   if(thatNum == 0) {
      throw new invalid_argument("Division by 0.");
   } 
   if(*this == 0) {
      return *this;
   }
   if (!this->isPositive && !thatNum.isPositive) {
      return (-(*this))/(-thatNum);
   } 
   else if (!this->isPositive) {
      return -((-(*this))/thatNum);
   } 
   else if (!thatNum.isPositive) {
      return -((*this)/(-thatNum));
   }
   // both numbers should be positive at this point
   if (thatNum>(*this)) {
      return 0;
   }
   BigIntBase remainder = (*this)%thatNum;
   BigIntBase numToDivide = (*this)-remainder;
   BigIntBase result = 0;
   BigIntBase start = 0;
   BigIntBase end = *this;
   while(start < end){
      result = (start+end).half();
      if(numToDivide > result*thatNum) {
         start = result+1;
      } 
      else {
         end = result;
      }
   }
   return end;
}
BigIntBase BigIntBase::operator/(int const& thatNum) const {
   return (*this)/(BigIntBase(thatNum));
}
BigIntBase BigIntBase::half() {
/*  Halves an integer by checking the next digit.
   A zero is attached to the front of the BigIntBase for the algorithm
   to work.
   If the current digit is even, resulting digit is next/2.
   If the current digit is odd, resulting digit is next/2 + 5. */

   this->intAsList.push_front(0);
   BigIntBase result;
   result.isPositive = this->isPositive;
   IntList::const_iterator iter = this->intAsList.begin();
   IntList::const_iterator next = ++this->intAsList.begin();
   IntList::const_iterator end = this->intAsList.end();
   while(next!=end) {
      if((*iter)%2 == 0) {
         result.intAsList.push_back((*next)/2);
      }
      else {
         result.intAsList.push_back((*next)/2+5);
      }
      ++iter; ++next;
   }
   this->intAsList.pop_front();
   while(result.intAsList.front()==0) {
      result.intAsList.pop_front();
   }
   if(result.intAsList.empty()) {
      return 0;
   }
   return result;
}
void BigIntBase::borrow(IntList::reverse_iterator place) const {
// for subtraction, borrows from iterator at place
   if (*place == 0) {
      *place = 9;
      borrow(++place);
   } 
   else {
      --(*place);
   }
}

BigIntBase BigIntBase::random(int const& digits) {
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
   return BigIntBase(stringStream.str());
}

BigIntBase BigIntBase::randomPrime(int const& digits) {
   srand(time(NULL));
   BigIntBase value = BigIntBase::random(digits);
   
   if(value % 2 == 0) {
      value = value + 1;
   }

   while(!BigIntBase::fermatTest(value, 3)) {
      value = value + 2;
   }

   // while(true) {
      


      // for(int i = 0; i < 3; i++) {
      //    BigIntBase a = BigIntBase(2 + i * 2);
      //    if(BigIntBase::modExp(a, value - 1, value) != 1) {
      //       value = value + 2;
      //       break;
      //    }
      //    prime = true;
      // }
   // }
   return value;
}

bool BigIntBase::fermatTest(BigIntBase value, int iterations) {
   if(value == 1 ||
      value == 2) {
      return true;
   }

   for(int i = 0; i < iterations; i++) {
      BigIntBase a = BigIntBase(2 + i * 2);
      if(BigIntBase::modExp(a, value - 1, value) != 1) {
         return false;
      }
   }   
   return true;
}

// bool Fermat(ll p, int iterations)
// {
//     if (p == 1)
//     {
//         return false;
//     }
//     for (int i = 0; i < iterations; i++)
//     {
//         ll a = rand() % (p - 1) + 1; 
//         if (modulo(a, p - 1, p) != 1)
//         { 
//             return false;
//         }
//     }
//     return true;
// }

////*****************************************
////*****************************************
////*** testing..............................
//void br() {
//   cout << "------------------------------------------------------------\n";
//}
//void constructionTests() {
//   br();
//   cout << "Construction Tests\n";
//   br();
//   string bigNum = "00123456789123456789123456789123456789";
//   cout << BigIntBase(bigNum) << " should equal\n" << 
//      "123456789123456789123456789123456789\n";
//   BigIntBase c = BigIntBase(-5);
//   cout << BigIntBase("0")<< " should output 0\n";
//   cout << BigIntBase(1)<< " should output 1\n";
//   cout << BigIntBase("-1234")<< " should output -1234\n";
//   cout << BigIntBase(-1234)<< " should output -1234\n"; 
//   cout << c << " should output -5\n";
//   IntList v1; v1.push_back(5); v1.push_back(1); v1.push_back(9);
//   cout << BigIntBase(v1,false) << " should output -519\n";
//}
//void comparisonTests() {
//   br();
//   cout << "Comparison Tests\n";
//   br();
//   BigIntBase n1 = BigIntBase(1859);
//   BigIntBase n2 = BigIntBase(1958);
//   BigIntBase n3 = n2;
//   BigIntBase n4 = -1958;
//   BigIntBase n5 = -1859;
//   BigIntBase n6 = 0;
//   cout << n2 << " == " << n3 << ": " << (n2==n3) <<", " << true << endl;
//   cout << n2 << " <= " << n3 << ": " << (n2<=n3) <<", " << true << endl;
//   cout << n1 << " < " << n2 << ": " << (n1<n2) <<", " <<  true << endl;
//   cout << n2 << " > " << n1 << ": " << (n2>n1) <<", " <<  true <<endl;
//   cout << n2 << " >= " << n1 << ": " << (n2>=n1) <<", " <<  true << endl;
//   cout << n2 << " > " << n4 << ": " << (n2>n4) <<", " <<  true <<endl;
//   cout << n4 << " < " << n2 << ": " << (n4<n2) <<", " <<  true <<endl;    
//   cout << n4 << " < " << n5 << ": " << (n4<n2) <<", " <<  true <<endl;
//   cout << n5 << " >= " << n4 << ": " << (n5>=n4) <<", " <<  true <<endl;
//}
//void additionSubtractionTests() {
//   br();
//   cout << "Addition/Subtraction Tests\n";
//   br();
//   BigIntBase c = BigIntBase(100);
//   BigIntBase one = BigIntBase(1);
//   cout << c << " - " << c << " = " << c-c << " ? Should be 0\n";
//   cout << c << " - " << -c << " = " << c-(-c) << " ? Should be 200\n";
//   cout << -c << " - " << -c << " = " << -c-(-c) << " ? Should be 0\n";
//   cout << -c << " + " << -c << " = " << -c+(-c) << " ? Should be -200\n";
//   cout << one << " - " << c << " = " << one-c << " ? Should be -99\n";
//   cout << -one << " - " << c << " = " << -one-c << " ? Should be -101\n";
//   cout << c << " - " << one << " = " << c-one << " ? Should be 99\n";
//   BigIntBase n1("-6579874651321");
//   BigIntBase n2("456465654");
//   BigIntBase n3 = n1+n2;
//   cout << n1 << " + " << n2 << " = " << n1+n2
//      << " ? Should be -6579418185667\n";
//   cout << n2 << " + " << n1 << " = " << n2+n1
//      << " ? Should be -6579418185667\n";
//   cout << n2 << " - " << n1 << " = " << n2-n1
//      << " ? Should be 6580331116975\n";
//   cout << n1 << " - " << n2 << " = " << n1-n2
//      << " ? Should be -6580331116975\n";
//}
//void multModTests() {
//   br();
//   cout << "Multiplication/Mod Tests\n";
//   br();
//   BigIntBase n10(123456789);
//   BigIntBase n11(18237);
//   
//   cout << n10 << " * " << -n11 << " = "<< n10*(-n11) << "? Should equal" 
//      << "-2251481460993" << endl;
//   cout << "0" << " * " << "-1" <<  " = " << BigIntBase(0)*BigIntBase(-1)
//      << "? Should equal 0\n";
//   
//   cout << n10 << "%" << n11 << " = " << n10%n11 
//      << " and should equal " << "123456789%18237=10536" << endl;
//   cout << n10 << "%2 = " << n10%2 << " and should equal 1"<< endl;
//   cout << "2%2 = " << BigIntBase(2)%BigIntBase(2) << endl;
//   cout << "4%2 = " << BigIntBase(4)%2 << endl;
//
//   BigIntBase n12(367564621);
//   cout << n12.half() << " is half of " << n12 << endl;
//   cout << (-n12).half() << " is half of " << -n12 << endl;
//   cout << BigIntBase(1).half() << " is half of 1\n";
//
//}
//void modExpTests() {
//   br();
//   cout << "Modular Exponentiation Tests\n";
//   br();
//   cout << "modExp(2,4,5) = " << BigIntBase::modExp(2,4,5) << "? Should equal 1\n";
//}
//void divisionTests() {
//   br();
//   cout << "Division Tests\n";
//   br();
//   cout << BigIntBase(195)/BigIntBase(3) << " should be 65\n";
//   cout << BigIntBase(-195)/BigIntBase(3) << " should be -65\n";
//   cout << BigIntBase(195)/BigIntBase(-3) << " should be -65\n";
//   cout << BigIntBase(-195)/BigIntBase(-3) << " should be 65\n";
//   cout << BigIntBase("168849879")/BigIntBase("98794613254") << " should be 0\n";
//   cout << BigIntBase("98794613254")/BigIntBase("168849879") << " should be 585\n";
//}
//void BigIntBaseTests() {
//   constructionTests();
//   comparisonTests();
//   additionSubtractionTests();
//   multModTests();
//   divisionTests();
//}
//
//int main(int argc, char *argv[]) {
//   BigIntBaseTests();    
//   return 0;
//}
