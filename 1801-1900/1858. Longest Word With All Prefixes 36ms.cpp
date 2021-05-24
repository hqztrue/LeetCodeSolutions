const int N=100005,CH=26;
int Q[N*CH],q,*chg[N],c1;
vector<string*> v[N];
inline bool insert(char *s,int l){
	int x=0,_q=q;
	for (char *s1=s;s1<s+l;++s1){
		char c=*s1-'a'; int &y=Q[x+c];
		if (!y){
			if (s1<s+l-1)return 0;
			y=q; q+=CH;
			chg[c1++]=&y;
			return 1;
		}
		x=y;
	}
	return 0;
}
class Solution {
public:
	string longestWord(vector<string>& w) {
		string ans; int l=0; q=CH; c1=0;
		for (auto &s:w)v[s.size()].push_back(&s),l=max(l,(int)s.size());
		for (int i=1;i<=l;++i)
			for (auto &p:v[i])
				if (insert(&((*p)[0]),p->size()))
					if (ans==""||(p->size()>ans.size()||p->size()==ans.size()&&*p<ans))ans=*p;
		for (auto &s:w)v[s.size()].clear();
		for (int i=0;i<c1;++i)*chg[i]=0;
		return ans;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

