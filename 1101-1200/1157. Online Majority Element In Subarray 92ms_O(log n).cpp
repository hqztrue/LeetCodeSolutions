const int N=20005;
vector<int> V[N]; int id[N],*a,n;
inline int _rand(){static unsigned int x=31253125;x+=(x<<4)+1;return x&=0x7fffffff;}  //x+=(x<<4)+(x<<21)+1;
class MajorityChecker {
public:
	MajorityChecker(vector<int>& a) {
		::a=&a[0]; n=a.size();
		for (int i=0;i<n;++i)V[a[i]].clear();
		for (int i=0;i<n;++i)id[i]=V[a[i]].size(),V[a[i]].push_back(i);
	}
	int query(int l,int r,int t) {
		static const int M=7;  //O(log n)
		int m=r-l+1,m1=(m+2)/4,val=0;
		for (int i=0;i<M;++i){
			int j=l+_rand()%(r-l+1);
			vector<int> &v=V[a[j]];
			int k=id[j],s=v.size();
			if ((k+m1>=s||v[k+m1]>r)&&(k-m1<0||v[k-m1]<l))continue;
			if (a[j]==val)continue;
			int *p=lower_bound(&v[0],&v[0]+s,l)+t-1;
			if (p<&v[0]+s&&*p<=r)return a[j];
			if (val)return -1; else val=a[j];
		}
		return -1;
	}
};

//IO
int _IO=[](){
	std::ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

