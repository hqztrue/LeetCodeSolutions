const int N=100005,W=32;
typedef unsigned int uint;
template<int N>
struct LinearDisjointSet{
	int f[N/W+2],root[N/W+2],rank[N/W+2]; uint c[N/W+2];
	void init(int n){for (int i=0;i<=n/W+1;++i)f[i]=root[i]=i,c[i]=~0,rank[i]=0;}
	int _find(int x){
		if (f[x]==x)return x;
		else return f[x]=_find(f[x]);
	}
	void _link(int x,int y){
		int f1=_find(x),f2=_find(y);
		if (f1==f2)return;
		if (rank[f1]>rank[f2])f[f2]=f1,root[f1]=root[f2];
		else if (rank[f1]<rank[f2])f[f1]=f2;
		else f[f2]=f1,++rank[f1],root[f1]=root[f2];
	}
	void _del(int x){_link(x,x+1);}
	int find(int x){
		int y=x/W,z=x%W; uint t=c[y]>>z<<z;
		if (t)return y*W+__builtin_ctz(t);
		y=root[_find(y+1)]; return y*W+__builtin_ctz(c[y]);
	}
	void del(int x){int y=x/W;c[y]&=~(1u<<x%W);if (!c[y])_del(y);}
};
LinearDisjointSet<N> D;
class Solution {
public:
	vector<int> avoidFlood(vector<int>& rains) {
		int n=rains.size(),*a=&rains[0]-1;
		vector<int> res(n); unordered_map<int,int> H;
		D.init(n);
		for (int i=1;i<=n;++i)
			if (a[i]){
				D.del(i); res[i-1]=-1;
				unordered_map<int,int>::iterator p=H.find(a[i]);
				if (p!=H.end()){
					int j=D.find(p->second);
					if (j>i)return vector<int>();
					res[j-1]=a[i]; D.del(j); p->second=i;
				}
				else H.insert(make_pair(a[i],i));
			}
			else res[i-1]=1;
		return res;
	}
};

//IO
int _IO=[](){
	std::ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

