
#define LL long long int
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

	root = new node();

	addNode(10);

	query(20);
}

