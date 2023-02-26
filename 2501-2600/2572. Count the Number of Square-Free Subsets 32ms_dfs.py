U=30; P=1000000007
v=[1]*(U+1); p=[]
for i in range(2,U+1):
    if v[i]:
        p.append(i)
        for j in range(i+i,U+1,i): v[j]=0
class Solution:
    def squareFreeSubsets(self, a):
        c=defaultdict(int)
        for x in a: c[x]+=1
        for p0 in p: c[p0]+=1
        v=[p[0]]
        def dfs(i):
            if i==len(p):
                return reduce(lambda x,y:x*y%P,[c[x] for x in v])
            v.append(p[i])
            ans=dfs(i+1)
            v.pop()
            for j in range(len(v)):
                if v[j]*p[i]<=U:
                    v[j]*=p[i]
                    ans=(ans+dfs(i+1))%P
                    v[j]/=p[i]
            return ans
        return (dfs(1)*(2**c[1])-1)%P
