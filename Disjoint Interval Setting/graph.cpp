#include "graph.h"

using namespace std;

long long _hash(int A, int B){
	if(A > B)swap(A, B);
	return 1000000000ll*A+B;
}

Graph::Graph(int _n){
	n = _n;
	m = 0;
	neighbor.resize(n+5);
	directed_neighbor.resize(n+5);
	edge.resize(n+5);
	directed_edge.resize(n+5);
	lower.resize(n+5);
	upper.resize(n+5);
}

Graph::~Graph(){
	n = 0;
	m = 0;
	neighbor.clear();
	directed_neighbor.clear();
	edge.clear();
	directed_edge.clear();
	lower.clear();
	upper.clear();
}

void Graph::add_edge(int x, int y){
	m++;
	if(edge_count[_hash(x, y)] == 0){
		neighbor[x].push_back(y);
		neighbor[y].push_back(x);
	}
	edge[x].push_back(y);
	edge[y].push_back(x);
	edge_count[_hash(x, y)]++;
}

void Graph::rebuild(){
	for(int x = 1; x <= n; x++){
		for(int i = 0; i < neighbor[x].size(); i++){
			int y = neighbor[x][i];
			if(neighbor[x].size() > neighbor[y].size())continue;
			if(neighbor[x].size() == neighbor[y].size() && x > y)continue;
			directed_neighbor[x].push_back(y);
		}
	}
	for(int x = 1; x <= n; x++){
		for(int i = 0; i < edge[x].size(); i++){
			int y = edge[x][i];
			if(neighbor[x].size() > neighbor[y].size())continue;
			if(neighbor[x].size() == neighbor[y].size() && x > y)continue;
			directed_edge[x].push_back(y);
		}
	}
}

/*int main(){
	freopen("Dataset1.txt","r",stdin);
	int n = 10000;
	Graph *g = new Graph(n);
	char s1[1000],s2[1000];
	while(scanf("%s%s",s1,s2)!=EOF){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		if(a==b)continue;
		g->add_edge(a, b);
	}
	delete g;
	g = new Graph(n); 
	printf("!!!\n");
	return 0;
}*/
