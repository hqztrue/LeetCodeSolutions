#O(n^2*k*|Σ|)
import numpy as np
class Solution:
    def getLengthOfOptimalCompression(self, s: str, k: int) -> int:
        if len(s) <= k: return 0
        f=np.full((len(s),k+1,26,len(s)+1),10000)
        f[0][0][ord(s[0])-ord('a')][1] = 1
        for i in range(1, len(s)):
            if i <= k:
                f[i][i][ord(s[i])-ord('a')][1] = 1  # delete all items before
            s1=ord(s[i])
            end=min(len(s)+1, i+2)
            _c=s1-97
            for j in range(min(k+1, i+1)):
                # not delete s[i]
                # l != 1
                g=f[i][j][_c]
                h=f[i-1][j][_c]
                if end<10:
                    g[3:end]=np.minimum(g[3:end],h[2:end-1])
                else:
                    g[3:10]=np.minimum(g[3:10],h[2:9])
                    g[11:end]=np.minimum(g[11:end],h[10:end-1])
                if end>2:f[i][j][_c][2] = min(f[i-1][j][_c][2-1]+1, f[i][j][_c][2])
                if end>10:f[i][j][_c][10] = min(f[i-1][j][_c][10-1]+1, f[i][j][_c][10])
                if end>100:f[i][j][_c][100] = min(f[i-1][j][_c][100-1]+1, f[i][j][_c][100])
                # l == 1
                t=int(f[i][j][_c][1])
                h=f[i-1][j]
                if _c>0:t=min(t,np.amin(h[0:_c])+1)
                if _c+1<26:t=min(t,np.amin(h[_c+1:26])+1)
                f[i][j][_c][1]=t
                # delete s[i]
                if j >= 1:
                    g=f[i][j]
                    h=f[i-1][j-1]
                    g[:][:]=np.minimum(g[:][:],h[:][:])
        ans = 10000
        for ch in range(26):
            for l in range(1, len(s)+1):
                ans = min(ans, f[len(s)-1][k][ch][l])
        return ans

