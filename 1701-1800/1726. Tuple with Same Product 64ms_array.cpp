const int N=100000005;
typedef unsigned short us;
us c[N];
class Solution {
public:
	int tupleSameProduct(vector<int>& a) {
		int n=a.size(),ans=0;
		for (int *i=&a[0],*end=i+n;i!=end;++i)
			for (int *j=i+1;j!=end;++j)++c[*i*(*j)];
		for (int *i=&a[0],*end=i+n;i!=end;++i)
			for (int *j=i+1;j!=end;++j){
				us &t=c[*i*(*j)]; ans+=t*(t-1); t=0;
			}
		return ans*4;
	}
};

