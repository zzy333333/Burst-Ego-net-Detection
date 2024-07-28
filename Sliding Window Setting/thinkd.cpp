#include "graph.h"
#include<iostream>

double P(int e, int nb, int ng, int K){
	int y = min(K, e+nb+ng);
	return (1.0*y)/(1.0*(e+nb+ng))*(y-1.0)/(e+nb+ng-1.0);
}

double rand01(int N){
	return (rand()*rand()%(N+1)*1.0)/(1.0*N);
}

bool Bernoulli(double p){
	return rand01(1e9)<p;
}

unordered_set<int> Graph::add_edge(int x, int y, int id){
	m++;
	unordered_set<int> ret;
	ret.insert(x);
	ret.insert(y);
	unordered_set<int>::iterator it;
	for(it = neighbor[x].begin(); it != neighbor[x].end(); it++){
		int z = *it;
		if(query(_hash(y, z)) > 0){
			density[z] += 1.0/P(sample_edge.size(), nb, ng, K)/(neighbor[z].size()+1.0);
			ret.insert(z);
		}
	}
	density[x] *= neighbor[x].size()+1;
	density[y] *= neighbor[y].size()+1;
	if(query(_hash(x, y)) == 0){
		for(it = neighbor[x].begin(); it != neighbor[x].end(); it++){
			int z = *it;
			if(query(_hash(y, z)) > 0){
				density[x] += query(_hash(y, z))/P(sample_edge.size(), nb, ng, K);
				density[y] += query(_hash(x, z))/P(sample_edge.size(), nb, ng, K);
			}
		}
	}
	if(nb+ng == 0){
		if(sample_edge.size() < K){
			sample_edge[id] = make_pair(x, y);
		}
		else if(Bernoulli(1.0*K/(1.0*m))){
			int rid = sample_edge.begin()->first;
			int rx = sample_edge[rid].first;
			int ry = sample_edge[rid].second;
			if(query(_hash(rx, ry)) == 1){
				neighbor[rx].erase(ry);
				neighbor[ry].erase(rx);
			}
			ins(_hash(rx, ry), -1);
			sample_edge.erase(sample_edge.begin());
			sample_edge[id] = make_pair(x, y);
		}
		if(query(_hash(x, y)) == 0){
			neighbor[x].insert(y);
			neighbor[y].insert(x);
		}
		ins(_hash(x, y), 1);
	}
	else if(Bernoulli(1.0*nb/(1.0*(nb+ng)))){
		sample_edge[id] = make_pair(x, y);
		if(query(_hash(x, y)) == 0){
			neighbor[x].insert(y);
			neighbor[y].insert(x);
		}
		ins(_hash(x, y), 1);
		nb -= 1;
	}
	else{
		ng -= 1;
	}
	density[x] = (density[x]+1.0)/(neighbor[x].size()+1.0);
	density[y] = (density[y]+1.0)/(neighbor[y].size()+1.0);
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
			density[z] -= 1.0/P(sample_edge.size(), nb, ng, K)/(neighbor[z].size()+1.0);
			ret.insert(z);
		}
	}
	density[x] *= neighbor[x].size()+1;
	density[y] *= neighbor[y].size()+1;
	if(query(_hash(x, y)) == 1){
		for(it = neighbor[x].begin(); it != neighbor[x].end(); it++){
			int z = *it;
			if(query(_hash(y, z)) > 0){
				density[x] -= query(_hash(y, z))/P(sample_edge.size(), nb, ng, K);
				density[y] -= query(_hash(x, z))/P(sample_edge.size(), nb, ng, K);
			}
		}
	}
	if(sample_edge[id].first){
		if(query(_hash(x, y)) == 1){
			neighbor[x].erase(y);
			neighbor[y].erase(x);
		}
		ins(_hash(x, y), -1);
		nb += 1;
	}
	else{
		ng += 1;
	}
	density[x] = (density[x]-1.0)/(neighbor[x].size()+1.0);
	density[y] = (density[y]-1.0)/(neighbor[y].size()+1.0);
	return ret;
}
