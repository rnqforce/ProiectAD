#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "FirstSolution.h"

int main()
{
    int** map;
    int no_vertex;
    int source;
    int destination;
    int chose;

    map=GenerateRandGraphs(&no_vertex);

    printf("===The meniu of the program===\n");
    printf("===Insert the source and the destination between [0,%d]===\n" , no_vertex - 1);
    printf("Source=");
    scanf("%d", &source);
    printf("Destination=");
    scanf("%d", &destination);

    printf("===Chose the the way to solve problem===\n");
    printf("===For DFS + Dijkstra press 1===\n");
    printf("===For BFS + Dijkstra press 2===\n chose = ");
    scanf("%d",&chose);

    dijkstra(map, source, no_vertex, destination,chose);



    return 0;


}
