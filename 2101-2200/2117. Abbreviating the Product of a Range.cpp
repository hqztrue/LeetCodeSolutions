#include<bits/stdc++.h>
using namespace std;
typedef __float128 D;
const D PI=3.1415926535897932384626433832795028841971Q,
	E=2.7182818284590452353602874713526624977572Q;
void print(__float128 x,int K=35){
	if (x<0){printf("-");x=-x;}
	int y=0,t;
	while (x>=1)x*=0.1Q,++y;
	if (!y)printf("0.");
	for (int i=1;i<=max(y,K);++i){
		x*=10; t=(int)x;
		if (x<t)--t;
		else if (x>=t+1)++t;
		printf("%d",t);
		if (i==y)printf(".");
		x-=t;
	}
	printf("\n");
}
inline __float128 sqrt(__float128 x){
	__float128 f=1.5Q,x1=x*0.5Q,y=1.Q/sqrt((double)x);
	for (int i=1;i<=4;++i)y=y*(f-x1*y*y);
	return x*y;
}
inline __float128 exp(__float128 x){
	if (x<0)return 1/exp(-x);
	int t=0; for (;x>1e-5;++t)x/=2;
	__float128 ans=0,y=x;
	for (int i=1;i<=7;++i,y*=x/i)ans+=y;
	while (t--)ans=ans*2+ans*ans;
	return ans+1;
}
inline __float128 log(__float128 x){
	if (x<1)return -log(1/x);
	int t=0; for (x-=1;x>1e-5;++t)x=x/(sqrt(x+1)+1);
	__float128 ans=0,y=x;
	for (int i=1;i<=7;++i,y*=-x)ans+=y/i;
	ans*=1<<t;
	return ans;
}
inline __float128 pow(__float128 x,__float128 y){return exp(y*log(x));}
const D B[]={1,D(1)/2,D(1)/6,0,-D(1)/30,0,D(1)/42,0,-D(1)/30,0,D(5)/66,0,
	-D(691)/2730,0,D(7)/6,0,-D(3617)/510,0,D(43867)/798,0,-D(174611)/330};
const int M=10;
D log_fac(D n){
	D ans=0;
	if (n>20){
		ans=n*log(n/E)+log(n)/2+log(sqrt(PI*2));
		for (int i=2;i<=M;++i)ans+=(i%2?-1:1)*B[i]/(D(i)*(i-1)*pow(n,D(i-1)));
	}
	else for (int i=1;i<=n;++i)ans+=log(D(i));
	return ans;
}
int leading(int l,int r){
	D t=log_fac(r)-log_fac(l-1);
	t/=log(10.Q); t-=int(t)-4;
	return pow(10.Q,t);
}
class Solution {
public:
	string abbreviateProduct(int l, int r) {
		
		return "";
	}
};

