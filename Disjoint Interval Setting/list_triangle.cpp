#include "graph.h"

void Graph::calculate(int x){
	lower[x] = 0;
	for(int i = 0; i < neighbor[x].size(); i++){
		int y = neighbor[x][i];
		lower[x] += edge_count[_hash(x, y)];
		for(int j = 0; j < directed_neighbor[y].size(); j++){
			int z = directed_neighbor[y][j];
			if(z == x)continue;
			if(edge_count[_hash(x, z)] > 0){
				lower[x] += edge_count[_hash(y, z)];
			}
		}
	}
	lower[x] /= neighbor[x].size()+1.0;
	upper[x] = lower[x];
}
