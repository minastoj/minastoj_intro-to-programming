#include "bigint.h"
#include <iostream>
#include <string>
#include <climits>
#include <cmath>
#include <algorithm>
using namespace std;

//******************************************************************
//START OF THE CONSTRUCTORS SECTION
//******************************************************************

/*
// Create a default BigInt with base 10.
// This function is complete. You do not have to add anything.
*/
BigInt::BigInt(){
  base = 10;
  isPositive = true;
}

/*
// Create a BigInt with a specified base.
// This function is complete. You do not have to add anything.
*/
BigInt::BigInt(int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    base = setbase;
    isPositive = true;
}

/*
// Destructure. You do not have to add anything.
// This function is complete
*/
BigInt::~BigInt(){}

/*
//  Create a BigInt from int (base 10).
//  - Convert the int (base 10) input into a specified base (setbase).
//  - Don't forget to set the base accordingly
//  For example:
//     BigInt k(6,2) <- int 6 base 10 to BigInt base 2
//          - Result:  BigInt k with value 110 (base 2)
//     BigInt k(154,16) <- 154 base 10 to BigInt base 16
//          - Result: BigInt k with value 9A (base 16)
*/
BigInt::BigInt(int input,int setbase){
  if(setbase < 2 || setbase > 36){
      throw InvalidBaseException();
  }
  /************* You complete *************/
  if(input == 0)
  {
    base = setbase;
    isPositive = true;
    vec.push_back(0);
  }
  else // input != 0, is positive or negative
  {
    base = setbase; // sets base to the passed in base
    
    if(input > 0) // input is positive
    {
      isPositive = true; // makes the number positive
    }
    else // input is negative
    {
      input *= -1; // make input positive
      isPositive = false; // makes the number negative
    }

    // loop to add ints to vec
    while((input / base) >= 0)
    {
      if(input == 0) break;
      
      vec.push_back(input % base);
      input /= base;
    }
  }
}

/*
//  Create a BigInt from string.
//  Don't forget to set the base accordingly
//  The input string will contain
//      - numbers (0-9) and/or 
//      - uppercase letters (A-Z) [A=10, B=11, ... , Z=35]
//  The input string may contain
//      - a negative sign ('-') to signify that the number is negative.
//  Note: char '0' = int 48 (see ASCII table)
//  Note: char 'A' = int 65
*/
BigInt::BigInt(const string &s, int setbase){
  if(setbase < 2 || setbase > 36){
      throw InvalidBaseException();
  }
  
  /************* You complete *************/
  // set to negative if the first thing is a negative symbol
  // if not, set to positive  
  base = setbase;
  isPositive = true;
  int index = 0;
  
  if(s[0] == '-')
  {
    isPositive = false;
    index = 1;
  } 
  //for(int i = index; i < (int)s.length(); i++)
  for(int i = (int)s.length(); i >= index; i--)
  {
    if(s[i] >= 48 && s[i] <= 57) // checks that the char is an int
    {
      // pushes back an int from ASCII table via subtraction
      vec.push_back((int)s[i] - 48);
    }
    else if(s[i] >= 65 && s[i] <= 90) // it is a letter, not an int
    {
      vec.push_back((int)s[i] - 55);
    }
  }
}

/*
//  Create a BigInt from another BigInt.
//  This is a copy constructor.
//  Simply call the assignment operator (=) below.
*/
BigInt::BigInt(const BigInt &b){
  /************* You complete *************/
  *this = b;
}

/*
//  Assignment operator. (i.e., BigInt a = b;)
//  Overriding a's data with BigInt b's data
//       - vec
//       - isPositive
//       - base
*/
BigInt & BigInt::operator = (const BigInt &b){
  /************* You complete *************/
  isPositive = b.isPositive;
  base = b.base;
  vec = b.vec;
  return *this;
}


//******************************************************************
//END OF THE CONSTRUCTORS SECTION
//******************************************************************

//******************************************************************
//START OF THE DISPLAYS SECTION
//******************************************************************

