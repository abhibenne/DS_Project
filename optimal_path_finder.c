#include <stdio.h>
#include <limits.h>
 
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

int max_dist(const int *dist, int *spt_set)
{
    int max = INT_MIN, max_idx = 0;
    int i;
    for (i = 0; i < VERTEX; i++)
        if (spt_set[i] == 0 && max < dist[i]) {
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
        printf("%d ",v);
        return ;
    }
    // trying to alter it
    graph[parent[v]][v]=graph[parent[v]][v]+1;
    graph[v][parent[v]]=graph[v][parent[v]]+1;
    if(graph[v][parent[v]]<0)
    {
        graph[v][parent[v]]=0;
        graph[parent[v]][v]=0;
    }
    print_path(graph,parent, parent[v]);
    printf("%d ",v);
}
 
void print_spt(int graph[VERTEX][VERTEX],const int *dist, int src,int dest, const int *parent)
{
    puts("  Vertex    Distance");
    int i;
    for (i = 0; i < VERTEX; i++) {
       printf(" %2d -> %2d      %2d", src, i, dist[i]);
       putchar('\n');
    }
    // printf(" %2d -> %2d      %2d         ", src,dest, dist[4]);
    printf("Path  ");
    print_path(graph,parent, dest);
    printf("\n\n");
}
 
void dijkstra_max(int graph[VERTEX][VERTEX], int src,int dest)
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
        dist[i]    = INT_MIN;       /* unreachable */
        spt_set[i] = 0;         /* not in SPT set */
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
        spt_set[u] = 1;
 
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
            if (graph[u][v] && spt_set[v] == 0 &&
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
    int spt_set[VERTEX];
 
    /* parent array to store shortest path tree */
    int parent[VERTEX];
    parent[src]  = -1;            /* assuming source have no parent */
    int i;
    for (i = 0; i < VERTEX; i++) 
	{
        dist[i]    = INT_MAX;       /* unreachable */
        spt_set[i] = 0;         /* not in SPT set */
    }
 
    /* distance of source vertex to itself always 0 */
    dist[src] = 0;
 
    /* find shortest path for all vertices */
    for (i = 0; i < VERTEX-1; i++) 
	{
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
            if (graph[u][v] && spt_set[v] == 0 &&
                    dist[u] + graph[u][v] < dist[v])
            {
                dist[v]   = dist[u] + graph[u][v];
                parent[v] = u;
            }
    }
    /* print the constructed distance array */
    print_spt(graph,dist, src,dest, parent);
}
 
