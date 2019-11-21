#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
 
struct node
{
    int vertex;
    int weight;
    struct node* link;
};
typedef struct node node;
struct Graph
{
    int numVertices;
    struct node** adjLists;
};

struct node* createNode(int v,int w)
{
    struct node* newNode=malloc(sizeof(struct node));
    newNode->vertex=v;
    newNode->weight=w;
    newNode->link=NULL;
    return newNode;
}
 
struct Graph* createGraph(int vertices)
{
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
 
    graph->adjLists = malloc(vertices * sizeof(struct node*));
 
    int i;
    for (i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;
 
    return graph;
}
 
void addEdge(struct Graph* graph, int src, int dest,int weight)
{
    //undirected
    struct node* newNode = createNode(dest,weight);
    newNode->link = graph->adjLists[src];
    graph->adjLists[src] = newNode;
 
    newNode = createNode(src,weight);
    newNode->link = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}
 
void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->numVertices; v++)
    {
        struct node* temp = graph->adjLists[v];
        printf("\n Adjacency list of vertex %d\n ", v);
        while (temp)
        {
            printf("%d -> ", temp->vertex);
            temp = temp->link;
        }
        printf("\n");
    }
}

/* number of vertices in graph */
int VERTEX=0;

int min_dist(const int *dist, int *spt_set)
{
    int min = INT_MAX, min_idx = 0;
  int i;
    for (i = 1; i < VERTEX; i++)
        if (spt_set[i] == 0 && min > dist[i]) {
            min     = dist[i];
            min_idx = i;
        }
 
    return min_idx;
}

void print_path_once(int graph[VERTEX][VERTEX],const int *parent, int v,int visited[])
{
    /* TODO: for large array  stack is better choice */
    if (parent[v] == -1) {
        printf("%d ", v);
        return ;
    }
    // trying to alter it
    graph[parent[v]][v]=graph[parent[v]][v]+1;
    graph[v][parent[v]]=graph[v][parent[v]]+1;
    if(visited[v]==0)
    {
        visited[v]=1;
    }
    if(graph[v][parent[v]]<0)
    {
        graph[v][parent[v]]=0;
        graph[parent[v]][v]=0;
    }
    print_path_once(graph,parent, parent[v],visited);
    printf("%d ", v);
}

void print_spt_once(int graph[VERTEX][VERTEX],const int *dist, int src,int dest, const int *parent,int visited[])
{
    puts("\nVertex    Distance\n");
    int i;
    for (i = 0; i < VERTEX; i++) {
       printf(" %2d -> %2d      %2d         ", src, i, dist[i]);
       putchar('\n');
    }
    printf("\nPath\n");
    print_path_once(graph,parent, dest,visited);
}

void dijkstra_min_once(int graph[VERTEX][VERTEX], int src,int dest,int visited[])
{
    int dist[VERTEX];
    int spt_set[VERTEX];
    int parent[VERTEX];
    parent[src]  = -1; 
    int i;
    for (i = 0; i < VERTEX; i++) {
        dist[i]    = INT_MAX;       /* cant reach will be INT_MAX */
        spt_set[i] = 0;     
    }
 
     dist[src] = 0;
 
    for (i = 0; i < VERTEX-1; i++) {
        int u = min_dist(dist, spt_set);
        spt_set[u] = 1;
        if (dist[u] == INT_MAX) continue;
        int v;
        for (v = 0; v < VERTEX; v++)
            if (graph[u][v] && spt_set[v] == 0 &&
                    dist[u] + graph[u][v] < dist[v])
            {
                dist[v]   = dist[u] + graph[u][v];
                parent[v] = u;
            }
    }
    print_spt_once(graph,dist, src,dest, parent,visited);
}

void AlterWeight(struct Graph* graph,int source,int destination,int new)
{
    node* temp=graph->adjLists[source];
    while(temp)
    {
        if(temp->vertex==destination)
        {
            temp->weight=new;
        }
        temp=temp->link;
    }
}


