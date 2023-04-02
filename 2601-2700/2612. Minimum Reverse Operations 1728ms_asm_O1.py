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

buf=mmap.mmap(-1,mmap.PAGESIZE,prot=mmap.PROT_READ|mmap.PROT_WRITE|mmap.PROT_EXEC)
def compile_asm(s,ftype):
    buf.write(translate(s))
    return ftype(addressof(c_void_p.from_buffer(buf)))

#https://gcc.godbolt.org/
#https://defuse.ca/online-x86-assembler.htm
#order: edi,esi,edx,ecx,r8d

#sum x in a
asm_calc=compile_asm('''
0:  55                      push   rbp
1:  48 89 e5                mov    rbp,rsp
4:  41 57                   push   r15
6:  41 56                   push   r14
8:  41 55                   push   r13
a:  41 54                   push   r12
c:  53                      push   rbx
d:  48 83 ec 08             sub    rsp,0x8
11: 41 89 f5                mov    r13d,esi
14: 89 d6                   mov    esi,edx
16: 48 89 cb                mov    rbx,rcx
19: 45 89 c4                mov    r12d,r8d
1c: 45 85 ed                test   r13d,r13d
1f: 7e 19                   jle    3a <L2>
21: 48 89 f8                mov    rax,rdi
24: 49 63 d5                movsxd rdx,r13d
27: 48 8d 14 97             lea    rdx,[rdi+rdx*4]
000000000000002b <L3>:
2b: c7 00 ff ff ff ff       mov    DWORD PTR [rax],0xffffffff
31: 48 83 c0 04             add    rax,0x4
35: 48 39 d0                cmp    rax,rdx
38: 75 f1                   jne    2b <L3>
000000000000003a <L2>:
3a: 45 85 e4                test   r12d,r12d
3d: 7e 1d                   jle    5c <L4>
3f: 48 89 d8                mov    rax,rbx
42: 49 63 d4                movsxd rdx,r12d
45: 48 8d 0c 93             lea    rcx,[rbx+rdx*4]
0000000000000049 <L5>:
49: 48 63 10                movsxd rdx,DWORD PTR [rax]
4c: c7 04 97 00 00 00 00    mov    DWORD PTR [rdi+rdx*4],0x0
53: 48 83 c0 04             add    rax,0x4
57: 48 39 c8                cmp    rax,rcx
5a: 75 ed                   jne    49 <L5>
000000000000005c <L4>:
5c: 49 63 c5                movsxd rax,r13d
5f: 48 8d 04 85 0f 00 00    lea    rax,[rax*4+0xf]
66: 00
67: 48 83 e0 f0             and    rax,0xfffffffffffffff0
6b: 48 29 c4                sub    rsp,rax
6e: 4c 8d 5c 24 03          lea    r11,[rsp+0x3]
73: 4c 89 d8                mov    rax,r11
76: 48 c1 e8 02             shr    rax,0x2
7a: 49 83 e3 fc             and    r11,0xfffffffffffffffc
7e: 89 34 85 00 00 00 00    mov    DWORD PTR [rax*4+0x0],esi
85: 48 63 f6                movsxd rsi,esi
88: c7 04 b7 00 00 00 00    mov    DWORD PTR [rdi+rsi*4],0x0
8f: 41 b8 00 00 00 00       mov    r8d,0x0
95: b9 01 00 00 00          mov    ecx,0x1
9a: 45 29 cd                sub    r13d,r9d
9d: eb 26                   jmp    c5 <L10>
000000000000009f <L8>:
9f: 48 83 c0 02             add    rax,0x2
a3: 39 c2                   cmp    edx,eax
a5: 7c 15                   jl     bc <L7>
00000000000000a7 <L9>:
a7: 83 3c 87 ff             cmp    DWORD PTR [rdi+rax*4],0xffffffff
ab: 75 f2                   jne    9f <L8>
ad: 89 34 87                mov    DWORD PTR [rdi+rax*4],esi
b0: 4c 63 d1                movsxd r10,ecx
b3: 43 89 04 93             mov    DWORD PTR [r11+r10*4],eax
b7: 8d 49 01                lea    ecx,[rcx+0x1]
ba: eb e3                   jmp    9f <L8>
00000000000000bc <L7>:
bc: 49 83 c0 01             add    r8,0x1
c0: 44 39 c1                cmp    ecx,r8d
c3: 7e 4d                   jle    112 <L19>
00000000000000c5 <L10>:
c5: 47 8b 14 83             mov    r10d,DWORD PTR [r11+r8*4]
c9: 49 63 c2                movsxd rax,r10d
cc: 44 8b 34 87             mov    r14d,DWORD PTR [rdi+rax*4]
d0: 44 89 d6                mov    esi,r10d
d3: 44 29 ce                sub    esi,r9d
d6: 83 c6 01                add    esi,0x1
d9: b8 00 00 00 00          mov    eax,0x0
de: 0f 48 f0                cmovs  esi,eax
e1: 45 39 d5                cmp    r13d,r10d
e4: 45 89 d7                mov    r15d,r10d
e7: 45 0f 4e fd             cmovle r15d,r13d
eb: 41 8d 54 71 ff          lea    edx,[r9+rsi*2-0x1]
f0: 44 29 d2                sub    edx,r10d
f3: 43 8d 44 79 ff          lea    eax,[r9+r15*2-0x1]
f8: 44 29 d0                sub    eax,r10d
fb: 41 39 f7                cmp    r15d,esi
fe: 7c 06                   jl     106 <L6>
100:    89 c6                   mov    esi,eax
102:    89 d0                   mov    eax,edx
104:    89 f2                   mov    edx,esi
0000000000000106 <L6>:
106:    39 d0                   cmp    eax,edx
108:    7f b2                   jg     bc <L7>
10a:    48 98                   cdqe
10c:    41 8d 76 01             lea    esi,[r14+0x1]
110:    eb 95                   jmp    a7 <L9>
0000000000000112 <L19>:
112:    45 85 e4                test   r12d,r12d
115:    7e 1d                   jle    134 <L1>
117:    48 89 d8                mov    rax,rbx
11a:    4d 63 e4                movsxd r12,r12d
11d:    4a 8d 0c a3             lea    rcx,[rbx+r12*4]
0000000000000121 <L12>:
121:    48 63 10                movsxd rdx,DWORD PTR [rax]
124:    c7 04 97 ff ff ff ff    mov    DWORD PTR [rdi+rdx*4],0xffffffff
12b:    48 83 c0 04             add    rax,0x4
12f:    48 39 c8                cmp    rax,rcx
132:    75 ed                   jne    121 <L12>
0000000000000134 <L1>:
134:    48 8d 65 d8             lea    rsp,[rbp-0x28]
138:    5b                      pop    rbx
139:    41 5c                   pop    r12
13b:    41 5d                   pop    r13
13d:    41 5e                   pop    r14
13f:    41 5f                   pop    r15
141:    5d                      pop    rbp
142:    c3                      ret
''',CFUNCTYPE(c_int,POINTER(c_int),c_int,c_int,POINTER(c_int),c_int,c_int))

class Solution:
    def minReverseOperations(self, n: int, p: int, _b: List[int], k: int) -> List[int]:
        a=(c_int*n)()
        m=len(_b)
        b=(c_int*m)(*_b)
        asm_calc(a,n,p,b,m,k)
        ans=[a[i] for i in range(n)]
        return ans
