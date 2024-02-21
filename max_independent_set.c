#include <stdio.h>
#include <stdlib.h>

int mis(int root, int parent, int** adjList, int* dp, int* dpChildren) {
    /* adjList refers to the adjacency list which is 0-indexed and has the first element of every list as the length of the list (equivalent to the degree of the vertex),
    * parent is initially passed as -1,
    * fill dp[i] (notice that the return statement already handles this) with the answer (|MIS|) for the subtree of node i,
    * fill dpChildren[i] with the answer for the immediate children of the node i,
    * result should contain the final |MIS| for the tree,
    * feel free to make additional functions as might be required be your solution.
    */
    int result = 0;

    // write your code here
    if (adjList[root][0]==0){// leaf
        result=1;
        return dp[root] = result;
    }
    if(dp[root]){ // already solved
            return dp[root];
    }
    
        int m1,m2;
        m1=0;
        m2=1;
        for (int j=1;j<adjList[root][0];j++){
            // m1+=dp[adjList[root][j]];
            m1 += mis(adjList[root][j], parent, adjList, dp, dpChildren);
            for (int k=1;k<adjList[adjList[root][j]][0];k++){
                m2+=dp[adjList[adjList[root][j]][k]];
            }
        }
        if (m1>m2){
            result=m1;
        }
        else{
            result=m2;
        }    
    
    return dp[root] = result;
}

int main() {
    FILE *input, *output, *expectedOutput;
    input = fopen("input_2.txt", "r");
    output = fopen("output_2.txt", "w");

    if (input == NULL || output == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    int n;
    fscanf(input, "%d", &n);

    int** adjList = (int**)malloc(n * sizeof(int*));
    int edges[2*(n-1)], degree[n], dp[n], dpChildren[n];
    for (int i = 0; i < n; i++) {
        degree[i] = 0;
        dp[i] = 0;
        dpChildren[i] = 0;
    }
    for (int i = 0; i < n-1; i++) {
        fscanf(input, "%d %d", &edges[2*i], &edges[2*i+1]);
        degree[edges[2*i]]++;
        degree[edges[2*i+1]]++;
    }
    for (int i = 0; i < n; i++) {
        adjList[i] = (int *) malloc((degree[i] + 1) * sizeof(int));
        adjList[i][0] = degree[i];
    }
    for (int i = 0; i < n-1; i++) {
        adjList[edges[2*i]][degree[edges[2*i]]] = edges[2*i+1];
        adjList[edges[2*i+1]][degree[edges[2*i+1]]] = edges[2*i];
        degree[edges[2*i]]--;
        degree[edges[2*i+1]]--;
    }
    int result = mis(0, -1, adjList, dp, dpChildren);
    for (int i = 0; i < n; i++) {
        fprintf(output, "%d ", dp[i]);
        fprintf(output, " ");
    }
    free(adjList);
    return 0;
}
