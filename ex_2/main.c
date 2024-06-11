/***********
*Name: Ben Tau
*Id: 325394997
*Assignment: ex_2
***********/
#include <stdio.h>

const int NO_REMINDER = 0;
const int START_AT_NATURAL = 0;
const int BEGIN_AT_SECOND = 2;
const int MISSION_FROM_ONE = 1;
const int MISSION_FROM_ZERO = 0;
const int ERROR_SIGN = -9;

/**
this function take an number from the client and make sure it is an intager bigger than one or zero (depend on the input mission)
and if it is the func will return the number to the func that called it or if it not it will return -9
**/
long long getNum(int mission){
    printf("Enter a number: ");
    double num;
    scanf("%lf",&num);
    if(num-(long long)num==NO_REMINDER) {
        if(num>mission){
            return ((long long) num);
        }else{
            if(mission==MISSION_FROM_ONE)printf("Foolish mortal! You cannot solve Thanos's quest with an input that isn't a number bigger than 1\n");
            else printf("Foolish mortal! You cannot solve Thanos's quest with an input that isn't a number bigger than 0\n");
        }
    }
    else{
        printf("Foolish mortal! You cannot solve Thanos's quest with an input that isn't a Integer number!\n");
    }
    return (ERROR_SIGN);
}
/**
This mission takes an number and returns the fizz buzz game till this number.
**/
void mission1(){
    const int FIZZ_IDX = 3;
    const int BUZZ_IDX = 5;
    long long num = getNum(MISSION_FROM_ONE);
    if(num>START_AT_NATURAL){
        for(long long i=1;i<=num;i++){
            if(i%FIZZ_IDX==NO_REMINDER)printf("Fizz");
            if(i%BUZZ_IDX==NO_REMINDER)printf("Buzz");
            else if(i%FIZZ_IDX!=NO_REMINDER)printf("%llu",i);
            printf("\n");
        }
    }
    printf("\n");
}

/**
This mission takes an number and returns the first Fibonacci sequence numbers according to the selected number.
**/
void mission2(){
    int num = getNum(MISSION_FROM_ZERO);
    if(num>START_AT_NATURAL){
        unsigned long long firstNum = 0;
        unsigned long long secondNum = 1;
        printf("%llu ",firstNum);
        for(int i=BEGIN_AT_SECOND;i<=num;i++){
            printf("%llu ",secondNum);
            secondNum+=firstNum;
            firstNum=secondNum-firstNum;
        }
    printf("\n");
    }
    printf("\n");
}

/**
This mission takes an number and returns the sum of all the prime numbers till the selected number.
**/
void mission3(){
    long long num = getNum(MISSION_FROM_ONE);
    if(num>START_AT_NATURAL){
        unsigned long long sum = 0;
        for(long long i=BEGIN_AT_SECOND;i<=num;i++){
                sum+=i;
            for(long long j=BEGIN_AT_SECOND;j<=i/2;j++){
                if(i%j==NO_REMINDER){
                    sum-=i;
                    j=i;
                }
            }
        }
        printf("%llu\n",sum);
    }
    printf("\n");
}

/**
This mission takes an number and returns if the number is perfect or not.
**/
void mission4(){
    long long num = getNum(MISSION_FROM_ZERO);
    if(num>START_AT_NATURAL){
        long long sum = 1;
        for(long long i=BEGIN_AT_SECOND;i<num;i++){
            if(num%i==NO_REMINDER)sum+=i;
        }
        if(num==sum)printf("Perfect!\n");
        else printf("Not Perfect!\n");
    }
    printf("\n");
}

/**
This is the main screen
**/
int main()
{
    char flag = 'T';
    while (flag=='T'){
    printf("Welcome to Thanos's playground.\n");
    printf("Choose your adventure:\n");
    printf("1. Revealing the Hidden Code\n");
    printf("2. Thanos' numeric mayhem\n");
    printf("3. Thanos' Maze System\n");
    printf("4. The Sorcery of Thanos\n");
    printf("5. Quit the quest\n");
    double chose;
    scanf(" %lf",&chose);
    printf("\n");
    if(chose-(int)chose==0)
    switch ((int)chose) {
      case 1:
          mission1();
        break;
      case 2:
          mission2();
        break;
      case 3:
          mission3();
        break;
      case 4:
          mission4();
        break;
       case 5:
          printf("Congratulations! You finished the quest and managed to defeat Thanos");
          flag='F';
        break;
      default:
          printf("Thanos is mad! You are playing his game and this is not an option. Choose again, wisely.\n\n");
          break;
    }else printf("Thanos is mad! You are playing his game and this is not an option. Choose again, wisely.\n\n");
    }
    return 0;
}




