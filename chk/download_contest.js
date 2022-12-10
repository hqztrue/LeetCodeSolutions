var func_str = 'vector<string> run(string message, int limit)';
var func_name = 'splitMessage';
var func_arg = 'message, limit';
var id = 0;
{
  void (async function main() {
    // 配置需要获取的题目索引,从 1 开始,想要获取哪题就添加哪一题的索引
    // 比如只想获取第三题和第四题,那就写 [3,4],要获取全部题目的提交的话,就写 [1,2,3,4]
    const questions = [4]
    // 需要获取的页数,指定要获取哪几页的
    // 可以是数字,或者是用一个数组表示的区间,如 [3,6] 表示从 3 页到第 6 页
    const pages = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22]
    // 需要获取的竞赛 ID,可以通过每个比赛的链接处获取
    // 比如 https://leetcode.cn/contest/biweekly-contest-68/ 这是第 68 场双周赛的链接,其中 biweekly-contest-68 就是需要的部分
    const contestId = 'biweekly-contest-91'

    let res = `// # ${contestId}\n`
    try {
      for (const page of pages) {
        if (Array.isArray(page)) {
          for (let i = page[0]; i <= page[1]; i++) {
            res += await getContest(questions, contestId, i)
          }
        } else {
          res += await getContest(questions, contestId, page)
        }
      }
      download(res, `codes_CN.h`)
    } catch (error) {
      console.log(error.message)
      download(res, `${contestId} - 目前已完成部分.md`)
    }
  })()

  /**
   *
   * @param submissionId 提交id
   * @returns {{code:string,contest_submission:number,id:number,lang:string}}
   */
  function getCode(submissionId, retry = 1) {
    return fetch(`https://leetcode.cn/api/submissions/${submissionId}/`, {
      headers: {
        'content-type': 'application/json',
      },
      referrer: 'https://leetcode.cn/contest/',
      referrerPolicy: 'strict-origin-when-cross-origin',
      body: null,
      method: 'GET',
      mode: 'cors',
      credentials: 'include',
    }).then((res) => {
      if (res.status === 429) {
        console.log(`超出接口限制,休息一下,等待第${retry}次重试...`)
        if (retry > 5) {
          throw new Error(
            '已重试 5 次,仍然无法获取,可能力扣君生气了,晚点在试试吧...'
          )
        }
        // 请求太频繁的限制
        return sleep(3000).then(() => getCode(submissionId, retry + 1))
      }
      return res.json()
    })
  }

  /**
   * 获取比赛的数据
   * @param contestId 比赛Id
   * @param page 页数
   * @returns {{
   *    is_past: boolean
   *    submissions: {
   *      [submissionId:string]:{
   *        id: number
   *        date: number
   *        question_id: number
   *        submission_id: number
   *        status: number
   *        contest_id: number
   *        data_region: string
   *        fail_count: number
   *        lang: string
   *      }
   *    }[]
   *    questions: {
   *      id: number
   *      question_id: number
   *      credit: number
   *      title: string
   *      english_title: string
   *      title_slug: string
   *      category_slug: string
   *    }[]
   *    total_rank:{
   *      contest_id: number
   *      username: string
   *      user_slug: string
   *      real_name: string
   *      country_code: string
   *      country_name: string
   *      rank: number
   *      score: number
   *      finish_time: number
   *      global_ranking: number
   *      data_region: string
   *      avatar_url: string
   *      rank_v2: number
   *    }[]
   *    user_num: number
   * }}
   */
  function getRankData(contestId, page = 1) {
    return fetch(
      `https://leetcode.cn/contest/api/ranking/${contestId}/?pagination=${page}&region=local`,
      {
        headers: {
          'content-type': 'application/json',
        },
        referrer: 'https://leetcode.cn/contest/',
        referrerPolicy: 'strict-origin-when-cross-origin',
        body: null,
        method: 'GET',
        mode: 'cors',
        credentials: 'include',
      }
    ).then((res) => res.json())
  }

  /**
   * 创建文件下载
   * @param str 需要下载的内容
   * @param filename 文件名
   */
  function download(str, filename = 'contest.md') {
    const blob = new Blob([str], { type: 'text/plain' })
    const url = URL.createObjectURL(blob)

    const a = document.createElement('a')
    a.href = url
    a.download = filename
    document.body.appendChild(a)
    a.click()

    document.body.removeChild(a)
  }

  function sleep(time) {
    return new Promise(function (resolve, reject) {
      setTimeout(resolve, time)
    })
  }

  async function getContest(questionsArr, contestId, page) {
    console.log(`正在下载第 ${page} 页`)
    const questionSelect = new Set(questionsArr)
    const { submissions, total_rank, questions } = await getRankData(
      contestId,
      page
    )
    const questionIds = questions.map(({ question_id }) => question_id)

    let res = ``
    for (let i = 0; i < submissions.length; i++) {
      const { username, real_name } = total_rank[i]
      //res += `## ${real_name}\n`

      const submission = submissions[i]

      for (let j = 0; j < questionIds.length; j++) {
        if (!questionSelect.has(j + 1)) continue

        const questionId = questionIds[j]

        if (!submission[questionId]) {
          //res += '\n无\n\n'
          continue
        }

        const { submission_id, lang } = submission[questionId]
				
				if (lang=='cpp'){
					const code = await getCode(submission_id)
					id += 1
					code1 = process_cpp(code.code, id)
					res += `//-----*****-----\n`
					res += `${code1}`
				}
      }
      // await sleep(100)
    }
    return res
  }
	
	
	function is_comment(s) {
        var n = s.length;
        var i = 0;
        while (i < n - 1) {
            if (s[i] == '/' && s[i + 1] == '/') {
                while (i < n && s[i] != '\r' && s[i] != '\n')
                    ++i;
                if (++i >= n)
                    return 1;
            }
            else if (s[i] == '/' && s[i + 1] == '*') {
                i += 3;
                while (i < n && (s[i - 1] != '*' || s[i] != '/'))
                    ++i;
                if (++i >= n)
                    return 1;
            }
            else
                ++i;
        }
        return 0;
  }
	function process_cpp(s, id) {
        var res = '';
        res += "namespace space".concat(id, "{\n");
        s = s.replaceAll(' ', ' ');
        //Solution::
        s = s.replaceAll('Solution::', "Solution".concat(id, "::"));
        //constructor: Solution()
        s = s.replaceAll('Solution()', "Solution".concat(id, "()"));
        var pos = s.search(/\b(class|struct)\s+Solution(\b|{)/g), pos1;
        while (pos != -1) {
            pos1 = pos + 1;
            while (s[pos1] != 'n')
                ++pos1;
            if (!is_comment(s.substring(0, pos + 1)))
                break;
            pos = s.substring(pos1 + 1, s.length).search(/\b(class|struct)\s+Solution(\b|{)/g) + pos1 + 1;
        }
        if (pos == -1) {
            console.log("".concat(s));
            throw new Error('no class');
        }
        s = s.substring(0, pos) + "class Solution".concat(id, ": public Solution") + s.substring(pos1 + 1, s.length);
        //run
        pos = s.indexOf('{', pos);
        s = s.substring(0, pos + 1) + '\n\t' + func_str + " {auto *p = new Solution".concat(id, "(); auto ans = p->").concat(func_name, "(").concat(func_arg, "); delete p; return ans;}\n") + s.substring(s[pos + 1] == '\n' ? pos + 2 : pos + 1, s.length);
        //undef
        var tail = "";
        var l = s.length;
        pos = -1;
        while (1) {
            pos = s.indexOf("define", pos + 1);
            if (pos == -1)
                break;
            var pos1_1 = pos - 1;
            while (pos1_1 >= 0 && (s[pos1_1] == ' ' || s[pos1_1] == '\t'))
                --pos1_1;
            if (pos1_1 < 0 || s[pos1_1] != '#')
                continue;
            pos1_1 = pos + 6;
            if (s[pos1_1] != ' ' && s[pos1_1] != '\t')
                continue;
            while (pos1_1 < l && (s[pos1_1] == ' ' || s[pos1_1] == '\t') && s[pos1_1] != '\n')
                ++pos1_1;
            if (pos1_1 >= l || s[pos1_1] == '\n')
                continue;
            var pos2 = pos1_1;
            while (pos2 < l && s[pos2] != ' ' && s[pos2] != '\t' && s[pos2] != '\n' && s[pos2] != '\r' && s[pos2] != '(')
                ++pos2;
            tail += "#undef " + s.substring(pos1_1, pos2) + "\n";
        }
        //pragma
        pos = -1;
        while (1) {
            pos = s.indexOf("pragma", pos + 1);
            if (pos == -1)
                break;
            var pos1_2 = pos - 1;
            while (pos1_2 >= 0 && (s[pos1_2] == ' ' || s[pos1_2] == '\t'))
                --pos1_2;
            if (pos1_2 < 0 || s[pos1_2] != '#')
                continue;
            if (pos + 6 >= s.length || s[pos + 6] != ' ' && s[pos + 6] != '\t')
                continue;
            s = s.substring(0, pos1_2) + '//' + s.substring(pos1_2, s.length);
            pos += 2;
        }
        res += "".concat(s, "\n");
        res += tail + "int _init".concat(id, "=[](){ptr[").concat(id, "] = new Solution").concat(id, "(); return 0;}();\n") + "}\n\n";
        return res;
    }
}