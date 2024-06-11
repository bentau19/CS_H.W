/***********
*Name: Ben Tau
*Id: 325394997
*Assignment: ex_4
***********/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE_BOARD 30
#define MAX_SIZE_WORD 8
#define PLAYER_LEN 21
#define MEMBERS_LEN 10
#define ERROR_SYNTAX -1
typedef struct player{
    char name[PLAYER_LEN];
    int points;
}player;
void landingScreen(const int BOARD_DIM,const int NUM_OBJECTS,char objects[][MAX_SIZE_WORD]);

/// seperate the players and returns 1 if not valid and 0 if valid
int sepPlayersInit(char *players, player *targetArr, int playersNum) {
    const char SEP_WORD[2] = "#";
    char *token = strtok((char *)players, SEP_WORD);
    int i = 0;
    while (token != NULL && i < playersNum) {
        // Copy the token into the name field of the target array element
        strncpy(targetArr[i].name, token, PLAYER_LEN - 1);
        targetArr[i].name[PLAYER_LEN - 1] = '\0';
        targetArr[i].points=0;
        token = strtok(NULL, SEP_WORD);
        i++;
    }
    if(token == NULL&&i<playersNum)return 1;
    return 0;
}
void gameStart(const int BOARD_DIM,const int NUM_PLAYERS,player* players,char objects[][MAX_SIZE_WORD], int* positions);


/// check if the inputs is valid
int isNotValid(int argc,char* argv[] ){
    if(argc<4)return (1);
    const int BOARD_DIM =atoi(argv[1]);
    const int NUM_OBJECTS = (BOARD_DIM*BOARD_DIM)/2;
    int numPos=NUM_OBJECTS*2;
    if(argc!=4+NUM_OBJECTS+numPos)return (1);
    int position2[numPos];
    memset(position2, 0, sizeof(position2));
    for(int i=0;i<numPos;i++){
        int current_pos = atoi(argv[i+4+NUM_OBJECTS]);
        if(current_pos>=numPos||numPos<0)return 1;
        if (position2[current_pos]==ERROR_SYNTAX)return 1;
        else position2[current_pos]=ERROR_SYNTAX;
    }
    return 0;
}


int main(int argc, char* argv[])
{
    ///check if the input is valid
    if(isNotValid(argc,argv)){
        printf("INVALID INPUT");
        return 0;
    }
    /// insert the input to the varibles
    const int BOARD_DIM =atoi(argv[1]);
    const int NUM_OBJECTS = (BOARD_DIM*BOARD_DIM)/2;
    char objects[NUM_OBJECTS][MAX_SIZE_WORD];
    for(int i=0;i<NUM_OBJECTS;i++)strcpy(objects[i],argv[i+4]);
    int numPos=NUM_OBJECTS*2;
    int positions[numPos+1];
    for(int i=0;i<numPos;i++)positions[i]=atoi(argv[i+4+NUM_OBJECTS]);
    const int NUM_PLAYERS = atoi(argv[2]);
    char players[NUM_PLAYERS*20];
    strcpy(players,argv[3]);
    player sepPlayers[MEMBERS_LEN];
    if(sepPlayersInit(players,sepPlayers,NUM_PLAYERS)){
        printf("INVALID INPUT");
        return 0;
    }

    //start the game!!!
    landingScreen(BOARD_DIM,NUM_OBJECTS,objects);
    gameStart(BOARD_DIM,NUM_PLAYERS,sepPlayers,objects,positions);
    return 0;
}


///*landing screen*///
    ///.print landing table's funcitons
void printLandingTitleRow(int rowDim){
//print the title of the row
        printf("  |");
        for(int i=0;i<rowDim;i++){
            printf("  %d  |",i);
        }
        printf("\n");
}
void printLandingSepLine(int rowDim){
//print the separate line of the row
    const char sepLine[]="------";
    printf("---");
        for(int i =0;i<rowDim;i++){
            printf("%s",sepLine);
        }
        printf("\n");
}

