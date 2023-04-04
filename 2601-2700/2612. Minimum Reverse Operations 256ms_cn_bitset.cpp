const int N=100005;
bitset<N/2> bs[2]; 
class Solution {
public:
    vector<int> minReverseOperations(int n, int p, vector<int>& b, int k) {
    	vector<int> ans(n);
        for (int i=0;i<n;++i)ans[i]=-1,bs[i&1][i/2]=1;
		for (auto &x:b)bs[x&1][x/2]=0;
		int q[n],h=0,t=1; q[0]=p; ans[p]=0; bs[p&1][p/2]=0;
		while (h<t){
			int x=q[h++],d=ans[x],l=max(k-1-x,x-k+1),r=min(n*2-k-x-1,x+k-1);
			for (int j=bs[l&1]._Find_next(l/2-1);j<=r/2;j=bs[l&1]._Find_next(j))
				ans[j*2+(l&1)]=d+1,bs[l&1][j]=0,q[t++]=j*2+(l&1);
		}
		return ans;
    }
};
