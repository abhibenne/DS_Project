//#include "header.h"
#include "server.c"
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
        printf("\nPublic Trasnport graph\n");
        printGraph(graph2);
    }
    popular* po[vertex];
    for(i=0;i<vertex;i++)
    {
        po[i]=newPopularity(i);
    }
    int source,destination,num_travelers;int visited[vertex];int choice3,loc,rate;char s[10000];
    printf("\nEnter your choice:\n1) Traveler or travelers which have to visit places\n2) Shortest route from one place to another based on distance and traffic\n");
    printf("3)To report connection changes from place A to B\n4)To display shortest route to place via public trasnport\n");
    printf("5)Look for popular places or leave a review?\n6)To display the graphs\n");
    scanf("%d",&choice);
    do{
    switch(choice)
    {
        case 1:
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
                printf("Public transport route not inserted.Insert it now? (1 for yes, 0 for no)\n");
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
        case 5:
            printf("\nLeave a review or see other people's review about a place. 1 for inserting,2 for viewing\n");
            scanf("%d",&choice3);
            if(choice3==1)
            {   
                printf("Enter the location which you want to review\n");
                scanf("%d",&loc);
                fflush(stdin);
                printf("Enter the review\n");
                scanf("%[^\n]c", s); 
                fflush(stdin);
                printf("Enter the rating for the location\n");
                scanf("%d",&rate);
                insertReview(po,loc,s,rate);
                printf("Do you want to see reviews? (2 for seeing)\n");
                scanf("%d",&choice3);
            }
            if(choice3==2)
            {
                printf("Enter the location for which you want to see review\n");
                scanf("%d",&loc);
                DisplayReviews(po,loc);
            }
            break;
        case 6:
            printf("\nDistance graph\n");
            printGraphwithWeights(graph1);
            if(choice1==1)
            {
                printf("\nBus route graph\n");
                printGraphwithWeights(graph2);
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


// Graph examples for testing
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
