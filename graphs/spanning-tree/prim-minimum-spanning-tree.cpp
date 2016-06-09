

/*

	Prim
	In this approach, we act like Dijkstra. We have a set of vertices S, in each step we add the nearest vertex to S, 
	in S (distance of v from  where weight(i, j) is the weight of the edge from i to j) .

	So, pseudo code will be like this:

	Prim()
		S = new empty set
		for i = 1 to n
			d[i] = inf
		while S.size() < n
			x = inf
			v = -1
			for each i in V - S // V is the set of vertices
				if x >= d[v]
					then x = d[v], v = i
			d[v] = 0
			S.insert(v)
			for each u in adj[v]
				do d[u] = min(d[u], w(v,u))
	C++ code:

	As Dijkstra you can use std :: priority_queue instead of std :: set.

	Problems:
		http://www.spoj.com/problems/CSTREET/
		http://www.spoj.com/problems/BLINNET/

*/

// O(n logn)
int parent[MAX];
void prim(){
	fill(d, d + n, inf);
	fill(visited, visited + n, 0);
	set<pair<int,int> > s;
	for(int i = 0;i < n;i ++)
		s.insert({d[i],i});
	int v;
	while(!s.empty()){
		v = s.begin() -> second;
		s.erase(s.begin());

		visited[v] = true;
		for(auto p : adj[v]){
			int u = p.first, w = p.second;
			if((!visited[u]) && (d[u] > w)) {
				parent[v] = u;
				s.erase({d[u], u});
				d[u] = w;
				s.insert({d[u], u});
			}
		}
	}
}


// O(n^2)
bool mark[MAXN];
void prim(){
	fill(d, d + n, inf);
	fill(mark, mark + n, false);
	int x,v;
	while(true){
		x = inf;
		v = -1;
		for(int i = 0;i < n;i ++)
			if(!mark[i] and x >= d[i])
				x = d[i], v = i;
		if(v == -1)
			break;
		d[v] = 0;
		mark[v] = true;
		for(auto p : adj[v]){ //adj[v][i] = pair(vertex, weight)
			int u = p.first, w = p.second;
			d[u] = min(d[u], w);
		}
	}
}