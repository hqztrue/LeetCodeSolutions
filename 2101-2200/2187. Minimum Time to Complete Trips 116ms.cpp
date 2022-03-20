typedef long long ll;
const int N=100005;
struct node{
	int v,t;
	bool operator <(const node &A)const{
		return v<A.v;
	}
}c[N];
class Solution {
public:
	ll minimumTime(vector<int>& _a, int t) {
		int n=_a.size(),*a=&_a[0]; double tmp=0;
		for (int x:_a)tmp+=1./x;
		ll s=t/tmp; int r=n-1;
		for (int i=0;i<n;++i)t-=s/a[i],c[i].v=a[i]-s%a[i],c[i].t=a[i];
		while (t>0){
			int mid=r/2,s0=mid+1;
			nth_element(c,c+mid,c+r+1);
			int cur=c[mid].v;
			for (int i=0;i<=mid;++i)s0+=(cur-c[i].v)/c[i].t;
			if (s0<=t){
				for (int i=0;i<=mid;++i)c[i].v=c[i].t-(cur-c[i].v)%c[i].t;
				for (int i=mid+1;i<=r;++i)
					if (c[i].v==cur)++s0,c[i].v=c[i].t;
					else c[i].v-=cur;
				t-=s0; s+=cur;
			}
			else r=mid;
		}
		return s;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

