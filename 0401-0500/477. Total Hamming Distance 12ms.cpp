const int L=16,W=32;
class Solution {
public:
	void add(int *a,int *b,int m){
		int t=0;
		for (int i=0;i<m;++i){
			int t1=a[i]^b[i]^t;
			t=a[i]&(b[i]|t)|b[i]&t;
			a[i]=t1;b[i]=0;
		}
		a[m]=t;
	}
	int totalHammingDistance(vector<int>& a){
		static int c_[L*L*2]; memset(c_,0,sizeof(c_));
		int *c[L],*c1=c_;
		for (int i=0;i<L;++i)c[i]=c1,c1+=i+2;
		int n=a.size();
		for (int i=0;i<n;++i){
			add(c[0],&a[i],1);
			for (int j=0;((i+1)&(1<<j))==0;++j)add(c[j+1],c[j],j+2);
		}
		for (int i=0;i<L-1;++i)add(c[i+1],c[i],i+2);
		int ans=0;
		for (int i=0;i<W-1;++i){
			int s=0;
			for (int j=0;j<L;++j)s+=((c[L-1][j]>>i)&1)<<j;
			ans+=s*(n-s);
		}
		return ans;
	}
};

