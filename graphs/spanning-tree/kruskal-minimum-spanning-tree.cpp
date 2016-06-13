/*

	Minimum spanning tree

	Problems:
		http://www.spoj.com/problems/CSTREET/

*/


/*

	Kruskal algo:
		ElogE + ElogV

*/		
struct node {
	int p, height;	
} parents[MAX];


int find(int x) {
	if(parents[x].p) {
		//compression
		return parents[x].p = find(parents[x].p);
	} else {
		return x;
	}
}

//Reducing tree height
void doUnion(int src, int dest) {
	if(parents[src].height > parents[dest].height) {
		parents[src].p = dest;
	} else if(parents[src].height < parents[dest].height) {
		parents[dest].p = src;
	} else {
		parents[src].p = dest;
		parents[src].height++;
	}
}

#define MAX_EDGES 300002
struct edge {
	int s, d;
	LL w;
} edges[MAX_EDGES];

bool cmp(edge &a, edge &b) {
	return a.w <= b.w;
}

LL minSpanningTree(int n, int m) {
	for(int i=0;i<n;i++) {
		parents[i].p = parents[i].height = 0;
	}

	int cnt = n-1;
	LL result = 0;
	for(int i=0;(i<m) && (cnt>0);i++) {
		int x = find(edges[i].s);
		int y = find(edges[i].d);
		if(x != y) {
			doUnion(x, y);
			cnt--;
			result += edges[i].w;
		}
	}
	return result;
}


int main() {

	int tests, n, m;
	LL cost;

	cin>>tests;
	while(tests--) {
		cin>>cost>>n>>m;
		for(int i=0;i<m;i++) {
			cin>>edges[i].s>>edges[i].d>>edges[i].w;
		}	

		sort(edges, edges+m, cmp);

		LL result = minSpanningTree(n, m) * cost;
		cout<<result<<endl;
	}
	return 0;
}

