#include "route.h"
#include "lib_record.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <iostream>
#include <string.h>

// 边的结构体
typedef struct edge{
	int id; // 该条边的编号
	int st;	// 弧尾
	int ed; // 弧头
	int wt; // 权重
	struct edge *next;
}Edge_T;


// 顶点结构体
typedef struct vertex{
	int id;
	int out_degree;   // 该顶点的出度
	Edge_T *e_list;   // 以该顶点为起点的所有边的集合链表
	int search_flag;  // 遍历标记
	int special_flag; // 特殊点标记
	struct vertex *next;
}Vertex_T;

#define MAX_ROUTE 0X7FFFFFFF
#define UNIT_NUM  10
#define MAX_GEN   10

// 个体单元---即一条路径，记录该路径上的所有顶点信息，以及该路径的信息
typedef struct unit_t{
	Vertex_T *vList; // 路径上的所有顶点
	int special_num; // 路径上包含的特殊点个数
	int length;      // 路径上的权重和
}Unit_T;


// 种群-------多个个体（路径）的集合
Unit_T group[UNIT_NUM];

// 最优个体，指向group中的一个
Unit_T *best_one=NULL;


// 图的存储结构:顶点的邻接表
Vertex_T v_list[600];

// 所求路径的源点和终点
int path_source=-1;
int path_target=-1;
int special_total=-1;




inline int GetRandNum(int from, int to)
{
	struct timeval tm;
	gettimeofday(&tm,0);
	srand(tm.tv_usec);
	return (int)(rand()%(to-from+1)+from);
}

// 随机深度优先遍历，产生一条从指定源点到目标点的路径,存储到path中
void RandDeepSearch(int source_id, int target_id, Unit_T *path)
{
	
}

// 种群初始化：随机产生多条从s->t的路径
void group_init()
{
	for(int i=0;i<UNIT_NUM;i++){
		group[i].vList = NULL;
		group[i].special_num = 0;
		
		RandDeepSearch(path_source, path_target,&group[i]);
	}
}


inline void ReadDemand(char *demand)
{
	sscanf(demand,"%d,%d,",&path_source, &path_target);
	char *infile = strrchr(demand,',')+1;
	char tmp[5]=" ";

	while( *infile!='\0' ){
		
		sscanf(infile,"%[^|]",tmp);// 读一串字符直到遇到 '|' 为止

		v_list[ atoi(tmp) ].special_flag = 1; // 标记特殊点
		
		infile+=strlen(tmp)+1;
		memset(tmp,'\0',5);
	}

	v_list[path_source].special_flag = -1; // 源点的特殊点标记
	v_list[path_target].special_flag = 1;  // 目标点的特殊点标记
}


void map_init(char *topo[5000], int edge_num, char *demand)
{
	for(int i=0;i<600;i++)
	{
		v_list[i].id = -1;
		v_list[i].out_degree = 0;
		v_list[i].e_list = NULL;
		v_list[i].search_flag = -1;
		v_list[i].special_flag = -1;
		v_list[i].next = NULL;
	}
	
	ReadDemand(demand);

	// 构建邻接表
	for(int i=0;i<edge_num;i++)
	{
		int e_id,v_st,v_ed,e_w;
		sscanf(topo[i], "%d,%d,%d,%d",&e_id,&v_st,&v_ed,&e_w);

		Edge_T *new_edge = (Edge_T*)malloc(sizeof(Edge_T));
		new_edge->id = e_id;
		new_edge->st = v_st;
		new_edge->ed = v_ed;
		new_edge->wt = e_w;
		new_edge->next = NULL;

		if(NULL==v_list[v_st].e_list){
			v_list[v_st].id = v_st;
			v_list[v_st].e_list = new_edge; 		
			v_list[v_st].out_degree = 1;
		}
		else{
			new_edge->next = v_list[v_st].e_list;
			v_list[v_st].e_list = new_edge;
			v_list[v_st].out_degree += 1;			
		}
	}
}


void search_route(char *topo[5000], int edge_num, char *demand)
{
	map_init(topo, edge_num, demand);

	group_init();// 种群初始化


	for(int i=0;i<edge_num;i++)
		std::cout<<topo[i];

	std::cout<<"\ntest-------------------------------\n";

	std::cout<<"source: "<<path_source<<std::endl;
	std::cout<<"target: "<<path_target<<std::endl;

	for(int i=0;i<600;i++)
		if( v_list[i].id>=0){
			std::cout<<"vertex: "<<i<<"-----------";
			if(v_list[i].special_flag==1)
				std::cout<<"   "<<"is special";
			std::cout<<std::endl;

			Edge_T *e = v_list[i].e_list;
			while(e){
				std::cout<<e->id<<"  "<<e->st<<" "<<e->ed<<" "<<e->wt<<std::endl;
				e = e->next;
			}
		}
}











































