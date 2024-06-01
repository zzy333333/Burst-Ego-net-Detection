//temporal graph

#ifndef Temporal_Graph
#define Temporal_Graph

#include<vector>
#include<unordered_map>

using namespace std;

class Graph{
	private://need to change to private
		int n, m;
		vector<vector<int> >neighbor;//ignore repeated edge
		vector<vector<int> >directed_neighbor; 
		vector<vector<int> >edge;
		vector<vector<int> >directed_edge;
		unordered_map<long long, int>edge_count;//number of repeated edge
	public:
		vector<double>lower;//lower_bound of density
		vector<double>upper;//upper_bound of density
		Graph(int _n);
		~Graph();
		void add_edge(int x, int y);
		void rebuild();
		void approximate(int x);
		void calculate(int x);
		void divide(int x); 
};

long long _hash(int A, int B);

#endif
