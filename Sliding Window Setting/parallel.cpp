#include "graph.h"
#include<iostream>

unordered_map<int, pair<int, int> > Graph::add_edge(int x, int y){
	unordered_map<int, pair<int, int> > ret;
	#pragma omp atomic
	m++;
	unordered_set<int>::iterator it;
	for(it = neighbor[x].begin(); it != neighbor[x].end(); it++){
		int z = *it;
		if(query(_hash(y, z)) > 0){
			ret[z] = make_pair(0, 1);
		}
	}
	int retx = 1, rety = 1;
	if(query(_hash(x, y)) == 0){
		for(it = neighbor[x].begin(); it != neighbor[x].end(); it++){
			int z = *it;
			if(query(_hash(y, z)) > 0){
				retx += query(_hash(y, z));
				rety += query(_hash(x, z));
			}
		}
		#pragma omp critical (neighbor_change)
		{
		neighbor[x].insert(y);
		neighbor[y].insert(x);
		}
		ret[x] = make_pair(1, retx), ret[y] = make_pair(1, rety);
	}
	else{
		ret[x] = make_pair(0, retx), ret[y] = make_pair(0, rety);
	}
	#pragma omp critical (edge_count)
	{
	ins(_hash(x, y), 1);
	}
	return ret;
}

unordered_map<int, pair<int, int> > Graph::delete_edge(int x,int y){
	unordered_map<int, pair<int, int> > ret;
	#pragma omp atomic
	m--;
	unordered_set<int>::iterator it;
	for(it = neighbor[x].begin(); it != neighbor[x].end(); it++){
		int z = *it;
		if(query(_hash(y, z)) > 0){
			ret[z] = make_pair(0, -1);
		}
	}
	int retx = -1, rety = -1;
	if(query(_hash(x, y)) == 1){
		for(it = neighbor[x].begin(); it != neighbor[x].end(); it++){
			int z = *it;
			if(query(_hash(y, z)) > 0){
				retx -= query(_hash(y, z));
				rety -= query(_hash(x, z));
			}
		}
		#pragma omp critical (neighbor_change)
		{
		neighbor[x].erase(y);
		neighbor[y].erase(x);
		}
		ret[x] = make_pair(-1, retx), ret[y] = make_pair(-1, rety);
	}
	else{
		ret[x] = make_pair(0, retx), ret[y] = make_pair(0, rety);
	}
	#pragma omp critical (edge_count)
	{
	ins(_hash(x, y), -1);
	}
	return ret;
}
