class Solution {
public:
	int countTriples(int n) {
		int ans=0;
		for (int i=1;i*i<n;++i)
			for (int j=i+1;i*i+j*j<=n;++j)
				if (__gcd(i,j)==1&&!(i*j%2))ans+=n/(i*i+j*j);
		return ans*2;
	}
};

