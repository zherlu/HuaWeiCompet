#include "route.h"
#include "lib_record.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <iostream>

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
	int id;           // 顶点编号
	int out_degree;   // 该顶点的出度
	Edge_T *e_list;// 以该顶点为起点的所有边的集合链表
}Vertex_T;


// 图的存储结构:顶点的邻接表
Vertex_T v_list[600];


inline int GetRandNum(int from, int to)
{
	struct timeval tm;
	gettimeofday(&tm,0);
	srand(tm.tv_usec);
	return (int)(rand()%(to-from+1)+from);
}

void map_init(char *topo[5000], int edge_num)
{
	for(int i=0;i<600;i++)
	{
		v_list[i].id = -1;
		v_list[i].out_degree = 0;
		v_list[i].e_list = NULL;
	}

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
	map_init(topo, edge_num);

	for(int i=0;i<edge_num;i++)
		std::cout<<topo[i];

	std::cout<<"test\n";

	for(int i=0;i<600;i++)
		if( v_list[i].id>=0){
			std::cout<<"v_id: "<<i<<"\n";
			Edge_T *e = v_list[i].e_list;
			while(e){
				std::cout<<e->id<<"  "<<e->st<<" "<<e->ed<<" "<<e->wt<<std::endl;
				e = e->next;
			}
		}
}










































