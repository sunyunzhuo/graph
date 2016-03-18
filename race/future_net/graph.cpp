#include "graph.h"

graph_t *graph_init(int vn, int edgeNumbers)
{
	graph_t *graph = NULL;

	graph = (graph_t *)malloc(sizeof(*graph));
	graph->relation = (gnode_t *)malloc(sizeof(gnode_t) * vn);
	memset(graph->relation, 0, sizeof(gnode_t) * vn);
	graph->visit = (char *)malloc(sizeof(char) * vn);
	memset(graph->visit, 0, sizeof(char) *vn);
	graph->vn = vn;
	graph->edgeNumbers = edgeNumbers;
	return graph;
}

int graph_destroy(graph_t *graph)
{
	gnode_t *p = NULL;
	gnode_t *tmp = NULL;
	int i;

	for (i = 0; i < graph->vn; i++) {
		p = graph->relation[i].next;
		while (NULL != p) {
			tmp = p;
			p = p->next;
			free(tmp);
		}
	}
	free(graph->relation);
	free(graph->visit);
	free(graph);

	return 0;
}

int graph_add_adge(graph_t *graph, int edgeInfo[4])
{
	gnode_t *gnode = NULL;
	gnode_t *p = graph->relation + edgeInfo[1];
	p->outNumbers++;
	/* locate */
	while (NULL != p->next && p->next->weight < edgeInfo[3])
		p = p->next;

	if (NULL == p->next || p->next->weight >= edgeInfo[3]) {
		gnode = create_gnode(edgeInfo[2], edgeInfo[0], edgeInfo[3]);
		gnode->next = p->next;
		p->next = gnode;
	}

	return 0;
}
/*
int graph_add_adge(graph_t *graph, int vx, int vy)
{
	if (vx < 0 || vx >= graph->vn || vy < 0 || vy >= graph->vn)
		return -1;

	_graph_add_adge1_(graph, vx, vy);
	//_graph_add_adge1_(graph, vy, vx);

	return 0;
}
*/

int graph_show(graph_t *graph)
{
	gnode_t *p = NULL;
	int i;

	for (i = 0; i < graph->vn; i++) {
		p = graph->relation[i].next;

		printf("V%3d(%d):", i, graph->relation[i].outNumbers);
		while (NULL != p) {
			printf(" V%3d(%4d:%2d),", p->nodeIndex, p->edgeIndex, p->weight);
			p = p->next;
		}
		puts("\b ");
	}
	return 0;
}

gnode_t *create_gnode(int nodeIndex, int edgeIndex, int weight)
{
	gnode_t *p = NULL;

	p = (gnode_t *)malloc(sizeof(*p));
	p->nodeIndex = nodeIndex;
	p->weight = weight;
	p->edgeIndex = edgeIndex;	
	p->outNumbers = 0;
	p->next = NULL;

	return p;
}

gnode_t * graph_first_adj(graph_t *graph, int vn)
{
	gnode_t *p = graph->relation[vn].next;

	if (NULL == p)
		return NULL;

	return p;
}

gnode_t * graph_next_adj(graph_t *graph, int vx, int vy)
{
	gnode_t *p = graph->relation[vx].next;

	while (NULL != p && p->nodeIndex != vy)
		p = p->next;

	if (NULL == p || NULL == p->next)
		return NULL;

	return p;
}

int graph_dfs(graph_t *graph, gnode* start_gnode, int vpath[], int vpathIndex, int cost, int cvMNum, int vmustNum)
{
	gnode_t * gnode = NULL;

	if (graph->visit[start_gnode->nodeIndex])
		return 0;

	//printf(" V%d,", start);
	
	if(start_gnode->nodeIndex == t){
		if(cvMNum == vmustNum){
			printf("find one way!:");
			for(int i = 0; i < *vpathIndex; i++){
				printf("%d->",vpath[i]);
			}
			printf("\b\b  !\n");
		}
		return 0;
	}

	graph->visit[start_gnode->nodeIndex] = 1;
	if(graph->relation[start_gnode->nodeIndex].vmust){
		cvMNum++;
	}

	cost += start_gnode->weight;
	vpath[(vpathIndex++] = start_gnode->edgeIndex
	gnode = graph_first_adj(graph, start);

	while (gnode != NULL) {
		graph_dfs(graph, gnode, vpath, vpathIndex, cost, cvMNum, vmustNum);
		gnode = graph_next_adj(graph, start, gnode->nodeIndex);
	}

	return 0;
}
/*
int graph_bfs(graph_t *graph, int start)
{
	sequeue_t *queue = NULL;
	int vn;

	memset(graph->visit, 0, sizeof(*graph->visit) * graph->vn);

	queue = sequeue_init(5);
	sequeue_enque(queue, start);
	graph->visit[start] = 1;

	while (!sequeue_isempty(queue)) {
		sequeue_deque(queue, &start);
		printf(" V%d,", start);

		vn = graph_first_adj(graph, start);
		while (vn != -1) {
			if (!graph->visit[vn]) {
				sequeue_enque(queue, vn);
				graph->visit[vn] = 1;
			}
			vn = graph_next_adj(graph, start, vn);
		}
	}

	sequeue_destroy(queue);
	return 0;
}
*/