/* print path from source v using parent array */
void print_path(struct Graph* graph,const int *parent, int v)
{
    /* TODO: for large array  stack is better choice */
    if (parent[v] == -1) {
        printf("%d ", v);
        return ;
    }
    AlterWeight(graph,parent[v],v,FindWeight(graph,parent[v],v)+1);
    AlterWeight(graph,v,parent[v],FindWeight(graph,v,parent[v])+1);
    // graph[parent[v]][v]=graph[parent[v]][v]+1;
    // graph[v][parent[v]]=graph[v][parent[v]]+1;
    if(FindWeight(graph,v,parent[v])<0)
    {
        AlterWeight(graph,parent[v],v,0);
        AlterWeight(graph,v,parent[v],0);
    }

    print_path(graph,parent, parent[v]);
    printf("%d ", v);
}
 
void print_spt(struct Graph* graph,const int *dist, int src,int dest, const int *parent)
{
    puts("\nVertex    Distance");
    int i;
    for (i = 0; i < VERTEX; i++) {
       printf(" %2d -> %2d      %2d         ", src, i, dist[i]);
       putchar('\n');
    }
    // printf(" %2d -> %2d      %2d         ", src,dest, dist[4]);
    printf("\nPath\n");
    print_path(graph,parent, dest);
}
 

void dijkstra_min(struct Graph* graph, int src,int dest)
{
    /* dist[] will hold the shortest distance sourced src */
    int dist[VERTEX];
    /* Shortest Path Tree Set  true if a vertex in included in SPT
     *  or shortest distance from src to i is finalized
     * */
    int spt_set[VERTEX];
 
    /* parent array to store shortest path tree */
    int parent[VERTEX];
    parent[src]  = -1;            /* assuming source have no parent */
    int i;
    for (i = 0; i < VERTEX; i++) {
        dist[i]    = INT_MAX;       /* unreachable */
        spt_set[i] = 0;         /* not in SPT set */
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
        spt_set[u] = 1;
 
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
            if (FindWeight(graph,u,v) && spt_set[v] == 0 &&
                    dist[u] + FindWeight(graph,u,v) < dist[v])
            {
                dist[v]   = dist[u] + FindWeight(graph,u,v);
                parent[v] = u;
            }
    }
    /* print the constructed distance array */
    print_spt(graph,dist, src,dest, parent);
}
 
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

int distance_dijkstra(struct Graph* graph, int src,int dest)
{
    int dist[VERTEX];
    int spt_set[VERTEX];         
    int i;
    for (i = 0; i < VERTEX; i++) {
        dist[i]    = INT_MAX;       /* unreachable */
        spt_set[i] = 0;         /* not in SPT set */
    }

    dist[src] = 0;
 
    /* find shortest path for all vertices */
    for (i = 0; i < VERTEX-1; i++) {
        /* pick minimum vertex of those vertices not processed
         *  u is always equal to src in the first call of min_dist()
         *  */
        int u = min_dist(dist, spt_set);
 
        /* mark the picked vertex as processed */
        spt_set[u] = 1;
 
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
            if (FindWeight(graph,u,v) && spt_set[v] == 0 &&
                    dist[u] + FindWeight(graph,u,v) < dist[v])
            {
                dist[v]   = dist[u] + FindWeight(graph,u,v);
            }
    }
    return dist[dest];
}

