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
#define L 22
#define MOD 1000000007LL

struct node {
	int cnt;
	bool flag;
} mat[L][MAX*3];

int tree[MAX*3];

void add(int root, int ind, int l, int r, int mid) {
	if(mat[ind][root].flag) {
		mat[ind][root<<1].flag = !mat[ind][root<<1].flag;
		mat[ind][root<<1].cnt = (mid-l+1) - mat[ind][root<<1].cnt;

		mat[ind][(root<<1)+1].flag = !mat[ind][(root<<1)+1].flag;
		mat[ind][(root<<1)+1].cnt = (r-mid) - mat[ind][(root<<1)+1].cnt;

		mat[ind][root].flag = 0;
	}
}

void update(int root, int ind, int l, int r, int x, int y) {
	if((l==x) && (r==y)) {
		mat[ind][root].cnt = (r-l+1) - mat[ind][root].cnt;
		mat[ind][root].flag = !mat[ind][root].flag;
	} else {
		int mid = (l + r) >> 1;

		add(root, ind, l, r, mid);

		if(x > mid) {
			update((root<<1)+1, ind, mid+1, r, x, y); 
		} else if(y <= mid) {
			update(root<<1, ind, l, mid, x, y); 
		} else {
			update(root<<1, ind, l, mid, x, mid); 
			update((root<<1)+1, ind, mid+1, r, mid+1, y); 
		}

		mat[ind][root].cnt = mat[ind][root<<1].cnt + mat[ind][(root<<1)+1].cnt;
	}
}



int query(int root, int ind, int l, int r, int x, int y) {
	if((l==x) && (r==y)) {
		return mat[ind][root].cnt;
	} else {
		int mid = (l + r) >> 1;

		add(root, ind, l, r, mid);

		int result = 0;
		if(x > mid) {
			result = query((root<<1)+1, ind, mid+1, r, x, y);
		} else if(y <= mid) {
			result = query(root<<1, ind, l, mid, x, y);
		} else {
			result = query(root<<1, ind, l, mid, x, mid) +
				query((root<<1)+1, ind, mid+1, r, mid+1, y); 
		}

		mat[ind][root].cnt = mat[ind][root<<1].cnt + mat[ind][(root<<1)+1].cnt;

		return result;
	}
}

int main() {

	int n, m, op, x, y, val;

	sc1(n);
	FOR(i, 1, n+1) {
		sc1(val);
		FOR(j, 0, L) {
			if((1<<j) & val) {
				update(1, j, 1, n, i, i);
			}
		}
	}

	sc1(m);
	FOR(i, 0, m) {
		sc3(op, x, y);

		if(op == 1) {
			LL result = 0;

			FOR(j, 0, L) {
				result += ((1LL<<j) * query(1, j, 1, n, x, y));
			}

			pr1(result);
		} else {
			sc1(val);

			FOR(j, 0, L) {
				if((1<<j) & val) {
					update(1, j, 1, n, x, y);
				}
			}
		}
	}


	return 0;
}







