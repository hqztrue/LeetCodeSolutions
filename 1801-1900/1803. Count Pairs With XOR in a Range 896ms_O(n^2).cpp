#define us unsigned short
const int N=20005;
us a[N];
class Solution {
public:
	__attribute__((no_sanitize_address,no_sanitize_memory))
	int countPairs(vector<int>& _a, us l, us r) {
		int n=_a.size(),ans=0,d=0;
		for (int i=0;i<n;++i)a[i]=_a[i];
		sort(a,a+n);
		for (us *i=a,*end=i+n;i!=end;++i){
			if (i>a&&*i==*(i-1)){ans+=d; continue;}
			us *j=i+1,*end1=end-8; d=0;
			for (;j<end1;j+=8){
				us x=*i^*j,x1=*i^*(j+1),x2=*i^*(j+2),x3=*i^*(j+3),
					x4=*i^*(j+4),x5=*i^*(j+5),x6=*i^*(j+6),x7=*i^*(j+7);
				d+=(x>=l&&x<=r)+(x1>=l&&x1<=r)+(x2>=l&&x2<=r)+(x3>=l&&x3<=r)
					+(x4>=l&&x4<=r)+(x5>=l&&x5<=r)+(x6>=l&&x6<=r)+(x7>=l&&x7<=r);
			}
			for (;j<end;++j)d+=(*i^*j)>=l&&(*i^*j)<=r;
			ans+=d;
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

