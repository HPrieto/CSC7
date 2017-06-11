/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr/Heriberto Prieto
 * Created on February 21, 2017, 8:35 AM
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//Global Constants
enum CrdCard {AmericanExpress,Visa,MasterCard,Discover,ALL};

//Function Prototypes
char rndDgit();
void prpLuhn(char*,int);
void Luhn(char*,int);
char dblLuhn(char);
bool chkLuhn(char*,int);
void genCC(CrdCard,char *);
char *blnkCrd(int);
void delCard(char *);
void fillCrd(char *,int,int);
int  crdSum(char *,int,int);
void flipDig(char *,int);
void crdMenu(char *);
void testCrd(char *,int);

int main() {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    const int SIZE=16;
    char crdCard[SIZE];
    //Output/Input Credit Card Selection Menu
    crdMenu(crdCard);
    //Begin Flip and Test
    testCrd(crdCard,SIZE);
    return 0;
}

/* Randomly flips one digit */
void testCrd(char *card,int n) {
    int tests   = 10000;
    int valid   = 0;
    int invalid = 0;
    for (int i = 0; i < tests; i++) {
        if (chkLuhn(card,n))
            valid++;
        else invalid++;
        flipDig(card,n);
    }
    cout<<"Digit Flip Test Results"<<endl;
    cout<<"Invalid Credit Cards: "<<invalid<<endl;
    cout<<"Valid Credit Cards:   "<<valid<<endl;
}

/* Outputs Menu for Credit Card Selection, then generates */
void crdMenu(char *card) {
    CrdCard crdType;
    int crd;
    //Output/Input Menu for user
    cout<<"Select your card type:"<<endl;
    cout<<"1.) American Express     2.) Visa"<<endl;
    cout<<"3.) Master Card          4.) Discover"<<endl;
    cin>>crd;
    switch(crd) {
        case 1:
            genCC(AmericanExpress,card);
        break;
        case 2:
            genCC(Visa,card);
        break;
        case 3:
            genCC(MasterCard,card);
        break;
        default:
            genCC(Discover,card);
        break;
    }
}

void Luhn(char *cc,int n) {
    //Perform Luhn Loop
    for(int i=n; i>=0; i-=2)
        (cc[i]>'4')?cc[i]=dblLuhn(cc[i]):cc[i]=(cc[i]*2)-48;
}

void prpLuhn(char *cc,int n) {
    for(int i=0;i<n;i++)
        cc[i]=rndDgit();
    //Put null terminator at the end
        cc[n]='\0';
}

/* Generates and returns random value */
char rndDgit() {
    return rand()%10+48;
}

/* Doubles value of char within credit card/2DArray */
char dblLuhn(char c) {
    const short val  = static_cast<unsigned short>(c-48);
    const short vDbl = val*2;    //Character value doubled
    const short fDgt = (vDbl/10);//First Digit in doubled character value
    const short sDgt = (vDbl%10);//Second Digit in doubled character value
    return '0'+(fDgt+sDgt);      //Return Sum of first and second digit
}

/* Returns true for valid card using Luhn Algorithm, else returns false. */
bool chkLuhn(char *cc,int n) {
    short sum = 0;
    //Perform loop to sum credit card digits
    for (int i=0; i<n; i++)
        sum+=static_cast<unsigned int>(cc[i]-48);
    return ((sum*9)%10)==0;
}

/* Generates Credit Card/2DArray */
void genCC(CrdCard crdType,char *card) {
    //Declare variables and initialize new card
    int crdLen = 16;
    int sum = 0;
    //Generate Valid Card
    while (!chkLuhn(card,crdLen)) {
        prpLuhn(card,crdLen);
        //Generate CreditCard Number usign Card Type
        switch (crdType) {
        case AmericanExpress:
            card[0] = '3';
        break;
        case Visa:
            card[0] = '4';
        break;
        case MasterCard:
            card[0] = '5';
        break;
        default:
            card[0] = '6';
            card[1] = '0';
            card[2] = '1';
            card[3] = '1';
        break;
        }
    }
}

/* Fills card/2DArray at given index */
void fillCrd(char *cc,int s,int n) {
    //Create a random cc in prep for Luhn checksum
    for (int i = s; i < n; i++)
        cc[i]=rndDgit();
    cc[n] = '\0';
}

/* Gets sum of 2DArray within given index */
int crdSum(char *cc,int s,int n) {
    int sum = 0;
    for (int i = s; i < n; i++)
        sum += static_cast<int>(cc[i]-48);
    return sum;
}

/* Allocates memory and returns 'card'/2DArray */
char *blnkCrd(int length) {
    char *card = new char[length];
    for (int i = 0; i < length; i++)
        card[i] = '0';
    return card;
}

/* Randomly 'flips' a random digit at given index */
void flipDig(char *card,int n) {
    //Random index
    int i  = (rand() % n) + 1;
    //Flip digit in credit card number
    card[i] = rndDgit();
}

/* Deallocates memory for card */
void delCard(char *card) {
    delete []card;
}
