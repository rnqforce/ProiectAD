///\file FirstSolution.h

struct a_list_node{
    int info;
    struct a_list_node *next;
};



/// A function to generate random graph.
int** GenerateRandGraphs( int *no_vertex)
{

    srand(time(0));
	int iterator;
	int no_edge ;
	int rand_edge_1 ;
	int rand_edge_2 ;
	int rand_cost ;
    int** adiacent_matrix;
    ///\var *no_vertex No of nodes random generated between [3,20];
    *no_vertex = 3 + rand()%18;
    /// Dynamic allocation of matrix
    adiacent_matrix =  (int**)calloc ((*no_vertex) , sizeof(int));
    for (iterator = 0; iterator <= (*no_vertex); iterator++){
         adiacent_matrix[iterator] = (int *)calloc((*no_vertex) + 1 , sizeof(int));
    }
    ///\var *no_edge No of nodes random generated
	no_edge = rand() % ((*no_vertex)*((*no_vertex-1)/2))  ;

	for(iterator = 1 ; iterator <= no_edge ; iterator ++ )
	{
            rand_edge_1 =  rand() % *no_vertex ;
            rand_edge_2 =  rand() % *no_vertex ;
            rand_cost = 1 + rand()%1000 ;
            adiacent_matrix[rand_edge_1][rand_edge_2] = rand_cost;
            adiacent_matrix[rand_edge_2][rand_edge_1] = rand_cost;


	}

	for(iterator = 1 ; iterator < *no_vertex ; iterator ++ )
        adiacent_matrix[iterator][iterator] = 0;

    /// Display the matrix
    for(int i = 0 ; i < *no_vertex ; i++){
        for(int j = 0 ; j < *no_vertex ; j++)
            printf("%d ",adiacent_matrix[i][j]);
        printf("\n");
    }
    /// Return the adiacency matrix obtained
    return adiacent_matrix;

}
/// A utility function to find the vertex with minimum distance,
/// not yet included in shortest path tree
int minDistance( int dist[] , bool sptSet[] ,int no_vertex )
{

    /// Initialize min value
    int min = INT_MAX, min_index;
    int iterator ;
    for (iterator = 0; iterator < no_vertex ; iterator ++ )
        if (sptSet[iterator] == false && dist[iterator] <= min){
            min = dist[iterator];
            min_index = iterator;
        }
    return min_index;
}

/// Function to print shortest  path from source to destination  using parent array
void printPath(int parent[], int destination)
{

    int aux[30];
    int iterator = 0 ;
    int iterator_2 ;
    while( destination != - 1){
        aux[iterator ++ ] = destination;
        destination = parent[destination] ;
    }
    for(iterator_2 = iterator - 1 ; iterator_2 >= 0 ; iterator_2 -- )
        printf("%d " , aux[iterator_2]);
    return ;
}

