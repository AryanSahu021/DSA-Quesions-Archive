#include <stdio.h>
#include <string.h>
#include <stdlib.h>
enum {
    WHITE,
    RED,
    GREEN,
    ORANGE,
    BLUE,
    YELLOW,
    R,
    R2,
    U,
    U2,
    F,
    F2,
    RI,
    UI,
    FI,
    D,
    L
};
typedef char cube[6][2][2];
/*    R,6
    R2,7
    U,8
    U2,9
    F,10
    F2,11
    RI,12
    UI,13
    FI,14
*/

typedef struct parentNode{
    cube board;
    char move;
    struct parentNode* parent;
} parentNode;

typedef struct paths{
    parentNode* start;
    parentNode* end;
}paths;

typedef struct QueueNode {
    cube board;
    char move;
    struct QueueNode* next;
    struct parentNode* same;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;


void enqueue(Queue* queue, cube board, char move,parentNode* p) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (!newNode) {
        perror("Memory allocation error");
        exit(1);
    }

    memcpy(newNode->board, board, sizeof(cube));
    newNode->move = move;
    newNode->next = NULL;
    newNode->same = p;
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
void transpose(char face[2][2],char side){
    if (side==R){
        char temp=face[0][0];
        face[0][0]=face[1][0];
        face[1][0]=face[1][1];
        face[1][1]=face[0][1];
        face[0][1]=temp;
    }
    else if (side==L){
        char temp=face[0][0];
        face[0][0]=face[0][1];
        face[0][1]=face[1][1];
        face[1][1]=face[1][0];
        face[1][0]=temp;
    }
}
void rotate_cube(cube c,char side){
    char face[2][2];
    char face_2[2][2];
    char face_3[2][2];
    switch (side)
    {
    case R:
        transpose(c[0],R);
        transpose(c[5],R);
        transpose(c[2],R);
        transpose(c[4],R);
        for (int k=0;k<6;k++){
            for (int i=0;i<2;i++){
                for (int j=0;j<2;j++){
                    switch (k)
                    {
                    case 0:
                        face[i][j]=c[k][i][j];
                        c[k][i][j]=c[k+4][i][j];
                        break;
                    case 4:
                        c[k][i][j]=c[k+1][i][j];
                        break;
                    case 5:
                        c[k][i][j]=face_2[i][j];
                        break;
                    case 2:
                        face_2[i][j]=c[k][i][j];
                        c[k][i][j]=face[i][j];
                        break;
                    
                    default:
                        break;
                    }
                }
            }

        }
        transpose(c[1],R);
        transpose(c[3],L);
        break;
    case L:
        transpose(c[0],L);
        transpose(c[5],L);
        transpose(c[2],L);
        transpose(c[4],L);
        for (int k=0;k<6;k++){
            for (int i=0;i<2;i++){
                for (int j=0;j<2;j++){
                    switch (k)
                    {
                    case 0:
                        face[i][j]=c[k][i][j];
                        c[k][i][j]=c[k+2][i][j];
                        break;
                    case 2:
                        c[k][i][j]=c[k+3][i][j];
                        break;
                    case 5:
                        c[k][i][j]=face_2[i][j];
                        break;
                    case 4:
                        face_2[i][j]=c[k][i][j];
                        c[k][i][j]=face[i][j];
                        break;
                    
                    default:
                        break;
                    }
                }
            }

        }
        transpose(c[1],L);
        transpose(c[3],R);
        break;
    case F:
        for (int k=0;k<6;k++){
            for (int i=0;i<2;i++){
                for (int j=0;j<2;j++){
                    switch (k)
                    {
                    case 1:
                        face[i][j]=c[k][i][j];
                        c[k][i][j]=c[k+3][i][j];
                        break;
                    case 4:
                        c[k][i][j]=face_3[i][j];
                        break;
                    case 3:
                        face_3[i][j]=c[k][i][j];
                        c[k][i][j]=face_2[i][j];
                        break;
                    case 2:
                        face_2[i][j]=c[k][i][j];
                        c[k][i][j]=face[i][j];
                        break;
                    
                    default:
                        break;
                    }
                }
            }

        }
        transpose(c[0],L);
        transpose(c[5],R);
        break;
    case FI:
        
        for (int k=0;k<6;k++){
            for (int i=0;i<2;i++){
                for (int j=0;j<2;j++){
                    switch (k)
                    {
                    case 1:
                        face[i][j]=c[k][i][j];
                        c[k][i][j]=c[k+1][i][j];
                        break;
                    case 2:
                        c[k][i][j]=c[k+1][i][j];
                        break;
                    case 3:
                        c[k][i][j]=c[k+1][i][j];
                        break;
                    case 4:
                        c[k][i][j]=face[i][j];
                        break;
                    
                    default:
                        break;
                    }
                }
            }

        }
        transpose(c[0],R);
        transpose(c[5],L);
        break;
    default:
        break;
    }
}

void Right(cube board){
    char x=board[0][0][1];
    char y=board[0][1][1];
    board[0][0][1]=board[1][0][1];
    board[0][1][1]=board[1][1][1];
    board[1][0][1]=board[5][0][1];
    board[1][1][1]=board[5][1][1];
    board[5][0][1]=board[3][1][0];
    board[5][1][1]=board[3][0][0];
    board[3][1][0]=x;
    board[3][0][0]=y;
    transpose(board[2],R);
}
void Right_I(cube board){
    char x=board[0][0][1];
    char y=board[0][1][1];
    board[0][0][1]=board[3][1][0];
    board[0][1][1]=board[3][0][0];
    board[3][1][0]=board[5][0][1];
    board[3][0][0]=board[5][1][1];
    board[5][0][1]=board[1][0][1];
    board[5][1][1]=board[1][1][1];
    board[1][0][1]=x;
    board[1][1][1]=y;
    transpose(board[2],L);
}

void play_move(cube c,char move){
    switch (move)
    {
    case R:
        Right(c);
        break;
    case RI:
        Right_I(c);
        break;
    case R2:
        Right(c);
        Right(c);
        break;
    case U:
        rotate_cube(c,R);
        Right(c);
        rotate_cube(c,L);
        break;
    case UI:
        rotate_cube(c,R);
        Right_I(c);
        rotate_cube(c,L);
        break;
    case U2:
        rotate_cube(c,R);
        Right(c);
        Right(c);
        rotate_cube(c,L);
        break;
    case F:
        rotate_cube(c,F);
        Right(c);
        rotate_cube(c,FI);
        break;
    case FI:
        rotate_cube(c,F);
        Right_I(c);
        rotate_cube(c,FI);
        break;
    case F2:
        rotate_cube(c,F);
        Right(c);
        Right(c);
        rotate_cube(c,FI);
        break;
    default:
        break;
    }
}
char oppose(char move){
    switch (move)
    {
    case R:
        return RI;
        break;
    case U:
        return UI;
        break;
    case F:
        return FI;
        break;
    case RI:
        return R;
        break;
    case UI:
        return U;
        break;
    case FI:
        return F;
        break;    
    default:
        return move;
        break;
    }
}
char colours[6]={WHITE,RED,GREEN,ORANGE,BLUE,YELLOW};
int has_won(cube c)
{   
    int flag=1;
    int start;
    for (int m=0;m<6;m++){
        if (c[0][0][0]==colours[m]){
            start=m;
        }
    }
    for (int i=0;i<6;i++){
        for (int j=0;j<2;j++){
            for (int k=0;k<2;k++){
                if (c[(start+i)%6][j][k]!=colours[i]){
                    flag= 0;
                }
            }
        }
    }
    return flag;
}

void reset_move(cube board,char move){
    play_move(board,oppose(move));
}
/*Hierarchy:
WHITE>RED>GREEN>ORANGE>BLUE>YELLOW
*/
char moves[9]={R,R2,RI,U,U2,UI,F,F2,FI};
int visited[40320][6600];
char shotest_path[100];
typedef char scube[3];
scube all[8]={{WHITE,RED,BLUE},{WHITE,RED,GREEN},{RED,YELLOW,BLUE},{RED,YELLOW,GREEN},{WHITE,ORANGE,GREEN},{WHITE,ORANGE,BLUE},{ORANGE,GREEN,YELLOW},{ORANGE,BLUE,YELLOW}};
typedef struct indexes{
    int ind_8;
    __uint8_t ind_3;
}indexes;
indexes calc_ind(cube c){
    scube cubes[8]={{c[0][1][0],c[1][0][0],c[4][0][1]},{c[0][1][1],c[1][0][1],c[2][0][0]},{c[1][1][0],c[5][0][0],c[4][1][1]},{c[1][1][1],c[5][0][1],c[2][1][0]},{c[0][0][1],c[3][0][0],c[2][0][1]},{c[0][0][0],c[3][0][1],c[4][0][0]},{c[3][1][0],c[2][1][1],c[5][1][1]},{c[3][1][1],c[4][1][0],c[5][1][0]}};
    int value_8[8];
    int value_3[8];
    for (int i=0;i<8;i++){
        for (int l=0;l<8;l++){
            for (int j=0;j<3;j++){
                int flag=1;
                for (int k=0;k<3;k++){
                    if (!all[l][(k+j)%3]==cubes[i][k]){
                        flag=0;
                    }
                }
                if (flag){
                    value_8[i]=l;
                    value_3[i]=j;
                }
            }
        }
    }
    indexes ind;
    int ind_8=1;
    for (int i=0;i<8;i++){
        int count=0;
        for (int j=i+1;j<8;j++){
            if (value_8[j]<value_8[i]){
                count++;
            }
        }
        int fact;
        switch (7-i)
        {
        case 0:
            fact=1;
            break;
        case 1:
            fact=1;
            break;
        case 2:
            fact=2;
            break;
        case 3:
            fact=6;
            break;
        case 4:
            fact=24;
            break;
        case 5:
            fact=120;
            break;
        case 6:
            fact=720;
            break;
        case 7:
            fact=5040;
            break;
        
        default:
            break;
        }
        ind_8+=count*fact;
    }
    __uint8_t ind_3=0;
    int k=1;
    for (int i=0;i<8;i++){
        ind_3=ind_3+(value_3[i]*k);
        k=k*3;
    }
    ind.ind_3=ind_3;
    ind.ind_8=ind_8;
    return ind;
}

int bfs_solver(cube initial_board) {
    int won=0;
    paths path;
    parentNode* p=(parentNode*)malloc(sizeof(parentNode));
    memcpy(p->board,initial_board,sizeof(cube));
    char initial_move=-1;
    p->move=initial_move;
    p->parent=NULL;
    path.start=p;
    Queue queue;
    queue.front = queue.rear = NULL;
    enqueue(&queue, initial_board, initial_move,p);
    while (!isEmpty(&queue)) {
        cube current_board;
        char current_move;
        char temp;
        memcpy(current_board, queue.front->board, sizeof(cube));
        
        current_move = queue.front->move;
        parentNode* p=queue.front->same;
        dequeue(&queue);
        if (has_won(current_board)) {
            path.end=p;
            int step=0;
            while(path.end){
                shotest_path[step]=(path.end->move);
                path.end=path.end->parent;
                step++;
            }
            step--;
            while(step>0){
                switch (shotest_path[step-1])
                {
                case 6:
                    printf("R -> ");
                    break;
                case 7:
                    printf("R2 -> ");
                    break;
                case 8:
                    printf("U -> ");
                    break;
                case 9:
                    printf("U2 -> ");
                    break;
                case 10:
                    printf("F -> ");
                    break;
                case 11:
                    printf("F2 -> ");
                    break;
                case 12:
                    printf("RI -> ");
                    break;
                case 13:
                    printf("UI -> ");
                    break;
                case 14:
                    printf("FI -> ");
                    break;
                
                default:
                    break;
                }
                step--;
            }
            printf("\nGame Solved!!\n");
        } else {
            for (int l=0;l<9;l++){
                char next_move;
                next_move=moves[l];
                if ((oppose(current_move)!=next_move)){              
                    play_move(current_board,next_move);
                    indexes ind=calc_ind(current_board);
                    if (!visited[ind.ind_3][ind.ind_8]){
                        parentNode*q=(parentNode*)malloc(sizeof(parentNode));
                        memcpy(q->board,current_board,sizeof(cube));
                        q->move=next_move;
                        q->parent=p;
                        path.end=q;
                        enqueue(&queue,current_board,next_move,q);
                        visited[ind.ind_3][ind.ind_8]=1;
                    }
                    reset_move(current_board,next_move);
                }
            }
        }
    }
    return won;
}

int main()
{
    cube board={{{WHITE,WHITE},{WHITE,WHITE}},{{RED,RED},{RED,RED}},{{GREEN,GREEN},{GREEN,GREEN}},{{ORANGE,ORANGE},{ORANGE,ORANGE}},{{BLUE,BLUE},{BLUE,BLUE}},{{YELLOW,YELLOW},{YELLOW,YELLOW}}};
    play_move(board,F);
    play_move(board,R);
    play_move(board,UI);
    bfs_solver(board);
    return 0;
}