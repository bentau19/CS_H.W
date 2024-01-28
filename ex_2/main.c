/**
CREATED BY BEN TAU!
**/
#include <stdio.h>
#include <stdlib.h>
#define NO_REMINDER 0
#define START_AT_NATURAL 0
#define BEGIN_AT_SECOND 2
/**
This mission takes an number and returns the fizz buzz game till this number.
**/

int getNum(int mission){
    printf("Enter a number: ");
    double num;
    scanf("%lf",&num);
    if(num-(int)num==NO_REMINDER){
        if(num>START_AT_NATURAL){return ((int) num);}
        else {
            if(mission==0)
            printf("Foolish mortal! You cannot solve Thanos's quest with an input that isn't a number bigger than 0\n");
            else
            printf("Foolish mortal! You cannot solve Thanos's quest with an input that isn't a number bigger than 1\n");
            return (-9);
        }
    }else{
        printf("Foolish mortal! You cannot solve Thanos's quest with an input that isn't a number that not integer!\n");
        return (-9);
    }
}

void mission1(){
    int num = getNum(1);
    if(num>START_AT_NATURAL){
        for(int i=1;i<=num;i++){
            if(i%3==NO_REMINDER)printf("Fizz");
            if(i%5==NO_REMINDER)printf("Buzz");
            else if(i%3!=NO_REMINDER)printf("%d",i);
            printf("\n");
        }
    }
    printf("\n");
}

/**
This mission takes an number and returns the first Fibonacci sequence numbers according to the selected number.
**/
void mission2(){
    int num = getNum(0);
    if(num>START_AT_NATURAL){
        int firstNum = 0;
        int secondNum = 1;
        printf("%d ",firstNum);
        for(int i=BEGIN_AT_SECOND;i<=num;i++){
            printf("%d ",secondNum);
            secondNum+=firstNum;
            firstNum=secondNum-firstNum;
        }
    printf("\n");
    }printf("\n");
}

/**
This mission takes an number and returns the sum of all the prime numbers till the selected number.
**/
void mission3(){
    int num = getNum(1);
    if(num>START_AT_NATURAL){
        int sum = 0;
        for(int i=BEGIN_AT_SECOND;i<=num;i++){
                sum+=i;
            for(int j=BEGIN_AT_SECOND;j<i;j++){
                if(i%j==NO_REMINDER){
                    sum-=i;
                    j=i;
                }
            }
        }
        printf("%d\n",sum);
    }printf("\n");
}

/**
This mission takes an number and returns if the number is perfect or not.
**/
void mission4(){
    int num = getNum(0);
    if(num>START_AT_NATURAL){
        int sum = 1;
        for(int i=BEGIN_AT_SECOND;i<num;i++){
            if(num%i==NO_REMINDER)sum+=i;
        }
        if(num==sum)printf("Perfect!\n");
        else printf("Not Perfect!\n");
    }printf("\n");
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




