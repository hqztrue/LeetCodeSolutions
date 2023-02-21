U=30; P=1000000007
v=[1]*(U+1); p=[]
for i in range(2,U+1):
    if v[i]:
        p.append(i)
        for j in range(i+i,U+1,i): v[j]=0
p1=len(p); p2=bisect_right(p,int(U**0.5))
mask=[0]*(U+1)
for i in range(2,U+1):
    for j,p0 in enumerate(p):
        if i%p0==0:
            if i%(p0*p0)==0:
                mask[i]=0
                break
            mask[i]|=1<<j
class Solution:
    def squareFreeSubsets(self, nums: List[int]) -> int:
        cnt=Counter(nums)
        f=[0]*(1<<p2)
        f[0]=1
        d=defaultdict(list)
        def upd(f,f1,m):
            j=other=((1<<p2)-1)^m
            while True:
                f[j|m]=(f[j|m]+f1[j]*c)%P
                j=(j-1)&other
                if j==other: break
        for x,c in cnt.items():
            m=mask[x]
            if m:
                if m>>p2:
                    p_large=p[m.bit_length()-1]
                    d[p_large].append((x//p_large,c))
                else: upd(f,f,m)
        for _,l in d.items():
            f1=f.copy()
            for x,c in l: upd(f,f1,mask[x])
        return (sum(f)*pow(2,cnt[1],P)-1)%P