void display(int v;int graph[v][v],int v,int type)
{
    int m,n;
	printf("\t");
    FILE *fp;
    if(type==1)
    {
    	fp = fopen("distance.txt","w");
		fprintf(fp,"Distance Graph\n\n");
	}
	else if(type==2)
	{
    	fp = fopen("bus.txt","w"); 
		fprintf(fp,"Bus Graph\n\n");
	}
    int i;
    for(i=0;i<v;i++)
    {
        int j;
        for(j=0;j<v;j++)
        {
        	fprintf(fp,"%d\t",graph[i][j]);
            printf("%d\t",graph[i][j]);
        }
		printf("\n\t");
		fprintf(fp,"\n");
    }
    fclose(fp);
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

int distance_dijkstra(int graph[VERTEX][VERTEX], int src,int dest)
{
    int dist[VERTEX];
    int spt_set[VERTEX];         
    int i;
    for (i = 0; i < VERTEX; i++) 
	{
        dist[i]    = INT_MAX;       /* unreachable */
        spt_set[i] = 0;         /* not in SPT set */
    }

    dist[src] = 0;
 
    /* find shortest path for all vertices */
    for (i = 0; i < VERTEX-1; i++) 
    {
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
            if (graph[u][v] && spt_set[v] == 0 &&
                    dist[u] + graph[u][v] < dist[v])
            {
                dist[v]   = dist[u] + graph[u][v];
            }
    }
    return dist[dest];
}

void nearest_node(int bus_graph[VERTEX][VERTEX],int profit_graph[VERTEX][VERTEX],int source,int destination)
{
    int queue[VERTEX],i;
    for(i=0;i<VERTEX;i++)
    {
        queue[i]=-1;
    }
    // int neighbours=bfs(bus_graph,destination,queue);
    int neighbours=0;
    for(i=0;i<VERTEX;i++)
    {
        if(profit_graph[i][destination]>0)
        {
            queue[neighbours]=i;
            neighbours++;
        }
    }
    if(neighbours==0)
    {
    	printf("No immediate neighbours, maybe take an alternate route..\n");
	}
	else
	{
		printf("\nImmediate Neighbour Nodes are present,Bus plus Walk can be done\n");
		printf("%d %d %d\n",queue[0],queue[1],queue[2]);
	    // dijkstra_mini(bus_graph,profit_graph,queue,source,destination);
        int min=INT_MAX-1;int mini=VERTEX;
        for(i=0;i<VERTEX;i++)
        {
//        	printf("queue %d\n",queue[i]);
			if(queue[i]!=-1 && (distance_dijkstra(bus_graph,source,queue[i]))!=INT_MAX && (distance_dijkstra(bus_graph,source,queue[i])+profit_graph[queue[i]][destination])<min)
            {
//            	printf("distance is %d for %d\n",distance_dijkstra(bus_graph,source,queue[i]),queue[i]);
//        		printf("distance_graph value %d\n",profit_graph[queue[i]][destination]);
                min=distance_dijkstra(bus_graph,source,queue[i])+profit_graph[queue[i]][destination];
				mini=queue[i];
//                printf("\nminimum is %d\n",mini);
            }
        }
//        printf("final min chosen is %d\n",mini);
        dijkstra_min(bus_graph,source,mini);
        printf("\nFrom %d move to %d by using other means for %d distance\n",mini,destination,profit_graph[mini][destination]);
	}
}

void bfs(int graph[VERTEX][VERTEX],int visit[],int order[],int source)
{
    int q[VERTEX];
    int count=0,j;
    int visited[VERTEX];
    for(j=0;j<VERTEX;j++)
    {
     visited[j]=0;
    }
    int top=-1;int index=0;
    visited[source]=1;top++;
    q[0]=source;int front=0;
    while(front!=(top+1))
   {
        printf("Inside BFS: %d",q[top]);
        printf("Top value is %d\n",top);
        int a=q[front++];
        int i;
        for(i=0;i<VERTEX;i++)
        {
            if(!visited[i] && graph[a][i]!=0)
            {
                if(visit[i]==1)
                {
                    order[index++]=i;
                }
                visited[i]=1;
                q[++top]=i;
            }
        }
   }
}

void DFS(int graph[VERTEX][VERTEX],int visited[],int visit[],int order[],int source,int index)
{
    visited[source]=1;
    if(visit[source]==1)
    {
        order[index++]=source;
    }
    int j;
    for(j=0;j<VERTEX;j++)
       if(!visited[j] && graph[source][j]!=0)
       {
            DFS(graph,visited,visit,order,j,index);
       }
}
 
void dfs(int graph[VERTEX][VERTEX],int visit[],int order[],int source)
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
    printf("Let us first Create the graph,\nEnter the Number of Vertices=>");
    int vertex,weight,prof,p; 
    scanf("%d",&vertex);
    int visit_loc[vertex],ordered_loc[vertex];
    int graph1[vertex][vertex];
    int graph3[vertex][vertex];
    VERTEX=vertex;
    initialize(graph1,vertex);
    initialize(graph3,vertex);
    while(1)
    {
        printf("\nEnter Vertices for Edges and -1 and -1 for Exit\n");
        scanf("%d %d",&i,&j);
        if(i==-1 && j==-1)
            break;
        printf("Enter Distance=>");
        scanf("%d",&weight);
        graph1[i][j]=weight;
        graph1[j][i]=weight;
    }
    int choice1,choice;
    printf("\n\nDo you want to add a Bus/Train Route? (1-yes or 0-no)\n");
    scanf("%d",&choice1);
    if(choice1==1)
    {
    	while(1)
    	{
    		int dist;
    		printf("\nEnter Vertices for Edges and -1 and -1 for Exit\n");
        	scanf("%d %d",&i,&j);
        	if(i==-1 && j==-1)
            	break;
        	printf("Enter Distance=>");
        	scanf("%d",&dist);
        	graph3[i][j]=dist;
        	graph3[j][i]=dist;
		}
    }
    printf("==============================================================================");
    printf("\n\nDISTANCE graph\n");
    display(graph1,vertex,1);
    if(choice1==1)
    {
        printf("\nBUS ROUTE graph\n");
        display(graph3,vertex,2);
    }
    int source,destination,num_travelers;
    printf("\n----------------------------------------------------------------------------");
    printf("\n\nFeatures of Optimal Path Finder:-\n1) Traveler or Travelers which have to visit places\n2) Shortest route from one place to another based on distance and traffic\n");
    printf("3) To report connection changes from place A to B\n4) To display shortest route to place via public trasnport\n5) To display the graphs\nEnter Your choice:");
    scanf("%d",&choice);
    do{
    switch(choice)
    {
        case 1:
            printf("======================================================================");
            printf("\n\nSuggesting path for travelers\n");
            printf("Traveler based on locations\n");
            printf("\nEnter Source and Destination vertex=>");
            scanf("%d %d",&source,&destination);
            printf("Enter the Number of Travelers going from %d to %d=>",source,destination);
            scanf("%d",&num_travelers);
            int i;
            printf("\nEnter '1' for the Vertices You want to visit between the Source and Destination and '0' for nodes which are not needed\n");
            for(i=0;i<vertex;i++)
            {
                printf("\n%d =>");
                scanf("%d",&visit_loc[i]);
            }
            for(i=0;i<vertex;i++)
            {
				ordered_loc[i]=-1;
            }
            dfs(graph1,visit_loc,ordered_loc,source);
            dijkstra_min(graph1,source,ordered_loc[0]);
            for(i=0;i<(vertex-1) && ordered_loc[i+1]!=-1;i++)
            {
                dijkstra_min(graph1,ordered_loc[i],ordered_loc[i+1]);
            }
            dijkstra_min(graph1,ordered_loc[i],destination);
            break;
        case 2:
            printf("#####################################################################");
            printf("\n\nShortest Route only based on Distance and Traffic");
            printf("Traveler based on Locations\n");
            printf("Enter Source and Destination Vertex=>");
            scanf("%d %d",&source,&destination);
            printf("Enter the Number of Travelers going from %d to %d=>",source,destination);
            scanf("%d",&num_travelers);
            for(i=0;i<num_travelers;i++)
            {
                dijkstra_min(graph1, source,destination);
                printf("\n");  
            }
            break;
        case 3:
            printf("---------------------------------------------------------------------");
            printf("\n\nConnection changes\n");
            int source,destination,new_weight;
            printf("Enter Source and Destination vertex=>");
            scanf("%d %d",&source,&destination);
            printf("Enter Altered weight=>");
            scanf("%d",&new_weight);
            graph1[source][destination]=new_weight;
            graph1[destination][source]=new_weight;
            printf("\nModified graph\n");
            display(graph1,VERTEX,1);
            break;
        case 4:
            if(choice1==1)
            {
                printf("=====================================================================");
            	printf("\n\nBus route:-\n");int i;int flag=0;
                printf("Enter Source and Destination vertex=>");
                scanf("%d %d",&source,&destination);
               printf("Enter the Number of travelers going from %d to %d=>",source,destination);
               scanf("%d",&num_travelers);
               int num=num_travelers/30;
                for(i=0;i<VERTEX;i++)
                {
                    if(graph3[i][destination])
                    {
                        printf("Direct bus from %d to %d\n",source,destination);
                        dijkstra_min(graph3,source,destination);
                        printf("\n"); 
                        flag=1;
                        break;
                    }
                }
                if(flag==0)
                {
                	printf("No Direct bus from %d to %d..\n",source,destination);
                    nearest_node(graph3,graph1,source,destination);
                }
            }
            else
            {
                printf("Bus Route is not inserted...Insert it now? (1 for yes, 0 for no)\n");
                scanf("%d",&choice1);
                if(choice1==1)
                {
                    while(1)
                    {
                        printf("Enter Vertices for Edges and -1 and -1 for Exit\n");
                        scanf("%d %d",&i,&j);
                        if(i==-1 && j==-1)
                            break;
                        printf("Enter Distance=>");
                        scanf("%d",&weight);
                        graph3[i][j]=weight;
                        graph3[j][i]=weight;
                    }
                }
                else
                {
                    break;
                }
            }
            break;
        case 5:
            printf("\nDistance graph\n");
            display(graph1,vertex,1);
            if(choice1==1)
            {
                printf("\nBus Route graph\n");
                display(graph3,vertex,1);
            }
            break;
        default:
            printf("Wrong option\n");
            break;
    }
    printf("\n\nFeatures of Optimal Path Finder:-\n1) Traveler or Travelers which have to visit places\n2) Shortest route from one place to another based on distance and traffic\n");
    printf("3) To report connection changes from place A to B\n4) To display shortest route to place via public trasnport\n5) To display the graphs\n");
    printf("6)Other choices to quit\nEnter Your choice:");
    scanf("%d",&choice);
    }while(choice<6 && choice>=1);
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