void nearest_node(struct Graph* bus_graph,struct Graph* dist_graph,int source,int destination)
{
    int queue[VERTEX],i;
    for(i=0;i<VERTEX;i++)
    {
        queue[i]=-1;
    }
    int neighbours=0;
    // int neighbours=bfs(bus_graph,destination,queue);
    node* temp=dist_graph->adjLists[destination];
    while(temp)
    {
        queue[neighbours++]=temp->vertex;
        temp=temp->link;
    }
    // for(i=0;i<VERTEX;i++)
    // {
    //     if(FindWeight(dist_graph,i,destination)>0)
    //     {
    //         queue[neighbours]=i;
    //         neighbours++;
    //     }
    // }
    if(neighbours==0)
    {
    	printf("\nNo immediate neighbours, maybe take an alternate route?\n");
	}
	else
	{
		printf("\nImmediate neighbour nodes are present,bus plus walk can be done\n");
	    // dijkstra_mini(bus_graph,profit_graph,queue,source,destination);
        int min=INT_MAX-1;int mini=VERTEX;
        for(i=0;i<VERTEX;i++)
        {
       	printf("queue %d\n",queue[i]);
			if(queue[i]!=-1 && (distance_dijkstra(bus_graph,source,queue[i]))!=INT_MAX && (distance_dijkstra(bus_graph,source,queue[i])+FindWeight(dist_graph,queue[i],destination))<min)//dist_graph[queue[i]][destination])<min)
            {
//            	printf("distance is %d for %d\n",distance_dijkstra(bus_graph,source,queue[i]),queue[i]);
//        		printf("distance_graph value %d\n",profit_graph[queue[i]][destination]);
                min=distance_dijkstra(bus_graph,source,queue[i])+FindWeight(dist_graph,queue[i],destination);//profit_graph[queue[i]][destination];
				mini=queue[i];
//                printf("\nminimum is %d\n",mini);
            }
        }
//        printf("final min chosen is %d\n",mini);
        dijkstra_min(bus_graph,source,mini);
        printf("\nfrom %d move to %d by using other means for %d distance\n",mini,destination,FindWeight(dist_graph,mini,destination));//profit_graph[mini][destination]
	}
}

int FindWeight(struct Graph* graph,int source,int destination)
{
    node* temp=graph->adjLists[source];
    while(temp)
    {
        if(temp->vertex==destination)
        {
            return temp->weight;
        }
        temp=temp->link;
    }
    return 0;
}

void DFS(struct Graph* graph,int visited[],int visit[],int order[],int source,int index)
{
    visited[source]=1;
    if(visit[source]==1)
    {
        order[index++]=source;
    }
    int j;
    for(j=0;j<VERTEX;j++)
       if(!visited[j] && FindWeight(graph,source,j)!=0)
       {
            DFS(graph,visited,visit,order,j,index);
       }
}
 
void dfs(struct Graph* graph,int visit[],int order[],int source)
{
    int j;
    int visited[VERTEX];
    for(j=0;j<VERTEX;j++)
    {
     visited[j]=0;
    }
    int index=0;
    DFS(graph,visited,visit,order,source,0);
}

