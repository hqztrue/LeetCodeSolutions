const int L=9005,M=7,CH=26;  //L=14005
int Q[L*CH],q,*chg[L]; int c1;
inline bool insert(char *s,int l){
	int x=0; int _q=q;
	for (char *s1=s+l-1;s1>=s;--s1){
		char c=*s1-'a'; int &y=Q[x+c];
		if (!y){
			y=q; q+=CH;
			chg[c1++]=&y;
		}
		x=y;
	}
	return q>_q;
}
vector<string*> v[M+1];
class Solution {
public:
	int minimumLengthEncoding(vector<string>& words) {
		int n=words.size(),ans=0; q=CH; c1=0;
		for (int i=1;i<=M;++i)v[i].clear();
		for (int i=0;i<n;++i)v[words[i].size()].push_back(&words[i]);
		for (int i=M;i;--i)
			for (string *s:v[i])
				if (insert(&(*s)[0],s->size()))ans+=s->size()+1;
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

