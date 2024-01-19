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

asm_calc=compile_asm('''
0:  85 f6                   test   esi,esi
2:  0f 8e 99 00 00 00       jle    a1 <L8>
8:  41 55                   push   r13
a:  41 89 d2                mov    r10d,edx
d:  31 c0                   xor    eax,eax
f:  48 63 d6                movsxd rdx,esi
12: 41 54                   push   r12
14: be 01 00 00 00          mov    esi,0x1
19: 55                      push   rbp
1a: 48 89 cd                mov    rbp,rcx
1d: 53                      push   rbx
000000000000001e <L3>:
1e: 0f be 0c 07             movsx  ecx,BYTE PTR [rdi+rax*1]
22: 89 f3                   mov    ebx,esi
24: 83 e9 61                sub    ecx,0x61
27: d3 e3                   shl    ebx,cl
29: 89 5c 85 00             mov    DWORD PTR [rbp+rax*4+0x0],ebx
2d: 48 83 c0 01             add    rax,0x1
31: 48 39 d0                cmp    rax,rdx
34: 75 e8                   jne    1e <L3>
36: 4c 8d 4c 85 00          lea    r9,[rbp+rax*4+0x0]
3b: 48 89 eb                mov    rbx,rbp
3e: 45 31 db                xor    r11d,r11d
41: 41 bc 01 00 00 00       mov    r12d,0x1
0000000000000047 <L7>:
47: 44 8b 2b                mov    r13d,DWORD PTR [rbx]
4a: 31 c9                   xor    ecx,ecx
000000000000004c <L6>:
4c: 44 89 e0                mov    eax,r12d
4f: 31 d2                   xor    edx,edx
51: 41 b8 01 00 00 00       mov    r8d,0x1
57: d3 e0                   shl    eax,cl
59: 89 03                   mov    DWORD PTR [rbx],eax
5b: 48 89 e8                mov    rax,rbp
000000000000005e <L5>:
5e: 8b 30                   mov    esi,DWORD PTR [rax]
60: 31 ff                   xor    edi,edi
62: 09 f2                   or     edx,esi
64: f3 0f b8 fa             popcnt edi,edx
68: 41 39 fa                cmp    r10d,edi
6b: 7d 06                   jge    73 <L4>
6d: 41 83 c0 01             add    r8d,0x1
71: 89 f2                   mov    edx,esi
0000000000000073 <L4>:
73: 48 83 c0 04             add    rax,0x4
77: 49 39 c1                cmp    r9,rax
7a: 75 e2                   jne    5e <L5>
7c: 45 39 c3                cmp    r11d,r8d
7f: 45 0f 4c d8             cmovl  r11d,r8d
83: 83 c1 01                add    ecx,0x1
86: 83 f9 1a                cmp    ecx,0x1a
89: 75 c1                   jne    4c <L6>
8b: 44 89 2b                mov    DWORD PTR [rbx],r13d
8e: 48 83 c3 04             add    rbx,0x4
92: 4c 39 cb                cmp    rbx,r9
95: 75 b0                   jne    47 <L7>
97: 5b                      pop    rbx
98: 44 89 d8                mov    eax,r11d
9b: 5d                      pop    rbp
9c: 41 5c                   pop    r12
9e: 41 5d                   pop    r13
a0: c3                      ret
00000000000000a1 <L8>:
a1: 31 c0                   xor    eax,eax
a3: c3                      ret
''',CFUNCTYPE(c_int,POINTER(c_char),c_int,c_int,POINTER(c_int)))

class Solution:
    def maxPartitionsAfterOperations(self, s: str, k: int) -> int:
        n=len(s)
        s1=(c_char*n)(*[ord(c) for c in s])
        a=(c_int*n)(*list(range(n)))
        return asm_calc(s1,n,k,a)
