typedef long long ll;
const int N=(1<<21)+1,P=1000000007;
int c[N];
class Solution {
public:
	int countPairs(vector<int>& a) {
		int n=a.size(),*sta=&a[0],*end=sta+n,ans=0;
		for (int *p=sta;p!=end;++p)++c[*p];
		for (int *p=sta;p!=end;++p){
			for (int i=1<<20,x=*p,x1=x<<1;i>x1;i>>=1)ans+=c[i-x];
			if (ans>=P)ans-=P;
		}
		for (int i=1<<20;i;i>>=1)ans=(ans+(ll)c[i]*(c[i]-1)/2)%P;
		for (int *p=sta;p!=end;++p)c[*p]=0;
		return ans;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();


