const int CH=255,N=5005;
char *_a[26][N],**a[CH]; int a1[CH];
class Solution {
public:
	int numMatchingSubseq(const string &s, vector<string>& w) {
		int n=s.size(),m=w.size(),ans=0;
		for (int i=0;i<26;++i)a['a'+i]=_a[i],a1['a'+i]=0;
		for (int i=0;i<m;++i){
			char &c=w[i][0];
			a[c][a1[c]++]=&c;
		}
		for (int i=0;i<n;++i){
			char c=s[i]; int k=a1[c]; a1[c]=0;
			for (char **j=a[c],**end=j+k;j!=end;++j){
				char x=*(++*j);
				if (!x)++ans;
				else a[x][a1[x]++]=*j;
			}
		}
		return ans;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

