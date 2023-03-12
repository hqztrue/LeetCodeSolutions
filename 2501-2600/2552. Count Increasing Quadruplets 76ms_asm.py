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
    fpointer=c_void_p.from_buffer(buf)
    buf.write(translate(s))
    return ftype(addressof(fpointer))

asm_count=compile_asm('''
0:  55                      push   rbp
1:  4c 63 de                movsxd r11,esi
4:  4a 8d 04 9d 0f 00 00    lea    rax,[r11*4+0xf]
b:  00
c:  48 83 e0 f0             and    rax,0xfffffffffffffff0
10: 48 89 e5                mov    rbp,rsp
13: 48 29 c4                sub    rsp,rax
16: 48 8d 54 24 03          lea    rdx,[rsp+0x3]
1b: 48 89 d0                mov    rax,rdx
1e: 48 83 e2 fc             and    rdx,0xfffffffffffffffc
22: 48 c1 e8 02             shr    rax,0x2
26: c7 04 85 00 00 00 00    mov    DWORD PTR [rax*4+0x0],0x0
2d: 00 00 00 00
31: 83 fe 01                cmp    esi,0x1
34: 7e 4c                   jle    82 <L7>
36: b9 01 00 00 00          mov    ecx,0x1
3b: 45 31 c9                xor    r9d,r9d
000000000000003e <L6>:
3e: c7 04 8a 00 00 00 00    mov    DWORD PTR [rdx+rcx*4],0x0
45: 44 8b 04 8f             mov    r8d,DWORD PTR [rdi+rcx*4]
49: 31 c0                   xor    eax,eax
4b: 31 f6                   xor    esi,esi
4d: eb 13                   jmp    62 <L5>
000000000000004f <L13>:
4f: 4c 63 14 82             movsxd r10,DWORD PTR [rdx+rax*4]
53: 48 83 c0 01             add    rax,0x1
57: 83 c6 01                add    esi,0x1
5a: 4d 01 d1                add    r9,r10
5d: 48 39 c8                cmp    rax,rcx
60: 74 12                   je     74 <L12>
0000000000000062 <L5>:
62: 44 3b 04 87             cmp    r8d,DWORD PTR [rdi+rax*4]
66: 7f e7                   jg     4f <L13>
68: 01 34 82                add    DWORD PTR [rdx+rax*4],esi
6b: 48 83 c0 01             add    rax,0x1
6f: 48 39 c8                cmp    rax,rcx
72: 75 ee                   jne    62 <L5>
0000000000000074 <L12>:
74: 48 83 c1 01             add    rcx,0x1
78: 49 39 cb                cmp    r11,rcx
7b: 75 c1                   jne    3e <L6>
7d: c9                      leave
7e: 4c 89 c8                mov    rax,r9
81: c3                      ret
0000000000000082 <L7>:
82: c9                      leave
83: 45 31 c9                xor    r9d,r9d
86: 4c 89 c8                mov    rax,r9
89: c3                      ret
''',CFUNCTYPE(c_long,POINTER(c_int),c_int))

class Solution:
    def countQuadruplets(self, nums: List[int]) -> int:
        n=len(nums)
        a=(c_int*n)()
        for i in range(n): a[i]=nums[i]
        return asm_count(a,n)
