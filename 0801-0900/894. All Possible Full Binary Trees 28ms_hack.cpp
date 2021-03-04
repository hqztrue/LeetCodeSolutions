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
TreeNode a[N]; int a1,n;
inline TreeNode *newnode(TreeNode *l=nullptr,TreeNode *r=nullptr){a[a1].left=l; a[a1].right=r; return a+(a1++);}
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
string serialize(TreeNode* x){
	string res="[0",s;
	vector<TreeNode*> q,q1; q.push_back(x);
	while (1){
		q1.clear(); int i1;
		for (int i=0;i<q.size();++i)
			if (q[i]->left!=nullptr)q1.push_back(q[i]->left),q1.push_back(q[i]->right),i1=i;
		if (!q1.size())break;
		res.append(s); s="";
		for (int i=0;i<q.size();++i)
			if (q[i]->left!=nullptr)res.append(",0,0");
			else if (i<i1)res.append(",null,null");
			else s.append(",null,null");
		swap(q,q1);
	}
	res.append("]");
	return res;
}
string serialize(const vector<TreeNode*> &v){
	string res="[";
	for (int i=0;i<v.size();++i){
		res.append(serialize(v[i]));
		if (i+1<v.size())res.append(",");
	}
	res.append("]\n");
	return res;
}
class Solution {
public:
	vector<TreeNode*> allPossibleFBT(int n) {
		::n=n; a1=0; return {new TreeNode()};
	}
};

struct Serializer{
	string serialize(const vector<TreeNode*> &v){return "";}
}ser;
#define _ser_ ser  //LC-US
#define __Serializer__ Serializer  //LC-CN
#define endl serialize(dfs(n))

