#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _graph_node_ {
	int nodeIndex;
	int weight;
	int edgeIndex;
	int outNumbers;
	int vmust;
	struct _graph_node_ *next;
}gnode_t;

typedef struct _adjlist_graph_ {
	gnode_t *relation;
	int vn;
	int edgeNumbers;
	char *visit;
}graph_t;

gnode_t *create_gnode(int nodeIndex, int edgeIndex, int weight);
graph_t *graph_init(int vn, int edgeNumbers);
int graph_destroy(graph_t *graph);
int graph_add_adge(graph_t *graph, int edgeInfo[4]);
int graph_show(graph_t *graph);
gnode_t *graph_first_adj(graph_t *graph, int vn);
gnode_t *graph_next_adj(graph_t *graph, int vx, int vy);
int graph_dfs(graph_t *graph, int start);
