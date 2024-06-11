/***********
*Name: Ben Tau
*Id: 325394997
*Assignment: ex_4
***********/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZEBOARD 30
#define MAXSIZEWORD 8
#define PLAYERLEN 21
#define MEMBERSLEN 10
#define ERRORSYNTC -1
typedef struct player{
    char name[PLAYERLEN];
    int points;
}player;
void landing_screen(const int board_dim,const int num_objects,char objects[][MAXSIZEWORD]);

/// seperate the players and returns 1 if not valid and 0 if valid
int sep_players_init(char *players, player *target_arr, int players_num) {
    const char sep_word[2] = "#";
    char *token = strtok((char *)players, sep_word); 
    int i = 0;
    while (token != NULL && i < players_num) {
        // Copy the token into the name field of the target array element
        strncpy(target_arr[i].name, token, PLAYERLEN - 1);
        target_arr[i].name[PLAYERLEN - 1] = '\0'; 
        target_arr[i].points=0;
        token = strtok(NULL, sep_word); 
        i++;
    }
    if(token == NULL&&i<players_num)return 1;
    return 0;
}
void game_start(const int board_dim,const int num_players,player* players,char objects[][MAXSIZEWORD], int* positions);


/// check if the inputs is valid
int is_not_valid(int argc,char* argv[] ){
    if(argc<4)return (1);
    const int board_dim =atoi(argv[1]);
    const int num_objects = (board_dim*board_dim)/2;
    int num_pos=num_objects*2;
    if(argc!=4+num_objects+num_pos)return (1);
    int position2[num_pos];
    memset(position2, 0, sizeof(position2));
    for(int i=0;i<num_pos;i++){
        int current_pos = atoi(argv[i+4+num_objects]);
        if(current_pos>=num_pos||num_pos<0)return 1;
        if (position2[current_pos]==ERRORSYNTC)return 1;
        else position2[current_pos]=ERRORSYNTC;
    }
    return 0;
}


int main(int argc, char* argv[])
{
    ///check if the input is valid
    if(is_not_valid(argc,argv)){
        printf("INVALID INPUT");
        return 0;
    }
    /// insert the input to the varibles
    const int board_dim =atoi(argv[1]);
    const int num_objects = (board_dim*board_dim)/2;
    char objects[num_objects][MAXSIZEWORD];
    for(int i=0;i<num_objects;i++)strcpy(objects[i],argv[i+4]);
    int num_pos=num_objects*2;
    int positions[num_pos+1];
    for(int i=0;i<num_pos;i++)positions[i]=atoi(argv[i+4+num_objects]);
    const int num_players = atoi(argv[2]);
    char players[num_players*20];
    strcpy(players,argv[3]);
    player sep_players[MEMBERSLEN];
    if(sep_players_init(players,sep_players,num_players)){
        printf("INVALID INPUT");
        return 0;
    }

    //start the game!!!
    landing_screen(board_dim,num_objects,objects);
    game_start(board_dim,num_players,sep_players,objects,positions);
    return 0;
}


///*landing screen*///
    ///.print landing table's funcitons
void print_landing_title_row(int row_dim){
//print the title of the row
        printf("  |");
        for(int i=0;i<row_dim;i++){
            printf("  %d  |",i);
        }
        printf("\n");
}
void print_landing_sep_line(int row_dim){
//print the separate line of the row
    const char sep_line[]="------";
    printf("---");
        for(int i =0;i<row_dim;i++){
            printf("%s",sep_line);
        }
        printf("\n");
}
void print_landing_table_row(int row_idx,int row_dim){
//print the actual row in the table
        printf("%d |",row_idx);
        for(int i=0;i<row_dim;i++){
            printf("(%d,%d)|",row_idx,i);
        }
        printf("\n");

}
    ///.
//this func will print the welcome table
void print_landing_table(const int board_dim){
    print_landing_title_row(board_dim);
    for(int i=0;i<board_dim;i++){
      print_landing_sep_line(board_dim);
      print_landing_table_row(i,board_dim);
    }
    print_landing_sep_line(board_dim);
    printf("\n");
}
    ///..print players functions
void print_player_row(int idx,char *name){
    printf("%d. %s\n", idx,name);
}
    ///..
void print_objects(const int num_objects, char objects[][MAXSIZEWORD]){
//this func will print the players
    for (int i = 0; i < num_objects; i++) {
        print_player_row((i+1),objects[i]);
    }
}
///
//this func will print the starting message
void landing_screen(const int board_dim,const int num_objects,char objects[][MAXSIZEWORD]){
    printf("Welcome to the Memory Card Game!\n"
    "The game will be played on the following board:\n\n");
    print_landing_table(board_dim);
    printf("And the following objects:\n\n");
    print_objects(num_objects,objects);
    printf("\n");
    printf("Let the game begin!\n\n");
}
///*end landing screen*///


///*game start*///
///
    ///.print game table's funcitons
    void print_game_sep_line(const int board_dim){
        printf("-");
        //this func will print the sep lines
        for(int i=0;i<board_dim;i++)printf("----------------");
        printf("\n");
    }
        ///..print print_game_table_row's funcitons
    void wordCenter(char* word){
    const int CELL_LEN=15;
    int current_half_way =(15 - strlen(word))/2;
    int unnecessary_space = strlen(word)%2;
    for(int i=0;i<current_half_way;i++)printf(" ");
    printf("%s",word);
    for(int i=0;i<current_half_way-unnecessary_space;i++)printf(" ");
}
        void print_cell(char* value){
            wordCenter(value);
            printf("|");
        //this func will print the cell of the table
        }
        ///..