/// A utility function to print the constructed distance array
void printSolution(int dist[],int parent[] ,int src , int no_vertex , int destination)
{
    int iterator;
    printf("Vertex\t\t Distance\tPath");
    for (iterator = 0; iterator < no_vertex ; iterator ++ ){
        if(dist[iterator] != INT_MAX && dist[iterator] != INT_MIN){

            printf("\n%d -> %d \t\t %d\t\t ",src, iterator, dist[iterator] );
            printPath(parent, iterator);
        }
        else
            printf("\n%d -> %d \t\t No Path ",src, iterator );


    }
}
/// function doing push beginig to a list
void push_begining_list(struct a_list_node *head, int new_element_value){
    struct a_list_node *next_element;
    struct a_list_node *new_element;

    next_element = head->next;
    ///\var new_element dynamic allocation
    new_element = malloc(sizeof(struct a_list_node));
    new_element->info = new_element_value;
    ///\var new_element point to first element now
    new_element->next = head->next;
    ///\var head point to new_element
    head->next = new_element;
}
/// function doing push beginig to a list
int pop_begining_list(struct a_list_node *head){
    struct a_list_node *deleted_element;
    int aux;

    if (head->next != NULL) {
        deleted_element = head->next;
        aux = deleted_element->info;
        head->next = deleted_element->next;
        free(deleted_element);
        return aux;
    }else{
        printf("\n The list is empty");
        return -1; //the list is empty
    }
}
///function doing pop end to a list
int pop_end_list(struct a_list_node *head) {
    struct a_list_node *deleted_element;
    struct a_list_node *iterator;
    int aux;

    if (head->next != NULL) {
        for (iterator = head; iterator->next->next != NULL; iterator = iterator->next);
        deleted_element = iterator->next;
        aux = deleted_element->info;
        iterator->next = deleted_element->next;
        free(deleted_element);
        return aux;
    } else {
        printf("\n The list is empty");
        return -1; ///the list is empty
    }
}
///modified function bfs
void graph_bfs(int** graph, int start_node , int no_vertex , int destination){
    struct a_list_node *head_queue;
    int *visited;
    int column_index;
    int aux;
    int current_node;
    int parent[no_vertex];
    head_queue = calloc(1, sizeof(struct a_list_node));
    head_queue->next = NULL;
    head_queue->info = 0;
    ///no of elements in the queue
    visited = calloc(no_vertex, sizeof(int));
    push_begining_list(head_queue, start_node);
    visited[start_node] = 1;
    ///delete the direct route between the nodes start_node and destination in order not to find it again
    aux = graph[start_node][destination];
    graph[start_node][destination] = 0 ;
    /// initialize all array parent with -1
    for(int iterator = 0 ; iterator < no_vertex ; iterator ++ )
        parent[iterator] = -1;
    printf("\nBFS traversal: ");
    while (head_queue->next != NULL){
        ///\var current_node is the top of the stack
        current_node = pop_begining_list(head_queue);
        if(current_node == destination){
            ///we arrived to the destination node
            ///Display the path
            printPath(parent,destination);
            graph[start_node][destination] = aux ;
            return ;
        }
        for(column_index = 0; column_index < no_vertex; column_index++){
            if ( (graph[current_node][column_index] != 0) && ( (visited[column_index]) == 0 )){
                push_begining_list(head_queue, column_index);
                /// add to stack all neighbor of current node unvisited
                parent[column_index] = current_node;
                visited[column_index] = 1;
            }
        }
    }
    printf("\n");
    free(head_queue);
    free(visited);
}
///function bfs_2 who search for second path simpilary with previous function
void graph_bfs_2(int** graph, int start_node , int no_vertex , int destination){
    struct a_list_node *head_queue;
    int *visited;
    int column_index;
    int aux;
    int current_node;
    int parent[no_vertex];
    head_queue = calloc(1, sizeof(struct a_list_node));
    head_queue->next = NULL;
    head_queue->info = 0; //no of elements in the queue
    visited = calloc(no_vertex, sizeof(int));
    push_begining_list(head_queue, start_node);
    visited[start_node] = 1;
    aux = graph[start_node][destination];
    graph[start_node][destination] = 0 ;

    for(int iterator = 0 ; iterator < no_vertex ; iterator ++ )
        parent[iterator] = -1;
    printf("\nBFS traversal: ");
    while (head_queue->next != NULL){
        current_node = pop_begining_list(head_queue);
        if(current_node == destination){
            printPath(parent,destination);
            graph[start_node][destination] = aux ;
            return ;
        }
        ///the diference is here we start with the last node
        for(column_index = no_vertex - 1 ; column_index >= 0 ; column_index -- ){
            if ( (graph[current_node][column_index] != 0) && ( (visited[column_index]) == 0 )){
                push_begining_list(head_queue, column_index);
                parent[column_index] = current_node;
                visited[column_index] = 1;
            }
        }
    }
    printf("\n");
    free(head_queue);
    free(visited);
}
///dfs function used for the second method
void graph_dfs(int** graph, int start_node , int no_vertex , int destination){
    struct a_list_node *head_queue;
    int *visited;
    int column_index;
    int aux;
    int current_node;
    int parent[no_vertex];
    head_queue = calloc(1, sizeof(struct a_list_node));
    head_queue->next = NULL;
    head_queue->info = 0; //no of elements in the queue
    visited = calloc(no_vertex, sizeof(int));
    push_begining_list(head_queue, start_node);
    visited[start_node] = 1;
    aux = graph[start_node][destination];
    graph[start_node][destination] = 0 ;

    for(int iterator = 0 ; iterator < no_vertex ; iterator ++ )
        parent[iterator] = -1;
    printf("\nBFS traversal: ");
    while (head_queue->next != NULL){
            ///diference between dfs and bfs function is here
            /// dfs using queue
        current_node = pop_end_list(head_queue);
        if(current_node == destination){
            printPath(parent,destination);
            graph[start_node][destination] = aux ;
            return ;
        }
        for(column_index = no_vertex - 1 ; column_index >= 0 ; column_index -- ){
            if ( (graph[current_node][column_index] != 0) && ( (visited[column_index]) == 0 )){
                push_begining_list(head_queue, column_index);
                parent[column_index] = current_node;
                visited[column_index] = 1;
            }
        }
    }
    printf("\n");
    free(head_queue);
    free(visited);
}
///Function DFS_2 similary with previous function
void graph_dfs_2(int** graph, int start_node , int no_vertex , int destination){
    struct a_list_node *head_queue;
    int *visited;
    int column_index;
    int aux;
    int current_node;
    int parent[no_vertex];
    head_queue = calloc(1, sizeof(struct a_list_node));
    head_queue->next = NULL;
    head_queue->info = 0; //no of elements in the queue
    visited = calloc(no_vertex, sizeof(int));
    push_begining_list(head_queue, start_node);
    visited[start_node] = 1;
    aux = graph[start_node][destination];
    graph[start_node][destination] = 0 ;

    for(int iterator = 0 ; iterator < no_vertex ; iterator ++ )
        parent[iterator] = -1;
    printf("\nBFS traversal: ");
    while (head_queue->next != NULL){
        current_node = pop_end_list(head_queue);
    if(current_node == destination){
        printPath(parent,destination);
        graph[start_node][destination] = aux ;
        return ;
    }   ///the differnce is here ,we start with first node
        for(column_index = 0; column_index < no_vertex; column_index++){
            if ( (graph[current_node][column_index] != 0) && ( (visited[column_index]) == 0 )){
                push_begining_list(head_queue, column_index);
                parent[column_index] = current_node;
                visited[column_index] = 1;
            }
        }
    }
    printf("\n");
    free(head_queue);
    free(visited);
}
/// A function using to print the alternativ path between two consecutive nodes from the path source - destination
///This function is the output for first method with DFS
void printAlternativPath(int parent[] ,int** graph , int no_vertex , int destination){
    int a[20] , i = 0;

    while(destination != -1){
            a[i] = destination;
            destination = parent[destination] ;
            i++;

    }
    for(int j = i-1 ; j >= 1 ; j--){
        printf("\nAlternativ between %d and %d\n",a[j],a[j-1]);
        graph_dfs_2( graph , a[j], no_vertex , a[j-1]);
        graph_dfs( graph , a[j], no_vertex , a[j-1]);

    }
}
/// A function using to print the alternativ path between two consecutive nodes from the path source - destination
///This function is the output for second method with BFS
void printAlternativPath_2(int parent[] ,int** graph , int no_vertex , int destination){
    int a[30] , i = 0;

    while(destination != -1){
            a[i] = destination;
            destination = parent[destination] ;
            i++;

    }
    for(int j = i-1 ; j >= 1 ; j--){
        printf("\nAlternativ between %d and %d\n",a[j],a[j-1]);
        graph_bfs_2( graph , a[j], no_vertex , a[j-1]);
        graph_bfs( graph , a[j], no_vertex , a[j-1]);

    }
}
void dijkstra(int** graph, int src , int no_vertex, int destination, int chose)
{
    int iterator;
    int iterator_2;
    /// The output array. dist[i] will hold the shortest distance from src to i
    int dist[no_vertex];

    /// sptSet[iterator] will true if nodes iterator is included  in shortest path tree

    bool sptSet[no_vertex];

    /// Parent array to store shortest path tree
    int parent[no_vertex];

    /// Initialize all distances as INFINITE and stpSet[] as false
    for ( iterator = 0; iterator < no_vertex; iterator++)
    {
        parent[iterator] = -1 ;
        dist[iterator] = INT_MAX;
        sptSet[iterator] = false;
    }

    /// Distance of source nodes from itself is always 0
    dist[src] = 0;

    /// Find shortest path for all nodes
    for (int iterator = 0; iterator < no_vertex - 1; iterator++)
    {
        /// Pick the minimum distance vertex from the set of nodes
        int min_distance = minDistance(dist, sptSet , no_vertex);

        /// Mark the picked node as processed
        sptSet[min_distance] = true;

        for ( iterator_2 = 0; iterator_2 < no_vertex; iterator_2++)

            /// Update dist[iterator_2] only if is not in sptSet, there is
            /// an edge from min_distance to iterator_2, and total weight of path from
            /// src to itrator_2 through min_distance is smallerthan current value of dist[iterator_2]
            if (!sptSet[iterator_2] && graph[min_distance][iterator_2] &&
                dist[min_distance] + graph[min_distance][iterator_2] < dist[iterator_2])
            {
                parent[iterator_2] = min_distance;
                dist[iterator_2] = dist[min_distance] + graph[min_distance][iterator_2];
            }
    }

    /// print the constructed distance array and the path
    printSolution(dist, parent , src ,no_vertex , destination);
        printf("\n");
    ///print the output of the chosen metohod
    if(chose == 1)
        printAlternativPath(parent ,graph , no_vertex , destination);
    else printAlternativPath_2(parent ,graph , no_vertex , destination);
}
