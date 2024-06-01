#include "graph.h"
#include<iostream>

unordered_set<int> Graph::add_edge(int x, int y, int id){
	m++;
	unordered_set<int> ret;
	ret.insert(x);
	ret.insert(y);
	unordered_set<int>::iterator it;
	for(it = neighbor[x].begin(); it != neighbor[x].end(); it++){
		int z = *it;
		if(query(_hash(y, z)) > 0){
			density[z] += 1.0/(neighbor[z].size()+1.0);
			ret.insert(z);
		}
	}
	density[x] *= neighbor[x].size()+1;
	density[y] *= neighbor[y].size()+1;
	if(query(_hash(x, y)) == 0){
		for(it = neighbor[x].begin(); it != neighbor[x].end(); it++){
			int z = *it;
			if(query(_hash(y, z)) > 0){
				density[x] += query(_hash(y, z));
				density[y] += query(_hash(x, z));
			}
		}
		neighbor[x].insert(y);
		neighbor[y].insert(x);
	}
	density[x] = (density[x]+1.0)/(neighbor[x].size()+1.0);
	density[y] = (density[y]+1.0)/(neighbor[y].size()+1.0);
	ins(_hash(x, y), 1);
	return ret;
}

unordered_set<int> Graph::delete_edge(int x,int y, int id){
	m--;
	unordered_set<int> ret;
	ret.insert(x);
	ret.insert(y);
	unordered_set<int>::iterator it;
	for(it = neighbor[x].begin(); it != neighbor[x].end(); it++){
		int z = *it;
		if(query(_hash(y, z)) > 0){
			density[z] -= 1.0/(neighbor[z].size()+1.0);
			ret.insert(z);
		}
	}
	density[x] *= neighbor[x].size()+1;
	density[y] *= neighbor[y].size()+1;
	if(query(_hash(x, y)) == 1){
		for(it = neighbor[x].begin(); it != neighbor[x].end(); it++){
			int z = *it;
			if(query(_hash(y, z)) > 0){
				density[x] -= query(_hash(y, z));
				density[y] -= query(_hash(x, z));
			}
		}
		neighbor[x].erase(y);
		neighbor[y].erase(x);
	}
	density[x] = (density[x]-1.0)/(neighbor[x].size()+1.0);
	density[y] = (density[y]-1.0)/(neighbor[y].size()+1.0);
	ins(_hash(x, y), -1);
	return ret;
}
