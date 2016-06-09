

#define MAX 1000000
int arr[MAX];
int mat[MAX];


int buildTree(int left, int right, int root) {
	if(left == right) {
		return mat[root] = arr[left-1];
	} else {
		int mid = (left + right) / 2;
		int lValue = buildTree(left, mid, root<<1);
		int rValue = buildTree(mid+1, right, (root<<1)+1);
		return mat[root] = min(lValue, rValue);
	}
}


int find(int left, int right, int root, int x, int y) {
	if((left == x) && (right == y)) {
		return mat[root];
	} else {
		int mid = (left + right) / 2;
		int lValue = (x <= mid) ? find(left, mid, root<<1, x, min(y,mid) ): INT_MAX;
		int rValue = (y > mid) ? find(mid+1, right, (root<<1)+1, max(x, mid+1), y) : INT_MAX;
		return min(lValue, rValue);
	}
}


