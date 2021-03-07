/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
namespace Hash{
	typedef unsigned int uint;
	const uint S=14,S1=32-S,M=1996090921;
	struct node{
		uint x; int y,t;
	}h[(1<<S)+1005];
	int T=1;
	inline bool insert(uint x){
		node *p=h+((uint)x*M>>S1);
		for (;p->t==T;++p)
			if (p->x==x)return ++p->y==2?1:0;
		p->t=T; p->x=x; p->y=1; return 0;
	}
} using namespace Hash;
const int M1=1732479145,M2=2012582971,M3=1713253213;
vector<TreeNode*> ans;
uint dfs(TreeNode *x){
	if (!x)return 0;
	uint l=dfs(x->left),r=dfs(x->right),h=(l*M1+r*M2+x->val)^M3;
	if (insert(h))ans.push_back(x);
	return h;
}
class Solution {
public:
	vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
		++T; ans.clear();
		dfs(root);
		return ans;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

