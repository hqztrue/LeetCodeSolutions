const int N=100000;
int _c[N*4+1],*c=_c+N*2;
#define CLR for (int i=0;i<n;++i)c[a[i]]=0;
class Solution {
public:
	bool canReorderDoubled(vector<int>& A) {
		if (!A.size())return 1;
		int n=A.size(),*a=&A[0];
		for (int i=0;i<n;++i)++c[a[i]];
		if (c[0]%2){CLR; return 0;}
		for (int i=0;i<n;++i){
			int x=a[i],x1=x;
			if (x&&c[x]){
				while (!(x&1)&&c[x>>1])x>>=1;
				while (1){
					if ((c[x*2]-=c[x])<0){c[x*2]=0; CLR; return 0;}
					c[x]=0;
					if (x==x1)break;
					x*=2;
				}
			}
		}
		CLR; return 1;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();


