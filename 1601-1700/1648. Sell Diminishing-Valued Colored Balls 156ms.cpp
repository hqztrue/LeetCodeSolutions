typedef long long ll;
const int P=1000000007;
int tot,val; ll num,ans;
template<class T>
void Q(T a[],int s,int t){
	if (s>t){
		int x=tot/num;
		ans+=num*(val*2-x+1)*x/2;
		ans+=tot%num*(val-x);
		return;
	}
	int i=s,j=t,tmp,m=a[s+rand()%(t-s+1)];
	do {
		while (a[i]<m)++i;
		while (a[j]>m)--j;
		if (i<=j){
			tmp=a[i]; a[i]=a[j]; a[j]=tmp;
			++i; --j;
		}
	}while (i<=j);
	ll c=num*(val-m)-(ll)m*(t-j);
	for (int k=j+1;k<=t;++k)c+=a[k];
	if (c<=tot){
		tot-=c; ans+=num*(val+m+1)*(val-m)/2;
		for (int k=j+1;k<=t;++k)ans+=(ll)(a[k]+m+1)*(a[k]-m)/2;
		val=m; num+=t-j;
		Q(a,s,j);
	}
	else {
		if (a[j+1]==m)++j;
		Q(a,j+1,t);
	}
}
class Solution {
public:
	int maxProfit(vector<int>& a, int orders) {
		int n=a.size(); tot=orders; ans=0; num=0;
		Q(&a[0],0,n-1);
		return ans%P;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();


