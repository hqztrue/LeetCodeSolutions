LeetCode 代码自动对拍系统
========

## 使用方式

### Python 版
1. 在 [download_contest_py_CN.js](https://github.com/hqztrue/LeetCodeSolutions/tree/master/chk/download_contest_py_CN.js) 中，将第 6 行的 contestId 修改为要下载的周赛编号。将 pages 设置为要下载的页数。
2. 在网页上按 F12，在弹出的 Console 界面中把之前的 JS 代码粘贴进去。按回车运行。
3. 等待几分钟。完成后会下载形如 weekly-contest-333_P4.py 的文件。
4. 在等待过程中可以修改 chk.py，随机生成一些你想用来对拍的数据。
5. 将下载的 weekly-contest-333_P4.py 粘贴到 chk.py 的头部，并运行 chk.py (在 windows 上可方便地使用 run.bat)。由于目前本项目的局限性，可能需要手动处理下全局变量命名冲突的问题。
6. 观察输出结果中是否有 WA/TLE/RE，hack成功的话会输出对应数据。如果异常退出则可能出了一些其他问题，需要调试一下。对于绝大部分题目，对拍十分钟就足以找到所有 bug 了。
7. (建议)将对拍得到的测试数据及对应的代码在 LC 官网上测试，并提交至 [LeetCode-Feedback](https://github.com/LeetCode-Feedback/LeetCode-Feedback/issues)。

### C++ 版
1. 在 [download_contest.js](https://github.com/hqztrue/LeetCodeSolutions/tree/master/chk/download_contest.js) 中，设置前 3 行的参数。func_str 为题目中的函数声明(需将函数名替换为 run)。func_name 为题中实际函数名，func_arg 为函数参数。
2. 运行 download_contest.js(方法类似)。
3. 修改 chk.cpp，用来随机生成一些数据。将第 10 行的 virtual int run() 修改为题目中实际使用的函数。
4. 将下载的 codes_CN.h 文件复制到 chk.cpp 同目录下。编译运行 chk.cpp。由于编译环境不同的问题，可能需要手动修一些编译错误。
5. 得到对拍数据。

## 文件描述

### download_contest_py_CN.js
用来下载周赛/双周赛的 Python 代码。可在国服使用。下载文件存储于形如 weekly-contest-333_P4.py。  
开头的参数 questions 表示要下载的题目编号，pages 表示要下载的页数，contestId 表示周赛编号。

### download_contest_py.js
用来下载周赛/双周赛的 Python 代码。可在国服或美服使用。下载文件存储于形如 weekly-contest-333_P4.py。  
region 参数设置为 local 表示国服，global 表示美服。

### download_contest.js
用来下载周赛/双周赛的 C++ 代码。可在国服或美服使用。下载文件存储于 codes_CN.h 或 codes_US.h。

### download_histogram_py.js
用来下载题库中题目的 Python 代码。可在国服或美服使用。
由 [download_histogram_py.ts](https://github.com/hqztrue/LeetCodeSolutions/tree/master/chk/download_histogram/download_histogram_py.ts) 编译得到。

### download_histogram.js
用来下载题库中题目的 C++ 代码。可在国服或美服使用。
由 [download_histogram.ts](https://github.com/hqztrue/LeetCodeSolutions/tree/master/chk/download_histogram/download_histogram.ts) 编译得到。

### chk.py
用来对拍 Python 代码的文件，包含测试数据生成器(需要手动修改)。  
其中的 _check 函数可以用指定数据测试所有的代码。  
print_name 函数可以输出所有当前被 hack 掉的用户名称。  
`bad=set([])` 为已被 hack 掉的代码编号，可手动添加进去。  
代码运行超时会显示 TLE，但运行时间过长时不会自动终止，需手动结束。  
默认将第一份代码的输出作为基准值。

### chk.cpp
用来对拍 C++ 代码的文件，包含测试数据生成器(需要手动修改)。  
其中的 check 函数可以用指定数据测试所有的代码。  
`vector<int> arr` 包含了已被 hack 掉的代码编号，可手动添加进去。

