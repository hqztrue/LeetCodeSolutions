const int N=5005;
int c[N],ans[N],t1[N],n;
int interpolation_search(int *a,int n,int x){
	if (a[n]<x)return n+1;
	if (a[1]>=x)return 1;
	int l=1,r=n;
	while (l<r){
		int m=l+double(r-l-1)*(x-a[l])/(a[r]-a[l]);
		if (a[m]>=x)r=m;
		else if (a[m+1]<x)l=m+1;
		else return m+1;
	}
	return l;
}
class TopVotedCandidate {
public:
	TopVotedCandidate(vector<int>& p, vector<int>& t) {
		int cur=0; n=p.size();
		for (int i=0;i<n;++i){
			int x=p[i];
			if (++c[x]>=cur)cur=c[x],ans[i]=x;
			else ans[i]=ans[i-1];
		}
		memcpy(t1,&t[0],sizeof(int)*n);
	}
	int q(int t) {
		//return ans[upper_bound(t1,t1+n,t)-t1-1];
		return ans[interpolation_search((int*)t1-1,n,t+1)-2];
	}
	~TopVotedCandidate(){
		memset(c,0,sizeof(int)*n);
	}
};

/**
 * Your TopVotedCandidate object will be instantiated and called as such:
 * TopVotedCandidate* obj = new TopVotedCandidate(persons, times);
 * int param_1 = obj->q(t);
 */

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

