const int CH=255,N=5005,W=(1<<16)-1;
int _a[26][N],*a[CH],a1[CH],b[N],l[N];
class Solution {
public:
	int numMatchingSubseq(const string &s, vector<string>& w) {
		int n=s.size(),m=w.size(),ans=0;
		for (int i=0;i<26;++i)a['a'+i]=_a[i],a1['a'+i]=0;
		for (int i=0;i<m;++i){
			l[i]=w[i].size();
			char c=w[i][0];
			a[c][a1[c]++]=i<<16;
		}
		for (int i=0;i<n;++i){
			int k=a1[s[i]];
			memcpy(b,a[s[i]],sizeof(int)*k);
			a1[s[i]]=0;
			for (int j=0;j<k;++j){
				int x=b[j]>>16,y=(b[j]&W)+1;
				if (y==l[x])++ans;
				else {
					char c=w[x][y];
					a[c][a1[c]++]=b[j]+1;
				}
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


