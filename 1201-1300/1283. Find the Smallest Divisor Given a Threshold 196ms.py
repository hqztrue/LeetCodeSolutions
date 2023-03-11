from ctypes import *
import mmap

buf=mmap.mmap(-1,mmap.PAGESIZE,prot=mmap.PROT_READ|mmap.PROT_WRITE|mmap.PROT_EXEC)
ftype=CFUNCTYPE(c_int,POINTER(c_int),c_int,c_int)
fpointer=c_void_p.from_buffer(buf)
f=ftype(addressof(fpointer))
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

#del fpointer
#buf.close()

class Solution:
    def smallestDivisor(self, nums: List[int], threshold: int) -> int:
        n = len(nums)
        l, r = ceil(sum(nums) / threshold), ceil(max(nums) / floor(threshold / n))
        #nums = [x-1 for x in nums]
        a=(c_int*n)()
        for i in range(n): a[i]=nums[i]-1
        while l < r:
            mid = (l + r) >> 1
            #cur = sum(n // mid for n in nums) + n
            cur = f(a,n,mid) + n
            if cur > threshold:
                l = mid + 1
            else:
                r = mid
        return l
