# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def invertTree(self, root):
        """
        :type root: TreeNode
        :rtype: TreeNode
        """
        def g(self,name):
            if name=='left':
                return object.__getattribute__(self,'right')
            elif name=='right':
                return object.__getattribute__(self,'left')
            else:
                return object.__getattribute__(self,name)
        TreeNode.__getattribute__=g
        return root

