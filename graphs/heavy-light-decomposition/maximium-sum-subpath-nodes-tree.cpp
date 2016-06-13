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

#define MAX 100005
#define H 20
#define MOD 1000000007LL


vector <int> adj[MAX], costs[MAX], indexx[MAX];
int ptr;
int chainNo, chainInd[MAX], chainHead[MAX], posInBase[MAX];
int depth[MAX], pa[H][MAX], subsize[MAX];


int arr[MAX];

struct node {
	LL m, l, r, t; 

	node() {
		m = l = r = t = 0; 
	}
} tree[MAX*5];

node combine(node a, node b) {
	node p;

	p.t = a.t + b.t;
	p.l = max(a.l, a.t + b.l);
	p.r = max(b.r, a.r + b.t);
	
	p.m = max(max(a.m, b.m), a.r + b.l);

	return p;
}


void build_tree(int root, int l, int r) {
	if(l == r) {
		if(arr[l] >= 0) {
			tree[root].m = tree[root].l = tree[root].r = tree[root].t = arr[l]; 
		} else {
			tree[root].m = tree[root].l = tree[root].r = 0;
			tree[root].t = arr[l]; 
		}
	} else {
		int mid = (l+r) >> 1;

		build_tree(root<<1, l, mid);
		build_tree((root<<1)+1, mid+1, r);

		tree[root] = combine(tree[root<<1], tree[(root<<1)+1]);
	}
}

node query_tree(int root, int l, int r, int x, int y) {
	if((l==x) && (r==y)) {
		return tree[root];
	} else {
		int mid = (l + r) >> 1;

		if(x > mid) {
			return query_tree((root<<1)+1, mid+1, r, x, y);
		} else if(y <= mid) {
			return query_tree(root<<1, l, mid, x, y);
		} else {
			return combine(query_tree(root<<1, l, mid, x, mid),
					query_tree((root<<1)+1, mid+1, r, mid+1, y)); 
		}
	}
}



node query_up(int u, int v) {
	node ans;

	if(u == v) return ans; // Trivial
	int uchain, vchain = chainInd[v];
	
	// uchain and vchain are chain numbers of u and v
	while(true) {
		uchain = chainInd[u];

		if(uchain == vchain) {
			// Both u and v are in the same chain, so we need to query from u to v, update answer and break.
			// We break because we came from u up till v, we are done
			if(u==v) break;

			ans = combine(query_tree(1, 0, ptr-1, posInBase[v]+1, posInBase[u]), ans); // Update answer
			break;
		}
		ans = combine(query_tree(1, 0, ptr-1, posInBase[chainHead[uchain]], posInBase[u]), ans); // Update answer
		u = chainHead[uchain]; // move u to u's chainHead
		u = pa[0][u]; //Then move to its parent, that means we changed chains
	}
	return ans;
}


int LCA(int u, int v) {
	if(depth[u] < depth[v]) swap(u,v);
	int diff = depth[u] - depth[v];
	for(int i=0; i<H; i++) if( (diff>>i)&1 ) u = pa[i][u];
	if(u == v) return u;
	for(int i=H-1; i>=0; i--) if(pa[i][u] != pa[i][v]) {
		u = pa[i][u];
		v = pa[i][v];
	}
	return pa[0][u];
}

LL combineChild(node a, node b) {
	LL result = max(a.m, b.m);
	result = max(result, a.t+b.t);
	result = max(result, a.t+b.l);
	result = max(result, a.l+b.t);
	result = max(result, a.l+b.l);

	return result;
}


void query(int u, int v) {
	int lca = LCA(u, v);

	LL result = 0;
	if(lca == u) {
		result = query_up(v, lca).m;
	} else if(lca == v) {
		result = query_up(u, lca).m;
	} else {
		result = combineChild(query_up(u, lca), query_up(v, lca));
	}
	
	pr1(result);

	//printf("%lld %lld %lld\n", result, query_up(u, lca).m, query_up(v, lca).m);
}


void HLD(int curNode, int cost, int prev) {
	if(chainHead[chainNo] == -1) {
		chainHead[chainNo] = curNode; // Assign chain head
	}
	chainInd[curNode] = chainNo;
	posInBase[curNode] = ptr; // Position of this node in baseArray which we will use in Segtree
	arr[ptr++] = cost;

	int sc = -1, ncost;
	// Loop to find special child
	for(int i=0; i<adj[curNode].size(); i++) if(adj[curNode][i] != prev) {
		if(sc == -1 || subsize[sc] < subsize[adj[curNode][i]]) {
			sc = adj[curNode][i];
			ncost = costs[curNode][i];
		}
	}

	if(sc != -1) {
		// Expand the chain
		HLD(sc, ncost, curNode);
	}

	for(int i=0; i<adj[curNode].size(); i++) if(adj[curNode][i] != prev) {
		if(sc != adj[curNode][i]) {
			// New chains at each normal node
			chainNo++;
			HLD(adj[curNode][i], costs[curNode][i], curNode);
		}
	}
}


void dfs(int cur, int prev, int _depth=0) {
	pa[0][cur] = prev;
	depth[cur] = _depth;
	subsize[cur] = 1;
	for(int i=0; i<adj[cur].size(); i++)
		if(adj[cur][i] != prev) {
			dfs(adj[cur][i], cur, _depth+1);
			subsize[cur] += subsize[adj[cur][i]];
		}
}


void init(int n) {
	FOR(i, 0, n) {
		chainHead[i] = -1;
		FOR(j, 0, H) pa[j][i] = -1;
	}
}

int main() {

	int n, q, u, v, c;

	sc2(n, q);

	init(n);

	FOR(i, 1, n) {
		sc3(u, v, c);
		u--; v--;

		adj[u].pb(v);
		costs[u].pb(c);
		indexx[u].pb(i-1);


		adj[v].pb(u);
		costs[v].pb(c);
		indexx[v].pb(i-1);
	}


	chainNo = ptr = 0;
	dfs(0, -1); 
	HLD(0, 0, -1); 

	build_tree(1, 0, ptr-1);

	FOR(i, 1, H) {
		FOR(j, 0, n) {
			if(pa[i-1][j] != -1) pa[i][j] = pa[i-1][pa[i-1][j]];
		}
	}


	FOR(i, 0, q) {
		sc2(u, v);
		u--; v--;

		query(u, v);
	}


	return 0;
}







