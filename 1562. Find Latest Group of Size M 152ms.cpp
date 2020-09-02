const int N=100005;
int len[N];
class Solution {
public:
	int findLatestStep(vector<int>& a, int m) {
		int n=a.size(),ans=-1;
		if (m==n)return m;
		memset(len,0,sizeof(int)*(n+2));
		for (int *sta=&a[0],*p=sta,*end=&a[0]+n;p!=end;++p){
			int t=*p,l=len[t-1],r=len[t+1];
			if (l==m||r==m)ans=p-sta;
			len[t-l]=len[t+r]=l+r+1;
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

