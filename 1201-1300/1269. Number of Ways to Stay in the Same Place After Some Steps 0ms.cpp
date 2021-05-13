typedef long long ll;
const int N=505,P=1000000007;
ll inv[N],fac[N],ifac[N];
int _f[N*2],*f,*f1;
inline ll C(int n,int m){return fac[n]*ifac[m]%P*ifac[n-m]%P;}
class Solution {
public:
	int numWays(int n, int m) {
		ll ans=0;
		if (m<=sqrt(n)){
			f=_f; f1=_f+N;
			int s=min(n/2+1,m);
			for (int i=0;i<=s+1;++i)f[i]=f1[i]=0;
			f[1]=1;
			for (int j=1;j<=n;++j){
				for (int i=1;i<=s;++i)f1[i]=((long)f[i]+f[i-1]+f[i+1])%P;
				swap(f,f1);
			}
			return f[1];
		}
		--m;
		for (int n0=0;n0<=n;n0+=2){
			ll t=C(n0,n0/2);
			for (int i=1;;++i){
				int j=n0/2-(i-1)*m-(2*i-1);
				if (j<0)break;
				t-=C(n0,j);
			}
			for (int i=1;;++i){
				int j=n0/2+i*m+2*i;
				if (j>n0)break;
				t+=C(n0,j);
			}
			for (int i=1;;++i){
				int j=n0/2+i*m+(2*i-1);
				if (j>n0)break;
				t-=C(n0,j);
			}
			for (int i=1;;++i){
				int j=n0/2-i*m-2*i;
				if (j<0)break;
				t+=C(n0,j);
			}
			ans=(ans+t%P*C(n,n0))%P;
		}
		return (ans+P)%P;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	inv[1]=fac[0]=ifac[0]=fac[1]=ifac[1]=1;
	for (int i=2;i<N;++i)inv[i]=inv[P%i]*(P-P/i)%P,fac[i]=fac[i-1]*i%P,ifac[i]=ifac[i-1]*inv[i]%P;
	return 0;
}();

