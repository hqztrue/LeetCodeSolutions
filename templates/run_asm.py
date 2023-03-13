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

asm_func=compile_asm('''

''',CFUNCTYPE(c_int,POINTER(c_int),c_int))


#https://gcc.godbolt.org/
#https://defuse.ca/online-x86-assembler.htm
#order: edi,esi,edx,ecx,r8d
#-Ofast -mavx -mavx2

n=100000
a=[i%100 for i in range(n)]
a1=(c_int*n)()
for i in range(n): a1[i]=a[i]
n1=c_int(n)
d=7
d1=c_int(d)

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
print('time sum=',time.time()-t1) #4633 vs 446ms


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
''',CFUNCTYPE(c_int,POINTER(c_int),c_int)) #189ms


#sum -Ofast
asm_sum_Ofast=compile_asm('''
0:  85 f6                   test   esi,esi
2:  0f 8e 83 00 00 00       jle    8b <L7>
8:  8d 46 ff                lea    eax,[rsi-0x1]
b:  83 f8 03                cmp    eax,0x3
e:  76 7f                   jbe    8f <L8>
10: 89 f2                   mov    edx,esi
12: 48 89 f8                mov    rax,rdi
15: 66 0f ef c0             pxor   xmm0,xmm0
19: c1 ea 02                shr    edx,0x2
1c: 48 c1 e2 04             shl    rdx,0x4
20: 48 01 fa                add    rdx,rdi
0000000000000023 <L5>:
23: f3 0f 6f 10             movdqu xmm2,XMMWORD PTR [rax]
27: 48 83 c0 10             add    rax,0x10
2b: 66 0f fe c2             paddd  xmm0,xmm2
2f: 48 39 d0                cmp    rax,rdx
32: 75 ef                   jne    23 <L5>
34: 66 0f 6f c8             movdqa xmm1,xmm0
38: 89 f2                   mov    edx,esi
3a: 66 0f 73 d9 08          psrldq xmm1,0x8
3f: 83 e2 fc                and    edx,0xfffffffc
42: 66 0f fe c1             paddd  xmm0,xmm1
46: 66 0f 6f c8             movdqa xmm1,xmm0
4a: 66 0f 73 d9 04          psrldq xmm1,0x4
4f: 66 0f fe c1             paddd  xmm0,xmm1
53: 66 0f 7e c0             movd   eax,xmm0
57: 40 f6 c6 03             test   sil,0x3
5b: 74 31                   je     8e <L10>
000000000000005d <L3>:
5d: 48 63 ca                movsxd rcx,edx
60: 03 04 8f                add    eax,DWORD PTR [rdi+rcx*4]
63: 8d 4a 01                lea    ecx,[rdx+0x1]
66: 39 ce                   cmp    esi,ecx
68: 7e 23                   jle    8d <L1>
6a: 48 63 c9                movsxd rcx,ecx
6d: 03 04 8f                add    eax,DWORD PTR [rdi+rcx*4]
70: 8d 4a 02                lea    ecx,[rdx+0x2]
73: 39 ce                   cmp    esi,ecx
75: 7e 16                   jle    8d <L1>
77: 48 63 c9                movsxd rcx,ecx
7a: 83 c2 03                add    edx,0x3
7d: 03 04 8f                add    eax,DWORD PTR [rdi+rcx*4]
80: 39 d6                   cmp    esi,edx
82: 7e 09                   jle    8d <L1>
84: 48 63 d2                movsxd rdx,edx
87: 03 04 97                add    eax,DWORD PTR [rdi+rdx*4]
8a: c3                      ret
000000000000008b <L7>:
8b: 31 c0                   xor    eax,eax
000000000000008d <L1>:
8d: c3                      ret
000000000000008e <L10>:
8e: c3                      ret
000000000000008f <L8>:
8f: 31 d2                   xor    edx,edx
91: 31 c0                   xor    eax,eax
93: eb c8                   jmp    5d <L3>
''',CFUNCTYPE(c_int,POINTER(c_int),c_int)) #129ms


#sum -Ofast -mavx -mavx2
asm_sum_Ofast_avx=compile_asm('''
0:  49 89 f8                mov    r8,rdi
3:  89 f2                   mov    edx,esi
5:  85 f6                   test   esi,esi
7:  0f 8e b5 00 00 00       jle    c2 <L7>
d:  8d 46 ff                lea    eax,[rsi-0x1]
10: 83 f8 06                cmp    eax,0x6
13: 0f 86 b0 00 00 00       jbe    c9 <L8>
19: 89 f1                   mov    ecx,esi
1b: 48 89 f8                mov    rax,rdi
1e: c5 f1 ef c9             vpxor  xmm1,xmm1,xmm1
22: c1 e9 03                shr    ecx,0x3
25: 48 c1 e1 05             shl    rcx,0x5
29: 48 01 f9                add    rcx,rdi
000000000000002c <L4>:
2c: c5 f5 fe 08             vpaddd ymm1,ymm1,YMMWORD PTR [rax]
30: 48 83 c0 20             add    rax,0x20
34: 48 39 c8                cmp    rax,rcx
37: 75 f3                   jne    2c <L4>
39: c5 f9 6f c1             vmovdqa xmm0,xmm1
3d: c4 e3 7d 39 c9 01       vextracti128 xmm1,ymm1,0x1
43: 89 d1                   mov    ecx,edx
45: c5 f9 fe c1             vpaddd xmm0,xmm0,xmm1
49: 83 e1 f8                and    ecx,0xfffffff8
4c: c5 f1 73 d8 08          vpsrldq xmm1,xmm0,0x8
51: c5 f9 fe c1             vpaddd xmm0,xmm0,xmm1
55: c5 f1 73 d8 04          vpsrldq xmm1,xmm0,0x4
5a: c5 f9 fe c1             vpaddd xmm0,xmm0,xmm1
5e: c5 f9 7e c0             vmovd  eax,xmm0
62: f6 c2 07                test   dl,0x7
65: 74 5e                   je     c5 <L12>
67: c5 f8 77                vzeroupper
000000000000006a <L3>:
6a: 48 63 f9                movsxd rdi,ecx
6d: 48 8d 34 bd 00 00 00    lea    rsi,[rdi*4+0x0]
74: 00
75: 41 03 04 b8             add    eax,DWORD PTR [r8+rdi*4]
79: 8d 79 01                lea    edi,[rcx+0x1]
7c: 39 fa                   cmp    edx,edi
7e: 7e 44                   jle    c4 <L1>
80: 8d 79 02                lea    edi,[rcx+0x2]
83: 41 03 44 30 04          add    eax,DWORD PTR [r8+rsi*1+0x4]
88: 39 fa                   cmp    edx,edi
8a: 7e 38                   jle    c4 <L1>
8c: 8d 79 03                lea    edi,[rcx+0x3]
8f: 41 03 44 30 08          add    eax,DWORD PTR [r8+rsi*1+0x8]
94: 39 fa                   cmp    edx,edi
96: 7e 2c                   jle    c4 <L1>
98: 8d 79 04                lea    edi,[rcx+0x4]
9b: 41 03 44 30 0c          add    eax,DWORD PTR [r8+rsi*1+0xc]
a0: 39 fa                   cmp    edx,edi
a2: 7e 20                   jle    c4 <L1>
a4: 8d 79 05                lea    edi,[rcx+0x5]
a7: 41 03 44 30 10          add    eax,DWORD PTR [r8+rsi*1+0x10]
ac: 39 fa                   cmp    edx,edi
ae: 7e 14                   jle    c4 <L1>
b0: 83 c1 06                add    ecx,0x6
b3: 41 03 44 30 14          add    eax,DWORD PTR [r8+rsi*1+0x14]
b8: 39 ca                   cmp    edx,ecx
ba: 7e 08                   jle    c4 <L1>
bc: 41 03 44 30 18          add    eax,DWORD PTR [r8+rsi*1+0x18]
c1: c3                      ret
00000000000000c2 <L7>:
c2: 31 c0                   xor    eax,eax
00000000000000c4 <L1>:
c4: c3                      ret
00000000000000c5 <L12>:
c5: c5 f8 77                vzeroupper
c8: c3                      ret
00000000000000c9 <L8>:
c9: 31 c9                   xor    ecx,ecx
cb: 31 c0                   xor    eax,eax
cd: eb 9b                   jmp    6a <L3>
''',CFUNCTYPE(c_int,POINTER(c_int),c_int)) #59ms


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
print('time sum div=',time.time()-t1) #3788 vs 173ms


#count x in a s.t. x xor y in [l,r]
asm_xor_in_count=compile_asm('''
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

