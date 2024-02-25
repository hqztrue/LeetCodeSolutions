class Solution:
    def earliestSecondToMarkIndices(self, a: List[int], c: List[int]) -> int:
        n=len(a); m=len(c); tot=sum(a); s=set()
        for i in range(m):
            c[i]-=1
            if c[i] in s or a[c[i]]==0: c[i]=-1
            s.add(c[i])
        
        def f(n0):
            h=[]
            for i in range(n0,-1,-1):
                if c[i]>=0:
                    heapq.heappush(h,a[c[i]])
                    if len(h)>(n0-i+1)//2:
                        heapq.heappop(h)
            return tot-sum(h)+n<=n0+1-len(h)
        
        ans=bisect_left(range(m),True,key=f)
        return ans+1 if ans<m else -1
