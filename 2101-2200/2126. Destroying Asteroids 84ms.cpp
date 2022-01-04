const int M=17,U=100005;
int v[M],s[M];
class Solution {
public:
	bool asteroidsDestroyed(int m, vector<int>& a) {
		int n=a.size();
		for (int i=0;i<M;++i)v[i]=U,s[i]=0;
		for (int x:a){
			int t=31-__builtin_clz(x);
			v[t]=min(v[t],x); s[t]=min(s[t]+x,U);
		}
		for (int i=0;i<M;++i){
			if (v[i]<U&&v[i]>m)return 0;
			m+=s[i];
		}
		return 1;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

