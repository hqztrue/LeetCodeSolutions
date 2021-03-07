const int L=3205,CH=26;
struct node{
	node **son;
	bool flag;
};
node _P[L],*p,*_Q[L*CH],**q,*root,**chg[L]; string ans,cur; int c1;
vector<node*> chg_flag;
inline node *newnode(){p->son=q; q+=CH; return p++;}
inline void insert(char *s,int l){
	node *x=root;
	for (int i=0;i<l;++i){
		char c=s[i]-'a';
		if (!x->son[c]){
			x->son[c]=newnode();
			chg[c1++]=x->son+c;
		}
		x=x->son[c];
	}
	x->flag=1; chg_flag.push_back(x);
}
void dfs(node *x){
	if (!x->flag)return;
	if (cur.size()>ans.size()||cur.size()==ans.size()&&cur<ans)ans=cur;
	for (int i=0;i<CH;++i)
		if (x->son[i]){
			cur.push_back(i+'a');
			dfs(x->son[i]);
			cur.pop_back();
		}
}
class Solution {
public:
	string longestWord(vector<string>& w) {
		p=_P; q=_Q; root=newnode(); root->flag=1; ans=""; c1=0; chg_flag.clear();
		for (int i=0;i<w.size();++i)insert(&w[i][0],w[i].size());
		cur=""; dfs(root);
		for (int i=0;i<c1;++i)*chg[i]=0;
		for (int i=0;i<chg_flag.size();++i)chg_flag[i]->flag=0;
		return ans;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

