const int U=10000,inf=~0u>>2;
int c[U*2+1];
class Solution {
public:
	int maximumBeauty(vector<int>& _a) {
		int *a=&_a[0],n=_a.size(),*end=a+n,res=-inf;
		for (int *i=a;i!=end;++i)c[*i+U]=inf;
		for (int *i=a,s=0;i!=end;++i){
			int &t=c[*i+U];
			if (t==inf){
				if (*i>0)s+=*i;
				t=s;
			}
			else {
				res=max(res,s-t+*i*2);
				if (*i>0)s+=*i;
			}
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

