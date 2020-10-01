const int N=10000;
int _c[N*4+5],*c=_c+N*2;
class Solution {
public:
	int longestSubsequence(vector<int>& a, int d) {
		int n=a.size(),ans=0,*c1=c-d;
		memset(c-N,0,sizeof(int)*(N*2+1));
		for (int *i=&a[0],*end=i+n;i!=end;++i){
			int &x=c[*i],&y=c1[*i];
			if (y+1>x)x=y+1,ans=max(ans,x);
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
