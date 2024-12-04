class Solution:
    def maximumTotalSum(self, h: List[int]) -> int:
        cnt=defaultdict(int)
        for x in h: cnt[x]+=1
        to={}
        for x in h:
            if cnt[x]==1: continue
            t=0
            j=x
            while True:
                while j in to: j=to[j]
                if t+cnt[j]==0:
                    to[x]=j
                    break
                if j<=0: return -1
                t+=cnt[j]-1
                cnt[j]=1
                j-=1
        return sum(k for k,v in cnt.items() if v)