/*
// Convert to string and return the string
// Display it in its corresponding base
//  Note: char '0' = int 48 (see the ASCII table)
//  Note: char 'A' = int 65
*/
string BigInt::to_string(){
  /************* You complete *************/
  string result = "";
  
  if(isPositive == false)
  {
    result += '-'; // add a negative if it's negative
  }
  
  for(int i = vec.size() - 1; i >= 0; i--) // loop backwards
  {
    // if it's < 10, simply add 48
    if(vec[i] < 10)
    {
      result += (char)(vec[i] + 48);
    }
    // else it is >= 10, add 55 to use letters
    else result += (char)(vec[i] + 55);
  }
  return result;
}

/*
//  Convert BigInt to integer base 10 and return that int
//    If BigInt >= INT_MAX, return INT_MAX.
//    If BigInt =< INT_MIN, return INT_MIN.
//  Note: 1. INT_MAX and INT_MIN are already defined for you
//           in the 'climits' library.
//        2. INT_MAX = 2147483647, INT_MIN = -2147483648
//           therefore, INT_MIN does not equal to (-INT_MAX)
*/
int BigInt::to_int() const{
  /************* You complete *************/
  int result = 0, power = 0;
  
  for(int i = 0; i <= (int)vec.size() - 1; i++)
  {
    if(isPositive)
    {
      result +=(vec[i] * pow(base, power));
    }
    else if(!isPositive)
    {
      result -= (vec[i] * pow(base, power));
      
      if(result <= INT_MIN)
      {
        return INT_MIN;
      }
    } 
    power++;
  }
   
  if(result <= INT_MIN)
  {
    return INT_MAX;
  }
  
  return result;
}

//******************************************************************
//END OF THE DISPLAYS SECTION
//******************************************************************

//******************************************************************
//START OF THE EQUALITY CHECK OPERATORS SECTION
//******************************************************************

/*
//  Compare a and b.
//     If a = b, return 0.
//     If a < b, return -1.
//     If a > b, return 1.
//  See the HINT below
*/
int BigInt::compare(const BigInt &b) const{
  if(base != b.base){
      throw DiffBaseException();
  }
  /************* You complete *************/

  //HINT:
  //1. do NOT call the to_int() or to_string() function
  //2. do NOT convert bigInt to other datatypes first (e.g., long long, int)

  //First let's compare the signs
  //    - if the signs aren't the same,
  //              how do you know which one is larger?

  //If they have the same sign, let's compare their vec sizes 
  //    - what if both are positive, but a's vec is larger (a or b is larger?)
  //    - other cases?

  //If they have the same vec size, let's compare their digits one by one
  // Starting from the most-significant digits. --> in what vector position?
  // Remember that the BigInt vectors are in reverse order!
  //    - what if both are positive, but the digit of a is greater than that of b (a or b is larger?)
  //    - other cases?

  //If ALL digits are the same, then they MUST be equal!!
  
  if(isPositive && !b.isPositive) return 1; // a > b
  else if(!isPositive && b.isPositive) return -1; // a < b
  else if(isPositive && b.isPositive) // a and b are both positive
  {
    if(vec.size() > b.vec.size()) return 1; // a > b
    else if(vec.size() < b.vec.size()) return -1; // a < b
    else // loop through digits
    {
      for(int i = (int)vec.size() - 1; i >= 0; i--)
      {
        if(vec[i] > b.vec[i]) return 1;
        else if(vec[i] < b.vec[i]) return -1;
      }
      return 0;
    }
  }
  else if(!isPositive && !b.isPositive)// a and b are both negative
  {
    if(vec.size() > b.vec.size()) return -1; // a < b
    else if(vec.size() < b.vec.size()) return 1; // a > b
    else // loop through digits
    {
      for(int i = (int)vec.size() - 1; i >= 0; i--)
      {
        if(vec[i] > b.vec[i]) return -1;
        else if(vec[i] < b.vec[i]) return 1;
      }
      return 0;
    }
  }
  return 0;
}

//Call the compare function above to check if a == b
bool operator == (const BigInt &a, const BigInt &b){
  
  /************* You complete *************/
  // returning 0 from compare means they're the same
  if(a.compare(b) == 0) return true;
  return false;
}

//Call the compare function above to check if a != b
bool operator != (const BigInt &a, const BigInt &b){
  
  /************* You complete *************/
  // returning anything but 0 means they're not the same
  if(a.compare(b) != 0) return true;
  return false;
}

//Call the compare function above to check if a <= b
bool operator <= (const BigInt &a, const BigInt &b){
  
  /************* You complete *************/
  // -1 means a < b and 0 means a = b
  if(a.compare(b) == -1 || a.compare(b) == 0) return true;
  return false;
}

