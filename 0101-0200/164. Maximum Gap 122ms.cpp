const int N=100005,inf=~0u>>2;
int mi[N],ma[N];
class Solution {
public:
	int maximumGap(vector<int>& _a) {
		int *a=&_a[0],n=_a.size(),res=0;
		if (n<2)return 0;
		auto t=minmax_element(a,a+n);
		int _mi=*t.first,_ma=*t.second,d=ceil(1.*(_ma-_mi)/(n-1));
		if (d==0)return 0;
		for (int i=0;i<n;++i)mi[i]=inf,ma[i]=-inf;
		for (int i=0;i<n;++i){
			int &x=a[i]; int j=(x-_mi)/d;
			mi[j]=min(mi[j],x);
			ma[j]=max(ma[j],x);
		}
		int cur=_mi;
		for (int i=0;i<n;++i)
			if (mi[i]!=inf){
				res=max(res,mi[i]-cur);
				cur=ma[i];
			}
		return res;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

