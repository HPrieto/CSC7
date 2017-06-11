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


#ifndef INCLUDE_GENERALHASHFUNCTION_CPP_H
#define INCLUDE_GENERALHASHFUNCTION_CPP_H


#include <string>


typedef unsigned int (*HashFunction)(const std::string&);


unsigned int RSHash  (const std::string& str);
unsigned int JSHash  (const std::string& str);
unsigned int PJWHash (const std::string& str);
unsigned int ELFHash (const std::string& str);
unsigned int BKDRHash(const std::string& str);
unsigned int SDBMHash(const std::string& str);
unsigned int DJBHash (const std::string& str);
unsigned int DEKHash (const std::string& str);
unsigned int BPHash  (const std::string& str);
unsigned int FNVHash (const std::string& str);
unsigned int APHash  (const std::string& str);


#endif

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


unsigned int RSHash(const std::string& str)
{
   unsigned int b    = 378551;
   unsigned int a    = 63689;
   unsigned int hash = 0;

   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash = hash * a + str[i];
      a    = a * b;
   }

   return hash;
}
/* End Of RS Hash Function */


unsigned int JSHash(const std::string& str)
{
   unsigned int hash = 1315423911;

   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash ^= ((hash << 5) + str[i] + (hash >> 2));
   }

   return hash;
}
/* End Of JS Hash Function */


unsigned int PJWHash(const std::string& str)
{
   unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
   unsigned int ThreeQuarters     = (unsigned int)((BitsInUnsignedInt  * 3) / 4);
   unsigned int OneEighth         = (unsigned int)(BitsInUnsignedInt / 8);
   unsigned int HighBits          = (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
   unsigned int hash              = 0;
   unsigned int test              = 0;

   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash = (hash << OneEighth) + str[i];

      if((test = hash & HighBits)  != 0)
      {
         hash = (( hash ^ (test >> ThreeQuarters)) & (~HighBits));
      }
   }

   return hash;
}
/* End Of  P. J. Weinberger Hash Function */


unsigned int ELFHash(const std::string& str)
{
   unsigned int hash = 0;
   unsigned int x    = 0;

   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash = (hash << 4) + str[i];
      if((x = hash & 0xF0000000L) != 0)
      {
         hash ^= (x >> 24);
      }
      hash &= ~x;
   }

   return hash;
}
/* End Of ELF Hash Function */


unsigned int BKDRHash(const std::string& str)
{
   unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
   unsigned int hash = 0;

   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash = (hash * seed) + str[i];
   }

   return hash;
}
/* End Of BKDR Hash Function */


unsigned int SDBMHash(const std::string& str)
{
   unsigned int hash = 0;

   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash = str[i] + (hash << 6) + (hash << 16) - hash;
   }

   return hash;
}
/* End Of SDBM Hash Function */


unsigned int DJBHash(const std::string& str)
{
   unsigned int hash = 5381;

   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash = ((hash << 5) + hash) + str[i];
   }

   return hash;
}
/* End Of DJB Hash Function */


unsigned int DEKHash(const std::string& str)
{
   unsigned int hash = static_cast<unsigned int>(str.length());

   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash = ((hash << 5) ^ (hash >> 27)) ^ str[i];
   }

   return hash;
}
/* End Of DEK Hash Function */


unsigned int BPHash(const std::string& str)
{
   unsigned int hash = 0;
   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash = hash << 7 ^ str[i];
   }

   return hash;
}
/* End Of BP Hash Function */


unsigned int FNVHash(const std::string& str)
{
   const unsigned int fnv_prime = 0x811C9DC5;
   unsigned int hash = 0;
   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash *= fnv_prime;
      hash ^= str[i];
   }

   return hash;
}
/* End Of FNV Hash Function */


unsigned int APHash(const std::string& str)
{
   unsigned int hash = 0xAAAAAAAA;

   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash ^= ((i & 1) == 0) ? (  (hash <<  7) ^ str[i] * (hash >> 3)) :
                               (~((hash << 11) + (str[i] ^ (hash >> 5))));
   }

   return hash;
}
/* End Of AP Hash Function */

#include <fstream>
#include <iostream>
#include <string>

void bloom(string *,int);
void bloom2(string *,int);

int main(int argc, char* argv[]) {
   	//Declare Variables
	int nWords = 50;
	string words[nWords];
	ifstream file;
	//Get contents of file
	file.open("filter.txt");
	for (int i = 0; i < nWords; i++)
		file>>words[i];
	//Perform 2 of 9 hashes
	bloom(words,nWords);
	//Perform all hashes
	bloom2(words,nWords);
	//Close file
	file.close();
	return 0;
}

