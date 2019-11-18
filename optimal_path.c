#include <stdio.h>
#include <limits.h>
 
#ifndef bool
    #define bool  char
    #define false 0
    #define true  1
#endif

// FINDING PROFIT PER UNIT TIME

 
/* number of vertices in graph */
int VERTEX=0;
 
// #define VERTEX 9
 
//      int graph[VERTEX][VERTEX] = {
//         {0, 40, 0, 0, 0, 0, 0, 80, 0},
//         {40, 0, 8, 0, 0, 0, 0, 110, 0},
//         {0, 80, 0, 70, 0, 40, 0, 0, 20},
//         {0, 0, 70, 0, 90, 140, 0, 0, 0},
//         {0, 0, 0, 90, 0, 100, 0, 0, 0},
//         {0, 0, 40, 140, 100, 0, 20, 0, 0},
//         {0, 0, 0, 0, 0, 20, 0, 10, 60},
//         {80, 110, 0, 0, 0, 0, 10, 0, 70},
//         {0, 0, 20, 0, 0, 0, 60, 70, 0},
//     };
/* find the vertex with minimum distance value  from the set of
 *  vertices not yet included in shortest path tree(SPT)
 * */
int min_dist(const int *dist, const bool *spt_set)
{
    int min = INT_MAX, min_idx = 0;
  int i;
    for (i = 1; i < VERTEX; i++)
        if (spt_set[i] == false && min > dist[i]) {
            min     = dist[i];
            min_idx = i;
        }
 
    return min_idx;
}

int max_dist(const int *dist, const bool *spt_set)
{
    int max = INT_MIN, max_idx = 0;
    int i;
    for (i = 0; i < VERTEX; i++)
        if (spt_set[i] == false && max < dist[i]) {
            max     = dist[i];
            max_idx = i;
        }
 
    return max_idx;
}
/* print path from source v using parent array */
void print_path(int graph[VERTEX][VERTEX],const int *parent, int v)
{
    /* TODO: for large array  stack is better choice */
    if (parent[v] == -1) {
        printf("%d ", v);
        return ;
    }
    // trying to alter it
    graph[parent[v]][v]=graph[parent[v]][v]-1;
    graph[v][parent[v]]=graph[v][parent[v]]-1;
    print_path(graph,parent, parent[v]);
    printf("%d ", v);
}
 
void print_spt(int graph[VERTEX][VERTEX],const int *dist, int src,int dest, const int *parent)
{
    puts("  Vertex    Distance     Path");
    int i;
    for (i = 0; i < VERTEX; i++) {
//        printf(" %2d -> %2d      %2d         ", src, i, dist[i]);
//        putchar('\n');
    }
    printf(" %2d -> %2d      %2d         ", src,dest, dist[4]);
    print_path(graph,parent, dest);
}
 
/* time compl. of this implementation is O(V^2)  (due to matrix) */
void dijkstra_max(int graph[VERTEX][VERTEX], int src,int dest)
{
    /* dist[] will hold the shortest distance sourced src */
    int dist[VERTEX];
    /* Shortest Path Tree Set  true if a vertex in included in SPT
     *  or shortest distance from src to i is finalized
     * */
    bool spt_set[VERTEX];
 
    /* parent array to store shortest path tree */
    int parent[VERTEX];
    parent[src]  = -1;            /* assuming source have no parent */
  int i;
    for (i = 0; i < VERTEX; i++) {
        dist[i]    = INT_MIN;       /* unreachable */
        spt_set[i] = false;         /* not in SPT set */
    }
 
    /* distance of source vertex to itself always 0 */
    dist[src] = 0;
 
    /* find shortest path for all vertices */
    for (i = 0; i < VERTEX-1; i++) {
        /* pick minimum vertex of those vertices not processed
         *  u is always equal to src in the first call of min_dist()
         *  */
        int u = max_dist(dist, spt_set);
 
        /* mark the picked vertex as processed */
        spt_set[u] = true;
 
        /* if current unprocessed vertex is unreachable
         *  for those disconnected vertex
         * */
        if (dist[u] == INT_MIN) continue;
 
        /* update dist[] of adjacent vertices of the picked vertex */
        int v;
        for (v = 0; v < VERTEX; v++)
            /* update dist[v] only if
             *  1) there is a edge from u to v
             *  2) it's not in spt_set[]
             *  3) distance of path from src to v through u
             *    is smaller than current value of dist[v]
             * */
            if (graph[u][v] && spt_set[v] == false &&
                    dist[u] + graph[u][v] > dist[v])
            {
                dist[v]   = dist[u] + graph[u][v];
                parent[v] = u;
            }
    }
 
    /* print the constructed distance array */
    print_spt(graph,dist, src,dest, parent);
}

