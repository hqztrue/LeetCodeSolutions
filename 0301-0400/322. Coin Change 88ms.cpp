const int N=10005,inf=1<<30;
int D[N];
class Solution {
public:
	int coinChange(vector<int>& v, int t) {
		v.erase(remove_if(v.begin(),v.end(),[=](int x){return x > t;}),v.end());
		sort(v.begin(),v.end(),greater<int>());
		int n=v.size(),u=n?v[0]:0;
		D[0]=0;
		for (int i=1;i<=t;++i){
			D[i]=inf;
			for (int j=0;j<min((int)ceil(2.*u*u/i),n);++j)
				if (v[j]<=i)D[i]=min(D[i],D[i-v[j]]+1);
		}
		return D[t]<inf?D[t]:-1;
	}
};

