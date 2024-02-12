class Solution {
public:
    int minimumTimeToInitialState(string w, int k) {
        int n=w.size(),m=1; char *s=&w[0];
        for (;k*m<n && memcmp(s,s+k*m,n-k*m);++m);
        return m;
    }
};
