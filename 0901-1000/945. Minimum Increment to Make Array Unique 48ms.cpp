const int N=40005;
int c[N];
class Solution {
public:
	int minIncrementForUnique(vector<int>& a) {
		int n=a.size(),ans=0,m=0,s=0;
		if (!n)return 0;
		for (int *i=&a[0],*end=i+n;i!=end;++c[*i],++i)
			if (*i>m)m=*i;
		for (int *i=c,*end=c+m;i<=end;++i){
			s+=*i;
			if (s>=1)--s,ans+=s;
		}
		ans+=s*(s-1)/2;
		for (int i=0;i<n;++i)--c[a[i]];
		return ans;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

