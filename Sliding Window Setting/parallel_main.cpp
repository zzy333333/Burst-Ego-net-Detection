#include"graph.h"
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#include<vector>
#include<queue>
#include<unordered_map>
#include<omp.h>

const double eps = 1e-9; 

int n = 0, m = 0, k = 10, T = 1000000;

struct Operation{
	bool flag;
	bool now;
	int u;
	int v;
	int t;
	int vis;
	int sign;
	Operation* next;
	Operation* next2;
	Operation(){
		flag = now = u = v = t = vis = sign = 0;
		next = next2 = NULL;
	}
};

int predeg[1000010], nowdeg[1000010], preedge[1000010], nowedge[1000010], burst[1000010];

queue<pair<pair<int, int>, pair<int, int> > >qnow, qpre;// u v t id

queue<Operation>tmp;// match operation to t

queue<Operation*>operation;

Operation* preop[1000010];// each vertex has some operations

unordered_map<int, int>cnt, nxt;

unordered_map<int, vector<pair<int, pair<int, int> > > >match;//time t, changed vertices, type and changed value

Graph *pre, *now;

void query(Operation op);

void update(){
    //critical
	// cerr<<"#"<<endl;
	//cout<<"#"<<endl;
	Operation op;
	bool flag = 0;
	#pragma omp critical
	{
	if(operation.empty()){
		flag = 1;
	}
	else{
		op = *operation.front();
		// Operation* OP = operation.front();
		operation.pop();
		// delete OP;
	}
    //take update from queue
	// cerr<<"#"<<endl;
	//cout<<"###"<<endl;
	}
	if(flag)return;
    //parallel
	if(!op.flag){
		query(op);
		fflush(stdout);
		return;
	}
    //know the changed vertices
	unordered_map<int, pair<int, int> > ret;
	//cout<<"?"<<endl;
	if(op.now){
		if(op.sign == 1){
			ret = now->add_edge(op.u, op.v);
			// cerr<<"!!!!"<<endl;
		}
		else{
			// cerr<<"del"<<endl;
			ret = now->delete_edge(op.u, op.v);
			// cerr<<"deldel"<<endl;
		}
		#pragma omp critical (match)
		{
		match[op.t].push_back(make_pair(op.u, make_pair(3, ret[op.u].first)));
		match[op.t].push_back(make_pair(op.v, make_pair(3, ret[op.v].first)));
		for(auto pir: ret){
			int x = pir.first, y = pir.second.second;
			match[op.t].push_back(make_pair(x, make_pair(4, y)));
		}
		}
	}
	else{
		if(op.sign == 1){
			// cerr<<"?"<<endl;
			ret = pre->add_edge(op.u, op.v);
			// cerr<<"???"<<endl;
		}
		else{
			// cerr<<"delp"<<endl;
			ret = pre->delete_edge(op.u, op.v);
			// cerr<<"delpre"<<endl;
		}
		#pragma omp critical (match)
		{
		match[op.t].push_back(make_pair(op.u, make_pair(1, ret[op.u].first)));
		match[op.t].push_back(make_pair(op.v, make_pair(1, ret[op.v].first)));
		for(auto pir: ret){
			int x = pir.first, y = pir.second.second;
			match[op.t].push_back(make_pair(x, make_pair(2, y)));
		}
		}
	}
	ret.clear();
    //add change information to vector
	//cout<<"???"<<endl;
	#pragma omp critical
	{
    //add new update to queue
	if(op.next != NULL){
		op.next->vis--;
		if(op.next->vis == 0)operation.push(op.next);
	}
	if(op.next2 != NULL){
		op.next2->vis--;
		if(op.next2->vis == 0)operation.push(op.next2);
	}
	cnt[op.t]--;
	if(cnt[op.t] == 0){
		Operation* opt = new Operation();
		opt->flag = 0;
		opt->t = op.t;
		operation.push(opt);
	}
	}
	//cout<<"??????"<<endl;
	// update();
}

