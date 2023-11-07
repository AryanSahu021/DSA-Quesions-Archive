#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
enum {
    EMPTY = 0,
    L,
    R,
    U,
    D,
    TOP,
    BOTTOM,
    SIDE
};
typedef char cube;/* The position of the logo is specified by the following values-
0: Top 
1: Right
2: Back
3: Left
4: Front
5: Bottom*/

typedef cube board_t[3][3];

typedef struct {
    int col;
    int row;
    char side;
    int score;
} move_t;

typedef struct QueueNode {
    board_t board;
    move_t move;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

void enqueue(Queue* queue, board_t board, move_t move) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (!newNode) {
        perror("Memory allocation error");
        exit(1);
    }

    memcpy(newNode->board, board, sizeof(board_t));
    newNode->move = move;
    newNode->next = NULL;

    if (queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}


int isEmpty(Queue* queue) {
    return (queue->front == NULL);
}

void dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        return;
    }

    QueueNode* temp = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
}

void play_move(board_t board,move_t move){
    assert(board[move.row][move.col]==-1);
    cube c;
    switch (move.side)
    {
    case L:
        switch (board[move.row][move.col-1])
        {
        case 0:
            board[move.row][move.col]=1;
            break;
        case 1:
            board[move.row][move.col]=5;
            break;
        case 2:
            board[move.row][move.col]=2;
            break;
        case 3:
            board[move.row][move.col]=0;
            break;
        case 4:
            board[move.row][move.col]=4;
            break;
        case 5:
            board[move.row][move.col]=3;
            break;
        
        default:
            break;
        }
        board[move.row][move.col-1]=-1;
        break;
    case R:
        switch (board[move.row][move.col+1])
        {
        case 0:
            board[move.row][move.col]=3;
            break;
        case 1:
            board[move.row][move.col]=0;
            break;
        case 2:
            board[move.row][move.col]=2;
            break;
        case 3:
            board[move.row][move.col]=5;
            break;
        case 4:
            board[move.row][move.col]=4;
            break;
        case 5:
            board[move.row][move.col]=1;
            break;
        
        default:
            break;
        }
        board[move.row][move.col+1]=-1;
        break;
    case U:
        switch (board[move.row-1][move.col])
        {
        case 0:
            board[move.row][move.col]=4;
            break;
        case 1:
            board[move.row][move.col]=1;
            break;
        case 2:
            board[move.row][move.col]=0;
            break;
        case 3:
            board[move.row][move.col]=3;
            break;
        case 4:
            board[move.row][move.col]=5;
            break;
        case 5:
            board[move.row][move.col]=2;
            break;
        
        default:
            break;
        }
        board[move.row-1][move.col]=-1;
        break;
    case D:
        switch (board[move.row+1][move.col])
        {
        case 0:
            board[move.row][move.col]=2;
            break;
        case 1:
            board[move.row][move.col]=1;
            break;
        case 2:
            board[move.row][move.col]=5;
            break;
        case 3:
            board[move.row][move.col]=3;
            break;
        case 4:
            board[move.row][move.col]=0;
            break;
        case 5:
            board[move.row][move.col]=4;
            break;
        
        default:
            break;
        }
        board[move.row+1][move.col]=-1;
        break;
    
    default:
        break;
    }
}
char oppose(move_t move){
    switch (move.side)
    {
    case 1:
        return 2;
        break;
    case 2:
        return 1;
        break;
    case 3:
        return 4;
        break;
    case 4:
        return 1;
        break;
    default:
        break;
    }
}
int has_won(board_t board)
{   
    if (board[1][1]!=-1){
        return 0;
    }
    for (int i=0;i<3;i++){
        for (int j=0;j<3;j++){
            if (board[i][j]!=0){
                if ((i==1)&&(j==1)){
                    continue;
                }
                return 0;
            }
        }
    }
    return 1;
}

void reset_move(board_t board,move_t move){
    switch (move.side)
    {
    case L:
        move.col=move.col-1;
        move.side=R;
        break;
    case R:
        move.col=move.col+1;
        move.side=L;
        break;
    case U:
        move.row=move.row-1;
        move.side=D;
        break;
    case D:
        move.row=move.row+1;
        move.side=U;
        break;
    
    default:
        break;
    }
    play_move(board,move);
}
void printboard(board_t board){
    for (int i=0;i<3;i++){
        for (int j=0;j<3;j++){
            printf("%d ",board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
char moves[4]={L,R,U,D};
int visited[41000000];

int bfs_solver(board_t initial_board) {
    int won=0;
    Queue queue;
    queue.front = queue.rear = NULL;
    move_t initial_move = {1, 1, 0, 0};
    enqueue(&queue, initial_board, initial_move);
    
    while (!isEmpty(&queue)) {
        board_t current_board;
        move_t current_move;
        char temp;
        memcpy(current_board, queue.front->board, sizeof(board_t));
        current_move = queue.front->move;
        dequeue(&queue);

        if (has_won(current_board)) {
            printboard(current_board);
            printf("HAS WON!!");
            won=1;
        } else {
            for (int l=0;l<4;l++){
                move_t next_move=current_move;
                next_move.side=moves[l];
                switch (l)
                {
                case 0:
                    if (next_move.col>0){
                        next_move.col--;
                    }
                    else{continue;}
                    break;
                case 1:
                    if (next_move.col<2){ 
                        next_move.col++;
                    }
                    else{continue;}
                    break;
                case 2:
                    if (next_move.row>0){
                        next_move.row--;
                    }
                    else{continue;}
                    break;
                case 3:
                    if (next_move.row<2){
                        next_move.row++;
                    }
                    else{continue;}
                    break;
                default:
                    break;
                }
                if ((oppose(current_move)!=next_move.side)){              
                    temp=current_move.side;
                    current_move.side=next_move.side;
                    play_move(current_board,current_move);
                    
                    int ind=0;
                    int k=1;
                    for (int j=0;j<3;j++){
                        for (int i=0;i<3;i++){
                            ind+=(current_board[i][j]+1)*k;
                            k=k*7;
                        }
                    }
                    if (!visited[ind]){
                        enqueue(&queue,current_board,next_move);
                        visited[ind]=1;
                    }
                    reset_move(current_board,current_move);
                    current_move.side=temp;
                }
            }
        }
    }
    return won;
}

int main()
{
    board_t board={{5,5,5},{5,-1,5},{5,5,5}};
    
    bfs_solver(board);
    return 0;
}