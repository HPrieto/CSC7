/*
 **************************************************************************
 *                                                                        *
 *          General Purpose Hash Function Algorithms Library              *
 *                                                                        *
 * Author: Arash Partow - 2002                                            *
 * URL: http://www.partow.net                                             *
 * URL: http://www.partow.net/programming/hashfunctions/index.html        *
 *                                                                        *
 * Copyright notice:                                                      *
 * Free use of the General Purpose Hash Function Algorithms Library is    *
 * permitted under the guidelines and in accordance with the MIT License. *
 * http://www.opensource.org/licenses/MIT                                 *
 *                                                                        *
 **************************************************************************
*/


#include <vector>
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

template<class T>
class BloomFilter {
private:
   vector<bool> bitVctor;
   unsigned int size;
   unsigned int elements;
   unsigned int APHash(T);
   unsigned int BPHash(T);
public:
   //Class Constructor
   BloomFilter(unsigned int);
   //Class Destructor
   ~BloomFilter();
   //Inserts Element into BitVector
   void insert(T);
   //Bloom Filter Size Accessor
   unsigned int getSize()
      { return this->size; }
   //Returns False Positive -> (1-e^(-kn/m))^k where
   float getFalsePositive();
   //Returns true if string in BitVector
   bool contains(T);
   //Resizes BitVector on Request/When necessary
   void resize(unsigned int);
   //Clears contents of BitVector
   void clear();
};

/* BloomFilter Class Constructor */
template <class T>
BloomFilter<T>::BloomFilter(unsigned int size) {
   this->bitVctor.reserve(size);
   this->bitVctor.assign(size,false);
   this->elements = 0;
   this->size = size;
}

/* Class Destructor */
template <class T>
BloomFilter<T>::~BloomFilter() {
   this->bitVctor.clear();
   this->elements = 0;
   this->size = 0;
}

/* Inserts Value into BitVector using APHASH and BPHASH */
template <class T>
void BloomFilter<T>::insert(T element) {
   this->bitVctor[APHash(element)] = true;
   this->bitVctor[BPHash(element)] = true;
   this->elements++;
}

/* APHash Function */
template <class T>
unsigned int BloomFilter<T>::APHash(T str) {
   unsigned int hash = 0xAAAAAAAA;
   for(std::size_t i = 0; i < str.length(); i++) {
      hash ^= ((i & 1) == 0) ? (  (hash <<  7) ^ str[i] * (hash >> 3)) :
                               (~((hash << 11) + (str[i] ^ (hash >> 5))));
   }
   return hash;
}

/* BPHash Function */
template <class T>
unsigned int BloomFilter<T>::BPHash(T str) {
   unsigned int hash = 0;
   for(std::size_t i = 0; i < str.length(); i++)
      hash = hash << 7 ^ str[i];
   return hash;
}

/* BitVector False Positive -> (1-e^(-kn/m))^k where */
template <class T>
float BloomFilter<T>::getFalsePositive() {
   return pow(1 - exp(-2 * ((float)this->elements) / ((float)this->size)),2);
}

/* Returns True if Element is contained */
template <class T>
bool BloomFilter<T>::contains(T element) {
   return this->bitVctor[APHash(element)] && this->bitVctor[BPHash(element)];
}

/* Resizes BitVector */
template <class T>
void BloomFilter<T>::resize(unsigned int size) {
   this->bitVctor.reserve(size);
   this->bitVctor.assign(size,false);
   this->size = size;
}

/* Clears contents of BitVector */
template <class T>
void BloomFilter<T>::clear() {
   this->bitVctor.clear();
   this->elements = 0;
}

int main(int argc, char* argv[]) {
   //Declare Problem variables
   unsigned int size = 10;
   BloomFilter<string> bloom(size);
   string input;
   int selection;

   //Output/Input to user
   while (selection > 2 || selection < 1) {
      cout<<"Select from the following options: "<<endl;
      cout<<"1.) Insert             2.) Search"<<endl;
      cout<<"3.) Get False Positive"<<endl;
      cin>>selection;
      cin.clear();
      cin>>input;
      if (selection == 1) bloom.insert(input);
      else if (selection == 2)
         (bloom.contains(input) == true) ? cout<<input<<" is in Bit Vector!"<<endl:
                                           cout<<input<<" is not in Bit Vector!"<<endl;
      else if (selection == 3)
         cout<<"False Positive: "<<bloom.getFalsePositive()<<endl;
   }
   return 0;
}