void query(Operation op){
	#pragma omp critical (answer)
	{
    //know the changed vertices from previous query and this query
	int t = op.t;
	unordered_set<int> changed;
	for(auto val: match[t]){
		int x = val.first, y = val.second.first, z = val.second.second;
		changed.insert(x);
		if(y == 1){
			predeg[x] += z;
		}
		else if(y == 2){
			preedge[x] += z;
		}
		else if(y == 3){
			nowdeg[x] += z;
		}
		else{
			nowedge[x] += z;
		}
	}
	match[t].clear();
    //print change
	for(auto x: changed){
			if(nowedge[x]/(nowdeg[x]+1.0)+eps >= 1.0*k*preedge[x]/(predeg[x]+1.0) && nowedge[x]/(nowdeg[x]+1.0)+eps >= k){
			if(!burst[x]){
				burst[x] = 1;
				printf("%d %d burst\n", t, x);
			}
		}
		else{
			if(burst[x]){
				burst[x] = 0;
				printf("%d %d unburst\n", t, x);
			}
		}
	}
	changed.clear();
	#pragma omp critical
	{
	cnt[nxt[t]]--;
	if(cnt[nxt[t]] == 0){
		Operation *opt = new Operation();
		opt->flag = 0;
		opt->t = nxt[t];
		operation.push(opt);
	}
	}
	}
}

int main(){
	srand(time(0));
	scanf("%d%d", &n, &m);
	pre = new Graph(n);
	now = new Graph(n);
	int pretime = -1;
	for(int i = 1; i <= m; i++){
		int u, v, t;
		scanf("%d%d%d", &u, &v, &t);
		if(!qnow.empty() && t - qnow.front().second.first > T){
			//deal with burst
//			printf("%.3lf\n", now->density[445]);
			cnt[t] = tmp.size();
			while(!tmp.empty()){
				Operation *op = new Operation();
				*op = tmp.front();
				tmp.pop();
				op->t = t;
				if(preop[op->u] == NULL && preop[op->v] == NULL)operation.push(op);
				op->vis = 0;
				if(preop[op->u] != NULL){
					if(preop[op->u]->next == NULL)preop[op->u]->next = op;
					else preop[op->u]->next2 = op;
					op->vis++;
				}
				if(preop[op->v] != NULL){
					if(preop[op->v]->next == NULL)preop[op->v]->next = op;
					else preop[op->v]->next2 = op;
					op->vis++;
				}
				preop[op->u] = op;
				preop[op->v] = op;
			}
			if(pretime != -1){
				nxt[pretime] = t;
				cnt[t]++;
			}
			pretime = t;
			//delete old edge
			int tpre = 0;
			while(!qnow.empty() && t - qnow.front().second.first > T){
				tpre = qnow.front().second.first;
				int x = qnow.front().first.first, y = qnow.front().first.second, id = qnow.front().second.second;
				qnow.pop();
				Operation op;
				op.flag = 1;
				op.now = 1;
				op.sign = -1;
				op.u = x;
				op.v = y;
				tmp.push(op);
				// add for pre
				op.flag = 1;
				op.now = 0;
				op.sign = 1;
				op.u = x;
				op.v = y;
				tmp.push(op);
				qpre.push(make_pair(make_pair(x, y), make_pair(tpre, id)));
			}
			//(maybe)delete for pre
			while(!qpre.empty() && tpre - qpre.front().second.first > T){
				int x = qpre.front().first.first, y = qpre.front().first.second, id = qpre.front().second.second;
				qpre.pop();
				Operation op;
				op.flag = 1;
				op.now = 0;
				op.sign = -1;
				op.u = x;
				op.v = y;
				tmp.push(op);
			}
		}
		//add new edge
		Operation op;
		op.flag = 1;
		op.now = 1;
		op.sign = 1;
		op.u = u;
		op.v = v;
		tmp.push(op);
		qnow.push(make_pair(make_pair(u, v), make_pair(t, i)));
	}
	#pragma omp parallel for
	for(int i = 1; i <= 1000000000; i++){
		update();
	}
	return 0;
}
