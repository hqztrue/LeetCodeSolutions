LeetCode
========

## Introduction
Here are *theoretical solutions* for some interesting LeetCode problems, aiming for the *best* running time. The author is a TCS student who no longer remember how to code, so if you are looking for *code implementations*... sorry, this is the wrong place.

For most problems we consider here, the only thing we want to optimize is the running time. Randomization is usually allowed. Sometimes we will optimize on the space complexity as well. Lower bound will be provided, if the optimality of our algorithm is not obvious. If the main source of hardness of a problem is its coding complexity rather than its algorithm (e.g. simulation problems), we will skip the solution here.

### Notations
In some problems we will use the word-RAM model, where the assumption is each word has w bits and can store integers up to size W=2^w. In practice (i.e. 32-bit machines), w=32 and W=2^32. We assume the word length is w=\Omega(\log n), and the following basic word operations in the multiplicative instruction set can be executed in O(1): +, -, (*), &, |, ^, ~, <<, >>. By setting w'=\delta_0\log n for a sufficiently small constant \delta_0>0, we can simulate nonstandard word operations on w'-bit words in O(1) time by table lookup, with n^{O(\delta_0)}=o(n) preprocessing time. Theoretically speaking, you can always implement algorithms in the word-RAM model in codes.

For strings, let |\Sigma| denote the alphabet size (i.e. |\Sigma|=26 for lowercase letters), and we usually assume |\Sigma| is much smaller than n. In some cases, we further make the (non-theory) assumption that |\Sigma|<=w (since 26<32). If the input is a set of strings, we will use L to denote the total length of them, and n is the number of strings. If the input is a single string, we use n to denote its length.

For graph, let n denote the number of vertices and m denote the number of edges.

If the input is an n*m matrix, we sometimes use a single parameter n to denote max(n,m) for simplicity.

For space complexity, we use the definition which is in analogy to the following: for a TM with a (read-only) input tape, an output tape and work tapes, only the number of memory cells on work tapes counts. Here we assume the input is read-only, and for space complexity, we only count the number of memory cells on which we write. Note that this is different from the (relatively weaker) LeetCode definition, which usually allows in-place modifications to the memory cells containing the inputs. We call that definition "additional space complexity".

## Unsolved Problems
Here are a list of problems for which I don't know the current best algorithm. If a problem is open but the algorithm I provide here is (almost) the current best, it is viewed as "solved" and therefore not listed below. Some NP-hard problems are also not included.

Problem ID marked with leading ~ indicates there's good evidences that the algorithm we provide is hard to improve. Leading + indicates the original problem is solved, but there exists some interesting follow-up questions.

~7 Reverse Integer  
~10 Regular Expression Matching  
+116 Populating Next Right Pointers in Each Node  
211 Add and Search Word - Data structure design  
+225 Implement Stack using Queues  
~234 Palindrome Linked List  
264 Ugly Number II  
291 Word Pattern II  
~302 Smallest Rectangle Enclosing Black Pixels  
317 Shortest Distance from All Buildings  
318 Maximum Product of Word Lengths  
368 Largest Divisible Subset  
~375 Guess Number Higher or Lower II  
395 Longest Substring with At Least K Repeating Characters  
~403 Frog Jump  
~464 Can I Win  
~472 Concatenated Words  
~483 Smallest Good Base  
548 Split Array with Equal Sum  
~762 Prime Number of Set Bits in Binary Representation  
~898 Bitwise ORs of Subarrays  
~1027 Longest Arithmetic Sequence  

## Miscellaneous Topics
Get your hands dirty: [miscellaneous_topics.pdf](https://github.com/hqztrue/LeetCodeSolutions/blob/master/miscellaneous_topics.pdf)


