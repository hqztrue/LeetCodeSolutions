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

#sum
buf=mmap.mmap(-1,mmap.PAGESIZE,prot=mmap.PROT_READ|mmap.PROT_WRITE|mmap.PROT_EXEC)
ftype=CFUNCTYPE(c_int,POINTER(c_int),c_int)
fpointer=c_void_p.from_buffer(buf)
asm_sum=ftype(addressof(fpointer))
buf.write(
    b'\xb9\x00\x00\x00\x00'  # mov ecx,0
    b'\x48\x8d\x14\xb7'  # lea rdx,[rsi*4+rdi]
    # begin:
    b'\x8b\x1f'  # mov ebx,DWORD PTR [rdi]
    b'\x01\xd9'  # add ecx,ebx
    b'\x48\x8d\x7f\x04'  # lea rdi,0x4[rdi]
    b'\x48\x39\xd7'  # cmp rdi,rdx
    b'\x74\x02'  # jz end
    b'\xeb\xf1'  # jmp begin
    # end:
    b'\x89\xc8'  # mov eax,ecx
    b'\xc3'  # ret
)

t1=time.time()
for i in range(10000):
    #t=0
    #for x in a: t+=x
    #t=sum(a)
    t=asm_sum(a1,n1)
    #print(t)
print('time sum=',time.time()-t1) #8129 vs 736

#sum div
buf=mmap.mmap(-1,mmap.PAGESIZE,prot=mmap.PROT_READ|mmap.PROT_WRITE|mmap.PROT_EXEC)
ftype=CFUNCTYPE(c_int,POINTER(c_int),c_int,c_int)
fpointer=c_void_p.from_buffer(buf)
asm_sum_div=ftype(addressof(fpointer))
buf.write(
    b'\x89\xd3'  # mov ebx,edx
    b'\xb9\x00\x00\x00\x00'  # mov ecx,0
    b'\x48\x8d\x34\xb7'  # lea rsi,[rsi*4+rdi]
    # begin:
    b'\x8b\x07'  # mov eax,DWORD PTR [rdi]
    b'\xba\x00\x00\x00\x00'  # mov edx,0
    b'\xf7\xfb'  # idiv ebx
    b'\x01\xc1'  # add ecx,eax
    b'\x48\x8d\x7f\x04'  # lea rdi,0x4[rdi]
    b'\x48\x39\xf7'  # cmp rdi,rsi
    b'\x74\x02'  # jz end
    b'\xeb\xea'  # jmp begin
    # end:
    b'\x89\xc8'  # mov eax,ecx
    b'\xc3'  # ret
)

t1=time.time()
for i in range(1000):
    #t=sum(x//d for x in a)
    t=asm_sum_div(a1,n1,d1)
    #print(t)
print('time sum div=',time.time()-t1) #5324 vs 184

#del fpointer
#buf.close()
