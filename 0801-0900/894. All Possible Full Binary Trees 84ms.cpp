/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *	   int val;
 *	   TreeNode *left;
 *	   TreeNode *right;
 *	   TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *	   TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *	   TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
const int N=50005;
TreeNode a[N]; int a1;
TreeNode *newnode(TreeNode *l=nullptr,TreeNode *r=nullptr){a[a1].left=l; a[a1].right=r; return a+(a1++);}
class Solution {
public:
	vector<TreeNode*> dfs(int n) {
		vector<TreeNode*> ans;
		if (n<1||n%2==0)return ans;
		for (int i=2;i<n;i+=2){
			vector<TreeNode*> v1=dfs(i-1),v2=dfs(n-i);
			int n1=v1.size(),n2=v2.size();
			for (int i=0;i<n1;++i)
				for (int j=0;j<n2;++j)
					ans.push_back(newnode(v1[i],v2[j]));
		}
		if (ans.empty())ans.push_back(newnode());
		return ans;
	}
	vector<TreeNode*> allPossibleFBT(int n) {a1=0; return dfs(n);}
};

