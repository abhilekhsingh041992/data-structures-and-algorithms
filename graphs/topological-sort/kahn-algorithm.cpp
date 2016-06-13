/*

 Ref:
    https://en.wikipedia.org/wiki/Topological_sorting

 Algo:
	L ← Empty list that will contain the sorted elements
	S ← Set of all nodes with no incoming edges
	while S is non-empty do
	    remove a node n from S
	    add n to tail of L
	    for each node m with an edge e from n to m do
	        remove edge e from the graph
	        if m has no other incoming edges then
	            insert m into S
	if graph has edges then
	    return error (graph has at least one cycle)
	else 
	    return L (a topologically sorted order)

	
	Problems:
		http://www.spoj.com/problems/PFDEP/

*/


#define MAX 105

vector<int> graph[MAX];
int incE[MAX];
bool visited[MAX];
set<int> s;


void topologicalSort(int n, int e, vector<int> &result) {
	for(int i=1;i<=n;i++) {
		if(!incE[i]) s.insert(i);
	}	

	while(s.size()) {
		int u = *s.begin();
		result.push_back(u);

		s.erase(u);
		for(auto x: graph[u]) {
			incE[x]--;
			if(!incE[x]) s.insert(x);
		}
	}
}


int main() {

	int n, e, k, u, v;

	sc2(n, e);
	FOR(i, e) {
		sc2(u, k);
		incE[u] = k;
		FOR(j, k) {
			sc1(v);
			graph[v].push_back(u);
		}
	}

	vector<int> result;
	topologicalSort(n, e, result);
	for(int i=0;i<result.size();i++) {
		printf("%d ", result[i]);
	}
	printf("\n");

	return 0;
}