#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iomanip> 
#include<utility> 
#include<climits>
#include<climits>
#include<cmath>
#include<algorithm>


using namespace std;


#define LL long long int
#define sc1(x) scanf("%d", &x)
#define sc2(x, y) scanf("%d%d", &x, &y)
#define sc3(x, y, z) scanf("%d%d%d", &x, &y, &z)
#define pr1(x) printf("%lld\n", x)
#define FOR(i, a, n) for(int i=a;i<n;i++)
#define pp pair<int, int>
#define pb push_back 

#define MAX 100001
#define H 20
#define MOD 1000000007LL

vector<pp> adj[MAX];

int depth[MAX];

int parents[H][MAX];

class node {

public:
	LL pref, suff, total, result;

	node() {
		pref = suff = result = total = 0;
	}

	node combine(node &b) {
		node ans;

		ans.total = total + b.total;
		ans.pref = max(pref, total + b.pref);
		ans.suff = max(b.suff, suff + b.total);
		
		ans.result = max(max(result, b.result), suff + b.pref);

		return ans;
	}

} maxPath[H][MAX];



void setEdge(int v, int u, int w) {

	depth[v] = depth[u] + 1;
	parents[0][v] = u;

	maxPath[0][v].pref = maxPath[0][v].suff = maxPath[0][v].result = max(0, w);
	maxPath[0][v].total = w;	
}

void dfs(int u, int parent) {

	FOR(i, 0, adj[u].size()) {
		int v = adj[u][i].first;
		int w = adj[u][i].second;

		if(v != parent) {
			setEdge(v, u, w);
			dfs(v, u);
		}
	}
}

node lca(int u , int v) {

	if(depth[u] < depth[v]) swap(u , v);

	int diff = depth[u] - depth[v];

	node leftP, rightP;

	FOR(i, 0, H) {
		if(diff & (1 << i)){
			leftP = leftP.combine(maxPath[i][u]);
			u = parents[i][u];
		}
	}

	if(u == v) return leftP;;
	
	for(int i=H-1;i>=0; i--) {
		if(parents[i][u] != parents[i][v]) {
			leftP = leftP.combine(maxPath[i][u]);
			rightP = rightP.combine(maxPath[i][v]);
			u = parents[i][u];
			v = parents[i][v];
		}
	}
	leftP = leftP.combine(maxPath[0][u]);
	rightP = rightP.combine(maxPath[0][v]);

	swap(rightP.pref , rightP.suff);
	return leftP.combine(rightP);
}



void processParents(int n) {
	FOR(i, 1, H) {
		FOR(j, 1, n+1) {
			
			int nextP = parents[i - 1][j];

			parents[i][j] = parents[i - 1][nextP];
			maxPath[i][j] = maxPath[i - 1][j].combine(maxPath[i - 1][nextP]);
		}
	}
}

int main() {

	int n, m, u, v, w;

	sc2(n, m);
	FOR(i, 1, n) {
		sc3(u, v, w);

		adj[u].pb({v, w});
		adj[v].pb({u, w});	
	}


	dfs(1, 0);
	processParents(n);

	FOR(i, 0, m) {
		sc2(u, v);

		pr1(lca(u, v).result);
	}

	return 0;
}







