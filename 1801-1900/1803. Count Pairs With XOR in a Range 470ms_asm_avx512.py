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

asm_xor_in=compile_asm('''
0:  83 fe 01                cmp    esi,0x1
3:  0f 8e e1 04 00 00       jle    4ea <L13>
9:  55                      push   rbp
a:  41 89 d1                mov    r9d,edx
d:  b8 01 00 00 00          mov    eax,0x1
12: 41 89 ca                mov    r10d,ecx
15: c4 c1 79 6e e2          vmovd  xmm4,r10d
1a: c4 c1 79 6e d1          vmovd  xmm2,r9d
1f: 45 31 db                xor    r11d,r11d
22: c5 f9 6e d8             vmovd  xmm3,eax
26: 62 f2 7d 48 7b f2       vpbroadcastw zmm6,edx
2c: 62 f2 7d 48 7b f9       vpbroadcastw zmm7,ecx
32: 31 d2                   xor    edx,edx
34: 48 89 e5                mov    rbp,rsp
37: 41 57                   push   r15
39: c4 e2 7d 79 e4          vpbroadcastw ymm4,xmm4
3e: c4 e2 7d 79 d2          vpbroadcastw ymm2,xmm2
43: 41 56                   push   r14
45: c4 e2 7d 79 db          vpbroadcastw ymm3,xmm3
4a: 62 72 7d 48 7b d0       vpbroadcastw zmm10,eax
50: 41 55                   push   r13
52: 41 54                   push   r12
54: 53                      push   rbx
55: 89 f3                   mov    ebx,esi
57: be 01 00 00 00          mov    esi,0x1
5c: 48 83 e4 c0             and    rsp,0xffffffffffffffc0
60: eb 10                   jmp    72 <L12>
0000000000000062 <L3>:
62: 48 83 c6 01             add    rsi,0x1
66: 41 01 d3                add    r11d,edx
69: 48 39 f3                cmp    rbx,rsi
6c: 0f 84 39 04 00 00       je     4ab <L30>
0000000000000072 <L12>:
72: 44 0f b7 34 77          movzx  r14d,WORD PTR [rdi+rsi*2]
77: 66 44 3b 74 77 fe       cmp    r14w,WORD PTR [rdi+rsi*2-0x2]
7d: 74 e3                   je     62 <L3>
7f: 41 89 f0                mov    r8d,esi
82: 62 52 7d 48 7b ce       vpbroadcastw zmm9,r14d
88: 41 83 e0 e0             and    r8d,0xffffffe0
8c: 4d 63 e0                movsxd r12,r8d
8f: 4e 8d 2c 67             lea    r13,[rdi+r12*2]
93: 4c 39 ef                cmp    rdi,r13
96: 0f 84 24 04 00 00       je     4c0 <L14>
9c: 62 d1 7d 48 6f c9       vmovdqa32 zmm1,zmm9
a2: 48 89 f9                mov    rcx,rdi
a5: 31 d2                   xor    edx,edx
00000000000000a7 <L5>:
a7: 62 f1 75 48 ef 01       vpxord zmm0,zmm1,ZMMWORD PTR [rcx]
ad: 48 83 c1 40             add    rcx,0x40
b1: 62 f3 fd 48 3f cf 02    vpcmplew k1,zmm0,zmm7
b8: 62 f3 fd 49 3f c6 05    vpcmpnltw k0{k1},zmm0,zmm6
bf: c5 fb 93 c0             kmovd  eax,k0
c3: f3 0f b8 c0             popcnt eax,eax
c7: 01 c2                   add    edx,eax
c9: 49 39 cd                cmp    r13,rcx
cc: 75 d9                   jne    a7 <L5>
00000000000000ce <L4>:
ce: 41 89 f7                mov    r15d,esi
d1: 41 39 f0                cmp    r8d,esi
d4: 7d 8c                   jge    62 <L3>
d6: 89 f1                   mov    ecx,esi
d8: 44 29 c1                sub    ecx,r8d
db: 8d 41 ff                lea    eax,[rcx-0x1]
de: 83 f8 1e                cmp    eax,0x1e
e1: 0f 86 e0 03 00 00       jbe    4c7 <L15>
e7: 4c 89 e8                mov    rax,r13
ea: 41 89 cd                mov    r13d,ecx
ed: c5 f1 ef c9             vpxor  xmm1,xmm1,xmm1
f1: 41 c1 ed 05             shr    r13d,0x5
f5: 49 c1 e5 06             shl    r13,0x6
f9: 49 01 c5                add    r13,rax
00000000000000fc <L7>:
fc: 62 f1 b5 48 ef 00       vpxorq zmm0,zmm9,ZMMWORD PTR [rax]
102:    48 83 c0 40             add    rax,0x40
106:    62 f3 c5 48 3e c8 05    vpcmpnltuw k1,zmm7,zmm0
10d:    62 f3 cd 49 3e c8 02    vpcmpleuw k1{k1},zmm6,zmm0
114:    62 d1 ff c9 6f c2       vmovdqu16 zmm0{k1}{z},zmm10
11a:    62 f2 7d 48 33 e8       vpmovzxwd zmm5,ymm0
120:    62 f3 fd 48 3b c0 01    vextracti64x4 ymm0,zmm0,0x1
127:    62 f1 55 48 fe c9       vpaddd zmm1,zmm5,zmm1
12d:    62 f2 7d 48 33 c0       vpmovzxwd zmm0,ymm0
133:    62 f1 7d 48 fe c9       vpaddd zmm1,zmm0,zmm1
139:    49 39 c5                cmp    r13,rax
13c:    75 be                   jne    fc <L7>
13e:    c5 fd 6f e9             vmovdqa ymm5,ymm1
142:    62 f3 fd 48 3b c9 01    vextracti64x4 ymm1,zmm1,0x1
149:    c5 d5 fe e9             vpaddd ymm5,ymm5,ymm1
14d:    c4 e3 7d 39 e9 01       vextracti128 xmm1,ymm5,0x1
153:    c5 d1 fe c1             vpaddd xmm0,xmm5,xmm1
157:    c5 f1 73 d8 08          vpsrldq xmm1,xmm0,0x8
15c:    c5 f9 fe c1             vpaddd xmm0,xmm0,xmm1
160:    c5 f1 73 d8 04          vpsrldq xmm1,xmm0,0x4
165:    c5 f9 fe c1             vpaddd xmm0,xmm0,xmm1
169:    c5 f9 7e c0             vmovd  eax,xmm0
16d:    01 d0                   add    eax,edx
16f:    89 44 24 fc             mov    DWORD PTR [rsp-0x4],eax
173:    89 c8                   mov    eax,ecx
175:    83 e0 e0                and    eax,0xffffffe0
178:    41 01 c0                add    r8d,eax
17b:    f6 c1 1f                test   cl,0x1f
17e:    0f 84 6c 03 00 00       je     4f0 <L31>
184:    29 c1                   sub    ecx,eax
186:    44 8d 69 ff             lea    r13d,[rcx-0x1]
18a:    41 83 fd 0e             cmp    r13d,0xe
18e:    0f 86 4d 03 00 00       jbe    4e1 <L17>
0000000000000194 <L32>:
194:    4c 01 e0                add    rax,r12
197:    c4 c1 79 6e ce          vmovd  xmm1,r14d
19c:    c4 e2 7d 79 c9          vpbroadcastw ymm1,xmm1
1a1:    c5 f5 ef 0c 47          vpxor  ymm1,ymm1,YMMWORD PTR [rdi+rax*2]
1a6:    c4 e2 75 3a c4          vpminuw ymm0,ymm1,ymm4
1ab:    c5 f5 75 c0             vpcmpeqw ymm0,ymm1,ymm0
1af:    c4 e2 6d 3a c9          vpminuw ymm1,ymm2,ymm1
1b4:    c5 ed 75 c9             vpcmpeqw ymm1,ymm2,ymm1
1b8:    c5 fd db c1             vpand  ymm0,ymm0,ymm1
1bc:    c5 fd db c3             vpand  ymm0,ymm0,ymm3
1c0:    c4 e2 7d 33 c8          vpmovzxwd ymm1,xmm0
1c5:    c4 e3 7d 39 c0 01       vextracti128 xmm0,ymm0,0x1
1cb:    c5 f5 fe cd             vpaddd ymm1,ymm1,ymm5
1cf:    c4 e2 7d 33 c0          vpmovzxwd ymm0,xmm0
1d4:    c5 fd fe c1             vpaddd ymm0,ymm0,ymm1
1d8:    c5 f9 6f c8             vmovdqa xmm1,xmm0
1dc:    c4 e3 7d 39 c0 01       vextracti128 xmm0,ymm0,0x1
1e2:    c5 f1 fe c0             vpaddd xmm0,xmm1,xmm0
1e6:    c5 f1 73 d8 08          vpsrldq xmm1,xmm0,0x8
1eb:    c5 f9 fe c1             vpaddd xmm0,xmm0,xmm1
1ef:    c5 f1 73 d8 04          vpsrldq xmm1,xmm0,0x4
1f4:    c5 f9 fe c1             vpaddd xmm0,xmm0,xmm1
1f8:    c5 f9 7e c0             vmovd  eax,xmm0
1fc:    01 c2                   add    edx,eax
1fe:    89 c8                   mov    eax,ecx
200:    83 e0 f0                and    eax,0xfffffff0
203:    41 01 c0                add    r8d,eax
206:    83 e1 0f                and    ecx,0xf
209:    0f 84 53 fe ff ff       je     62 <L3>
000000000000020f <L10>:
20f:    49 63 c8                movsxd rcx,r8d
212:    44 0f b7 24 4f          movzx  r12d,WORD PTR [rdi+rcx*2]
217:    48 8d 04 09             lea    rax,[rcx+rcx*1]
21b:    45 31 f4                xor    r12d,r14d
21e:    44 89 e1                mov    ecx,r12d
221:    66 45 39 e2             cmp    r10w,r12w
225:    41 0f 93 c4             setae  r12b
229:    66 44 39 c9             cmp    cx,r9w
22d:    0f 93 c1                setae  cl
230:    0f b6 c9                movzx  ecx,cl
233:    44 21 e1                and    ecx,r12d
236:    01 ca                   add    edx,ecx
238:    41 8d 48 01             lea    ecx,[r8+0x1]
23c:    44 39 f9                cmp    ecx,r15d
23f:    0f 8d 1d fe ff ff       jge    62 <L3>
245:    0f b7 4c 07 02          movzx  ecx,WORD PTR [rdi+rax*1+0x2]
24a:    44 31 f1                xor    ecx,r14d
24d:    66 44 39 c9             cmp    cx,r9w
251:    41 0f 93 c4             setae  r12b
255:    66 41 39 ca             cmp    r10w,cx
259:    0f 93 c1                setae  cl
25c:    0f b6 c9                movzx  ecx,cl
25f:    44 21 e1                and    ecx,r12d
262:    01 ca                   add    edx,ecx
264:    41 8d 48 02             lea    ecx,[r8+0x2]
268:    44 39 f9                cmp    ecx,r15d
26b:    0f 8d f1 fd ff ff       jge    62 <L3>
271:    0f b7 4c 07 04          movzx  ecx,WORD PTR [rdi+rax*1+0x4]
276:    44 31 f1                xor    ecx,r14d
279:    66 41 39 ca             cmp    r10w,cx
27d:    41 0f 93 c4             setae  r12b
281:    66 44 39 c9             cmp    cx,r9w
285:    0f 93 c1                setae  cl
288:    0f b6 c9                movzx  ecx,cl
28b:    44 21 e1                and    ecx,r12d
28e:    01 ca                   add    edx,ecx
290:    41 8d 48 03             lea    ecx,[r8+0x3]
294:    44 39 f9                cmp    ecx,r15d
297:    0f 8d c5 fd ff ff       jge    62 <L3>
29d:    0f b7 4c 07 06          movzx  ecx,WORD PTR [rdi+rax*1+0x6]
2a2:    44 31 f1                xor    ecx,r14d
2a5:    66 41 39 ca             cmp    r10w,cx
2a9:    41 0f 93 c4             setae  r12b
2ad:    66 44 39 c9             cmp    cx,r9w
2b1:    0f 93 c1                setae  cl
2b4:    0f b6 c9                movzx  ecx,cl
2b7:    44 21 e1                and    ecx,r12d
2ba:    01 ca                   add    edx,ecx
2bc:    41 8d 48 04             lea    ecx,[r8+0x4]
2c0:    44 39 f9                cmp    ecx,r15d
2c3:    0f 8d 99 fd ff ff       jge    62 <L3>
2c9:    0f b7 4c 07 08          movzx  ecx,WORD PTR [rdi+rax*1+0x8]
2ce:    44 31 f1                xor    ecx,r14d
2d1:    66 41 39 ca             cmp    r10w,cx
2d5:    41 0f 93 c4             setae  r12b
2d9:    66 44 39 c9             cmp    cx,r9w
2dd:    0f 93 c1                setae  cl
2e0:    0f b6 c9                movzx  ecx,cl
2e3:    44 21 e1                and    ecx,r12d
2e6:    01 ca                   add    edx,ecx
2e8:    41 8d 48 05             lea    ecx,[r8+0x5]
2ec:    44 39 f9                cmp    ecx,r15d
2ef:    0f 8d 6d fd ff ff       jge    62 <L3>
2f5:    0f b7 4c 07 0a          movzx  ecx,WORD PTR [rdi+rax*1+0xa]
2fa:    44 31 f1                xor    ecx,r14d
2fd:    66 41 39 ca             cmp    r10w,cx
301:    41 0f 93 c4             setae  r12b
305:    66 44 39 c9             cmp    cx,r9w
309:    0f 93 c1                setae  cl
30c:    0f b6 c9                movzx  ecx,cl
30f:    44 21 e1                and    ecx,r12d
312:    01 ca                   add    edx,ecx
314:    41 8d 48 06             lea    ecx,[r8+0x6]
318:    44 39 f9                cmp    ecx,r15d
31b:    0f 8d 41 fd ff ff       jge    62 <L3>
321:    0f b7 4c 07 0c          movzx  ecx,WORD PTR [rdi+rax*1+0xc]
326:    44 31 f1                xor    ecx,r14d
329:    66 41 39 ca             cmp    r10w,cx
32d:    41 0f 93 c4             setae  r12b
331:    66 44 39 c9             cmp    cx,r9w
335:    0f 93 c1                setae  cl
338:    0f b6 c9                movzx  ecx,cl
33b:    44 21 e1                and    ecx,r12d
33e:    01 ca                   add    edx,ecx
340:    41 8d 48 07             lea    ecx,[r8+0x7]
344:    44 39 f9                cmp    ecx,r15d
347:    0f 8d 15 fd ff ff       jge    62 <L3>
34d:    0f b7 4c 07 0e          movzx  ecx,WORD PTR [rdi+rax*1+0xe]
352:    44 31 f1                xor    ecx,r14d
355:    66 41 39 ca             cmp    r10w,cx
359:    41 0f 93 c4             setae  r12b
35d:    66 44 39 c9             cmp    cx,r9w
361:    0f 93 c1                setae  cl
364:    0f b6 c9                movzx  ecx,cl
367:    44 21 e1                and    ecx,r12d
36a:    01 ca                   add    edx,ecx
36c:    41 8d 48 08             lea    ecx,[r8+0x8]
370:    44 39 f9                cmp    ecx,r15d
373:    0f 8d e9 fc ff ff       jge    62 <L3>
379:    0f b7 4c 07 10          movzx  ecx,WORD PTR [rdi+rax*1+0x10]
37e:    44 31 f1                xor    ecx,r14d
381:    66 41 39 ca             cmp    r10w,cx
385:    41 0f 93 c4             setae  r12b
389:    66 44 39 c9             cmp    cx,r9w
38d:    0f 93 c1                setae  cl
390:    0f b6 c9                movzx  ecx,cl
393:    44 21 e1                and    ecx,r12d
396:    01 ca                   add    edx,ecx
398:    41 8d 48 09             lea    ecx,[r8+0x9]
39c:    44 39 f9                cmp    ecx,r15d
39f:    0f 8d bd fc ff ff       jge    62 <L3>
3a5:    0f b7 4c 07 12          movzx  ecx,WORD PTR [rdi+rax*1+0x12]
3aa:    44 31 f1                xor    ecx,r14d
3ad:    66 41 39 ca             cmp    r10w,cx
3b1:    41 0f 93 c4             setae  r12b
3b5:    66 44 39 c9             cmp    cx,r9w
3b9:    0f 93 c1                setae  cl
3bc:    0f b6 c9                movzx  ecx,cl
3bf:    44 21 e1                and    ecx,r12d
3c2:    01 ca                   add    edx,ecx
3c4:    41 8d 48 0a             lea    ecx,[r8+0xa]
3c8:    44 39 f9                cmp    ecx,r15d
3cb:    0f 8d 91 fc ff ff       jge    62 <L3>
3d1:    0f b7 4c 07 14          movzx  ecx,WORD PTR [rdi+rax*1+0x14]
3d6:    44 31 f1                xor    ecx,r14d
3d9:    66 41 39 ca             cmp    r10w,cx
3dd:    41 0f 93 c4             setae  r12b
3e1:    66 44 39 c9             cmp    cx,r9w
3e5:    0f 93 c1                setae  cl
3e8:    0f b6 c9                movzx  ecx,cl
3eb:    44 21 e1                and    ecx,r12d
3ee:    01 ca                   add    edx,ecx
3f0:    41 8d 48 0b             lea    ecx,[r8+0xb]
3f4:    44 39 f9                cmp    ecx,r15d
3f7:    0f 8d 65 fc ff ff       jge    62 <L3>
3fd:    0f b7 4c 07 16          movzx  ecx,WORD PTR [rdi+rax*1+0x16]
402:    44 31 f1                xor    ecx,r14d
405:    66 41 39 ca             cmp    r10w,cx
409:    41 0f 93 c4             setae  r12b
40d:    66 44 39 c9             cmp    cx,r9w
411:    0f 93 c1                setae  cl
414:    0f b6 c9                movzx  ecx,cl
417:    44 21 e1                and    ecx,r12d
41a:    01 ca                   add    edx,ecx
41c:    41 8d 48 0c             lea    ecx,[r8+0xc]
420:    44 39 f9                cmp    ecx,r15d
423:    0f 8d 39 fc ff ff       jge    62 <L3>
429:    0f b7 4c 07 18          movzx  ecx,WORD PTR [rdi+rax*1+0x18]
42e:    44 31 f1                xor    ecx,r14d
431:    66 41 39 ca             cmp    r10w,cx
435:    41 0f 93 c4             setae  r12b
439:    66 44 39 c9             cmp    cx,r9w
43d:    0f 93 c1                setae  cl
440:    0f b6 c9                movzx  ecx,cl
443:    44 21 e1                and    ecx,r12d
446:    01 ca                   add    edx,ecx
448:    41 8d 48 0d             lea    ecx,[r8+0xd]
44c:    44 39 f9                cmp    ecx,r15d
44f:    0f 8d 0d fc ff ff       jge    62 <L3>
455:    0f b7 4c 07 1a          movzx  ecx,WORD PTR [rdi+rax*1+0x1a]
45a:    44 31 f1                xor    ecx,r14d
45d:    66 41 39 ca             cmp    r10w,cx
461:    41 0f 93 c4             setae  r12b
465:    66 44 39 c9             cmp    cx,r9w
469:    0f 93 c1                setae  cl
46c:    41 83 c0 0e             add    r8d,0xe
470:    0f b6 c9                movzx  ecx,cl
473:    44 21 e1                and    ecx,r12d
476:    01 ca                   add    edx,ecx
478:    45 39 f8                cmp    r8d,r15d
47b:    0f 8d e1 fb ff ff       jge    62 <L3>
481:    66 44 33 74 07 1c       xor    r14w,WORD PTR [rdi+rax*1+0x1c]
487:    66 45 39 f2             cmp    r10w,r14w
48b:    0f 93 c1                setae  cl
48e:    31 c0                   xor    eax,eax
490:    66 45 39 ce             cmp    r14w,r9w
494:    0f 93 c0                setae  al
497:    48 83 c6 01             add    rsi,0x1
49b:    21 c8                   and    eax,ecx
49d:    01 c2                   add    edx,eax
49f:    41 01 d3                add    r11d,edx
4a2:    48 39 f3                cmp    rbx,rsi
4a5:    0f 85 c7 fb ff ff       jne    72 <L12>
00000000000004ab <L30>:
4ab:    c5 f8 77                vzeroupper
4ae:    48 8d 65 d8             lea    rsp,[rbp-0x28]
4b2:    44 89 d8                mov    eax,r11d
4b5:    5b                      pop    rbx
4b6:    41 5c                   pop    r12
4b8:    41 5d                   pop    r13
4ba:    41 5e                   pop    r14
4bc:    41 5f                   pop    r15
4be:    5d                      pop    rbp
4bf:    c3                      ret
00000000000004c0 <L14>:
4c0:    31 d2                   xor    edx,edx
4c2:    e9 07 fc ff ff          jmp    ce <L4>
00000000000004c7 <L15>:
4c7:    31 c0                   xor    eax,eax
4c9:    89 54 24 fc             mov    DWORD PTR [rsp-0x4],edx
4cd:    c5 d1 ef ed             vpxor  xmm5,xmm5,xmm5
4d1:    29 c1                   sub    ecx,eax
4d3:    44 8d 69 ff             lea    r13d,[rcx-0x1]
4d7:    41 83 fd 0e             cmp    r13d,0xe
4db:    0f 87 b3 fc ff ff       ja     194 <L32>
00000000000004e1 <L17>:
4e1:    8b 54 24 fc             mov    edx,DWORD PTR [rsp-0x4]
4e5:    e9 25 fd ff ff          jmp    20f <L10>
00000000000004ea <L13>:
4ea:    31 c0                   xor    eax,eax
4ec:    c5 f8 77                vzeroupper
4ef:    c3                      ret
00000000000004f0 <L31>:
4f0:    8b 54 24 fc             mov    edx,DWORD PTR [rsp-0x4]
4f4:    e9 69 fb ff ff          jmp    62 <L3>
''',CFUNCTYPE(c_int,POINTER(c_ushort),c_int,c_ushort,c_ushort))