void printLandingTableRow(int roIdx,int rowDim){
//print the actual row in the table
        printf("%d |",rowIdx);
        for(int i=0;i<rowDim;i++){
            printf("(%d,%d)|",rowIdx,i);
        }
        printf("\n");

}
    ///.
//this func will print the welcome table
void printLandingTable(const int BOARD_DIM){
    printLandingTitleRow(BOARD_DIM);
    for(int i=0;i<BOARD_DIM;i++){
      printLandingSepLine(BOARD_DIM);
      printLandingTableRow(i,BOARD_DIM);
    }
    printLandingSepLine(BOARD_DIM);
    printf("\n");
}
    ///..print players functions
void printPlayerRow(int idx,char *name){
    printf("%d. %s\n", idx,name);
}
    ///..
void printObjects(const int NUM_OBJECTS, char objects[][MAX_SIZE_WORD]){
//this func will print the players
    for (int i = 0; i < NUM_OBJECTS; i++) {
        printPlayerRow((i+1),objects[i]);
    }
}
///
//this func will print the starting message
void landingScreen(const int BOARD_DIM,const int NUM_OBJECTS,char objects[][MAX_SIZE_WORD]){
    printf("Welcome to the Memory Card Game!\n"
    "The game will be played on the following board:\n\n");
    printLandingTable(BOARD_DIM);
    printf("And the following objects:\n\n");
    printObjects(NUM_OBJECTS,objects);
    printf("\n");
    printf("Let the game begin!\n\n");
}
///*end landing screen*///


///*game start*///
///
///.print game table's funcitons
void printGameSepLine(const int BOARD_DIM){
    printf("-");
    //this func will print the sep lines
    for(int i=0;i<BOARD_DIM;i++)printf("----------------");
    printf("\n");
}

///..print printGameTableRow's funcitons
void wordCenter(char* word){
    const int CELL_LEN=15;
    int currentHalfWay =(15 - strlen(word))/2;
    int unnecessarySpace = strlen(word)%2;
    for(int i=0;i<currentHalfWay;i++)printf(" ");
    printf("%s",word);
    for(int i=0;i<currentHalfWay-unnecessarySpace;i++)printf(" ");
}

void printCell(char* value){
    //this func will print the cell of the table
    wordCenter(value);
    printf("|");
}
        ///..
void printGameTableRow(const int BOARD_DIM, char (*currentRow)[MAX_SIZE_WORD]) {
    // This function will print the actual rows
    printf("|");
    for (int col = 0; col < BOARD_DIM; col++) {
        printCell(currentRow[col]);
    }
    printf("\n");
}

void printGameTable(const int BOARD_DIM, char currentTable[][MAX_SIZE_BOARD][MAX_SIZE_WORD]) {
    // This will print the game table
    for (int i = 0; i < BOARD_DIM; i++) {
        printGameSepLine(BOARD_DIM);
        printGameTableRow(BOARD_DIM, currentTable[i]);
    }
    printGameSepLine(BOARD_DIM);
    printf("\n");
}

///

///
///.print turn action functions
int isFlipped(char currentTable[][MAX_SIZE_BOARD][MAX_SIZE_WORD],int coordinate1,int coordinate2){
    //this function will check if this cell was chosen and return 1 or 0;
    return (strcmp(currentTable[coordinate1][coordinate2], "X"));
}
///.
///.put the value of the coordinate in the pointer
int getCoordinatesVal(const int BOARD_DIM,char name[PLAYER_LEN],int coord1,int coord2, char objects[][MAX_SIZE_WORD],int* positions){
    int positionIdx =  coord1*BOARD_DIM+coord2;
    for(int i = 0;i<BOARD_DIM*BOARD_DIM;i++){
        if(positions[i]==positionIdx){
            strcpy(name,objects[i/2]);

            if(i%2==0)return positions[i+1];
            return positions[i-1];
            //return positions[i+(((i%2))*2)-1];
        }
    }
    return ERROR_SYNTAX;

}
///.


int turnAction(const int BOARD_DIM,char currentTable[][MAXSIZEBOARD][MAXSIZEWORD],char objects[][MAXSIZEWORD],int* positions);

