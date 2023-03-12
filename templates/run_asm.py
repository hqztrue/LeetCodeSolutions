import time
from ctypes import *
import mmap

n=100000
a=[i%100 for i in range(n)]
a1=(c_int*n)()
for i in range(n): a1[i]=a[i]
n1=c_int(n)
d=7
d1=c_int(d)

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
#sum x in a
asm_sum=compile_asm('''
0:  b9 00 00 00 00          mov    ecx,0x0
5:  48 8d 14 b7             lea    rdx,[rdi+rsi*4]
0000000000000009 <begin>:
9:  8b 1f                   mov    ebx,DWORD PTR [rdi]
b:  01 d9                   add    ecx,ebx
d:  48 8d 7f 04             lea    rdi,[rdi+0x4]
11: 48 39 d7                cmp    rdi,rdx
14: 75 f3                   jne    9 <begin>
16: 89 c8                   mov    eax,ecx
18: c3                      ret
''',CFUNCTYPE(c_int,POINTER(c_int),c_int))

t1=time.time()
for i in range(10000):
    #t=0
    #for x in a: t+=x
    #t=sum(a)
    t=asm_sum(a1,n1)
    #print(t)
print('time sum=',time.time()-t1) #4633 vs 446


#sum parallel 4
asm_sum_4=compile_asm('''
0:  41 b8 00 00 00 00       mov    r8d,0x0
6:  41 b9 00 00 00 00       mov    r9d,0x0
c:  41 ba 00 00 00 00       mov    r10d,0x0
12: 41 bb 00 00 00 00       mov    r11d,0x0
18: 48 8d 14 b7             lea    rdx,[rdi+rsi*4]
000000000000001c <begin>:
1c: 44 03 07                add    r8d,DWORD PTR [rdi]
1f: 44 03 4f 04             add    r9d,DWORD PTR [rdi+0x4]
23: 44 03 57 08             add    r10d,DWORD PTR [rdi+0x8]
27: 44 03 5f 0c             add    r11d,DWORD PTR [rdi+0xc]
2b: 48 8d 7f 10             lea    rdi,[rdi+0x10]
2f: 48 39 d7                cmp    rdi,rdx
32: 75 e8                   jne    1c <begin>
34: 44 89 c0                mov    eax,r8d
37: 44 01 c8                add    eax,r9d
3a: 44 01 d0                add    eax,r10d
3d: 44 01 d8                add    eax,r11d
40: c3                      ret
''',CFUNCTYPE(c_int,POINTER(c_int),c_int))


#sum x//d where x in a
asm_sum_div=compile_asm('''
0:  89 d3                   mov    ebx,edx
2:  b9 00 00 00 00          mov    ecx,0x0
7:  48 8d 34 b7             lea    rsi,[rdi+rsi*4]
000000000000000b <begin>:
b:  8b 07                   mov    eax,DWORD PTR [rdi]
d:  ba 00 00 00 00          mov    edx,0x0
12: f7 fb                   idiv   ebx
14: 01 c1                   add    ecx,eax
16: 48 8d 7f 04             lea    rdi,[rdi+0x4]
1a: 48 39 f7                cmp    rdi,rsi
1d: 75 ec                   jne    b <begin>
1f: 89 c8                   mov    eax,ecx
21: c3                      ret
''',CFUNCTYPE(c_int,POINTER(c_int),c_int,c_int))

t1=time.time()
for i in range(1000):
    #t=sum(x//d for x in a)
    t=asm_sum_div(a1,n1,d1)
    #print(t)
print('time sum div=',time.time()-t1) #3788 vs 173


#count x in a s.t. x xor y in [l,r]
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


#del fpointer
#buf.close()

