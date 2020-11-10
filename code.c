#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 99999

//struct for the edges of the graph
struct Edge {
  int u;  //start vertex of the edge
  int v;  //end vertex of the edge
  int w;  //weight of the edge (u,v)
};

//Graph - it consists of edges
struct Graph {
  int V;        //total number of vertices in the graph
  int E;        //total number of edges in the graph
  struct Edge *edge;  //array of edges
};

void bellmanford(struct Graph *graph, int source);
void display(int arr[], int size, int parent[]);
//void printpath(int parent[], int x);

struct Graph* createGraph(int V, int E)
{

    struct Graph* graph = (struct Graph*) malloc( sizeof(struct Graph) );
    graph->V = V;
    graph->E = E;

    graph->edge = (struct Edge*) malloc( graph->E * sizeof( struct Edge ) );

    return graph;
}

 void BellmanFord(struct Graph* graph, int source)
 {
    int i,j,u,v,w;
    int V = graph->V;
    int E = graph->E;
    int dist[V];
    int parent[V];

  // Over Estimation
    for (int i = 1; i <= V; i++) //initialise all dist to INT_MAX
        dist[i]  = INF;
    dist[source] = 0;
    parent[i] = 0;

  // Relaxation
    for (i = 0; i <= V-1; i++)
    {
        for (j = 0; j < E; j++)
        {
          int u = graph->edge[j].u;
          int v = graph->edge[j].v;
          int weight = graph->edge[j].w;

            if (dist[u] + weight < dist[v])
            {
              dist[v] = dist[u] + weight;
              parent[v] = u;
            }
        }
    }

  // Negative Cycle check
      for (i = 0; i < E; i++)
      {
        int u = graph->edge[i].u;
        int v = graph->edge[i].v;
        int weight = graph->edge[i].w;

        if (dist[u] + weight < dist[v])
        {
          printf("Graph contains negative weight cycle");
        }
      }
      printf("OUTPUT: ");
      printf("\n Vertex\t  Distance\tPath");
   
  int destination;
	printf("\n Enter Destination vertex: ");
	scanf("%d",&destination);
	path(destination,parent,source);
      
   //display(dist, V, parent);
   // printpath(parent, V);
 }
 
/*void printpath(int parent[], int x)
  {

    if (parent[x]==0)
        return;
    printpath(parent, parent[x]);
 
    printf("%d ", x);
  }*/

int path(int destination, int parent[], int source){
	if(destination==source){
	printf("%d <-- ",destination);
	return 0;
	}
	if(destination!=source){
		printf("%d <-- ",destination);
		return(path(parent[destination-1],parent,source));
	}
}



 /* void display(int arr[], int size, int parent[]) 
  {
    int i;
    for (i = 0; i < size; i++)
    {
      printf("\n0 -> %d \t\t %d\t\t0 ", i, arr[i]);
      printpath(parent, i);
    }  
  printf("\n");
  } 
*/
int main()
{
  int V,E; 
  printf("Enter number of vertices: ");
  scanf("%d",&V); // Number of vertices in graph
  printf("Enter number of edges: ");
  scanf("%d",&E); // Number of edges in graph

    struct Graph* graph = createGraph(V, E);

    int i;
    for(i=0;i<E;i++)
    {
      printf("Enter source node and destination node for %d also its weight", i);
      printf("\n");
      scanf("%d",&graph->edge[i].u);
      scanf("%d",&graph->edge[i].v);
      scanf("%d",&graph->edge[i].w);
    }
    BellmanFord(graph,0); // 0 is the source node
    return 0;
}
