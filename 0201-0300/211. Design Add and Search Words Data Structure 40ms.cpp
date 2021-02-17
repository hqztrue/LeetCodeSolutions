static const int L=150005,N=505,CH=26;
struct node{
	node *son[CH];
	node *clear(){memset(son,0,sizeof(son));return this;}
};
node a[L],*root=a; int l;
class WordDictionary {
public:
	/** Initialize your data structure here. */
	WordDictionary() {
		for (int i=0;i<N;++i)a[i].clear(); l=N;
	}
	void addWord(const string &w) {
		const char *s=&w[0]; int len=w.size(); node *x=root+len;
		for (int i=0;i<len;++i){
			char c=s[i]-'a';
			if (!x->son[c])x->son[c]=a[l++].clear();
			x=x->son[c];
		}
	}
	bool dfs(const char *s,node *x){
		while (*s&&*s!='.'&&x)x=x->son[*s++-'a'];
		if (!x)return 0;
		if (!*s)return 1;
		for (int i=0;i<CH;++i)if (x->son[i]&&dfs(s+1,x->son[i]))return 1;
		return 0;
	}
	bool search(const string &w) {
		return dfs(w.c_str(),root+w.size());
	}
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

