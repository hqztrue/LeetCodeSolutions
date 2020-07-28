inline int _rand(){static unsigned int x=31253125;x+=(x<<4)+(x<<21)+1;x&=0x7fffffff;return x;}
int interpolation_search(int a[],int n,int x){
	if (a[n]<x)return n+1;
	if (a[1]>=x)return 1;
	int l=1,r=n;
	while (l<r){
		int m=l+double(r-l-1)*(x-a[l])/(a[r]-a[l]);
		if (a[m]>=x)r=m;
		else if (a[m+1]<x)l=m+1;
		else return m+1;
	}
	return l;
}
class Solution {
public:
    int search(vector<int>& nums, int t) {
        int n=nums.size(),p=interpolation_search(&nums[0]-1,n,t);
        return p<=n&&nums[p-1]==t?p-1:-1;
    }
};

