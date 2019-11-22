#include "server.c"
int main()
{
int i,j;
    printf("Let us first Create the graph, \nEnter the number of vertices=>");
    int vertex,weight,prof,p; scanf("%d",&vertex);
    int visit_loc[vertex],ordered_loc[vertex];
    VERTEX=vertex;
    struct Graph* graph1 = createGraph(vertex);
    struct Graph* graph2 = createGraph(vertex);
    while(1)
    {
        printf("Enter Vertices for Edges and -1 and -1 for Exit\n");
        scanf("%d %d",&i,&j);
        if(i==-1 && j==-1)
            break;
        printf("Enter Distance=>");
        scanf("%d",&weight);
        addEdge(graph1, i, j,weight);
    }
    int choice1,choice;
    printf("\n\nDo you want to add a bus/train route (1-yes or 0-no)\n");
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
            addEdge(graph2, i, j,dist);
		}
    }
    printf("\n\nDistance graph\n");
    printGraphwithWeights(graph1);
    if(choice1==1)
    {
        printf("\nPublic Trasnport graph\n");
         printGraphwithWeights(graph2);
    }
    popular* po[vertex];
    for(i=0;i<vertex;i++)
    {
        po[i]=newPopularity(i);
    }
    int source,destination,num_travelers;int visited[vertex];int choice3,loc;char s[10000];int rate;
    printf("\n=======================================================================");
    printf("\n\nFeatures of Map Simulator:-\n1)Shortest route from one place to another based on distance and traffic\n");
    printf("2)To report connection changes from place A to B\n3)To display shortest route to place via public trasnport\n");
    printf("4)Look for popular places or leave a review..\n5) Traveler or travelers which have to visit places\n6)To display the graphs\nEnter Your Choice:");
    scanf("%d",&choice);
    do{
    switch(choice)
    {
        case 5:
            printf("\nSuggesting path for travelers that covers all the path they need to visit\n");
            printf("Traveler based on locations\n");
            printf("\nEnter source and destination vertex\n");
            scanf("%d %d",&source,&destination);
            printf("Enter the number of travelers going from %d to %d\n",source,destination);
            scanf("%d",&num_travelers);
            int i;
            printf("\nEnter 1 for the vertices you want to visit between the source and destiantion and 0 for nodes which are not needed\n");
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
        case 1:
            printf("\nShortest route only based on distance and traffic\n");
            printf("Traveler based on locations\n");
            printf("\nEnter source and destination vertex\n");
            scanf("%d %d",&source,&destination);
            printf("Enter the number of travelers going from %d to %d\n",source,destination);
            scanf("%d",&num_travelers);
            for(i=0;i<num_travelers;i++)
            {
                dijkstra_min(graph1, source,destination);
                printf("\n");  
            }
            break;

        case 2:
            printf("\nConnection changes\n");
            int source,destination,new_weight;
            printf("\nEnter source and destination vertex\n");
            scanf("%d %d",&source,&destination);
            printf("\nEnter altered weight\n");
            scanf("%d",&new_weight);
            AlterWeight(graph1,source,destination,new_weight);
            AlterWeight(graph1,destination,source,new_weight);
            printf("\nModified graph\n");
            printGraph(graph1);
            break;
           
        case 3:
            if(choice1==1)
            {
            	printf("\nBus route:\n");int i;int flag=0;
                printf("Enter source and destination vertex\n");
                scanf("%d %d",&source,&destination);
//               printf("Enter the number of travelers going from %d to %d\n",source,destination);
//               scanf("%d",&num_travelers);
//               int num=num_travelers/30;
                for(i=0;i<VERTEX;i++)
                {
                    if(FindWeight(graph2,i,destination))
                    {
                        printf("Direct bus from %d to %d\n",source,destination);
                        dijkstra_min(graph2,source,destination);
                        printf("\n"); 
                        flag=1;
                        break;
                    }
                }
                if(flag==0)
                {
                	printf("No direct bus from %d to %d\n",source,destination);
                    nearest_node(graph2,graph1,source,destination);
                }
            }
            else
            {
                printf("\nPublic transport route is not inserted.Insert it now? (1 for yes, 0 for no)\n");
                scanf("%d",&choice1);
                if(choice1==1)
                {
                    while(1)
                    {
                        printf("\nEnter Vertices for Edges and -1 and -1 for Exit\n");
                        scanf("%d %d",&i,&j);
                        if(i==-1 && j==-1)
                            break;
                        printf("Enter distance=>");
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
        case 4:
            printf("\nLeave a review or see other people's review about a place.. '1' for inserting..'2' for viewing\n");
            scanf("%d",&choice3);
            if(choice3==1)
            {   
                printf("\nEnter the location which you want to review=>");
                scanf("%d",&loc);
                fflush(stdin);
                printf("Enter the review=>\n");
                scanf("%[^\n]c", s); 
                fflush(stdin);
                printf("Enter the rating for the location=>");
                scanf("%d",&rate);
                fflush(stdin);
                insertReview(po,loc,s,rate);
            }
            if(choice3==2)
            {
                printf("\nEnter the location for which you want to see review=>");
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
            printf("Wrong option\n");
            break;
    }
    printf("\nFeatures of Map Simulator:-1)Shortest route from one place to another based on distance and traffic\n");
    printf("2)To report connection changes from place A to B\n3)To display shortest route to place via public trasnport\n");
    printf("4)Look for popular places or leave a review..\n5) Traveler or travelers which have to visit places\n6)To display the graphs\nOthers to quit\n\nEnter Your Choice:");
    scanf("%d",&choice);
    }while(choice<7 && choice>=1);
    display(graph1,1);
    display(graph2,2);
    return 0;
}


// Graph examples to test
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
