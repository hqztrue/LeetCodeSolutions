LeetCode
========

## Introduction
Here are *theoretical solutions* for some interesting LeetCode problems, aiming for the *best* running time. The author is a TCS student who no longer remember how to code, so if you are looking for *code implementations*... sorry, this is the wrong place.

For most problems we consider here, the only thing we want to optimize is the running time. Sometimes we will optimize on the space complexity as well. Lower bound will be provided, if the optimality of our algorithm is not obvious. If the main source of hardness of a problem is its coding complexity rather than its algorithm (e.g. simulation problems), we will skip the solution here.

### Notations
In some problems we will use the word RAM model, where the assumption is each word has w bits and can store integers up to size W=2^w. In practice (i.e. 32-bit machines), w=32 and W=2^32. We assume the word length is $w=\Omega(\log n)$. By setting $w=\delta_0\log n$ for a sufficiently small constant $\delta_0>0$, we can simulate nonstandard word operations on $w$-bit words in $O(1)$ time by table lookup, with $n^{O(\delta_0)}=o(n)$ preprocessing time. If possible, I will try to construct the nonstandard word operations we want by basic word operations (e.g. & | ~).

For strings, let |\Sigma| denote the alphabet size (i.e. |\Sigma|=26 for lowercase letters), and we usually assume |\Sigma| is much smaller than n. In some cases, we further make the (non-theory) assumption that |\Sigma|<=w (since 26<32). If the input is a set of strings, we will use L to denote the total length of them, and n is the number of strings. If the input is a single string, we use n to denote its length.

If the input is an n*m matrix, we usually use n to denote max(n,m) for simplicity.

For space complexity, we use the definition which is in analogy to the following: for a TM with a (read-only) input tape, an output tape and work tapes, only the number of memory cells on work tapes counts. Here we assume the input is read-only, and for space complexity, we only count the number of memory cells on which we write. Note that this is different from the (relatively weaker) LeetCode definition, which usually allows in-place modifications to the memory cells containing the inputs. We call that definition "additional space complexity".

## Unsolved Problems
Here are a list of problems for which I don't know the current best algorithm. If a problem is open but the algorithm I provide here is (almost) the current best, it is viewed as "solved" and therefore not listed below. Some NP-hard problems are also not included.

Problem ID marked with leading ~ indicates there's good evidences that the algorithm we provide is hard to improve. Leading + indicates the original problem is solved, but there exists some interesting follow-up questions.

1 Two Sum  
+116 Populating Next Right Pointers in Each Node  
~234 Palindrome Linked List  
318 Maximum Product of Word Lengths  
421 Maximum XOR of Two Numbers in an Array  
611 Valid Triangle Number  
~898 Bitwise ORs of Subarrays  



