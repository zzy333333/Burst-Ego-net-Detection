#include "graph.h"

using namespace std;

long long _hash(int A, int B){
	if(A > B)swap(A, B);
	return 1234567799ll*A+B;
}

long long __hash(int A, int B){
	return 1000000000ll*A+B;
}

Graph::Graph(int _n){
	n = _n;
	m = 0;
	K = 1e5;
	nb = 0;
	ng = 0;
	neighbor.resize(n+5);
	edge.resize(n+5);
	sample_neighbor.resize(n+5);
	density.resize(n+5);
	is_burst.resize(n+5);
	hs.resize(59999999);
	match.resize(59999999);
}

Graph::~Graph(){
	n = 0;
	m = 0;
	K = 0;
	nb = 0;
	ng = 0;
	neighbor.clear();
	edge.clear();
	sample_neighbor.clear();
	sample_edge.clear();
	density.clear();
	is_burst.clear();
	hs.clear();
	match.clear();
}

void Graph::ins(long long x, int val){
	int id = x%hs.size();
	while(match[id] != 0 && match[id] != x)id = (id+1)%hs.size();
	match[id] = x;
	hs[id] += val;
	if(hs[id] == 0 && match[(id+1)%hs.size()] == 0)match[id] = 0;
}

int Graph::query(long long x){
	int id = x%hs.size();
	while(match[id] != 0 && match[id] != x)id = (id+1)%hs.size();
	return hs[id];
}

/*void Graph::add_edge(int x, int y){
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
}*/

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
