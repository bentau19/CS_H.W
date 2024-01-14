#include <stdio.h>
#include <math.h>
int main()
{
    //ex1
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

    bin11 = ((bin11 - '0') ^ (bin21 - '0')) + '0';
    bin12 = ((bin12 - '0') ^ (bin22 - '0')) + '0';
    bin13 = ((bin13 - '0') ^ (bin23 - '0')) + '0';
    bin14 = ((bin14 - '0') ^ (bin24 - '0')) + '0';

    printf("%c%c%c%c\n", bin11, bin12, bin13, bin14);
    printf("\n");



    //ex2
    printf("Exercise 2:\n");
    printf("Enter 2 hexadecimal numbers:\n");
    printf("Hex 1: ");
    int hex1,hex2;
    scanf(" %X",&hex1);
    printf("Hex 2: ");
    scanf(" %X",&hex2);
    int res2 = hex1+hex2;
    printf("\n%X + %X = %X\n",hex1,hex2,res2);
    int num21 = res2%2;
    int num22 = (res2/2)%2;
    int num23 = ((res2/2)/2)%2;
    int num24 = (((res2/2)/2)/2)%2;
    printf("The last 4 binary digits of the sum are %d%d%d%d",num24,num23,num22,num21);
    printf("\n\n");

    //ex3
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
    printf("Exercise 4:\n");
    printf("Enter a number: ");
    int num41;
    scanf(" %d", &num41);
    printf("I want to know the value of bit number: ");
    int bitIdx;
    scanf(" %d", &bitIdx);
    int bitVal = (num41 & (1 << (bitIdx - 1))) != 0;
    printf("\nThe value of the %d bit in %d is %d\n", bitIdx, num41, bitVal);
    printf("Congrats! You've found the philosopher's stone!");

    return 0;
}
