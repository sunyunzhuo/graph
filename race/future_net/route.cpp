#include "route.h"
#include "lib_record.h"
#include <stdio.h>
#include "graph.h"

void dealCSV(int *s, int *t, int *vmustNumn, graph_t *graph, char *topo[5000], int edge_num, char *demand);

void search(graph_t *graph, int s, int t, int vmustNum)
{
		

}

void spliteString(int edgeInfo[], char *topo, const char * delim)//字符串的分解：topo是目标字符串，用delim分解，分解后转化为整形存入edgeInfo数组中。
{
	int i = 0;
	char *token = strtok( topo, delim);

   	while( token != NULL){
        edgeInfo[i++] = atoi(token);
		token = strtok( NULL, delim);
	}
}

//你要完成的功能总入口
void search_route(char *topo[5000], int edge_num, char *demand)
{
	/*
    unsigned short result[] = {2, 6, 3};//示例中的一个解

    for (int i = 0; i < 3; i++)
        record_result(result[i]);
	*/
    int s = 0, t = 0, vmustNum = 0;//s:起始点，t:终点，vmustNum:V'中的顶点数
    graph_t *graph = graph_init(50, edge_num);//初始化图
	
	dealCSV(&s, &t, &vmustNum, graph, topo, edge_num, demand);
    search(graph, s, t, vmustNum);
	graph_destroy(graph);
}

void dealCSV(int *s, int *t, int *vmustNum, graph_t *graph, char *topo[5000], int edge_num, char *demand)
{
	//处理demand并解析顶点信息
	int vmust[50] = {-1};//存储V'中顶点的索引
	int edgeInfo[4] = {0};//存储拆解后边的信息
	int i = 0;

	char *token = strtok(demand, ",");// 2,3,2|3|4|7
	*s = atoi(token);//获取起始点索引，atoi()将字符串转化为整数
	token = strtok(NULL, ",");
	*t = atoi(token);//获取终点索引
	token = strtok(NULL, ",");//分离出必经点的字符串如：2|3|5|12
	spliteString(vmust, token, "|");//调用字符串分割函数，用"|"对其进行分割，并转化为整数存放在vmust[]数组中
/*	
	printf("S(%3d)-->T(%3d):", s, t);
	for(i = 0; i < 50; i++){
		printf("%3d ", vpath[i]);
	}
	printf("demand处理完毕\n");
*/	
    //处理topo并添加边的信息
	for (i = 0;i < edge_num; i++){//逐条处理边信息字符串
		if(i < 50 && vmust[i] > -1){//借用这个循环，将必经的顶点结构体中相应标志位置一
			(graph->relation + vmust[i])->vmust = 1;
			(*vmustNum)++;//统计V'中顶点的具体数目
		}
    	memset(edgeInfo, 0 ,4);//情况防止上一次数据的干扰
    	spliteString(edgeInfo, topo[i], ",");//用","分解边信息字符串如：0,0,1,7.将其拆分后转化为整形并存入edgeInfo[]数组中
		if(edgeInfo[2] == *s || edgeInfo[1] == *t) continue;//起点的入度和终点的出度都不再往图里添加
		graph_add_adge(graph, edgeInfo);//将分离出的topo中的边的信息添加到图中
    }
	printf("all the edges deal finish!\n");

	graph_show(graph);
}
