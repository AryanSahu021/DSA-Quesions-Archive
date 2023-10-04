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
    
}

void print_board(board_t board)
{
    for (int i = 0; i < 15; ++i) {
        switch (board[i]) {
        case RED: printf("R  "); break;
        case BLUE: printf("B  "); break;
        }
    }
}


int main()
{
    board_t board;
    player_t player = RED;
    while (!(is_full(board))){
        print_board(board);
        move_t move;
        scanf("%d",&move.line);
        board[move.line] = player;
        if (has_won(board, player)){
            printf("You Won!!");
            break;
        }
        move_t bestmove = best_move(board, invert(player));
        board[bestmove.line] = invert(player);
        printf("Updated Board: \n");
        if (has_won(board, invert(player))){
            printf("You Lost!!");
            break;
        }
    /* Your game play logic. */
    /* The user should have the option to select red or blue player. */
    return 0;
}