asm_sort=compile_asm('''
0000000000000000 <Qsort>:
0:  41 56                   push   r14
2:  48 63 c6                movsxd rax,esi
5:  49 89 fe                mov    r14,rdi
8:  41 89 d3                mov    r11d,edx
b:  41 55                   push   r13
d:  4c 8d 2c 47             lea    r13,[rdi+rax*2]
11: 41 54                   push   r12
13: 44 8d 60 01             lea    r12d,[rax+0x1]
17: 55                      push   rbp
18: 48 89 c5                mov    rbp,rax
1b: 53                      push   rbx
000000000000001c <L8>:
1c: 42 8d 44 1d 00          lea    eax,[rbp+r11*1+0x0]
21: 41 89 e8                mov    r8d,ebp
24: 45 89 e1                mov    r9d,r12d
27: 4c 89 ef                mov    rdi,r13
2a: d1 f8                   sar    eax,1
2c: 44 89 db                mov    ebx,r11d
2f: 48 98                   cdqe
31: 41 0f b7 34 46          movzx  esi,WORD PTR [r14+rax*2]
36: 49 63 c3                movsxd rax,r11d
0000000000000039 <L2>:
39: 44 0f b7 17             movzx  r10d,WORD PTR [rdi]
3d: 49 8d 0c 46             lea    rcx,[r14+rax*2]
41: 0f b7 11                movzx  edx,WORD PTR [rcx]
44: 66 41 39 f2             cmp    r10w,si
48: 72 47                   jb     91 <L3>
4a: 66 39 d6                cmp    si,dx
4d: 73 17                   jae    66 <L4>
4f: 49 8d 44 46 fe          lea    rax,[r14+rax*2-0x2]
0000000000000054 <L5>:
54: 48 89 c1                mov    rcx,rax
57: 0f b7 10                movzx  edx,WORD PTR [rax]
5a: 48 83 e8 02             sub    rax,0x2
5e: 83 eb 01                sub    ebx,0x1
61: 66 39 d6                cmp    si,dx
64: 72 ee                   jb     54 <L5>
0000000000000066 <L4>:
66: 44 89 c0                mov    eax,r8d
69: 41 39 d8                cmp    r8d,ebx
6c: 7e 0e                   jle    7c <L14>
000000000000006e <L6>:
6e: 41 39 c3                cmp    r11d,eax
71: 7f 35                   jg     a8 <L15>
0000000000000073 <L7>:
73: 39 dd                   cmp    ebp,ebx
75: 7d 28                   jge    9f <L16>
77: 41 89 db                mov    r11d,ebx
7a: eb a0                   jmp    1c <L8>
000000000000007c <L14>:
7c: 83 eb 01                sub    ebx,0x1
7f: 66 89 17                mov    WORD PTR [rdi],dx
82: 44 89 c8                mov    eax,r9d
85: 66 44 89 11             mov    WORD PTR [rcx],r10w
89: 41 39 d9                cmp    r9d,ebx
8c: 7f e0                   jg     6e <L6>
8e: 48 63 c3                movsxd rax,ebx
0000000000000091 <L3>:
91: 48 83 c7 02             add    rdi,0x2
95: 41 83 c1 01             add    r9d,0x1
99: 41 83 c0 01             add    r8d,0x1
9d: eb 9a                   jmp    39 <L2>
000000000000009f <L16>:
9f: 5b                      pop    rbx
a0: 5d                      pop    rbp
a1: 41 5c                   pop    r12
a3: 41 5d                   pop    r13
a5: 41 5e                   pop    r14
a7: c3                      ret
00000000000000a8 <L15>:
a8: 44 89 da                mov    edx,r11d
ab: 89 c6                   mov    esi,eax
ad: 4c 89 f7                mov    rdi,r14
b0: e8 4b ff ff ff          call   0 <Qsort>
b5: eb bc                   jmp    73 <L7>
''',CFUNCTYPE(c_int,POINTER(c_ushort),c_int,c_int))

class Solution:
    def countPairs(self, nums: List[int], l: int, r: int) -> int:
        n,ans=len(nums),0
        a=(c_ushort*n)(*nums)
        asm_sort(a,0,n-1)
        return asm_xor_in(a,n,l,r)
