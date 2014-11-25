/*
    SFSU SOE ENGR476: Computer Communication Networks
    Dr. Shahnasser
    Assignment 3: Routing Algorithms (Layer 3 protocol)

    File:   Dijkstra.c
    By:     Marcian Diamond
    Date:   7th May 2014

    Compile:    cc Dijkstra.c
    Usage:      a.out

    Description: This program reads an external cost matrix file containing a 
                    network graph with nodes and edge weights.  The user enters
                    two nodes, source and destination, on the network.  Next, 
                    the algorithm returns the cheapest route length from source
                    to destination as well as the route with all intermediate hops
                    included.
*/

#include <stdlib.h>
#include <stdio.h>
#include<string.h>

//number of nodes in cost matrix file;
#define numNodes 8

//node structure used for route tracing
struct node{
    int neighbor;
    int weight;
}nodes[numNodes];

//method declarations
//method to move processed node to settled set
void mvNodeToSettledSet(int node);
//get weights of edges for current node being processed
void getTmpWeights(int node);
//find node with smallest edge weight
int findNodeWithSmallestWeight(int weightIn[]);
//dijkstras algorithm to find shortest paths from origin to any node on network
void edgeProcess();
//use node structs to determine the route of the shortest path
void traceRoute();

//variable declarations
FILE *fp;
char inputString[100], srcLabel,dstLabel;
int settledIndx = 0;
char* pch;
char fileName[25];
int i,j,k, src, dst, weight = 0;
int costMatrix[numNodes][numNodes];
int unsettledNodes[] = {0,1,2,3,4,5,6,7};
int settledNodes[] = {999,999,999,999,999,999,999,999};
int weightSrc[]= {999,999,999,999,999,999,999,999};
int weightsTmp[8] = {0,0,0,0,0,0,0,0};
char route[] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
int smallestWeight = 999;
int nextNode, currWeight, newWeight;
int totalCost = 0;
int nxtNode,routeIndx;

int main(void){
    printf("\n%s\n", "--------DIJKSTRAS ALGORITHM PROGRAM--------");
    printf("Enter cost matrix file: ");
    scanf("%s", fileName);
    fp = fopen(fileName, "r");
    //first line of input contains node labels  
    for(i = 0; i < numNodes; i++){
        fgets(inputString, 100,fp);
        pch = strtok(inputString,"\t");
        for(j=0;j < numNodes; j++){
            weight = atoi(pch);
            costMatrix[i][j] = weight;
            pch = strtok(NULL, "\t");
        }
    } 
    //close cost matrix file
    fclose(fp);
    //nodes in network
    printf("%s", "Enter source and destination nodes(i.e. A H): ");
    scanf("\n%c %c", &srcLabel, &dstLabel);
    
    //define src and dst nodes numerically
    src = srcLabel - 65;
    dst = dstLabel - 65;
    printf("\nFinding shortest route from %c to %c...\n", srcLabel, dstLabel);  
    
    //vertex set initially contains origin vertex;
    mvNodeToSettledSet(src);
    for(i = 0; i < numNodes; i++){
        weightSrc[i] = costMatrix[src][i]; 
    }
    printf("\n");
    for(k =1;k<numNodes;k++){
        edgeProcess();
    }
    traceRoute();
    totalCost = weightSrc[dst];
    //if destination node is also source cost = 0;
    if(totalCost == 999) totalCost = 0;
   
    //print route hops to console; source and destination inclusive
    printf("\nRoute to go from %c to %c: \n",srcLabel, dstLabel);
    printf("%c", src + 65);
    for(i = routeIndx-1; i >= 0; i--){
        printf("%c",route[i]+65);
    }
    printf("%c\n",dst+65);
    
    //print total cost of shortest path from src to dst on console
    printf("\nTotal cost to go from %c to %c: %d\n", srcLabel, dstLabel, totalCost);
    //pause execution so user can read results
    sleep(100000);
    return 0;
}
//dijkstras algorithm
void edgeProcess(){
    nextNode = findNodeWithSmallestWeight(weightSrc);
    currWeight = weightSrc[nextNode];
    mvNodeToSettledSet(nextNode);
    getTmpWeights(nextNode);

    for(i=0;i<8;i++){
       if(unsettledNodes[i] != 999){ 
           newWeight = weightsTmp[i] + currWeight;
           if(newWeight < weightSrc[i] && newWeight < 999){
                weightSrc[i] = newWeight;      
                nodes[i].neighbor = nextNode; 
                nodes[nextNode].weight = currWeight;
            }
        }
    }
}

void mvNodeToSettledSet(int node){
    settledNodes[settledIndx++] = node;
    unsettledNodes[node] = 999;    
}

void getTmpWeights(int node){
    for(i = 0; i < numNodes; i++){
        weightsTmp[i] = costMatrix[node][i]; 
    }
}

int findNodeWithSmallestWeight(int weightIn[]){
    int smallest = 999;
    int smallestCost = 999;
    for(i = 0; i < numNodes; i++){
        if(unsettledNodes[i]== i){
           if(weightIn[i] < smallestCost){
                smallest = i; 
                smallestCost = weightIn[i];   
            }
       }
    }    
    return smallest; 
}

void traceRoute(){
    nxtNode = dst;
    for(i = 0; i<numNodes;i++){
        route[i] = nodes[nxtNode].neighbor;
        nxtNode = route[i];
        if(nxtNode == 0){
            route[i] = src;
            return;
        }
        routeIndx++;
    }
}

