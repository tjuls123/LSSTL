#pragma once

#include <vector>
#include <iostream>
using std::vector;
using std::cout;
using std::endl;

const unsigned int INF = 0xFFFFFFFF;

//////////////////////////////////////////////////////////////////////////
// 邻接表
// 边表结构
typedef struct _EdgeNode
{
	int weight;  // 边的权重
	int vertex_index; // 顶点在数组中的索引索引
	_EdgeNode* next;
	_EdgeNode(int in_vertex_index, int in_weight) : weight(in_weight), vertex_index(in_vertex_index), next(nullptr) {}
}EdgeNode;

typedef struct _VertexNode
{
	int data; // 顶点数据
	EdgeNode* first_edge; // 第一条边的指针

	_VertexNode(int in_data) : data(in_data), first_edge(nullptr){}
}VertexNode;

class Graph
{
public:
	Graph() : vertex_number(0), edge_number(0) {}
	~Graph()
	{
	}

	void create_graph(int vertex_num, int edge_num, const vector<vector<unsigned int>>& edge_matrix)
	{
		vertex_number = vertex_num;
		edge_number = edge_num;

		vertex.reserve(vertex_number);
		for (int i = 0; i < vertex_number; ++i)
		{
			vertex.push_back(VertexNode(i));
		}
		for (int x = 0; x < edge_matrix.size(); ++x)
		{
			for (int y = 0; y < edge_matrix[x].size(); ++y)
			{
				if (x != y)
				{
					if (edge_matrix[x][y] != INF)
					{
						EdgeNode* new_edge = get_edge_node(y, edge_matrix[x][y]);
						new_edge->next = vertex[x].first_edge;
						vertex[x].first_edge = new_edge->next;
					}
				}
			}
		}
	}

private:
	EdgeNode* get_edge_node(int vertex_index, int weight)
	{
		return new EdgeNode(vertex_index, weight);
	}
private:
	int vertex_number;
	int edge_number;
	vector<VertexNode> vertex;
};


vector<vector<unsigned int>> get_graph_matrix()
{
	vector<vector<unsigned int>> matrix(6, vector<unsigned int>(6, INF));
	matrix[0][1] = 6; matrix[0][2] = 1; matrix[0][3] = 5;
	matrix[1][0] = 6; matrix[1][2] = 5; matrix[1][4] = 3;
	matrix[2][0] = 1; matrix[2][1] = 5; matrix[2][3] = 5; matrix[2][4] = 6; matrix[2][5] = 4;
	matrix[3][0] = 5; matrix[3][2] = 5; matrix[3][5] = 2;
	matrix[4][1] = 3; matrix[4][2] = 6; matrix[4][5] = 6;
	matrix[5][2] = 4; matrix[5][3] = 2; matrix[5][4] = 6;

	return matrix;
}
//////////////////////////////////////////////////////////////////////////
// prim算法
typedef struct Node
{
	unsigned int data;
	unsigned int lowest_cost;
}Node;


int minimum(const vector<Node>& close_edge)
{
	unsigned int min = INF;
	int index = -1;
	for (int i = 0; i < close_edge.size(); ++i)
	{
		if (close_edge[i].lowest_cost < min && close_edge[i].lowest_cost > 0)
		{
			min = close_edge[i].lowest_cost;
			index = i;
		}
	}
	return index;
}
int mst_prim(const vector<vector<unsigned int>>& adj_matrix, int src_index)
{
	int min_mst = 0;
	const int vertex_count = adj_matrix.size();
	vector<Node> close_edge(vertex_count);

	for (int i = 0; i < vertex_count; ++i)
	{
		close_edge[i].lowest_cost = INF;
	}

	// 标记src_index已经被访问
	close_edge[src_index].data = src_index;
	close_edge[src_index].lowest_cost = 0;

	for (int i = 0; i < vertex_count; ++i)
	{
		if (i != src_index)
		{
			close_edge[i].data = src_index;
			close_edge[i].lowest_cost = adj_matrix[src_index][i];
		}
	}
	for (int e = 1; e < vertex_count; ++e)
	{
		int k = minimum(close_edge);
		cout << close_edge[k].data << "->" << k << ": " << close_edge[k].lowest_cost << endl;
		min_mst += close_edge[k].lowest_cost;
		close_edge[k].lowest_cost = 0;
		for (int i = 0; i < vertex_count; ++i)
		{
			if (adj_matrix[k][i] < close_edge[i].lowest_cost)
			{
				close_edge[i].data = k;
				close_edge[i].lowest_cost = adj_matrix[k][i];
			}
		}
	}
	cout << "mst : " << min_mst << endl;
	return min_mst;
}


//////////////////////////////////////////////////////////////////////////
// kruska
typedef struct Arc
{
	int u;
	int v;
	unsigned int cost;

	Arc(int in_u, int in_v, unsigned int in_cost) : u(in_u), v(in_v), cost(in_cost) {}
}Arc;


void read_arc(const vector<vector<unsigned int>>& adj_matrix, vector<Arc>& arcs)
{
	for (int i = 0; i < adj_matrix.size(); ++i)
	{
		for (int j = i + 1; j < adj_matrix[i].size(); ++j)
		{
			if (adj_matrix[i][j] != INF)
			{
				arcs.push_back(Arc(i, j, adj_matrix[i][j]));
			}
		}
	}
}

struct Compare
{
	bool operator()(const Arc& a, const Arc& b)
	{
		return a.cost < b.cost;
	}
};


bool find_tree(int u, int v, vector<vector<int>>& tree)
{
	unsigned int index_u = INF;
	unsigned int index_v = INF;
	for (int i = 0; i < tree.size(); ++i)
	{
		if (find(tree[i].begin(), tree[i].end(), u) != tree[i].end())
			index_u = i;
		if (find(tree[i].begin(), tree[i].end(), v) != tree[i].end())
			index_v = i;
	}
	if (index_u != index_v)
	{
		for (int i = 0; i < tree[index_v].size(); ++i)
		{
			tree[index_u].push_back(tree[index_v][i]);
		}
		tree[index_v].clear();
		return true;
	}
	return false;
}

int mst_kruskal(const vector<vector<unsigned int>>& adj_matrix)
{
	const int vertex_count = adj_matrix.size();
	vector<Arc> arcs;
	read_arc(adj_matrix, arcs);
	sort(arcs.begin(), arcs.end(), Compare());
	vector<vector<int>> tree(vertex_count);
	for (int i = 0; i < vertex_count; ++i)
	{
		tree[i].push_back(i);
	}

	unsigned int mst = 0;
	for (int i = 0; i < arcs.size(); ++i)
	{
		int u = arcs[i].u;
		int v = arcs[i].v;
		if (find_tree(u, v, tree))
		{
			mst += arcs[i].cost;
			cout << u << "->" << v << ": " << arcs[i].cost << endl;
		}
	}
	cout << "mst: " << mst << endl;
	return mst;
}