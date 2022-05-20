const int N=100005,inf=~0u>>2;
struct bucket{
	int min,max;
}c[N];
class Solution {
public:
	int maxConsecutive(int l, int r, vector<int>& _a) {
		_a.push_back(l-1); _a.push_back(r+1);
		int *a=&_a[0],n=_a.size(),res=0;
		auto t=minmax_element(a,a+n);
		int mi=*t.first,ma=*t.second,d=ceil(1.*(ma-mi)/(n-1));
		for (int i=0;i<n;++i)c[i].min=inf,c[i].max=-inf;
		for (int i=0;i<n;++i){
			bucket *p=c+(a[i]-mi)/d;
			p->min=min(p->min,a[i]);
			p->max=max(p->max,a[i]);
		}
		int cur=mi;
		for (bucket *p=c,*end=c+n;p!=end;++p)
			if (p->min!=inf){
				res=max(res,p->min-cur);
				cur=p->max;
			}
		return res-1;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

