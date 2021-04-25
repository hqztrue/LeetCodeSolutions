const int N=3005,P=1000000007;
int inv[N];
inline int mod(int a,int b){  //a*b%mod
	int div, res;
	__asm__ __volatile__("mul %3; div %4": "=a" (div), "=&d" (res): "a" (a), "r" (b), "r" (P));
	return res;
}
class Solution {
public:
	int makeStringSorted(const string &s) {
		if (!inv[1]){
			inv[1]=1;
			for (int i=2;i<N;++i)inv[i]=(long)inv[P%i]*(P-P/i)%P;
		}
		int c[26]={0},ans=0; long t=1;
		for (int i=s.size()-1;i>=0;--i){
			int ch=s[i]-'a';
			t=mod(t,inv[++c[ch]]);
			ans=(ans+t*accumulate(c,c+ch,0))%P;
			t=mod(t,s.size()-i);
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

