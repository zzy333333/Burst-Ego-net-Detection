#include"graph.h"
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#include<queue>

const double eps = 1e-9; 

int n = 0, m = 0, k = 10, T = 10000000;

queue<pair<pair<int, int>, pair<int, int> > >qnow, qpre;// u v t id

int main(){
	freopen("input.in","r",stdin);
	freopen("ans.out","w",stdout);
	srand(time(0));
	scanf("%d%d", &n, &m);
	Graph *pre = new Graph(n);
	Graph *now = new Graph(n);
	unordered_set<int> changed;
	changed.clear();
	for(int i = 1; i <= m; i++){
		int u, v, t;
		scanf("%d%d%d", &u, &v, &t);
		if(!qnow.empty() && t - qnow.front().second.first > T){
			//deal with burst
//			printf("%.3lf\n", now->density[445]);
			for(auto z: changed){
				if(now->density[z]+eps >= pre->density[z]*k && now->density[z]+eps >= k){
					if(now->is_burst[z] == 0){
						now->is_burst[z] = 1;
						printf("%d %d burst\n", t, z);
					}
				}
				else{
					if(now->is_burst[z] == 1){
						now->is_burst[z] = 0;
						printf("%d %d unburst\n", t, z);
					}
				}
			}
			changed.clear();
			//delete old edge
			int tpre = 0;
			while(!qnow.empty() && t - qnow.front().second.first > T){
				tpre = qnow.front().second.first;
				int x = qnow.front().first.first, y = qnow.front().first.second, id = qnow.front().second.second;
				qnow.pop();
				unordered_set<int> tmp;
				tmp.clear();
				tmp = now->delete_edge(x, y, id);
				for(auto z: tmp){
					changed.insert(z);
				}
				tmp.clear();
				// add for pre
				tmp = pre->add_edge(x, y, id);
				for(auto z: tmp){
					changed.insert(z);
				}
				tmp.clear();
				qpre.push(make_pair(make_pair(x, y), make_pair(tpre, id)));
			}
			//(maybe)delete for pre
			while(!qpre.empty() && tpre - qpre.front().second.first > T){
				int x = qpre.front().first.first, y = qpre.front().first.second, id = qpre.front().second.second;
				qpre.pop();
				unordered_set<int> tmp;
				tmp.clear();
				tmp = pre->delete_edge(x, y, id);
				for(auto z: tmp){
					changed.insert(z);
				}
				tmp.clear();
			}
		}
		//add new edge
		unordered_set<int> tmp;
		tmp.clear();
		tmp = now->add_edge(u, v, i);
		for(auto z: tmp){
			changed.insert(z);
		}
		tmp.clear();
		qnow.push(make_pair(make_pair(u, v), make_pair(t, i)));
	}
	cerr<<"end"<<endl;
	return 0;
}
