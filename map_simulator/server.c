#include "header.h"
// building basic graph section

struct node* createNode(int v,int w)
{
    struct node* newNode=(struct node*)malloc(sizeof(struct node));
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
        printf("Adjacency list of vertex %d can be represented as:\n", v);
        while (temp->link)
        {
            printf("%d -> ", temp->vertex);
            temp = temp->link;
        }
        printf("%d", temp->vertex);
        printf("\n");
    }
}

void printGraphwithWeights(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->numVertices; v++)
    {
        struct node* temp = graph->adjLists[v];
        if(!temp)
        {
            printf("No links yet for vertex %d\n",v);
            continue;
        }
        printf("Adjacency list of vertex %d is displayed below:\n", v);
        while (temp)
        {
            printf("Vertex:%d Weight:%d\n", temp->vertex,temp->weight);
            temp = temp->link;
        }
    }
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


// end of basic graph functions section

// for review section

review* newReview(char *re,int rate)
{
    review* new=(review*)malloc(sizeof(review));
    strcpy(new->r,re);
    new->rating=rate;
    new->link=NULL;
    return new;
}

popular* newPopularity(int ind)
{
    popular* new=(popular*)malloc(sizeof(popular));
    new->head=NULL;
    new->index=ind;
    new->number_of_reviews=0;
    return new;
}

void insertReview(popular* p[],int loc,char* s,int rate)
{
    popular* temp=p[loc];
    p[loc]->number_of_reviews+=1;
    review* temp2=temp->head;
    if(temp2==NULL)
    {
        temp->head=newReview(s,rate);
    }
    else
    {
        review* prev=NULL;
        while(temp2 && temp2->rating>rate)
        {
            prev=temp2;
            temp2=temp2->link;
        }
        if(prev==NULL)
        {
            temp->head=newReview(s,rate);
            temp->head->link=temp2;
        }
        else
        {
            review* temp3=newReview(s,rate);
            prev->link=temp3;
            temp3->link=temp2;
        }
    }
}

void DisplayReviews(popular* p[],int loc)
{
    popular* temp=p[loc];
    review* temp2=temp->head;
    printf("Number of reviews on this place: %d\n",p[loc]->number_of_reviews);
    if(temp2==NULL)
    {
        printf("No reviews on this place yet!\n");
        return;
    }
    printf("\nReviews from highest to lowest are:\n");int n=1;
    while(temp2)
    {
        printf("\n%d)\n",n);n++;
        printf("Rating: %d\n",temp2->rating);
        printf("Review: %s",temp2->r);
        temp2=temp2->link;
    }
}

// end of review section


// dfs for traveler's path 


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


// end of dfs

// finding shortest path

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

void print_path(struct Graph* graph,const int *parent, int v)
{
    if (parent[v] == -1) {
        printf("%d ", v);
        return ;
    }
    AlterWeight(graph,parent[v],v,FindWeight(graph,parent[v],v)+1);
    AlterWeight(graph,v,parent[v],FindWeight(graph,v,parent[v])+1);
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
       printf(" %d -> %d      %d         \n", src, i, dist[i]);
    }
    printf("\nPath\n");
    print_path(graph,parent, dest);
}


void dijkstra_min(struct Graph* graph, int src,int dest)
{
    int dist[VERTEX];
    int spt_set[VERTEX];
    int parent[VERTEX];
    parent[src]  = -1;         
    int i;
    for (i = 0; i < VERTEX; i++) {
        dist[i]    = INT_MAX;     
        spt_set[i] = 0;        
    }
    dist[src] = 0;
    for (i = 0; i < VERTEX-1; i++) {
        int u = min_dist(dist, spt_set);
        spt_set[u] = 1;
 
        if (dist[u] == INT_MAX) continue;
 
        int v;
        for (v = 0; v < VERTEX; v++)
            if (FindWeight(graph,u,v) && spt_set[v] == 0 &&
                    dist[u] + FindWeight(graph,u,v) < dist[v])
            {
                dist[v]   = dist[u] + FindWeight(graph,u,v);
                parent[v] = u;
            }
    }
        print_spt(graph,dist, src,dest, parent);
}
 

// end of shortest path

// finding path for public transport


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
     for (i = 0; i < VERTEX-1; i++) {
        int u = min_dist(dist, spt_set);
         spt_set[u] = 1;
        if (dist[u] == INT_MAX) continue;
         int v;
        for (v = 0; v < VERTEX; v++)
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
    node* temp=dist_graph->adjLists[destination];
    while(temp)
    {
        queue[neighbours++]=temp->vertex;
        temp=temp->link;
    }
    if(neighbours==0)
    {
    	printf("\nNo immediate neighbours, maybe take an alternate route?\n");
	}
	else
	{
		printf("\nImmediate neighbour nodes are present,bus plus walk can be done\n");
        int min=INT_MAX-1;int mini=VERTEX;
        for(i=0;i<VERTEX;i++)
        {
       	// printf("queue %d\n",queue[i]);
			if(queue[i]!=-1 && (distance_dijkstra(bus_graph,source,queue[i]))!=INT_MAX && (distance_dijkstra(bus_graph,source,queue[i])+FindWeight(dist_graph,queue[i],destination))<min)
            {
//            	printf("distance is %d for %d\n",distance_dijkstra(bus_graph,source,queue[i]),queue[i]);
//        		printf("distance_graph value %d\n",profit_graph[queue[i]][destination]);
                min=distance_dijkstra(bus_graph,source,queue[i])+FindWeight(dist_graph,queue[i],destination);
				mini=queue[i];
            }
        }
        dijkstra_min(bus_graph,source,mini);
        printf("\nfrom %d move to %d by using other means for %d distance\n",mini,destination,FindWeight(dist_graph,mini,destination));//profit_graph[mini][destination]
	}
}


// end of path finding for public transport

// storing data in file
void display(struct Graph* graph,int type)
{
    int m,n;
	// printf("\t");
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
    for(i=0;i<VERTEX;i++)
    {
        int j;
        node* temp=graph->adjLists[i];
        while(temp)
        {
        	fprintf(fp,"Vertex:%d\t",temp->vertex);
        	fprintf(fp,"Weight:%d\t",temp->weight);
        	temp=temp->link;
            // printf("%d\t",graph[i][j]);
        }
		// printf("\n\t");
		fprintf(fp,"\n");
    }
    fclose(fp);
}