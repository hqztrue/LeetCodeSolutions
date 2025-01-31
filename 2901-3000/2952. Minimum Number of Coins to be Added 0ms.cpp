const int W=18,inf=~0u>>3;
int mi[W],sum[W];
class Solution {
public:
    int minimumAddedCoins(vector<int>& _a, int t) {
        int *a=&_a[0],n=_a.size(),ans=0,s=0;
        fill(mi,mi+W,inf);
        fill(sum,sum+W,0);
        for (int i=0;i<n;++i){
            int x=a[i],w=31-__builtin_clz(x);
            if (sum[w]<t)sum[w]+=x;
            if (x<mi[w])mi[w]=x;
        }
        for (int i=0;i<W;++i){
            int v=mi[i];
            while (v!=inf&&s<t&&s+1<v)++ans,s+=s+1;
            s+=sum[i];
        }
        while (s<t)++ans,s+=s+1;
        return ans;
    }
};
