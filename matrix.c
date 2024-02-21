#include<stdio.h>
#include<stdlib.h>
// Here the task is to implement matrix chain multiplication.

int *readInput(int *n){
  int i;
  int *A;
  int B[]={30,35,15,5,10,20,25};
  //FILE *fp;
  //fp=fopen("input.txt","r");
  //fscanf(fp,"%d",n);
  *n=6;
  //printf("%d",*n);
  A=(int *)malloc((*n+1)*sizeof(int));
  for(i=0;i<(*n+1);i++) A[i]=B[i];
  return A;
}

//Do not change the above part. If you do so your program may not be evaluated.


//1. Read the following code make sure you understand it. This the initialization of the DP table for cost.

int **initMat( int n){
  int i,j;
  int **X;
  X=(int **)malloc(n*sizeof(int *));
  for(i=0;i<n;i++) X[i]=(int *) malloc(n*sizeof(int));
  for(i=0;i<n;i++)
    for(j=0;j<n;j++)
      X[i][j]=0;
  return X;
}

void printMat(int **X, int n){
  int r,c;
  for(r=0;r<n;r++){
    printf("\n");
    for(c=0;c<n;c++){
      printf("%d\t",X[r][c]);
    }
  }
}



//3. Write a program to set the values of the DP tables
//a. M[i,j] will contain the optimal cost of multiplying A[i..j]
//b. S[i,j] will contain the index of the last multiplicaion in the subproblem A[i..j]
// Checks: Our script will check if you have set the correct values of M[i,j] and S[i,j]

void MCM(int n, int *p, int **M, int **S){
  for (int j=1;j<n;j++){
    for (int i=j-1;i>=0;i--){
      if (i<=j){
        int min=10000000;
        for (int k=0;k<(j-i);k++){
          if (min>(M[i][j-k-1]+M[j-k][j]+p[i]*p[j+1]*p[j-k])){
            min = M[i][j-k-1]+M[j-k][j]+p[i]*p[j+1]*p[j-k] ;
            S[i][j]=k+1;
          }
        }
        M[i][j]=min;
      }
    }
  }

}

int main(){
  int n,i;
  int *p;
  int **M,**S;
  p=readInput(&n);
  for(i=0;i<n+1;i++) printf("%d\t",*(p+i));printf("\n");
  M=initMat(n);
  S=initMat(n);
  
  //printMat(S,n);
  MCM(n,p,M,S);
  printMat(M,n); 
}
