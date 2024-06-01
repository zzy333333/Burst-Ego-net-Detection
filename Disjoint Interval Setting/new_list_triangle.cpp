#include "graph.h"

void Graph::calculate(int x){
    for(int i = 0; i < neighbor[x].size(); i++){
        int y = neighbor[x][i];
        lower[x] += edge_count[_hash(x, y)];
    }
	for(int i = 0; i < directed_neighbor[x].size(); i++){
		int y = directed_neighbor[x][i];
		for(int j = 0; j < directed_neighbor[y].size(); j++){
			int z = directed_neighbor[y][j];
			if(edge_count[_hash(x, z)] == 0)continue;
            lower[x] += edge_count[_hash(y, z)];
            lower[y] += edge_count[_hash(x, z)];
            lower[z] += edge_count[_hash(x, y)];
		}
	}
}

void Graph::divide(int x){
    lower[x] /= neighbor[x].size()+1;
    upper[x] = lower[x];
}
