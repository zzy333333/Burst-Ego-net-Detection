//temporal graph

#ifndef Temporal_Graph
#define Temporal_Graph

#include<vector>
#include<unordered_map>
#include<set>
#include<unordered_set>
//#include<ext/pb_ds/assoc_container.hpp>
//#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
//using namespace __gnu_pbds;

class Graph{
	private:
		int n, m;
		vector<unordered_set<int> >neighbor;//ignore repeated edge
		vector<unordered_multiset<int> >edge;
		vector<unordered_set<int> >sample_neighbor;
		vector<unordered_set<long long> >sample_edge;// vertex edge_id
		unordered_map<long long, int>edge_count;//number of repeated edge
		vector<int>hs;
		vector<long long>match;
	public:
		vector<double>density;
		vector<bool>is_burst;
		Graph(int _n);
		~Graph();
		void ins(long long x, int val);
		int query(long long x);
		unordered_set<int> add_edge(int x, int y, int id);
		unordered_set<int> delete_edge(int x, int y, int id);
		unordered_map<int, pair<int, int> > add_edge(int x, int y);
		unordered_map<int, pair<int, int> > delete_edge(int x, int y);
};

long long _hash(int A, int B);

long long __hash(int A, int B);

#endif
