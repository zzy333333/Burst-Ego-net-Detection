#include"graph.h"
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<algorithm>

const double eps = 1e-9;

int n = 0, m = 0, k = 10, T = 10000000;

int main(){
	srand(time(0));
	scanf("%d%d", &n, &m);
	int pretime = -1;
	Graph *pre = NULL;
	Graph *now = new Graph(n);
	int cnt = 0;
	for(int i = 1; i <= m; i++){
		int u, v, t;
		scanf("%d%d%d", &u, &v, &t);
		if(pretime == -1)pretime = t;
		//printf("%d %d\n", i, edge[i].t);
		if(t-pretime > T){
			pretime = t;
			//printf("??\n");
			now->rebuild();
			//printf("?\n");
			for(int x = 1; x <= n; x++){
				now->approximate(x);
//				double l = now->lower[x], r = now->upper[x];
//				now->calculate(x);
//				if(now->lower[x] < l)cerr<<"!"<<now->lower[x]<<" "<<r<<endl;
			}
//			printf("!%d\n", now->m);
			if(pre != NULL){
				cnt++;
				printf("#%d\n",cnt);
				int cnt_burst = 0;
				for(int x = 1; x <= n; x++){
					if(now->upper[x]+eps < k)continue;
					else if(now->lower[x]+eps >= k && now->lower[x]+eps >= pre->upper[x]*k){
						cnt_burst++;
						printf(" %d\n", x);
//						printf("%.3lf %.3lf\n", now->lower[x], now->upper[x]);
					}
                    else if(now->upper[x]+eps < pre->lower[x]*k)continue;
                    else{
                        if(pre->upper[x] - pre->lower[x] > eps)pre->calculate(x);
                        now->calculate(x);
                        if(now->lower[x]+eps >= k && now->lower[x]+eps >= pre->upper[x]*k){
                            cnt_burst++;
							// printf("%.3lf\n", now->upper[x]);
                            printf(" %d\n", x);
                        }
                    }
				}
//				printf("%d\n\n",cnt_burst);
				//printf("!");
				delete pre;
				//printf("!!");
				pre = NULL;
			}
			//printf("!!!\n");
			pre = now;
			//printf("?!\n");
			now = new Graph(n);
			//printf("!!!!\n");
		}
		now->add_edge(u, v);
	}
	return 0;
}
