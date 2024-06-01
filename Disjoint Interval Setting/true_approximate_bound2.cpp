#include "graph.h"
#include<cmath>
#include<algorithm>

const double EPS = 1e-6;

void Graph::approximate(int x){
	lower[x] = upper[x] = 0;
	if(neighbor[x].size() == 0)return;
	double c = 0.03;
	int cnt_sample = 30;
	int total = 0;
	for(int i = 0; i < neighbor[x].size(); i++){
		int y = neighbor[x][i];
		total += directed_edge[y].size();
		if(neighbor[x].size() < neighbor[y].size() || (neighbor[x].size() == neighbor[y].size() && x < y))lower[x] += edge_count[_hash(x, y)];
	}
	upper[x] = lower[x];
	double p = 0;
	int sample[150];
	for(int i = 1; i <= cnt_sample; i++){
		sample[i] = rand()%(total+1)-1;
	}
	sort(sample+1, sample+cnt_sample+1);
	int sum = 0, now = 0;
	for(int i = 1; i <= cnt_sample; i++){
		if(sample[i] == -1)continue;
		int y = neighbor[x][now];
		while(sum+directed_edge[y].size() <= sample[i]){
			sum += directed_edge[y].size();
			now++;
			y = neighbor[x][now];
		}
		int z = directed_edge[y][sample[i]-sum];
		if(z == x || edge_count[_hash(x, z)] > 0)p++;
	}
	p = p/cnt_sample;
	lower[x] = (lower[x] + max(0.0, p-c)*total)/(neighbor[x].size()+1.0);
	upper[x] = (upper[x] + min(1.0, p+c)*total)/(neighbor[x].size()+1.0);
}