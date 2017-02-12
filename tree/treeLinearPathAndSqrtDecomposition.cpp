/*
	
	Problems:
		https://www.hackerearth.com/challenge/competitive/february-clash-17/algorithm/tree-and-coprime-queries/
		
	Read:
		http://codeforces.com/blog/entry/43230



*/


#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iomanip> 
#include<utility> 
#include<climits>
#include<cmath>
#include<cassert>
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
 
#define MAX 100001
#define H 20
#define L 5001
#define SQRT 500
#define MOD 1000000007LL
 
int arr[MAX], st[MAX], en[MAX];
int depth[MAX], pa[H][MAX], subsize[MAX];
int bb[400][L];

int mem[L][L];
int tim;
int mat[3*MAX];
int con[3*MAX];

 
vector<int> adj[MAX];
 
 
 
int gcd(int a, int b) { 
	if(mem[a][b] != -1) return mem[a][b];
	return mem[a][b] = b ? gcd(b, a%b) : a; 
}
 
 
void dfs(int cur, int prev, int _depth=0) {
	pa[0][cur] = prev;
	depth[cur] = _depth;

	mat[tim] = cur;
	con[tim] = 1;
	st[cur] = tim;
	tim++;
	for(int i=0; i<adj[cur].size(); i++)
		if(adj[cur][i] != prev) {
			dfs(adj[cur][i], cur, _depth+1);
		}

	mat[tim] = cur;
	con[tim] = -1;
	en[cur] = tim;
	tim++;
}
 `
 
int query_up(int i, int c) {

	int block = st[i]/SQRT;
	int result = 0;

	if(block) {
		FOR(j, 1, L) {
			if(gcd(j, c) == 1) {
				result += bb[block-1][j];
			}
		}
	}

	FOR(j, block*SQRT, st[i]+1) {
		if(gcd(c, arr[mat[j]]) == 1) {
			result += con[j];
		}
	}

	return result;
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
 
 
void query(int u, int v, int c) {
	int lca = LCA(u, v);
 
	int result = 0;
	int x = (gcd(arr[lca], c) == 1);
	if(lca == u) {
		result = query_up(v, c) - query_up(lca, c) + x;
	} else if(lca == v) {
		result = query_up(u, c) - query_up(lca, c) + x;
	} else {
		result = query_up(v, c) + query_up(u, c) - (2 * query_up(lca, c)) + x;
	}
	
	pr1(result);
 
	//printf("%lld %lld %lld\n", result, query_up(u, lca).m, query_up(v, lca).m);
}
 
 
 
 
int main() {
 
	int n, q, x, a, b, c;
 
 	memset(mem, -1, sizeof(mem));

	sc2(n, q);
	FOR(i, 1, n+1) sc1(arr[i]);
 
	FOR(i, 1, n) {
		sc2(a, b);
 
		adj[a].pb(b);
		adj[b].pb(a);
			
	}
 
	dfs(1, -1); 
 
	FOR(i, 1, H) {
		FOR(j, 1, n+1) {
			if(pa[i-1][j] != -1) pa[i][j] = pa[i-1][pa[i-1][j]];
		}
	}
 
 	for(int i=1;i<L;i++) {
 		int block = 0;
 		for(int j=0;j<tim;j++) {
 			if((j/SQRT) != block) {
 				block = j/SQRT;
 				bb[block][i] = bb[block-1][i];	
 			}
 			if(arr[mat[j]] == i) {
 				bb[block][i] += con[j];
 			}
 		}
 	}

 
 	int y, block, k = (tim-1)/SQRT;
	FOR(i, 0, q) {
		sc3(x, a, b);
 
		if(x) {
			sc1(c);
 
			query(a, b, c);
 
		} else {
			
			y = con[st[a]];
			block = st[a]/SQRT;
			for(int j=block;j<=k;j++) {
				bb[j][arr[a]] -= y;
			}

			y = con[en[a]];
			block = en[a]/SQRT;
			for(int j=block;j<=k;j++) {
				bb[j][arr[a]] -= y;
			}

			arr[a] = b;

			y = con[st[a]];
			block = st[a]/SQRT;
			for(int j=block;j<=k;j++) {
				bb[j][arr[a]] += y;
			}

			y = con[en[a]];
			block = en[a]/SQRT;
			for(int j=block;j<=k;j++) {
				bb[j][arr[a]] += y;
			}

		}
	}
	return 0;
}
 