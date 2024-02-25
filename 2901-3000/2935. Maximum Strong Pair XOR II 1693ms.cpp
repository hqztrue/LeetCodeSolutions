#define unlikely(x) __builtin_expect(!!(x), 0)
class Solution {
public:
    __attribute__((no_sanitize_address,no_sanitize_memory))
    int maximumStrongPairXor(vector<int>& nums) {
        int *a=&nums[0],n=nums.size(),ans=0,ans1=0;
        sort(a,a+n);
        for (int i=n-1;i;--i){
            int x=a[i],mi=(x+1)/2,t=0;
            while ((x^t)<ans)t|=1<<(31-__builtin_clz(x^t^ans));
            mi=max(mi,t);
            int *p=lower_bound(a,a+i,mi);
            for (int *end=a+i;p<end;p+=2){
                if (unlikely((x^*p)>ans))ans=x^*p;
                if (unlikely((x^*(p+1))>ans1))ans1=x^*(p+1);
            }
        }
        ans=max(ans,ans1);
        return ans;
    }
};