//Call the compare function above to check if a >= b
bool operator >= (const BigInt &a, const BigInt &b){
  
  /************* You complete *************/
  // 1 means a > b and 0 means a = b
  if(a.compare(b) == 1 || a.compare(b) == 0) return true;
  return false;
}

//Call the compare function above to check if a > b
bool operator > (const BigInt &a, const BigInt &b){
  
  /************* You complete *************/
  // 1 means a > b
  if(a.compare(b) == 1) return true;
  return false;
}

//Call the compare function above to check if a < b
bool operator < (const BigInt &a, const BigInt &b){
  
  /************* You complete *************/
  // -1 means a < b
  if(a.compare(b) == -1) return true;
  return false;
}

//******************************************************************
//END OF THE EQUALITY CHECK OPERATORS SECTION
//******************************************************************

//******************************************************************
//START OF THE ARITHMETIC OPERATORS SECTION
//******************************************************************

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call += operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator + (const  BigInt &a, const BigInt & b){

  /************* You complete *************/
  BigInt c = a;
  c += b;
  return c;
}

/*
//==================
// MEMBER function
//==================
//  Addition assignment operator.
//    i.e., a += b
*/
const BigInt & BigInt::operator += (const BigInt &b){
  if(base != b.base){
      throw DiffBaseException();
  }
  /************* You complete *************/
  int carry = 0, a_val = 0, b_val = 0;
  
  // vectors are the same, but signs are different
  if(vec == b.vec && ((isPositive && !b.isPositive) || (!isPositive && b.isPositive)))
  {
    isPositive = true;
    vector<int> temp;
    temp.push_back(0);
    vec = temp;
    return *this;
  }
  // a is positive and b is negative
  else if(isPositive && !b.isPositive)
  {
    // works exactly like a = a - b
    BigInt c = b; // make a copy of b
    c.isPositive = true; // copy of b is positive
    *this = *this - c; // a = a(pos) - b(pos)
    return *this;
  }
  // a is negative and b is positive
  else if(!isPositive && b.isPositive)
  {
    // works exactly like a = b - a
    isPositive = true; // make a positive
    *this = b - *this; // a = b(pos) - a(pos)
    return *this;
  }
  else // both have the same sign
  {
    if(!isPositive && !b.isPositive) // if both negative, just set it to negative
    {
        isPositive = false;
    }
    else isPositive = true;
    
    // the actual addition
    for(int i = 0; i < max((int)vec.size(), (int)b.vec.size()); i++)
    {
      if(i < (int)vec.size() && i < (int)b.vec.size()) // vecs are long enough
      {
        a_val = vec[i];
        b_val = b.vec[i];
      }
      else if(i >= (int)vec.size() && i < (int)b.vec.size()) // a is too short
      {
        a_val = 0;
        b_val = b.vec[i];
      }
      else if(i < (int)vec.size() && i >= (int)b.vec.size()) // b is too short
      {
        a_val = vec[i];
        b_val = 0;
      }

      int column_val = (a_val + b_val + carry) % base;
      carry = (a_val + b_val + carry) / base;
      if(i >= (int)vec.size())
      {
        vec.push_back(column_val);
      }
      else vec[i] = column_val;
    }

    // if carry has a leftover value, add it to a new colum
    if (carry > 0) 
    {
      vec.push_back(carry);
    }
  }
  
  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call -= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator - (const  BigInt &a, const BigInt & b){

  /************* You complete *************/
  BigInt c = a;
  c -= b;
  return c;
}

/*
//==================
// MEMBER function
//==================
//  Subtraction assignment operator.
//    i.e., a -= b
//  Note: Think of base cases (e.g., subtract by itself)
*/
const BigInt & BigInt::operator -= (const BigInt &b){
  if(base != b.base){
      throw DiffBaseException();
  }
  /************* You complete *************/
  // first passed in thing is the top
  // second passed in thing is the bottom
  BigInt top = *this, bottom = b;
  int top_val = 0, bottom_val = 0, diff = 0;
  
  // if they are the same number, simply return 0
  if(this->compare(b) == 0)
  {
    isPositive = true;
    vector<int> temp;
    temp.push_back(0); // fill temp with one 0
    vec = temp;
    return *this;
  }
  
  // a is positive and b is positive
  if(isPositive && b.isPositive)
  {
    if(b > *this) // check if b > a
    {
      // do subtraction with b on top but set it to a
      top = b;
      bottom = *this;
      isPositive = false; // result will be negative
    }
    // if a >= b, result will be positive
    else
    {
      isPositive = true; // result will be positive
    }
  }
  // a is negative and b is negative
  else if(!isPositive && !b.isPositive)
  {
    if(b < *this) // |b| > |a| AKA b < a
    {
      // do subtraction with b on top but set it to a
      top = b;
      bottom = *this;
      isPositive = true; // result will be positive
    }
    else
    {
      isPositive = false; // result will be negative
    }
  }
  // a is positive and b is negative
  else if(isPositive && !b.isPositive)
  {
    // (pos)a - (neg)b = (pos)a + (pos)b
    BigInt c = b; // make a copy of b
    c.isPositive = true; // make c positive
    *this += c; // equivalent to a = a + b
    return *this;
  }
  // a is negative and b is positive
  else if(!isPositive && b.isPositive)
  { 
    BigInt c = b; // make a copy of b
    c.isPositive = false; // make c negative
    *this += c; // equivalent to a = a(neg) - b
    return *this;
  }
  
  int borrow = 0;
  for(int i = 0; i < (int)top.vec.size(); i++)
  {
    // there are values for both vectors
    if(i < (int)top.vec.size() && i < (int)bottom.vec.size())
    {
      top_val = top.vec[i];
      bottom_val = bottom.vec[i];
    }
    // overrun bottom (bc can't overrun top)
    else if(i < (int)top.vec.size() && i >= (int)bottom.vec.size())
    {
      top_val = top.vec[i];
      bottom_val = 0;
    }

    // checking if top value - bottom value would produce a negative
    if(top_val < bottom_val)
    {
      top_val += base; // bring over an extra base for subtraction
      diff = (top_val - bottom_val - borrow) % base;
      borrow = 1; // increase borrow if you borrowed a base
    }
    else
    {
      diff = (top_val - bottom_val - borrow) % base;
      borrow = 0;
    }
 
    // check if diff < 0
    if(diff < 0)
    {
      // add base to diff and do mod base
      diff = (diff + base) % base;
      borrow = 1;
    }
    
    if(i >= (int)vec.size()) // if it's outside the vector, push_back
    {
      vec.push_back(diff);
    }
    else vec[i] = diff;
  }
  
  // check if there are extra leading zeros
  for(int i = (int)vec.size() - 1; i >= 0; i--)
  {
    if(vec[i] == 0)
    {
      vec.pop_back(); // pop_back to get rid of leading zeros
    }
    if(vec[i] != 0) break;
  }

  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call *= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator * (const  BigInt &a, const BigInt & b){

  /************* You complete *************/
  BigInt c = a;
  c *= b;
  return c;
}

/*
//==================
// MEMBER function
//==================
//  Multiplication assignment operator.
//    i.e., a *= b
//  Implement Long Multiplication
//  Note: What are the base cases?? (e.g., multiply by 0)
*/
const BigInt & BigInt::operator *= (const BigInt &b){
  if(base != b.base){
      throw DiffBaseException();
  }
  /************* You complete *************/
  BigInt total(base);
  int carry = 0, product = 0;
  
  // checking if a or b are just equal to 0, then return 0
  if((vec.size() == 1 && vec[0] == 0) || (b.vec.size() == 1 && b.vec[0] == 0))
  {
    isPositive = true; // result will be positive bc 0 is "positive"
    vector <int> zero;
    zero.push_back(0);
    vec = zero;
    return *this;
  }
  // checking if a or b are just equal to 1, then return the one that isn't 1
  if(vec.size() == 1 && vec[0] == 1 && isPositive)
  {
    isPositive = b.isPositive; // result will be sign of b
    vec = b.vec;
    return *this;
  }
  if(vec.size() == 1 && vec[0] == 1 && !isPositive)
  {
    isPositive = !b.isPositive; // result will be sign of b
    vec = b.vec;
    return *this;
  }
  else if(b.vec.size() == 1 && b.vec[0] == 1 && b.isPositive)
  {
    return *this; // nothing changes in a
  }
  else if(b.vec.size() == 1 && b.vec[0] == 1 && !b.isPositive)
  {
    isPositive = !isPositive; // sign of a flips
    return *this; // rest of it doesn't change
  }
  
  // if a and b are both positive, it will be positive
  if(isPositive && b.isPositive)
  {
    isPositive = true;
  }
  // if a and b are both negative, it will be positive
  else if(!isPositive && !b.isPositive)
  {
    isPositive = true;
  }
  // if a is negative and b is positive, it will be negative
  else if(!isPositive && b.isPositive) 
  {
    isPositive = false;
  }
  else // if a is positive and b is negative, it will be negative
  {
    isPositive = false;
  }
  
  // looping through each digit in b.vec
  for(int i = 0; i < (int)b.vec.size(); i++)
  {
    BigInt temp(base); // change base of temp to match
    // push back i 0's into temp
    for(int j = 0; j < i; j++)
    {
      temp.vec.push_back(0);
    }
    
    // multiplication while looping through digits in vec
    for(int k = 0; k < (int)vec.size(); k++)
    {
      product = ((vec[k] * b.vec[i]) + carry) % base;
      carry = ((vec[k] * b.vec[i]) + carry) / base;
      temp.vec.push_back(product); // pushing in product
    }
    
    if(carry > 0) // there is carry left over?
    {
      temp.vec.push_back(carry);
    }
    carry = 0; // reset carry
    total += temp; // add temp to total
  }
  
  this->vec = total.vec; // make this = total
  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call /= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator / (const  BigInt &a, const BigInt & b){
  /************* You complete *************/
  BigInt c = a;
  c /= b;
  return c;
}

/*
//==================
// MEMBER function
//==================
//  Division assignment operator.
//    - Call 'divisionMain' to get the quotient;
*/
const BigInt & BigInt::operator /= (const BigInt &b){
  if(base != b.base){
      throw DiffBaseException();
  }
  if(b.vec.size() == 1 && b.vec[0] == 0){
      throw DivByZeroException();
  }
  /************* You complete *************/
  // keeping track of original signs
  bool a_positive = isPositive;
  bool b_positive = b.isPositive;
  
  // checks if the dividend is 0
  if(vec.size() == 1 && vec[0] == 0)
  {
    return *this; // simply return 0
  }
  
  // dividing by 1
  if(b.vec.size() == 1 && b.vec[0] == 1 && b.isPositive)
  {
    return *this;
  }
  
  // dividing by -1
  if(b.vec.size() == 1 && b.vec[0] == 1 && !b.isPositive)
  {
    isPositive = !isPositive;
    return *this;
  }
  
  // dividing by itself with same sign
  if(vec == b.vec && isPositive == b.isPositive)
  {
    vector<int> one;
    one.push_back(1); // fill it with a 1
    vec = one;
    isPositive = true; // make the sign positive
    return *this;
  }
  
  // dividing by itself with diff sign
  if(vec == b.vec && isPositive != b.isPositive)
  {
    vector<int> one;
    one.push_back(1); // fill it with a 1
    vec = one;
    isPositive = false; // make the sign negative
    return *this;
  }
  
  // make both of them positive
  isPositive = true;
  BigInt c = b;
  c.isPositive = true;
  
  // check if |b| > |a|, then return 0
  if(c > *this)
  {
    vector<int> zero;
    zero.push_back(0); // fill it with a 0
    vec = zero;
    isPositive = true; // make the sign positive
    return *this;
  }
  
  vector<int> quotient;
  
  int pos = (int)vec.size() - 1; // rightmost position in vec
  BigInt dividend_seq(vec[pos], base); // first # is rightmost # in vec
  while(dividend_seq < c)
  {
    pos--;
    dividend_seq.vec.insert(dividend_seq.vec.begin(), vec[pos]); // pushing to front
  }
  
  while(pos >= 0)
  { 
    // find out how many times you can subtract the divisor from dividend_seq
    int times = 0;
    while(dividend_seq >= c)
    {
      dividend_seq -= c;
      times++;
    }

    quotient.insert(quotient.begin(), times);
    
    if(dividend_seq.vec.size() == 1 && dividend_seq.vec[0] == 0)
    {
      dividend_seq.vec.clear(); // emptying out the vector
    }
    
    // more digits to pull from dividend?
    if(pos != 0)
    {
      dividend_seq.vec.insert(dividend_seq.vec.begin(), vec[pos - 1]); // insert new number
    }
    pos--;
  }
  
  // if dividend_seq is empty, remainder is 0
  if(dividend_seq.vec.empty())
  {
    isPositive = true;
  }
  else isPositive = a_positive;
  
  // change sign of quotient?
  // both numbers are positive or both numbers are negative
  if((a_positive && b_positive) || (!a_positive && !b_positive))
  {
    isPositive = true; // division will give a positive number
  }
  // different signs
  else if((a_positive && !b_positive) || (!a_positive && b_positive))
  {
    isPositive = false;
  }
  
  // put quotient as this->vec
  vec = quotient;

  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call %= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator % (const  BigInt &a, const BigInt & b){

  /************* You complete *************/
  BigInt c = a;
  c %= b;
  return c;
}

/*
//==================
// MEMBER function
//==================
//  Modulus assignment operator.
//    - Call 'divisionMain' to get the remainder;
//    - Note: remainder takes the sign of the dividend.
*/
const BigInt & BigInt::operator %= (const BigInt &b){
  if(base != b.base){
      throw DiffBaseException();
  }
  if(b.vec.size() == 1 && b.vec[0] == 0){
      throw DivByZeroException();//divide by zero.
  }
  /************* You complete *************/
  bool a_positive = isPositive;
  //bool b_positive = b.isPositive;
  
  // checks if the dividend is 0
  if(vec.size() == 1 && vec[0] == 0)
  {
    return *this; // simply return 0
  }
  
  // dividing by 1
  if(b.vec.size() == 1 && b.vec[0] == 1)
  {
    vector<int> zero;
    zero.push_back(0); // fill it with a 0
    vec = zero;
    isPositive = true;
    return *this;
  }
  
  // dividing by itself
  if(vec == b.vec)
  {
    vector<int> zero;
    zero.push_back(0); // fill it with a 0
    vec = zero;
    isPositive = true;
    return *this;
  }
  
  // make both of them positive
  isPositive = true;
  BigInt c = b;
  c.isPositive = true;
  
  // check if |b| > |a|, then return 0
  if(c > *this)
  {
    isPositive = a_positive;
    return *this;
  }
  
  vector<int> quotient;
  
  int pos = (int)vec.size() - 1; // rightmost position in vec
  BigInt dividend_seq(vec[pos], base); // first # is rightmost # in vec
  while(dividend_seq < c)
  {
    pos--;
    dividend_seq.vec.insert(dividend_seq.vec.begin(), vec[pos]); // pushing to front
  }
  
  while(pos >= 0)
  { 
    // find out how many times you can subtract the divisor from dividend_seq
    int times = 0;
    while(dividend_seq >= c)
    {
      dividend_seq -= c;
      times++;
    }

    quotient.insert(quotient.begin(), times);
    
    if(dividend_seq.vec.size() == 1 && dividend_seq.vec[0] == 0)
    {
      dividend_seq.vec.clear(); // emptying out the vector
    }
    
    // more digits to pull from dividend?
    if(pos != 0)
    {
      dividend_seq.vec.insert(dividend_seq.vec.begin(), vec[pos - 1]); // insert new number
    }
    pos--;
  }
  
  // if dividend_seq is empty, remainder is 0
  if(dividend_seq.vec.empty())
  {
    dividend_seq.vec.push_back(0);
    isPositive = true;
  }
  else isPositive = a_positive;
  
  // put dividend_seq as this->vec
  vec = dividend_seq.vec;

  return *this;
}

/*
//  Main function for the Division (/=) and Modulus (%=) operators.
//     - Compute (q)uotient and (r)emainder
//     - Implement Long Division
//  Note: 1. This should behave like integer division
//        2. What are the base cases?? (e.g., div by itself)
*/
void BigInt::divisionMain(const BigInt &b, BigInt &quotient, BigInt &remainder){
  /************* You complete *************/
  quotient = *this / b;
  remainder = *this % b;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call the 'exponentiation' function on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt pow(const  BigInt &a, const BigInt & b){
  /************* You complete *************/
  BigInt c = a;
  c.exponentiation(b);
  return c;
}

/*
//==================
// MEMBER function
//==================
//  Exponentiation assignment function.
//     - i.e., a.exponentiation(b);
// Note: 1. implement Exponentiation by Squaring (see the writeup)
//       2. b should be treated as BigInt, not int or other data type.
*/
const BigInt & BigInt::exponentiation(const BigInt &b){
  if(base != b.base){
      throw DiffBaseException();
  }
  if(!b.isPositive){
      throw ExpByNegativeException();
  }
  /************* You complete *************/
  BigInt result = *this; // copy of a
  bool odd = false; // flag for odd exponent
  BigInt c = b; // copy of b
  BigInt zero(0, base); // creates a bigint of value 0
  BigInt one(1, base); // creates a bigint of value 1 for decrementing
  BigInt two(2, base); // creates a bigint of value 2 for even/odd check
  BigInt copy(1, base); // to be used if exponent is odd
  // if b == 0, simply return 1
  if((int)b.vec.size() == 1 && b.vec[0] == 0)
  {
    isPositive = true;
    vec = one.vec;
    return *this;
  }
  
  // if b == 1, return a
  if((int)b.vec.size() == 1 && b.vec[0] == 1 && b.isPositive)
  {
    return *this;
  }
  // if a is negative and b is even
  if(!isPositive && b % two == zero)
  {
    // negative base to even power is positive
    isPositive = true;
  }
  else if(!isPositive && b % two == one)
  {
    // negative base to odd power is negative
    isPositive = false;
  }
  else isPositive = true; // positive base to any power is positive

  while(c / two >= one)
  {
    // if b is odd, bool odd = true
    if(c % two == one)
    {
      c -= one; // decrement power
      copy *= result; // make a copy of result at this point in time
      odd = true;
    }
    result *= result; // multiply a by itself, making a^2
    c /= two;
  }
  
  if(odd) // if odd marker got turned on, multiply by a again
  {
    result *= copy;
  }
  
  vec = result.vec;
  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call the 'modulusExp' function on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt modPow(const BigInt &a, const BigInt &b, const BigInt &m){
  /************* You complete *************/
  BigInt c = a;
  c.modulusExp(b, m);
  return c;
}

/*
//==================
// MEMBER function
//==================
//  Modulus Exponentiation assignment function.
//     - i.e., a.modulusExp(b)
// Note: 1. implement Modulus Exponentiation (see the writeup)
//       2. b should be treated as BigInt, not int or other data type.
// Hint: same implementation as exponentiation, but take modulus 
//          after every call to the *= operator.
*/
const BigInt & BigInt::modulusExp(const BigInt &b, const BigInt &m){
  if(base != b.base || base != m.base){
      throw DiffBaseException();
  }
  if(!b.isPositive){
      throw ExpByNegativeException();
  }
  /************* You complete *************/
    BigInt result = *this; // copy of a
  bool odd = false; // flag for odd exponent
  BigInt c = b; // copy of b
  BigInt zero(0, base); // creates a bigint of value 0
  BigInt one(1, base); // creates a bigint of value 1 for decrementing
  BigInt two(2, base); // creates a bigint of value 2 for even/odd check
  BigInt copy(1, base); // to be used if exponent is odd
  // if b == 0, simply return 1
  if((int)b.vec.size() == 1 && b.vec[0] == 0)
  {
    isPositive = true;
    vec = one.vec;
    return *this;
  }
  
  // if b == 1, return a
  if((int)b.vec.size() == 1 && b.vec[0] == 1 && b.isPositive)
  {
    return *this;
  }
  // if a is negative and b is even
  if(!isPositive && b % two == zero)
  {
    // negative base to even power is positive
    isPositive = true;
  }
  else if(!isPositive && b % two == one)
  {
    // negative base to odd power is negative
    isPositive = false;
  }
  else isPositive = true; // positive base to any power is positive

  while(c / two >= one)
  {
    // if b is odd, bool odd = true
    if(c % two == one)
    {
      c -= one; // decrement power
      copy *= result; // make a copy of result at this point in time
      copy %= m; // modulus
      odd = true;
    }
    result *= result; // multiply a by itself, making a^2
    result %= m; // modulus
    c /= two;
  }
  
  if(odd) // if odd marker got turned on, multiply by a again
  {
    result *= copy;
    result %= m; // modulus
  }
  
  vec = result.vec;
  return *this;
}

//******************************************************************
//END OF THE ARITHMETIC OPERATORS SECTION
//******************************************************************