const int U=10000;
int s[U+1];
class Solution {
public:
	int minStoneSum(vector<int>& a, int k) {
		int ans=0,i,t;
		memset(s,0,sizeof(s));
		for (int *p=&a[0],*end=p+a.size();p!=end;++p)++s[*p];
		for (i=U;k&&i;--i)
			if (s[i])t=min(s[i],k),k-=t,s[i]-=t,s[i-i/2]+=t;
		for (++i;i;--i)ans+=s[i]*i;
		return ans;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

