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

int play_move(board_t board,move_t move,player_t player){
    assert (board[0][move.col]==0);
    for (int i=3;i>=0;i--){
        if (board[i][move.col]==0){
            board[i][move.col]=player;
            return i;
        }
    }
}

int has_won(board_t board, player_t player)
{   
    // Horizontal
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 2; col++) {
            if (board[row][col] == player &&
                board[row][col + 1] == player &&
                board[row][col + 2] == player &&
                board[row][col + 3] == player) {
                return 1;
            }
        }
    }

    // Vertical
    for (int col = 0; col < 5; col++) {
        for (int row = 0; row < 1; row++) {
            if (board[row][col] == player &&
                board[row + 1][col] == player &&
                board[row + 2][col] == player &&
                board[row + 3][col] == player) {
                return 1;
            }
        }
    }

    // Diagonal1
    for (int row = 0; row < 1; row++) {
        for (int col = 0; col < 2; col++) {
            if (board[row][col] == player &&
                board[row + 1][col + 1] == player &&
                board[row + 2][col + 2] == player &&
                board[row + 3][col + 3] == player) {
                return 1;
            }
        }
    }

    // Diagonal2
    for (int row = 3; row >= 2; row--) {
        for (int col = 0; col < 2; col++) {
            if (board[row][col] == player &&
                board[row - 1][col + 1] == player &&
                board[row - 2][col + 2] == player &&
                board[row - 3][col + 3] == player) {
                return 1;
            }
        }
    }

    return 0;
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



move_t best_move(board_t board, player_t player)
{   move_t response;
    move_t candidate;
    int no_candidate = 1;

    for (int col = 0; col < 5; ++col) {
        if (board[0][col]==0) {
            move_t move;
            move.col=col;
            int row= play_move(board,move,player);
            if (has_won(board, player)) {
                board[row][col]=EMPTY;
                return (move_t){col, 1};
            }
            board[row][col]=EMPTY;
        }
    }

    player_t opponent = invert(player);
    for (int col = 0; col < 5; ++col) {
        if (board[0][col]==0) {
            move_t move;
            move.col=col;
            int row = play_move(board,move,player);
            if (has_won(board, opponent)) {
                board[row][col]=EMPTY;
                return (move_t){col, 1};
            }
            board[row][col]=EMPTY;
        }
    }

    for (int col = 0; col < 5; ++col) {
        if (board[0][col]==0) {
            move_t move;
            move.col=col;
            int row = play_move(board,move,player);
            if (is_full(board)) {
                board[row][col]=EMPTY;
                return (move_t){col, 0};
            }
            response = best_move(board, invert(player));
            board[row][col]=EMPTY;
            if (response.score == -1) {
                return (move_t){col, 1};
            } else if (response.score == 0) {
                candidate = (move_t){col, 0};
                no_candidate = 0;
            } else {
                if (no_candidate) {
                    candidate = (move_t){col, -1};
                    no_candidate = 0;
                }
            }
        }
    }

    return candidate;
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
    /* Your game play logic. */
    /* The user should have the option to select red or blue player. */
    int move, col;
    board_t board={{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
    move_t response;
    int x;
    printf("You are red colour, Do you choose to be player 1 or 2: ");
    scanf("%d", &x);
    player_t current;

    if (x == 1) {
        current = RED;
    } else if (x == 2) {
        current = BLUE;
    } else {
        printf("\nInvalid choice");
        return 1; // Exit the program due to invalid choice
    }

    while (1) {
        if (x != 1 && x != 2) {
            printf("\nInvalid choice");
            break;
        }
        print_board(board);
        printf("\n\n");

        if (current == RED) {
            printf("0  1  2  3  4\n");
            printf("\nEnter your move: ");
            scanf("%d", &move);
            col = move;

            if (col >= 0 && col < 5 && board[0][col]==0) {
                move_t move;
                move.col=col;
                play_move(board, move, current);
            } else {
                printf("Invalid move. Try again.\n");
                continue;
            }
        } else {
            response = best_move(board, current);
            col = response.col;

            if (col >= 0 && col < 5 && board[0][col]==0) {
                move_t move;
                move.col=col;
                play_move(board, move, current);
            }
        }

        if (has_won(board, current)) {
            print_board(board);
            printf("Player %c has won!\n", (current == RED) ? 'R' : 'B');
            break;
        }else if (is_full(board)) {
            printf("It's a draw!\n");
            break;
        }

        current = invert(current);
    }
    return 0;
}