int main()
{
int i,j;
    printf("Let us first create the graph, enter the number of vertices\n");
    int vertex,weight,prof,p; scanf("%d",&vertex);
    int visit_loc[vertex],ordered_loc[vertex];
    VERTEX=vertex;
    struct Graph* graph1 = createGraph(vertex);
    struct Graph* graph2 = createGraph(vertex);
    while(1)
    {
        printf("Enter vertexes for edges and -1 and -1 for exit\n");
        scanf("%d %d",&i,&j);
        if(i==-1 && j==-1)
            break;
        printf("Enter distance");
        scanf("%d",&weight);
        addEdge(graph1, i, j,weight);
    }
    int choice1,choice;
    printf("Do you want to add a bus/train route (1-yes or 0-no)\n");
    scanf("%d",&choice1);
    if(choice1==1)
    {
    	while(1)
    	{
    		int dist;
    		printf("Enter vertexes for edges and -1 and -1 for exit\n");
        	scanf("%d %d",&i,&j);
        	if(i==-1 && j==-1)
            	break;
        	printf("Enter distance\n");
        	scanf("%d",&dist);
            addEdge(graph2, i, j,dist);
		}
    }
    printf("Distance graph\n");
    printGraph(graph1);
    if(choice1==1)
    {
        printf("\nBus route graph\n");
        printGraph(graph2);
    }
    int source,destination,num_travelers;int visited[vertex];
    printf("\nEnter your choice:\n1) Traveler or travelers which have to visit places\n2) Shortest route from one place to another based on distance and traffic\n");
    printf("3)To report connection changes from place A to B\n4)To display shortest route to place via public trasnport\n");
    printf("5)Look for popular places or insert?\n6)To display the graphs\n");
    scanf("%d",&choice);
    do{
    switch(choice)
    {
        case 1:
//            int visited[vertex];
            printf("Suggesting path for travelers\n");
            printf("Traveler based on locations\n");
            printf("Enter source and destination vertex\n");
            scanf("%d %d",&source,&destination);
            printf("Enter the number of travelers going from %d to %d\n",source,destination);
            scanf("%d",&num_travelers);
            int i;
            printf("Enter 1 for the vertices you want to visit between the source and destiantion and 0 for nodes which are not needed\n");
            for(i=0;i<vertex;i++)
            {
                ordered_loc[i]=-1;
                visited[i]=0;
                printf("\n%d =>");
                scanf("%d",&visit_loc[i]);
            }
            dfs(graph1,visit_loc,ordered_loc,source);int ref;
            printf("%d",FindWeight(graph1,1,2));
            dijkstra_min(graph1,source,ordered_loc[0]);
            for(i=0;i<(vertex-1) && ordered_loc[i+1]!=-1;i++)
            {
                if(visited[ordered_loc[i+1]]==0)
                dijkstra_min(graph1,ordered_loc[i],ordered_loc[i+1]);
            }
            dijkstra_min(graph1,ordered_loc[i],destination);
            break;
        case 2:
            printf("Shortest route only based on distance and traffic\n");
            printf("Traveler based on locations\n");
            printf("Enter source and destination vertex\n");
            scanf("%d %d",&source,&destination);
            printf("Enter the number of travelers going from %d to %d\n",source,destination);
            scanf("%d",&num_travelers);
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
            AlterWeight(graph1,source,destination,new_weight);
            AlterWeight(graph1,destination,source,new_weight);
            printf("modified graph\n");
            printGraph(graph1);
            break;
           
        case 4:
            if(choice1==1)
            {
            	printf("Bus route:\n");int i;int flag=0;
                printf("Enter source and destination vertex\n");
                scanf("%d %d",&source,&destination);
               printf("Enter the number of travelers going from %d to %d\n",source,destination);
               scanf("%d",&num_travelers);
               int num=num_travelers/30;
                for(i=0;i<VERTEX;i++)
                {
                    if(FindWeight(graph2,i,destination))
                    {
                        printf("direct bus\n");
                        dijkstra_min(graph2,source,destination);
                        printf("\n"); 
                        flag=1;
                        break;
                    }
                }
                if(flag==0)
                {
                	printf("no direct bus\n");
                    nearest_node(graph2,graph1,source,destination);
                }
            }
            else
            {
                printf("Bus route not inserted.Insert it now? (1 for yes, 0 for no)\n");
                scanf("%d",&choice1);
                if(choice1==1)
                {
                    while(1)
                    {
                        printf("Enter vertexes for edges and -1 and -1 for exit\n");
                        scanf("%d %d",&i,&j);
                        if(i==-1 && j==-1)
                            break;
                        printf("Enter distance\n");
                        scanf("%d",&weight);
                        addEdge(graph2, i, j,weight);
                    }
                }
                else
                {
                    break;
                }
            }
            break;
        case 6:
            printf("\nDistance graph\n");
            printGraph(graph1);
            if(choice1==1)
            {
                printf("\nBus route graph\n");
                printGraph(graph2);
            }
            break;
        default:
            printf("wrong option\n");
            break;
    }
    printf("\nEnter your choice:\n1) Traveler or travelers which have to visit places\n2) Shortest route from one place to another based on distance and traffic\n");
    printf("3)To report connection changes from place A to B\n4)To display shortest route to place via public trasnport\n");
    printf("5)Look for popular places or insert?\n6)To display the graphs\n");
    printf("Other choices to quit\n");
    scanf("%d",&choice);
    }while(choice<7 && choice>=1);
    return 0;
}


/*
6
1 2 10 12
2 4 30 42
1 3 20 37
3 5 40 59
5 0 50 64
4 5 60 72
-1 -1
1
1 2 10
2 4 30
-1 -1
4
1 5
*/

/*
5
1 2 10
2 3 20
3 4 40
4 0 50
1 0 90
-1 -1
0
1
1 0
1
0
0
1
1
1
*/
/*
10
1 2 10
2 3 20
3 4 40
2 5 50
5 4 40
4 0 20
1 6 60
6 7 70
7 9 80
6 8 50
8 9 10
9 0 10
-1 -1
0
1
1 0
1
0
0
1
1
1
1
0
0
0
0
*/