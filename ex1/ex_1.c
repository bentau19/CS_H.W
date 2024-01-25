#include <stdio.h>
#include <math.h>
int main()
{
    //ex1
    // the code takes 2 4 bits binary strings and make xor action on it
    printf("Exercise 1:\n");
    printf("Please enter 2 binary strings with 4 digits:\n");
    char bin11, bin12, bin13, bin14;
    printf("Binary 1: ");
    scanf(" %c %c %c %c", &bin11, &bin12, &bin13, &bin14);
    char bin21, bin22, bin23, bin24;
    printf("Binary 2: ");
    scanf(" %c %c %c %c", &bin21, &bin22, &bin23, &bin24);
    printf("\n");
    printf("%c%c%c%c\n", bin11, bin12, bin13, bin14);
    printf("^\n");
    printf("%c%c%c%c\n", bin21, bin22, bin23, bin24);
    printf("--------\n");
    char asciiZeroIdx = '0';
    bin11 = ((bin11 - asciiZeroIdx) ^ (bin21 - asciiZeroIdx)) + asciiZeroIdx;
    bin12 = ((bin12 - asciiZeroIdx) ^ (bin22 - asciiZeroIdx)) + asciiZeroIdx;
    bin13 = ((bin13 - asciiZeroIdx) ^ (bin23 - asciiZeroIdx)) + asciiZeroIdx;
    bin14 = ((bin14 - asciiZeroIdx) ^ (bin24 - asciiZeroIdx)) + asciiZeroIdx;
    printf("%c%c%c%c\n", bin11, bin12, bin13, bin14);
    printf("\n");



    //ex2
    //The code takes 2 hex numbers make + action on them and print the binary value of the last number.
    printf("Exercise 2:\n");
    printf("Enter 2 hexadecimal numbers:\n");
    printf("Hex 1: ");
    int hex1,hex2;
    scanf(" %X",&hex1);
    printf("Hex 2: ");
    scanf(" %X",&hex2);
    int res2 = hex1+hex2;
    printf("\n%X + %X = %X\n",hex1,hex2,res2);
    const int binDivider = 2;
    int num21 = res2%binDivider;
    int num22 = (res2/binDivider)%binDivider;
    int num23 = ((res2/binDivider)/binDivider)%binDivider;
    int num24 = (((res2/binDivider)/binDivider)/binDivider)%binDivider;
    printf("The last 4 binary digits of the sum are %d%d%d%d",num24,num23,num22,num21);
    printf("\n\n");

    //ex3
    //The code takes num between 2-9 then takes 5 digit num and returns the decimal value
    //of the second num in the base of the first num
    printf("Exercise 3:\n");
    printf("Choose a base between 2 to 9: ");
    int base3;
    scanf(" %d",&base3);
    printf("Enter a 5 digit number using that base: ");
    int num31,num32,num33,num34,num35;
    scanf(" %1d %1d %1d %1d %1d",&num31,&num32,&num33,&num34,&num35);
    int res3=num35*(int)pow(base3,0)+num34*(int)pow(base3,1)+num33*(int)pow(base3,2)+
    num32*(int)pow(base3,3)+num31*(int)pow(base3,4);
    //-----------------------
    printf("The decimal value of %d%d%d%d%d in base %d is %d",num31,num32,num33,num34,num35,base3,res3);
    printf("\n\n");

    //ex4
    //The code take a number and a value of a bit and returns the value of that bit.
    printf("Exercise 4:\n");
    printf("Enter a number: ");
    int num41;
    scanf(" %d", &num41);
    printf("I want to know the value of bit number: ");
    int bitIdx;
    scanf(" %d", &bitIdx);
    int bitVal = (num41 >> (bitIdx -1))&1;
    printf("\nThe value of the %d bit in %d is %d\n", bitIdx, num41, bitVal);
    printf("Congrats! You've found the philosopher's stone!");

    return 0;
}
