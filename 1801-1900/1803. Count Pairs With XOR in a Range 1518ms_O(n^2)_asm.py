import time
from ctypes import *
import mmap

#https://defuse.ca/online-x86-assembler.htm#disassembly2
def translate(s):
    res=b''
    for l in s.split('\n'):
        if (not ':' in l) or (not '   ' in l): continue
        #l=l[l.find(':')+1:l.find('   ')].strip()
        l=l[l.find(':')+1:].strip()
        l=l[:l.find('   ')].strip()
        for b in l.split(' '):
            res+=int(b,16).to_bytes(1,byteorder='little')
    return res

def compile_asm(s,ftype):
    global buf
    buf=mmap.mmap(-1,mmap.PAGESIZE,prot=mmap.PROT_READ|mmap.PROT_WRITE|mmap.PROT_EXEC)
    fpointer=c_void_p.from_buffer(buf)
    buf.write(translate(s))
    return ftype(addressof(fpointer))

#order: edi,esi,edx,ecx,r8d
#-Ofast
asm_xor_in=compile_asm('''
0:  85 f6                   test   esi,esi
2:  0f 8e 07 01 00 00       jle    10f <L7>
8:  8d 46 ff                lea    eax,[rsi-0x1]
b:  49 89 f9                mov    r9,rdi
e:  89 d7                   mov    edi,edx
10: 83 f8 02                cmp    eax,0x2
13: 0f 86 f9 00 00 00       jbe    112 <L8>
19: 66 0f 6e fa             movd   xmm7,edx
1d: 89 f2                   mov    edx,esi
1f: 66 0f ef d2             pxor   xmm2,xmm2
23: 4c 89 c8                mov    rax,r9
26: 66 0f 70 f7 00          pshufd xmm6,xmm7,0x0
2b: c1 ea 02                shr    edx,0x2
2e: 66 0f 6e f9             movd   xmm7,ecx
32: 66 0f 6f da             movdqa xmm3,xmm2
36: 66 0f 70 ef 00          pshufd xmm5,xmm7,0x0
3b: 48 c1 e2 04             shl    rdx,0x4
3f: 66 41 0f 6e f8          movd   xmm7,r8d
44: 66 0f 70 e7 00          pshufd xmm4,xmm7,0x0
49: 4c 01 ca                add    rdx,r9
000000000000004c <L5>:
4c: f3 0f 6f 00             movdqu xmm0,XMMWORD PTR [rax]
50: 66 0f 6f cd             movdqa xmm1,xmm5
54: 48 83 c0 10             add    rax,0x10
58: 66 0f ef c6             pxor   xmm0,xmm6
5c: 66 0f 66 c8             pcmpgtd xmm1,xmm0
60: 66 0f 66 c4             pcmpgtd xmm0,xmm4
64: 66 0f 76 cb             pcmpeqd xmm1,xmm3
68: 66 0f 76 c3             pcmpeqd xmm0,xmm3
6c: 66 0f db c1             pand   xmm0,xmm1
70: 66 0f fa d0             psubd  xmm2,xmm0
74: 48 39 d0                cmp    rax,rdx
77: 75 d3                   jne    4c <L5>
79: 66 0f 6f c2             movdqa xmm0,xmm2
7d: 89 f2                   mov    edx,esi
7f: 66 0f 73 d8 08          psrldq xmm0,0x8
84: 83 e2 fc                and    edx,0xfffffffc
87: 66 0f fe d0             paddd  xmm2,xmm0
8b: 66 0f 6f c2             movdqa xmm0,xmm2
8f: 66 0f 73 d8 04          psrldq xmm0,0x4
94: 66 0f fe d0             paddd  xmm2,xmm0
98: 66 0f 7e d0             movd   eax,xmm2
9c: 40 f6 c6 03             test   sil,0x3
a0: 74 6c                   je     10e <L13>
00000000000000a2 <L3>:
a2: 4c 63 d2                movsxd r10,edx
a5: 53                      push   rbx
a6: 47 8b 1c 91             mov    r11d,DWORD PTR [r9+r10*4]
aa: 41 31 fb                xor    r11d,edi
ad: 41 39 cb                cmp    r11d,ecx
b0: 0f 9d c3                setge  bl
b3: 45 31 d2                xor    r10d,r10d
b6: 45 39 c3                cmp    r11d,r8d
b9: 41 0f 9e c2             setle  r10b
bd: 41 21 da                and    r10d,ebx
c0: 44 01 d0                add    eax,r10d
c3: 44 8d 52 01             lea    r10d,[rdx+0x1]
c7: 44 39 d6                cmp    esi,r10d
ca: 7e 40                   jle    10c <L1>
cc: 4d 63 d2                movsxd r10,r10d
cf: 47 8b 1c 91             mov    r11d,DWORD PTR [r9+r10*4]
d3: 41 31 fb                xor    r11d,edi
d6: 44 39 d9                cmp    ecx,r11d
d9: 0f 9e c3                setle  bl
dc: 45 31 d2                xor    r10d,r10d
df: 45 39 d8                cmp    r8d,r11d
e2: 41 0f 9d c2             setge  r10b
e6: 83 c2 02                add    edx,0x2
e9: 41 21 da                and    r10d,ebx
ec: 44 01 d0                add    eax,r10d
ef: 39 d6                   cmp    esi,edx
f1: 7e 19                   jle    10c <L1>
f3: 48 63 d2                movsxd rdx,edx
f6: 41 33 3c 91             xor    edi,DWORD PTR [r9+rdx*4]
fa: 41 39 f8                cmp    r8d,edi
fd: 40 0f 9d c6             setge  sil
101:    31 d2                   xor    edx,edx
103:    39 f9                   cmp    ecx,edi
105:    0f 9e c2                setle  dl
108:    21 f2                   and    edx,esi
10a:    01 d0                   add    eax,edx
000000000000010c <L1>:
10c:    5b                      pop    rbx
10d:    c3                      ret
000000000000010e <L13>:
10e:    c3                      ret
000000000000010f <L7>:
10f:    31 c0                   xor    eax,eax
111:    c3                      ret
0000000000000112 <L8>:
112:    31 d2                   xor    edx,edx
114:    31 c0                   xor    eax,eax
116:    eb 8a                   jmp    a2 <L3>
''',CFUNCTYPE(c_int,POINTER(c_int),c_int,c_int,c_int))

class Solution:
    def countPairs(self, nums: List[int], l: int, r: int) -> int:
        n,ans=len(nums),0
        a=(c_int*n)(*nums)
        for i in range(n):
            a1=cast(addressof(a)+4*(i+1),POINTER(c_int))
            ans+=asm_xor_in(a1,n-i-1,a[i],l,r)
        return ans
