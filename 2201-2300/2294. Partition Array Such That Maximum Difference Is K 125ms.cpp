const int U=100005,inf=~0u>>1;
vector<int> v[U];
class Solution {
public:
	int partitionArray(vector<int>& _a, int k) {
		int n=_a.size(),*a=&_a[0],ans=0; ++k;
		for (int i=0;i<n;++i)v[a[i]/k].push_back(a[i]);
		for (int i=0;i<n;++i)
			if (!v[a[i]/k].empty()){
				int j=a[i]/k;
				while (j&&!v[j-1].empty())--j;
				int *p=&v[j][0],x=*min_element(p,p+v[j].size());
				for (;;){
					++ans; v[j].clear();
					if (v[++j].empty())break;
					int nxt=inf; p=&v[j][0];
					for (int *end=p+v[j].size();p!=end;++p)
						if (*p<nxt&&*p>=x+k)nxt=*p;
					if (nxt==inf){
						v[j].clear();
						if (v[++j].empty())break;
						p=&v[j][0]; nxt=*min_element(p,p+v[j].size());
					}
					x=nxt;
				}
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

