import time
from ctypes import *
import mmap

def translate(s):
    res=b''
    for l in s.split('\n'):
        if not ':' in l or '>:' in l: continue
        l=l[l.find(':')+1:].strip()
        l=l[:l.find('   ')].strip()
        for b in l.split(' '):
            res+=int(b,16).to_bytes(1,byteorder='little')
    return res

def compile_asm(s,ftype):
    global buf
    buf=mmap.mmap(-1,mmap.PAGESIZE,prot=mmap.PROT_READ|mmap.PROT_WRITE|mmap.PROT_EXEC)
    buf.write(translate(s))
    return ftype(addressof(c_void_p.from_buffer(buf)))

#-Ofast -mavx -mavx2
asm_xor_in=compile_asm('''
0:  85 f6                   test   esi,esi
2:  7e 12                   jle    16 <LBB0_1>
4:  41 89 f1                mov    r9d,esi
7:  83 fe 20                cmp    esi,0x20
a:  73 0d                   jae    19 <LBB0_4>
c:  45 31 db                xor    r11d,r11d
f:  31 c0                   xor    eax,eax
11: e9 f5 00 00 00          jmp    10b <LBB0_7>
0000000000000016 <LBB0_1>:
16: 31 c0                   xor    eax,eax
18: c3                      ret
0000000000000019 <LBB0_4>:
19: 45 89 cb                mov    r11d,r9d
1c: 41 83 e3 e0             and    r11d,0xffffffe0
20: c5 f9 6e c2             vmovd  xmm0,edx
24: c4 e2 7d 58 c0          vpbroadcastd ymm0,xmm0
29: c5 f9 6e c9             vmovd  xmm1,ecx
2d: c4 e2 7d 58 c9          vpbroadcastd ymm1,xmm1
32: c4 c1 79 6e d0          vmovd  xmm2,r8d
37: c4 e2 7d 58 d2          vpbroadcastd ymm2,xmm2
3c: 4e 8d 14 8d 00 00 00    lea    r10,[r9*4+0x0]
43: 00
44: 49 83 e2 80             and    r10,0xffffffffffffff80
48: c5 e1 ef db             vpxor  xmm3,xmm3,xmm3
4c: 31 c0                   xor    eax,eax
4e: c5 dd 76 e4             vpcmpeqd ymm4,ymm4,ymm4
52: c5 d1 ef ed             vpxor  xmm5,xmm5,xmm5
56: c5 c9 ef f6             vpxor  xmm6,xmm6,xmm6
5a: c5 c1 ef ff             vpxor  xmm7,xmm7,xmm7
000000000000005e <LBB0_5>:
5e: c5 7d ef 04 07          vpxor  ymm8,ymm0,YMMWORD PTR [rdi+rax*1]
63: c5 7d ef 4c 07 20       vpxor  ymm9,ymm0,YMMWORD PTR [rdi+rax*1+0x20]
69: c5 7d ef 54 07 40       vpxor  ymm10,ymm0,YMMWORD PTR [rdi+rax*1+0x40]
6f: c5 7d ef 5c 07 60       vpxor  ymm11,ymm0,YMMWORD PTR [rdi+rax*1+0x60]
75: c4 41 75 66 e0          vpcmpgtd ymm12,ymm1,ymm8
7a: c4 41 75 66 e9          vpcmpgtd ymm13,ymm1,ymm9
7f: c4 41 75 66 f2          vpcmpgtd ymm14,ymm1,ymm10
84: c4 41 75 66 fb          vpcmpgtd ymm15,ymm1,ymm11
89: c5 3d 66 c2             vpcmpgtd ymm8,ymm8,ymm2
8d: c5 3d ef c4             vpxor  ymm8,ymm8,ymm4
91: c4 41 1d df c0          vpandn ymm8,ymm12,ymm8
96: c4 c1 65 fa d8          vpsubd ymm3,ymm3,ymm8
9b: c5 35 66 c2             vpcmpgtd ymm8,ymm9,ymm2
9f: c5 3d ef c4             vpxor  ymm8,ymm8,ymm4
a3: c4 41 15 df c0          vpandn ymm8,ymm13,ymm8
a8: c4 c1 55 fa e8          vpsubd ymm5,ymm5,ymm8
ad: c5 2d 66 c2             vpcmpgtd ymm8,ymm10,ymm2
b1: c5 3d ef c4             vpxor  ymm8,ymm8,ymm4
b5: c4 41 0d df c0          vpandn ymm8,ymm14,ymm8
ba: c4 c1 4d fa f0          vpsubd ymm6,ymm6,ymm8
bf: c5 25 66 c2             vpcmpgtd ymm8,ymm11,ymm2
c3: c5 3d ef c4             vpxor  ymm8,ymm8,ymm4
c7: c4 41 05 df c0          vpandn ymm8,ymm15,ymm8
cc: c4 c1 45 fa f8          vpsubd ymm7,ymm7,ymm8
d1: 48 83 e8 80             sub    rax,0xffffffffffffff80
d5: 49 39 c2                cmp    r10,rax
d8: 75 84                   jne    5e <LBB0_5>
da: c5 d5 fe c3             vpaddd ymm0,ymm5,ymm3
de: c5 cd fe c0             vpaddd ymm0,ymm6,ymm0
e2: c5 c5 fe c0             vpaddd ymm0,ymm7,ymm0
e6: c4 e3 7d 39 c1 01       vextracti128 xmm1,ymm0,0x1
ec: c5 f9 fe c1             vpaddd xmm0,xmm0,xmm1
f0: c5 f9 70 c8 ee          vpshufd xmm1,xmm0,0xee
f5: c5 f9 fe c1             vpaddd xmm0,xmm0,xmm1
f9: c5 f9 70 c8 55          vpshufd xmm1,xmm0,0x55
fe: c5 f9 fe c1             vpaddd xmm0,xmm0,xmm1
102:    c5 f9 7e c0             vmovd  eax,xmm0
106:    4d 39 cb                cmp    r11,r9
109:    74 24                   je     12f <LBB0_8>
000000000000010b <LBB0_7>:
10b:    42 8b 34 9f             mov    esi,DWORD PTR [rdi+r11*4]
10f:    31 d6                   xor    esi,edx
111:    39 ce                   cmp    esi,ecx
113:    41 0f 9d c2             setge  r10b
117:    44 39 c6                cmp    esi,r8d
11a:    40 0f 9e c6             setle  sil
11e:    44 20 d6                and    sil,r10b
121:    40 0f b6 f6             movzx  esi,sil
125:    01 f0                   add    eax,esi
127:    49 ff c3                inc    r11
12a:    4d 39 d9                cmp    r9,r11
12d:    75 dc                   jne    10b <LBB0_7>
000000000000012f <LBB0_8>:
12f:    c5 f8 77                vzeroupper
132:    c3                      ret
''',CFUNCTYPE(c_int,POINTER(c_int),c_int,c_int,c_int))

class Solution:
    def countPairs(self, nums: List[int], l: int, r: int) -> int:
        n,ans=len(nums),0
        a=(c_int*n)(*nums)
        for i in range(n):
            a1=cast(addressof(a)+4*(i+1),POINTER(c_int))
            ans+=asm_xor_in(a1,n-i-1,a[i],l,r)
        return ans
