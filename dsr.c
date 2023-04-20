#include <stdio.h>
#include <stdlib.h>
#define MAX_NODES 100
#define INF 99999
int graph[MAX_NODES][MAX_NODES];
int nodes;
void initialize_graph() {
   int i, j;
   for (i = 0; i < MAX_NODES; i++) {
     for (j = 0; j < MAX_NODES; j++) {
       if (i == j) {
        graph[i][j] = 0;
       } else {
        graph[i][j] = INF;
       }
     }
   }
}
void add_edge(int u, int v, int w) {
   graph[u][v] = w;
   graph[v][u] = w;
 }
void print_graph() {
   int i, j;
   printf("Graph:\n");
   for (i = 0; i < nodes; i++) {
     for (j = 0; j < nodes; j++) {
      printf("%d\t", graph[i][j]);
    }
   printf("\n");
   }
}
void dijkstra(int source, int dest) {
 int dist[MAX_NODES], visited[MAX_NODES], prev[MAX_NODES];
 int i, j, min_dist, next_node;
 for (i = 0; i < nodes; i++) {
 dist[i] = INF;
 visited[i] = 0;
 prev[i] = -1;
 }
 dist[source] = 0;
 visited[source] = 1;
 for (i = 0; i < nodes; i++) {
 if (i != source) {
 dist[i] = graph[source][i];
 }
 }
 for (i = 0; i < nodes - 1; i++) {
 min_dist = INF;
 for (j = 0; j < nodes; j++) {
 if (!visited[j] && dist[j] < min_dist) {
 min_dist = dist[j];
 next_node = j;
 }
 }
 visited[next_node] = 1;
 for (j = 0; j < nodes; j++) {
 if (!visited[j]) {
 if (min_dist + graph[next_node][j] < dist[j]) {
 dist[j] = min_dist + graph[next_node][j];
 prev[j] = next_node;
 }
 }
 }
 }
 if (dist[dest] == INF) {
 printf("No path found\n");
 } else {
 printf("Path found: ");
 int path[MAX_NODES], count = 0;
 j = dest;
 while (j != -1) {
 path[count] = j;
 count++;
 j = prev[j];
 }
 for (i = count - 1; i >= 0; i--) {
 printf("%d ", path[i]);
 if (i != 0) {
 printf("-> ");
 }
 }
 printf("\n");
 }
}
int main() {
 int i, j, u, v, w, source, dest;
 printf("Enter the number of nodes: ");
 scanf("%d", &nodes);
 initialize_graph();
 printf("Enter the number of edges: ");
 int edges;
 scanf("%d", &edges);
 printf("Enter the edges and weights:\n");
 for (i = 0; i < edges; i++) {
 scanf("%d %d %d", &u, &v, &w);
 add_edge(u, v, w);
 }
 print_graph();
 printf("Enter the source: ");
 scanf("%d", &source);
 printf("Enter the destination: ");
 scanf("%d", &dest);
 dijkstra(source, dest);
 return 0;
}