/* Performs 2 of 9 Hashes from General Hash Functions */
void bloom(string *words,int n) {
	//Declare a variable array
    int nBits=800;
    const int SIZE=nBits/8+1;
    char bitVec[SIZE]={};
    
    //Array and number of hashes
    int hashsize = 2;
    int hashes[hashsize]={};
     
    //Hash the first 100 words
    for(int i = 0; i < (n/2); i++){
        hashes[0] = RSHash(words[i])%nBits;
        hashes[1] = FNVHash(words[i])%nBits;
        
        //Set all bits in array
        for(int j = 0; j < hashsize; j++){
            //What bit to set?
            int bitSet=hashes[j];

            //What element is that in the array?
            int byte=bitSet/8;
            int bit=bitSet%8;

            //Now set that bit
            bitVec[byte]|=1<<bit;
        }
    }
    
    //Hash and check all 200 words
    bool positive = true;
    
    for(int i = 0; i < n; i++){
        hashes[0] = RSHash(words[i])%nBits;
        hashes[1] = FNVHash(words[i])%nBits;
        
        //Check each hash
        for(int j = 0; j < hashsize; j++){
            //What bit to set?
            int bitSet=hashes[j];

            //What element is that in the array?
            int byte=bitSet/8;
            int bit=bitSet%8;

            //Check and see if the bit got set
            bool set=(bitVec[byte]>>bit)&1;
            
            //If the bit was not set
            if(!set){
                //Flag negative
                positive = false;
            }
        }
 
        //Output result
        if(positive){
            cout <<"Word [" <<i <<"] = Positive!\n";
        }
        else{
            cout <<"Word [" <<i <<"] = Negative!\n";
        }
    }
}

void bloom2(string *words,int n) {
	//Declare a variable array
    int nBits=750;
    const int SIZE=nBits/8+1;
    char bitVec[SIZE]={};
    
    //Array and number of hashes
    int hashsize = 10;
    int hashes[hashsize]={};
     
    //Hash the first 100 words
    for(int i = 0; i < (n/2); i++){
        hashes[0] = RSHash(words[i])%nBits;
        hashes[1] = JSHash(words[i])%nBits;
        hashes[2] = PJWHash(words[i])%nBits;
        hashes[3] = ELFHash(words[i])%nBits;
        hashes[4] = BKDRHash(words[i])%nBits;
        hashes[5] = SDBMHash(words[i])%nBits; 
        hashes[6] = DJBHash(words[i])%nBits;
        hashes[7] = DEKHash(words[i])%nBits;
        hashes[8] = FNVHash(words[i])%nBits;
        hashes[9] = BPHash(words[i])%nBits;
        
        //Set all bits in array
        for(int j = 0; j < hashsize; j++){
            //What bit to set?
            int bitSet=hashes[j];

            //What element is that in the array?
            int byte=bitSet/8;
            int bit=bitSet%8;

            //Now set that bit
            bitVec[byte]|=1<<bit;
        }
    }
    
    //Hash and check all 200 words
    bool positive = true;
    
    for(int i = 0; i < n; i++){
        hashes[0] = RSHash(words[i])%nBits;
        hashes[1] = JSHash(words[i])%nBits;
        hashes[2] = PJWHash(words[i])%nBits;
        hashes[3] = ELFHash(words[i])%nBits;
        hashes[4] = BKDRHash(words[i])%nBits;
        hashes[5] = SDBMHash(words[i])%nBits; 
        hashes[6] = DJBHash(words[i])%nBits;
        hashes[7] = DEKHash(words[i])%nBits;
        hashes[8] = FNVHash(words[i])%nBits;
        hashes[9] = BPHash(words[i])%nBits;
        
        //Check each hash
        for(int j = 0; j < hashsize; j++){
            //What bit to set?
            int bitSet=hashes[j];

            //What element is that in the array?
            int byte=bitSet/8;
            int bit=bitSet%8;

            //Check and see if the bit got set
            bool set=(bitVec[byte]>>bit)&1;
            
            //If the bit was not set
            if(!set){
                //Flag negative
                positive = false;
            }
        }
 
        //Output result
        if(positive){
            cout <<"Word [" <<i <<"] = Positive!\n";
        }
        else{
            cout <<"Word [" <<i <<"] = Negative!\n";
        }      
    }
}



























