#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

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
typedef struct Graph Graph;
 
struct review
{
    char r[10000];
    int rating;
    struct review* link; 
};
typedef struct review review;
struct Popularity
{
    struct review* head;
    int index;
    int number_of_reviews;
};
typedef struct Popularity popular;
int VERTEX;
review* newReview(char *re,int rate);
popular* newPopularity(int ind);
struct node* createNode(int v,int w);
struct Graph* createGraph(int vertices);
void addEdge(struct Graph* graph, int src, int dest,int weight);
void printGraph(struct Graph* graph);
void printGraphwithWeights(struct Graph* graph);
int min_dist(const int *dist, int *spt_set);
void AlterWeight(struct Graph* graph,int source,int destination,int );
void print_path(struct Graph* graph,const int *parent, int v);
void print_spt(struct Graph* graph,const int *dist, int src,int dest, const int *parent);
void dijkstra_min(struct Graph* graph, int src,int dest);
int distance_dijkstra(struct Graph* graph, int src,int dest);
void nearest_node(struct Graph* bus_graph,struct Graph* dist_graph,int source,int destination);
int FindWeight(struct Graph* graph,int source,int destination);
void DFS(struct Graph* graph,int visited[],int visit[],int order[],int source,int index);
void dfs(struct Graph* graph,int visit[],int order[],int source);
void insertReview(popular* p[],int loc,char* s,int rate);
void DisplayReviews(popular* p[],int loc);