///. print invalid move
int invalidMove(const int BOARD_DIM,char currentTable[][MAX_SIZE_BOARD][MAX_SIZE_WORD],char objects[][MAX_SIZE_WORD],int* positions){
    printf("Invalid move. Try again.\n");
    return turnAction(BOARD_DIM,currentTable,objects,positions);
}


int turnAction(const int BOARD_DIM,char currentTable[][MAX_SIZE_BOARD][MAX_SIZE_WORD],char objects[][MAX_SIZE_WORD],int* positions){
//this will do the action
        char firstVal[PLAYER_LEN];
        int coord1,coord2,coord3,coord4;
        printf("Enter the coordinates of the first card (row col): ");
        scanf("%d",&coord1);
        scanf("%d",&coord2);
        //check if the move is valid
        if(coord1>=BOARD_DIM||coord2>=BOARD_DIM)
            return invalidMove(BOARD_DIM,currentTable,objects,positions);

        
        // get the correct next step
        int successPosition = getCoordinatesVal(BOARD_DIM,firstVal,coord1,coord2,objects,positions);


        printf("Enter the coordinates of the second card (row col): ");
        scanf("%d",&coord3);
        scanf("%d",&coord4);
        if(isFlipped(currentTable,coord1,coord2))
            return invalidMove(BOARD_DIM,currentTable,objects,positions);
        if(successPosition==ERRORSYNTC)
            return invalidMove(BOARD_DIM,currentTable,objects,positions);
        if(coord3>=BOARD_DIM||coord4>=BOARD_DIM||(coord3==coord1&&coord4==coord2))
            return invalidMove(BOARD_DIM,currentTable,objects,positions);
        
        if(coord3*BOARD_DIM+coord4==successPosition){
            strcpy(currentTable[coord1][coord2], firstVal);
            strcpy(currentTable[coord3][coord4], firstVal);
            printf("Match!\n\n");
            return 1;
        }
        printf("No match. Try again.\n\n");
//return it will return if the player was right 1/0
    return 0;
}
///

/// set the first table
void setCurrentTable(const int BOARD_DIM, char currentTable[][MAXSIZEBOARD][MAXSIZEWORD]) {
    for (int i = 0; i < BOARD_DIM; i++) {
        for(int j = 0; j < BOARD_DIM; j++) {
            strcpy(currentTable[i][j],"X");
        }
    }
}

/// print the results
void result(player* players,int numPlayers){
    int tie=0;
    char winner[PLAYERLEN];
    int sum=-1;
    for(int i=0;i<numPlayers;i++){
        if(players[i].points>sum){strcpy(winner,players[i].name);tie=0;sum=players[i].points;}
        else if(players[i].points==sum)tie=1;
    }
    if(tie==1) printf("It's a tie!");
    else printf("Congratulations %s! You won!",winner);
}

/// The actual game main function
void gameStart(const int BOARD_DIM,const int NUM_PLAYERS, player* players,char objects[][MAX_SIZE_WORD], int* positions){
    int totalPoints = BOARD_DIM*BOARD_DIM/2;
    int currentPlayerIdx = 0;
    char currentTable[MAX_SIZE_BOARD][MAX_SIZE_BOARD][MAX_SIZE_WORD];
    setCurrentTable(BOARD_DIM,currentTable);
    while(totalPoints!=0){
        printf("Current board state:\n");
        printGameTable(BOARD_DIM, currentTable);
        printf("It is %s's turn.\n",players[currentPlayerIdx].name);
        int pointTemp = turnAction(BOARD_DIM,currentTable,objects,positions);
        if(pointTemp==1){
            totalPoints-=1;
            players[currentPlayerIdx].points+=1;
        }else currentPlayerIdx = (++currentPlayerIdx)%NUM_PLAYERS;
        printf("The scores are:\n");
        for(int i=0;i<NUM_PLAYERS-1;i++)printf("%s: %d, ",players[i].name,players[i].points);
        printf("%s: %d\n",players[NUM_PLAYERS-1].name,players[NUM_PLAYERS-1].points);
    }
    result(players,NUM_PLAYERS);
}
///*end game start*///
