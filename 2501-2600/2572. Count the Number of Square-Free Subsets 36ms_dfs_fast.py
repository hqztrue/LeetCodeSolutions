U=30; P=1000000007
v=[1]*(U+1); p=[]
for i in range(2,U+1):
    if v[i]:
        p.append(i)
        for j in range(i+i,U+1,i): v[j]=0
p=p[::-1]
class Solution:
    def squareFreeSubsets(self, a):
        c=defaultdict(int)
        for x in a: c[x]+=1
        for p0 in p: c[p0]+=1
        def dfs(p,i,m,s):
            if i==-2:
                if p==[]: return s
                return dfs(p[1:],-1,p[0],s)
            else:
                ans=dfs(p,-2,1,s*c[m]%P)
                for j in range(len(p)-1,i,-1):
                    if m*p[j]<=U: ans=(ans+dfs(p[:j]+p[j+1:],j-1,m*p[j],s))%P
                    else: break
                return ans
        return (dfs(p,-2,1,1)*(2**c[1])-1)%P