void print_game_table_row(const int board_dim, char (*current_row)[MAXSIZEWORD]) {
    // This function will print the actual rows
    printf("|");
    for (int col = 0; col < board_dim; col++) {
        print_cell(current_row[col]);
    }
    printf("\n");
}

void print_game_table(const int board_dim, char current_table[][MAXSIZEBOARD][MAXSIZEWORD]) {
    // This will print the game table
    for (int i = 0; i < board_dim; i++) {
        print_game_sep_line(board_dim);
        print_game_table_row(board_dim, current_table[i]);
    }
    print_game_sep_line(board_dim);
    printf("\n");
}

///

///
    ///.print turn action functions
    int is_flipped(char current_table[][MAXSIZEBOARD][MAXSIZEWORD],int cordinate1,int cordinate2){
    //this function will check if this cell was chosen and return 1 or 0;
    return (strcmp(current_table[cordinate1][cordinate2], "X"));
    }
    ///.
    ///.put the value of the coordinate in the pointer
    int get_coordinates_val(const int board_dim,char name[PLAYERLEN],int coord1,int coord2, char objects[][MAXSIZEWORD],int* positions){
        int position_idx =  coord1*board_dim+coord2;
        for(int i = 0;i<board_dim*board_dim;i++){
            if(positions[i]==position_idx){
                strcpy(name,objects[i/2]);

                if(i%2==0)return positions[i+1];
                return positions[i-1];
                //return positions[i+(((i%2))*2)-1];
            }
        }
        return ERRORSYNTC;

    }
    ///.


int turn_action(const int board_dim,char current_table[][MAXSIZEBOARD][MAXSIZEWORD],char objects[][MAXSIZEWORD],int* positions);
    ///. print invalid move
    int invalid_move(const int board_dim,char current_table[][MAXSIZEBOARD][MAXSIZEWORD],char objects[][MAXSIZEWORD],int* positions){
        printf("Invalid move. Try again.\n");
        return turn_action(board_dim,current_table,objects,positions);
    }


int turn_action(const int board_dim,char current_table[][MAXSIZEBOARD][MAXSIZEWORD],char objects[][MAXSIZEWORD],int* positions){
//this will do the action
        char first_val[PLAYERLEN];
        int coord1,coord2,coord3,coord4;
        printf("Enter the coordinates of the first card (row col): ");
        scanf("%d",&coord1);
        scanf("%d",&coord2);
        //check if the move is valid
        if(coord1>=board_dim||coord2>=board_dim)
            return invalid_move(board_dim,current_table,objects,positions);

        
        // get the correct next step
        int success_position = get_coordinates_val(board_dim,first_val,coord1,coord2,objects,positions);


        printf("Enter the coordinates of the second card (row col): ");
        scanf("%d",&coord3);
        scanf("%d",&coord4);
        if(is_flipped(current_table,coord1,coord2))
            return invalid_move(board_dim,current_table,objects,positions);
        if(success_position==ERRORSYNTC)
            return invalid_move(board_dim,current_table,objects,positions);
        if(coord3>=board_dim||coord4>=board_dim||(coord3==coord1&&coord4==coord2))
            return invalid_move(board_dim,current_table,objects,positions);
        
        if(coord3*board_dim+coord4==success_position){
            strcpy(current_table[coord1][coord2], first_val);
            strcpy(current_table[coord3][coord4], first_val);
            printf("Match!\n\n");
            return 1;
        }
        printf("No match. Try again.\n\n");
//return it will return if the player was right 1/0
    return 0;
}
///

/// set the first table
void set_current_table(const int board_dim, char current_table[][MAXSIZEBOARD][MAXSIZEWORD]) {
    for (int i = 0; i < board_dim; i++) {
        for(int j = 0; j < board_dim; j++) {
            strcpy(current_table[i][j],"X");
        }
    }
}

/// print the results
void result(player* players,int num_players){
    int tie=0;
    char winner[PLAYERLEN];
    int sum=-1;
    for(int i=0;i<num_players;i++){
        if(players[i].points>sum){strcpy(winner,players[i].name);tie=0;sum=players[i].points;}
        else if(players[i].points==sum)tie=1;
    }
    if(tie==1) printf("It's a tie!");
    else printf("Congratulations %s! You won!",winner);
}

/// The actual game main function
void game_start(const int board_dim,const int num_players, player* players,char objects[][MAXSIZEWORD], int* positions){
    int total_points = board_dim*board_dim/2;
    int current_player_idx = 0;
    char current_table[MAXSIZEBOARD][MAXSIZEBOARD][MAXSIZEWORD];
    set_current_table(board_dim,current_table);
    while(total_points!=0){
        printf("Current board state:\n");
        print_game_table(board_dim, current_table);
        printf("It is %s's turn.\n",players[current_player_idx].name);
        int point_temp = turn_action(board_dim,current_table,objects,positions);
        if(point_temp==1){
            total_points-=1;
            players[current_player_idx].points+=1;
        }else current_player_idx = (++current_player_idx)%num_players;
        printf("The scores are:\n");
        for(int i=0;i<num_players-1;i++)printf("%s: %d, ",players[i].name,players[i].points);
        printf("%s: %d\n",players[num_players-1].name,players[num_players-1].points);
    }
    result(players,num_players);
}
///*end game start*///
