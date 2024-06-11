/***********
*Name: Ben Tau
*Id: 325394997
*Assignment: ex_3
***********/
#include <stdio.h>
#define ARRAY_SIZE 30
#define MISSION_ONE_COND 1
#define MISSION_TWO_COND 2
#define MISSION_THREE_COND 3
#define MISSION_FOUR_COND 4
#define MISSION_FIVE_COND 5
#define EXIT_COND 6

//mission's 1 functions:
//this function print the arrays at the correct order from smallest to bigger
void mergePrint(int a1[], int a2[], int start1, int start2, int end1, int end2){
    //if there is array with numbers left
    if(start1!=end1||start2!=end2){
        //if a1 array is done
        if(start1==end1){
            printf("%d ",a2[start2]);
            mergePrint(a1, a2, start1, ++start2, end1, end2);
        }else{
        //if a2 array is done
            if(start2==end2){
                printf("%d ",a1[start1]);
                mergePrint(a1, a2, ++start1, start2, end1, end2);
            }else{
                //if none of them done
                if(a1[start1]<a2[start2]){
                    printf("%d ",a1[start1]);
                    mergePrint(a1, a2, ++start1, start2, end1, end2);
                }else{
                    printf("%d ",a2[start2]);
                    mergePrint(a1, a2, start1, ++start2, end1, end2);
                }
            }
        }

    }

}


/*this mission take two arrays from the client and merge and print them by their size
from the smaller to the bigger*/
void mission1(){
    //initialize the first worker
    printf("Enter the length of the first worker array:\n");
    int arrayLenWorker1;
    scanf(" %d",&arrayLenWorker1);
    int firstWorker[ARRAY_SIZE];
    printf("Now enter the first array's elements:\n");
    for (int i=0;i<arrayLenWorker1;i++)
        scanf("%d",&firstWorker[i]);


    //initialize the second worker
    printf("Enter the length of the second worker array:\n");
    int arrayLenWorker2;
    scanf(" %d",&arrayLenWorker2);
    int secondWorker[ARRAY_SIZE];
    printf("Now enter the second array's elements:\n");
    for (int i=0;i<arrayLenWorker2;i++)
        scanf("%d",&secondWorker[i]);


    //print the row
    printf("start ");
    mergePrint( firstWorker, secondWorker, 0, 0, arrayLenWorker1, arrayLenWorker2);
    printf("end\n");
}
//end mission's 1 functions

//mission's 2 functions:
//this function returns the number of asymmetric at the inputed string.
int paliDistance(char str[], int start, int end){
    int sum = 0;
    if(start<end){
        // increase sum if there is asymmetric.
        if(str[start]!=str[end]) ++sum;
        //start the recurse to add the other cases of asymmetric.
        sum+=paliDistance(str,++start,--end);
    }
    return sum;
}

//this function an array from the client and prints the palindrome distance.
void mission2(){
    //initialize the first worker
    printf("Enter the length of the string:\n");
    int arrayLen;
    scanf("%d",&arrayLen);
    char text[ARRAY_SIZE];
    printf("Now enter the string:\n");
    for(int i=0;i<arrayLen;i++){
        scanf(" %c",&text[i]);
    }
    int sum = paliDistance(text,0,arrayLen-1);
    printf("The palindrome distance is %d.\n",sum);
}
//end mission's 2 functions

//mission's 3 functions:
//this function returns the number of how many times there is more a then b and vice versa.
int recursiveCheckBalance(char* str, int n){
    const char ARMY_LETTER = 'a';
    if(n==-1)return 0;
    int sum = recursiveCheckBalance(str,n-1);
    if(str[n]==ARMY_LETTER)return (sum+1);
    else return (sum-1);
}

//this function returns 0 if it balance and 1 if it not
int checkBalance(char* str, int n){
    int sum = recursiveCheckBalance(str,n);
    if(sum==0)return 0;
    else return 1;
}

