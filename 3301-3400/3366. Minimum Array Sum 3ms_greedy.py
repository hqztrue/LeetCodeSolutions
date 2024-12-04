class Solution:
    def minArraySum(self, a: List[int], k: int, op1: int, op2: int) -> int:
        a.sort()
        a1=[x for x in a if x<k]; n1=len(a1)
        a2=[x for x in a if k<=x<2*k-1]; n2=len(a2)
        a3=[x for x in a if x>=2*k-1]; n3=len(a3)
        for i in range(min(op1,n3)): a3[n3-1-i]=(a3[n3-1-i]+1)//2
        op1=max(0,op1-n3)
        for i in range(min(op2,n3)): a3[i]-=k
        op2=max(0,op2-n3)

        i=0
        for i in range(max(0,op1-n2),min(op1-max(0,n2-op2),n1)+1):
            if n1-1-i<0 or n2-(op1-i-1)-1>=n2 or a1[n1-1-i]<=a2[n2-(op1-i-1)-1]-k: break

        for j in range(i): a1[n1-1-j]=(a1[n1-1-j]+1)//2
        t=min(op2,n2-(op1-i))
        for j in range(t): a2[j]-=k
        a2[t:]=sorted(a2[t:],key=lambda x: -(x%2))
        for j in range(min(op2-t,n2-t)): a2[t+j]-=k
        a2=sorted(a2)
        for j in range(op1-i): a2[n2-1-j]=(a2[n2-1-j]+1)//2
        return sum(a1+a2+a3)