void dijkstra_min(int graph[VERTEX][VERTEX], int src,int dest)
{
    /* dist[] will hold the shortest distance sourced src */
    int dist[VERTEX];
    /* Shortest Path Tree Set  true if a vertex in included in SPT
     *  or shortest distance from src to i is finalized
     * */
    bool spt_set[VERTEX];
 
    /* parent array to store shortest path tree */
    int parent[VERTEX];
    parent[src]  = -1;            /* assuming source have no parent */
    int i;
    for (i = 0; i < VERTEX; i++) {
        dist[i]    = INT_MAX;       /* unreachable */
        spt_set[i] = false;         /* not in SPT set */
    }
 
    /* distance of source vertex to itself always 0 */
    dist[src] = 0;
 
    /* find shortest path for all vertices */
    for (i = 0; i < VERTEX-1; i++) {
        /* pick minimum vertex of those vertices not processed
         *  u is always equal to src in the first call of min_dist()
         *  */
        int u = min_dist(dist, spt_set);
 
        /* mark the picked vertex as processed */
        spt_set[u] = true;
 
        /* if current unprocessed vertex is unreachable
         *  for those disconnected vertex
         * */
        if (dist[u] == INT_MAX) continue;
 
        /* update dist[] of adjacent vertices of the picked vertex */
        int v;
        for (v = 0; v < VERTEX; v++)
            /* update dist[v] only if
             *  1) there is a edge from u to v
             *  2) it's not in spt_set[]
             *  3) distance of path from src to v through u
             *    is smaller than current value of dist[v]
             * */
            if (graph[u][v] && spt_set[v] == false &&
                    dist[u] + graph[u][v] < dist[v])
            {
                dist[v]   = dist[u] + graph[u][v];
                parent[v] = u;
            }
    }
 
    /* print the constructed distance array */
    print_spt(graph,dist, src,dest, parent);
}
 
// int main(void)
// {
//     /* graph based on top link */
// //    int graph[VERTEX][VERTEX] = {
// //        {0, 4, 0, 0, 0, 0, 0, 8, 0},
// //        {4, 0, 8, 0, 0, 0, 0, 11, 0},
// //        {0, 8, 0, 7, 0, 4, 0, 0, 2},
// //        {0, 0, 7, 0, 9, 14, 0, 0, 0},
// //        {0, 0, 0, 9, 0, 10, 0, 0, 0},
// //        {0, 0, 4, 14, 10, 0, 2, 0, 0},
// //        {0, 0, 0, 0, 0, 2, 0, 1, 6},
// //        {8, 11, 0, 0, 0, 0, 1, 0, 7},
// //        {0, 0, 2, 0, 0, 0, 6, 7, 0},
// //    };
 
//  int i;

//   for(i=0;i<3;i++)
//   {
//      printf("Dijkstra of vertex %d\n",1);
//     dijkstra(graph, 1);
// printf("\n");
// }
 
//     return 0;
// }
void display(int v;int graph[v][v],int v)
{
    int i;
    for(i=0;i<v;i++)
    {
        int j;
        for(j=0;j<v;j++)
        {
            printf("%d\t",graph[i][j]);
        }
        printf("\n");
    }
}

void initialize(int v;int graph[v][v],int v)
{
    int i;
    for(i=0;i<v;i++)
    {
        int j;
        for(j=0;j<v;j++)
        {
            graph[i][j]=0;
        }
        printf("\n");
    }
}

int main()
{
int i,j;
    printf("Let us first create the graph, enter the number of vertices\n");
    int vertex,weight,prof,p; scanf("%d",&vertex);
    int graph1[vertex][vertex];int graph2[vertex][vertex];
    VERTEX=vertex;
    initialize(graph1,vertex);
    initialize(graph2,vertex);
    while(1)
    {
        printf("Enter vertexes for edges and -1 and -1 for exit\n");
        scanf("%d %d",&i,&j);
        if(i==-1 && j==-1)
            break;
        printf("Enter distance");
        scanf("%d",&weight);
        printf("Enter profit or eagerness\n");
        scanf("%d",&prof);
        graph1[i][j]=weight;
        graph1[j][i]=weight;
        int p= (prof+10000)/weight;
        graph2[i][j]=p;
        graph2[j][i]=p;
    }

    printf("Distance graph\n");
    display(graph1,vertex);
    printf("\nCost graph\n");
    display(graph2,vertex);
    int choice;int source,destination,num_travelers;
    printf("Enter your choice:\n1) Traveler or travelers which have to visit places\n2) Emergency route from one place to another\n");
    printf("3)To report connection changes from place A to B\n4)To display the graphs");
    scanf("%d",&choice);
    do{
    switch(choice)
    {
        case 1:
            printf("Traveler based on locations\n");
            printf("Enter source and destination vertex\n");
            scanf("%d %d",&source,&destination);
            printf("Enter the number of travelers going from %d to %d\n",source,destination);
            scanf("%d",&num_travelers);
            for(i=0;i<num_travelers;i++)
            {
                dijkstra_max(graph2, source,destination);
                printf("\n");  
            }
            break;
        case 2:
            printf("emergency route only based on distance and traffic");
            printf("Traveler based on locations\n");
            printf("Enter source and destination vertex\n");
            scanf("%d %d",&source,&destination);
            printf("Enter the number of travelers going from %d to %d\n",source,destination);
            scanf("%d",&num_travelers);int i;
            for(i=0;i<num_travelers;i++)
            {
                dijkstra_min(graph1, source,destination);
                printf("\n");  
            }
            break;
        case 3:
            printf("Connection changes\n");
            int source,destination,new_weight;
            printf("Enter source and destination vertex\n");
            scanf("%d %d",&source,&destination);
            printf("Enter altered weight\n");
            scanf("%d",&new_weight);
            graph1[source][destination]=new_weight;
            graph1[destination][source]=new_weight;
            printf("modified graph\n");
            display(graph1,VERTEX);
            break;
        case 4:
            printf("\nDistance graph");
            display(graph1,vertex);
            printf("\nCost graph");
            display(graph2,vertex);
            break;
        default:
            printf("wrong option\n");
            break;
    }
    printf("Enter your choice:\n1) Traveler or travelers which have to visit places\n2) Emergency route from one place to another");
    printf("3)To report connection changes from place A to B\n4)To display the graphs\n");
    printf("Other choices to quit\n");
    scanf("%d",&choice);
    }while(choice<5);
    return 0;
}
