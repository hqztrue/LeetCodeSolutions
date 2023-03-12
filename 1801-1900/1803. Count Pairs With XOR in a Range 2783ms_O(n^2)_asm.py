import time
from ctypes import *
import mmap

#https://defuse.ca/online-x86-assembler.htm#disassembly2
def translate(s):
    res=b''
    for l in s.split('\n'):
        if (not ':' in l) or (not '   ' in l): continue
        l=l[l.find(':')+1:l.find('   ')].strip()
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
#-O2
asm_xor_in=compile_asm('''
0:  89 f0                   mov    eax,esi
2:  41 89 ca                mov    r10d,ecx
5:  89 d6                   mov    esi,edx
7:  85 c0                   test   eax,eax
9:  7e 2f                   jle    3a <L4>
b:  83 e8 01                sub    eax,0x1
e:  45 31 c9                xor    r9d,r9d
11: 4c 8d 5c 87 04          lea    r11,[rdi+rax*4+0x4]
0000000000000016 <L3>:
16: 8b 17                   mov    edx,DWORD PTR [rdi]
18: 31 f2                   xor    edx,esi
1a: 44 39 d2                cmp    edx,r10d
1d: 0f 9d c1                setge  cl
20: 31 c0                   xor    eax,eax
22: 44 39 c2                cmp    edx,r8d
25: 0f 9e c0                setle  al
28: 48 83 c7 04             add    rdi,0x4
2c: 21 c8                   and    eax,ecx
2e: 41 01 c1                add    r9d,eax
31: 49 39 fb                cmp    r11,rdi
34: 75 e0                   jne    16 <L3>
36: 44 89 c8                mov    eax,r9d
39: c3                      ret
000000000000003a <L4>:
3a: 45 31 c9                xor    r9d,r9d
3d: 44 89 c8                mov    eax,r9d
40: c3                      ret
''',CFUNCTYPE(c_int,POINTER(c_int),c_int,c_int,c_int))

class Solution:
    def countPairs(self, nums: List[int], l: int, r: int) -> int:
        n,ans=len(nums),0
        a=(c_int*n)(*nums)
        for i in range(n):
            a1=cast(addressof(a)+4*(i+1),POINTER(c_int))
            ans+=asm_xor_in(a1,n-i-1,a[i],l,r)
        return ans
