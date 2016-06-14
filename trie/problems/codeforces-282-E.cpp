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

#define MAX 100001
#define H 42
#define MOD 1000000007LL


LL arr[MAX];

struct node {
	node *left, *right;
}* root;

void addNode(LL x) {
	node* curr = root;

	for(int i=H-1;i>=0;i--) {
		LL v = 1LL<<i;
		if(x & v) {
			if(curr->right == NULL) {
				curr->right = new node();
			}
			curr = curr->right;
		} else {
			if(curr->left == NULL) {
				curr->left = new node();
			}
			curr = curr->left;
		}
	}
}


LL query(LL x) {
	LL result = 0;

	node* curr = root;
	for(int i=H-1;i>=0;i--) {
		LL v = 1LL<<i;
		if(x & v) {
			if(curr->left == NULL) {
				curr = curr->right;
			} else {
				result |= v;
				curr = curr->left;
			}
		} else {
			if(curr->right == NULL) {
				curr = curr->left;
			} else {
				result |= v;
				curr = curr->right;
			}
		}
	}

	return result;
}


int main() {

	int n;

	sc1(n);

	LL  xorT = 0, result = 0;
	FOR(i, 0, n) {
		cin>>arr[i];

		xorT ^= arr[i];
		result = max(result, xorT);
	}


	LL curr = 0;

	root = new node();
	addNode(0);
	FOR(i, 0, n) {
		result = max(result, query(xorT));
		xorT ^= arr[i];//removing

		curr ^= arr[i];//adding
		addNode(curr);
	}

	cout<<result<<endl;


	return 0;
}







