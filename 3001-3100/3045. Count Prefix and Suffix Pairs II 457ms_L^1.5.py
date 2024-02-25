class Solution:
    def countPrefixSuffixPairs(self, w: List[str]) -> int:
        ans=0
        d=defaultdict(int)
        for s in w:
            for j in range(1,len(s)+1):
                if j in d and s[:j]==s[-j:]: ans+=d[s[:j]]
            d[s]+=1; d[len(s)]=1
        return ans
