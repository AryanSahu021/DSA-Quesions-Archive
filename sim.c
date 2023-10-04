#include <stdio.h>
#include <assert.h>



/*
 * The status of a line.
 */
enum {
    NO = 0, /* No line */
    RED = 1,
    BLUE = 2
};

/*
 * The board records the colors of the lines.
 * board[0] = color of 12
 * board[1] = color of 13
 * ...
 * board[14] = color of 56
 */
typedef char board_t[15];
typedef char player_t; /* A player should be RED or BLUE. */

player_t invert(player_t player){
    switch (player){
        case RED: return BLUE;
        case BLUE: return RED;
    }
}

int has_won(board_t board, player_t player)
{   
    player = invert(player);
    int l=4;
    int k=l;
    for (int i=0;i<13;i++){
        if (board[i]==player){
            if (i<4){
                for (int j=i+1;j<5;j++){
                    if (board[j]==player){
                        if (board[j+k]==player){
                            return 1;
                        }
                    }
                } 
            }
            else if (i==4){
                k=0;
                l=4;
            }
            else if (i<8 && i>4){
                for (int j=i+1;j<9;j++){
                    if (board[j]==player){
                        if (board[j+k]==player){
                            return 1;
                        }
                    }
                }
            }
            else if (i==8){
                k=0;
                l=3;
            }
            else if (i<12 && i>8){
                for (int j=i+1;j<12;j++){
                    if (board[j]==player){
                        if (board[j+k]==player){
                            return 1;
                        }
                    }
                }
            }
            else if (i==12){
                if ((board[13]==player)&&(board[14]==player)){
                    return 1;
                }
            }
        }
        l--;
        k=k+l;
    }
    return 0;
}

int is_full(board_t board)
{
    int flag=1;
    for (int i=0;i<15;i++){
        if (board[i]==0){
            flag=0;
        }
    }
    return flag;
}

typedef struct {
    int line; /* 0 for 12, 1 for 13, ..., 14 for 56. */
    int score; /* -1 for loss, 0 for draw, 1 for win. */
} move_t;

move_t best_move(board_t board, player_t player)
{
    move_t move;
    int i=0;
    int movefound=0;
    move_t cur_move;
    while (i<15){
        if (board[i]==0){
            move.line=i;
            board[i]=player;
            if (has_won(board,player)){
                move.score=1;
                board[i]=0;
                return move;
            }
            else if (has_won(board,invert(player))){
                move.score=-1;
                if (movefound==0){
                    cur_move.line=i;
                    cur_move.score=-1;
                }
            }
            move_t newmove;
            newmove=best_move(board,invert(player));
            if (newmove.score==-1){
                move.score=1;
                board[i]=0;
                return move;
            }
            else if (newmove.score==0){
                if (movefound==0){
                    cur_move.line=i;
                    cur_move.score=0;
                    movefound=1;
                }
            }
            board[i]=NO;

        }
        i=i+1;
    }
    return cur_move;
}

void print_board(board_t board)
{
    for (int i = 0; i < 15; ++i) {
        switch (board[i]) {
        case NO: printf("N "); break;
        case RED: printf("R  "); break;
        case BLUE: printf("B  "); break;
        }
    }
}


int main()
{
    board_t board={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    player_t player=RED;
    while (!(is_full(board))){
        move_t move;
        scanf("%d",&move.line);
        assert(board[move.line]==0);
        board[move.line] = player;
        if (has_won(board, player)){
            printf("You Won!!");
            print_board(board);
            break;
        }
        move_t bestmove = best_move(board, invert(player));
        board[bestmove.line] = invert(player);
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
