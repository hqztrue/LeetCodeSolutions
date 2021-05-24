class Solution {
public:
	int minOperations(vector<int>& a) {
		int s=0,l=32;
		for (int *p=&a[0],*end=p+a.size();p<end;++p){
			s+=__builtin_popcount(*p);
			l=min(l,__builtin_clz(*p|1));
		}
		return s+31-l;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

