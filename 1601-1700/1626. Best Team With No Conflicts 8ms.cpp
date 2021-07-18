const int N=1005;
int f[N],id[N],*_s,*_a;
inline int get(int i){
	int res=0;
	for (;i;i-=i&-i)res=max(res,f[i]);
	return res;
}
inline void upd(int i,int x){
	for (;i<N;i+=i&-i)f[i]=max(f[i],x);
}
inline bool cmp(int i,int j){return _s[i]==_s[j]?_a[i]<_a[j]:_s[i]<_s[j];}
class Solution {
public:
	int bestTeamScore(vector<int>& s, vector<int>& a) {
		int n=a.size(),ans=0; _s=&s[0]; _a=&a[0];
		iota(id,id+n,0); sort(id,id+n,cmp);
		memset(f,0,sizeof(f));
		for (int i=0;i<n;++i){
			int t=id[i],v=get(a[t])+s[t];
			ans=max(ans,v); upd(a[id[i]],v);
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

