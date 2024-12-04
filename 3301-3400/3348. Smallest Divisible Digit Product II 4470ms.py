c=[[],[0,0,0,0],[1,0,0,0],[0,1,0,0],[2,0,0,0],[0,0,1,0],[1,1,0,0],[0,0,0,1],[3,0,0,0],[0,2,0,0]]
class Solution:
    def smallestNumber(self, a: str, t: int) -> str:
        cnt=[0]*4
        for i,p in enumerate([2,3,5,7]):
            while t%p==0: cnt[i]+=1; t/=p
        if t>1: return "-1"
        a=list(map(int,a))[::-1]
        def getlen(cnt):
            return cnt[2]+cnt[3]+min(1+(cnt[0]+1)//3+cnt[1]//2,(cnt[0]+2)//3+(cnt[1]+1)//2)
        def dfs(d,cnt,flag):
            for i in range(1,10):
                if not flag and i<a[d]: continue
                ans[d]=i
                cnt1=[max(0,cnt[j]-c[i][j]) for j in range(4)]
                if getlen(cnt1)<=d and (not d or dfs(d-1,cnt1,flag or i>a[d])): return True
        for i in range(0,100):
            ans=[0]*(len(a)+i)
            if dfs(len(ans)-1,cnt,i>0): return "".join(map(str,ans))[::-1]
