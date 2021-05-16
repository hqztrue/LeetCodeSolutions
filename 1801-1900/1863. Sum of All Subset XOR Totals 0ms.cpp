class Solution {
public:
	int subsetXORSum(vector<int>& a) {
		int t=~0u>>1; for (auto i:a)t|=i;
		return __builtin_popcount(t)<<(a.size()-1);
	}
};

