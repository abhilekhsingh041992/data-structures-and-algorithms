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
#define pr1(x) printf("%d\n", x)
#define FOR(i, a, n) for(int i=a;i<n;i++)
#define pp pair<int, int>
#define pb push_back 

#define MAX 200002
#define MOD 1000000007LL

int arr[MAX];
pp mat[3*MAX];
int st[MAX], ed[MAX];
vector<int> adj[MAX];


void update(int root, int l, int r, int x, int y, int val, bool odd) {
	if((l==x) && (r==y)) {
		if(odd) mat[root].first += val;
		else mat[root].second += val;
	} else {
		int mid = (l + r) >> 1;

		if(x > mid) {
			update((root<<1)+1, mid+1, r, x, y, val, odd);
		} else if(y <= mid) {
			update(root<<1, l, mid, x, y, val, odd);
		} else {
			update(root<<1, l, mid, x, mid, val, odd);
			update((root<<1)+1, mid+1, r, mid+1, y, val, odd); 
		}
	}
}


int query(int root, int l, int r, int x) {
	int result = mat[root].second - mat[root].first;
	//printf("%d %d %d %d\n", l, r, x, result);

	if(l==r) {
		return result;
	} else {
		int mid = (l + r) >> 1;

		if(x <= mid) {
			return result + query(root<<1, l, mid, x);	
		} else {
			return result + query((root<<1)+1, mid+1, r, x);
		} 
	}
}

int visited;
int depth[MAX];

void dfs(int u, int parent, int level) {
	st[u] = ++visited;
	depth[u] = level;
	FOR(i, 0, adj[u].size()) {
		int v = adj[u][i];
		if(v != parent) {
			dfs(v, u, level+1);
		}
	}
	ed[u] = visited;
}

int main() {

	int n, m, u, v, val, op, x;

	sc2(n, m);
	FOR(i, 1, n+1) sc1(arr[i]);

	FOR(i, 1, n) {
		sc2(u, v);
		adj[u].pb(v);
		adj[v].pb(u);
	}

	dfs(1, -1, 0);

	FOR(i, 0, m) {
		sc2(op, x);
		if(op == 1) {
			sc1(val);
			update(1, 1, n, st[x], ed[x], val, depth[x] & 1);
		} else {
			int result = query(1, 1, n, st[x]);
			if(depth[x] & 1) result = -result;

			pr1(result + arr[x]);
		}
	}

	return 0;
}







