# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def doubleIt(self, head: Optional[ListNode]):
        sys.set_int_max_str_digits(1<<20)
        s=__Serializer__()._serialize(head,'ListNode')
        s="".join(filter(str.isdigit,s))
        a=[int(x) for x in str(int(s)*2)]
        return __Deserializer__()._deserialize(str(a),'ListNode')
