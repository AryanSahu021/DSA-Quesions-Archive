#include <stdio.h>
#include <assert.h>
/* Implement connect 4 on a 5 (columns) x 4 (rows) board. */
enum {
    EMPTY = 0,
    RED = 1,
    BLUE = 2,
};

typedef char board_t[4][5];
typedef char player_t;

typedef struct {
    int col;
    int score;
} move_t;

player_t invert(player_t player){
    switch (player){
        case RED: return BLUE;
        case BLUE: return RED;
    }
}

void play_move(board_t board,move_t move,player_t player){
    assert (board[0][move.col]==0);
    for (int i=0;i<4;i++){
        if (board[i][move.col]!=0){
            board[i-1][move.col]=player;
            break;
        }
        else if (i==3){
            board[i][move.col]=player;
        }
    }
}

int has_won(board_t board, player_t player)
{   
    for (int i=0;i<4;i++){
        for (int j=0;j<5;j++){
            if (board[i][j]==player){
                if ((i+3)<4){
                    int flag=1;
                    for (int k=i;k<(i+4);k++){
                        if (board[k][j]!=player){
                            flag=0;
                            break;
                        }
                    }
                    if (flag){
                        return 1;
                    }
                }
                if ((i-3)>=0){
                    int flag=1;
                    for (int k=i;k>=(i-3);k--){
                        if (board[k][j]!=player){
                            flag=0;
                            break;
                        }
                    }
                    if (flag){
                        return 1;
                    }
                }
                if ((j+3)<=4){
                    int flag=1;
                    for (int k=j;k<(j+4);k++){
                        if (board[i][k]!=player){
                            flag=0;
                            break;
                        }
                    }
                    if (flag){
                        return 1;
                    }
                }
                if ((j-3)>=0){
                    int flag=1;
                    for (int k=j;k>=(j-3);k--){
                        if (board[i][k]!=player){
                            flag=0;
                            break;
                        }
                    }
                    if (flag){
                        return 1;
                    }
                }
                if (((i+3)<4)&&((j+3)<=4)){
                    int flag=1;
                    int k=i;
                    int l=j;
                    while (k<(i+4)){
                        if (board[k][l]!=player){
                            flag=0;
                            break;
                        }
                        k++;
                        l++;
                    }
                    if (flag){
                        return 1;
                    }
                }
                if (((i-3)>=0)&&((j-3)>=0)){
                    int flag=1;
                    int k=i;
                    int l=j;
                    while (k<(i+4)){
                        if (board[k][l]!=player){
                            flag=0;
                            break;
                        }
                        k--;
                        l--;
                    }
                    if (flag){
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

void reset_move(board_t board,move_t move){
    for (int i=0;i<4;i++){
        if (board[i][move.col]!=0){
            board[i][move.col]=0;
            break;
        }
    }
}
int is_full(board_t board)
{
    for (int j=0;j<5;j++){
        if (board[0][j]==0){
            return 0;
        }
    }
    return 1;
}

typedef struct{
    int visited;
    move_t move;
} tables;
tables table[3^20];


move_t best_move(board_t board, player_t player)
{   int index=0;
    int k=0;
    for (int j=4;j>=0;j--){
        for (int i=3;i>=0;i--){
            index=index+(board[i][j]*(3^k));
            k++;
        }
    }
    if (table[index].visited){
        return table[index].move;
    }
    move_t move;
    int j=0;
    int movefound=0;
    move_t cur_move;
    while (j<5){
        if (board[0][j]==0){
            move.col=j;
            play_move(board,move,player);
            if (has_won(board,player)){
                move.score=1;
                reset_move(board,move);
                table[index].move=move;
                table[index].visited=1;
                return move;
            }
            else if (has_won(board,invert(player))){
                move.score=-1;
                if (movefound==0){
                    cur_move.col=j;
                    cur_move.score=-1;
                }
            }
            move_t newmove;
            newmove=best_move(board,invert(player));
            if (newmove.score==-1){
                move.score=1;
                reset_move(board,move);
                table[index].visited=1;
                table[index].move=move;
                return move;
            }
            else if (newmove.score==0){
                if (movefound==0){
                    cur_move.col=j;
                    cur_move.score=0;
                    movefound=1;
                }
            }
            reset_move(board,move);

        }
        j=j+1;
    }
    table[index].move=cur_move;
    table[index].visited=1;
    return cur_move;
}

void print_board(board_t board)
{
    for (int i=0;i<4;i++){
        for (int j=0;j<5;j++){
            switch (board[i][j]){
                case RED: printf("R  "); break;
                case BLUE: printf("B  "); break;
                case EMPTY : printf("0  "); break;
            }
        }
        printf("\n");
    }
}

int main()
{
    board_t board={{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
    player_t player;
    printf("Choose Color: RED:1 or BLUE:2\n");
    scanf("%c",&player);
    while (!(is_full(board))){
        move_t move;
        scanf("%d",&move.col);
        play_move(board,move,player);
        if (has_won(board, player)){
            printf("You Won!!");
            print_board(board);
            break;
        }
        move_t bestmove = best_move(board, invert(player));
        play_move(board,bestmove,invert(player));
        printf("Updated Board: \n");
        print_board(board);
        if (has_won(board, invert(player))){
            printf("You Lost!!");
            break;
        }
    }
    /* Your game play logic. */
    /* The user should have the option to select red or blue player. */
    return 0;
}