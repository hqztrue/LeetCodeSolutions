#define double long double
const double PI=atan((double)1)*4,E=exp((double)1),
  B[]={1,1./2,1./6,0,-1./30,0,1./42,0,-1./30,0,5./66,0,-691./2730,0,7./6,0,-3617./510,0,43867./798,0,-174611./330};
const int M=10;
double log_fac(double n){
	double ans=n*log(n/E)+log(n)/2+log(sqrt(PI*2));
	for (int i=2;i<=M;++i)ans+=pow(-1,i)*B[i]/(i*(i-1)*pow(n,i-1));
	if (n<20){
		ans=0;
		for (int i=1;i<=n;++i)ans+=log(i);
	}
	return ans;
}
int leading(int l,int r){
	double t=log_fac(r)-log_fac(l-1);
	t/=log((double)10); t-=int(t)-4;
	return pow(10,t);
}

const int P=3125;
template<class T> T extend_gcd(T a,T b,T &x,T &y){
	if (!b){x=1;y=0;return a;}
	T res=extend_gcd(b,a%b,y,x); y-=x*(a/b);
	return res;
}
template<class T>
inline T inv(T a,T M){
	T x,y; extend_gcd(a,M,x,y);
	return (x%M+M)%M;
}
const int inv2=inv(2,P);
int exp(int x,int y,int z){
	int ans=1;
	while (y){
		if (y&1)ans=ans*x%z;
		x=x*x%z;y>>=1;
	}
	return ans;
}
int Chinese_Remainder_Theorem(int A[],int M[],int n){
	for (int i=1;i<n;++i){
		int x,y,P=M[0]*M[i];
		extend_gcd(M[0],M[i],x,y);
		x=(x*(A[i]-A[0])%P+P)%P;
		A[0]=(x*M[0]+A[0])%P; M[0]=P;
	}
	return A[0];
}
// PolynomialMod[Product[If[Mod[i,5]>0,5^4*x+i,1],{i,1,5^4}],3125]
int calc(int x,int d){
	switch(d){
		case 0: return x%5?x%P:1;
		case 1: return (24+250*x+875*x%P*x+1250*x%P*x%P*x+625*x%P*x%P*x%P*x)%P;
		case 2: return 124;
		case 3: return 624;
		case 4:
		case 5: return 3124;
	}
	return 0;
}
int get(int l,int r,int d){
	if (l>r||d<0)return 1;
	int mod=pow(5,d),l0=(l-1)/mod+1,r0=(r+1)/mod,res=1;
	for (int i=l0;i<r0;++i)res=res*calc(i,d)%P;
	if (l0<r0)return res*get(l,l0*mod-1,d-1)%P*get(r0*mod,r,d-1)%P;
	else return get(l,r,d-1);
}
string abbreviateProduct1(int left, int right) {  // brute force
    long long suff = 1, c = 0, total = 0, max_suff = 100000000000LL;
    double pref = 1.0;
    for (int i = left; i <= right; ++i) {
        pref *= i;
        suff *= i;
        while (pref >= 100000) {
            pref /= 10;
            total = total == 0 ? 6 : total + 1; 
        }
        while (suff % 10 == 0) {
            suff /= 10;
            ++c;
        }
        suff %= max_suff;
    }
    string s = to_string(suff);
    return to_string((int)pref) + (total - c <= 10 ? "" : "...") 
    	+ (total - c < 5 ? "" : s.substr(s.size() - min(5LL, total - c - 5))) + "e" + to_string(c);
}
class Solution {
public:
	string abbreviateProduct(int l, int r) {
		if (r-l<20)return abbreviateProduct1(l,r);
		int last=1,l0=l,r0=r,zeros=0;
		while (l0<=r0){
			last=last*get(l0,r0,5)%P;
			l0=(l0-1)/5+1; r0/=5;
			zeros+=r0-l0+1;
		}
		last=last*exp(inv2,zeros,P)%P;
		int A[]={0,last},M[]={32,3125};
		last=Chinese_Remainder_Theorem(A,M,2);
		char str1[15]; sprintf(str1,"%05d",last);
		return to_string(leading(l,r))+"..."+string(str1)+"e"+to_string(zeros);
	}
};

