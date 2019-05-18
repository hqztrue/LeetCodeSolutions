LeetCode
========

## Introduction
Here are *theoretical solutions* for some interesting LeetCode problems, aiming for the *best* running time. The author is a TCS student who no longer remember how to code, so if you are looking for *code implementations*... sorry, this is the wrong place.

For most problems we consider here, the only thing we want to optimize is the running time. Sometimes we will optimize on the space complexity as well. If the main source of hardness of a problem is its coding complexity rather than its algorithm (e.g. simulation problems), we will skip the solution here.

### Notations
In some problems we will use the word RAM model, where the assumption is each word has w bits and can store integers up to size W=2^w. In practice (i.e. 32-bit machines), w=32 and W=2^32. We assume the word length is $w=\Omega(\log n)$. By setting $w=\delta_0\log n$ for a sufficiently small constant $\delta_0>0$, we can simulate nonstandard word operations on $w$-bit words in $O(1)$ time by table lookup, with $n^{O(\delta_0)}=o(n)$ preprocessing time. If possible, I will try to construct the nonstandard word operations we want by $O(1)$ basic word operations (e.g. & | ~).

For strings, let $|\Sigma|$ denote the alphabet size, and we usually assume $|\Sigma|$ is much smaller than n.

## Unsolved Problems
Here are a list of problems for which I don't know the current best algorithm. If a problem is open but the algorithm I list here is (almost) the current best, it is viewed as "solved" and therefore not listed below.

problem id marked with leading ~ indicates there's good evidence that it is hard to improve.

* 1. Two Sum
*  234. Palindrome Linked List
* 421. Maximum XOR of Two Numbers in an Array
* 611. Valid Triangle Number
* ~898. Bitwise ORs of Subarrays