//this function take an array of a and b of gang members and prints if the army is balanced.
void mission3(){
    printf("Enter the number of gang members:\n");
    int gangMem;
    scanf("%d",&gangMem);
    printf("Enter the gang associations:\n");
    char gangAss[ARRAY_SIZE];
    for(int i=0;i<gangMem;i++){
        scanf(" %c",&gangAss[i]);
    }
    int sum = (int) (checkBalance(gangAss, gangMem - 1) == 1 ? " not" : "");
    printf("The army is%s balanced.\n",sum);
}
//end mission's 3 functions

//mission's 4 functions:
/*this function returns the minimal way to get from an int to 1 using
only n/2 n/3 and n-1 options*/
int escapingTime(int n){
    const int DIVIDE_BY_TWO = 2;
    const int DIVIDE_BY_THREE =3;
    if(n==1)return 0;
    if(n%DIVIDE_BY_THREE==0)return 1+escapingTime(n/DIVIDE_BY_THREE);
    if(n%DIVIDE_BY_TWO==0){
        int threeDivider = escapingTime(n-1);
        int twoDivider = escapingTime(n/DIVIDE_BY_TWO);
        if(threeDivider>twoDivider)return 1+twoDivider;
        return 1+threeDivider;
    }
    return 1+escapingTime(n-1);
}

//this function take an int and print the minimal way to get from this int to 1 using
//only n/2 n/3 and n-1 options
void mission4(){
    printf("What room are you in boss?\n");
    int roomNum;
    scanf("%d",&roomNum);
    printf("Your escaping time is: %d\n",escapingTime(roomNum));
}
//end mission's 4 functions

//mission's 5 functions:
/*this function return the most valueable way to store things in bag according
to its weight and the value of the staff*/
int heistOpt(int maxW, int optVal, int w[], int v[], int start, int len){
    //end condition
    if(maxW==0||start==len) return optVal;
    //if there is more space in maxW
    if(maxW>w[start]){
        maxW-=w[start];
        optVal+=v[start];
    }
    int first = heistOpt(maxW, optVal, w, v, (start+1),len);
    int second = heistOpt(maxW+w[start], (optVal-v[start]), w, v, (start+1),len);
    //return the best way
    if (first>second)return first;
    return second;
}

/*this function take two arrays of weight and values and max weight and returns
the what is the optimal value that can fit in this weight. */
void mission5(){
    printf("Enter the number of objects and the maximum weight:\n");
    int objectsNum,maxWeight;
    scanf("%d",&objectsNum);
    scanf("%d",&maxWeight);
    int values[ARRAY_SIZE],weights[ARRAY_SIZE];
    printf("Now enter the objects' values and weights:\n");
    for (int i=0;i<objectsNum;i++){
        scanf("%d",&values[i]);
        scanf("%d",&weights[i]);
    }
    int optimal = heistOpt(maxWeight, 0, weights, values, 0,objectsNum);
    printf("The optimal heist income value is %d\n",optimal);
}
//end mission's 5 functions
//this is the main menu function
int main()
{
    printf("What is your desired task boss?\n"
        "1. merge order incomes\n"
        "2. find distance from symmetry\n"
        "3. check if the gangs are balanced\n"
        "4. find optimal time for escaping\n"
        "5. check workers efficiency\n"
        "6. exit\n");
    int chose;
    scanf(" %d",&chose);
    switch (chose) {
      case MISSION_ONE_COND:
        mission1();
        break;
      case MISSION_TWO_COND:
        mission2();
        break;
      case MISSION_THREE_COND:
        mission3();
        break;
      case MISSION_FOUR_COND:
        mission4();
        break;
       case MISSION_FIVE_COND:
        mission5();
        break;
       case EXIT_COND:
          printf("goodbye boss!");
          return 0;
        break;
      default:
          printf("Sorry Tony, I don't understand...\n\n");
          break;
    }
    main();
    return 0;
}
