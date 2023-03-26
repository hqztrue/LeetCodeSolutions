class Solution:
    def collectTheCoins(self, c: List[int], e: List[List[int]]) -> int:
        n=len(c)
        d=[set() for i in range(n)]
        for x,y in e: d[x].add(y),d[y].add(x)
        q={i for i in range(n) if len(d[i])==1 and c[i]==0}
        while q:
            x=q.pop()
            for y in d[x]:
                d[y].remove(x)
                if len(d[y])==1 and c[y]==0: q.add(y)
            d[x].clear()
        for T in range(2):
            q=[i for i in range(n) if len(d[i])==1]
            for x in q:
                for y in d[x]: d[y].remove(x)
                d[x].clear()
        return (max(sum(len(d[i])>0 for i in range(n)),1)-1)*2
