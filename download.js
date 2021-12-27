//credit to @XYShaoKang
const website = 'leetcode'
{
  void (async function main() {
    // 配置需要获取的题目索引,从 1 开始,想要获取哪题就添加哪一题的索引
    // 比如只想获取第三题和第四题,那就写 [3,4],要获取全部题目的提交的话,就写 [1,2,3,4]
    const questions = [4]
    // 需要获取的页数,指定要获取哪几页的
    // 可以是数字,或者是用一个数组表示的区间,如 [3,6] 表示从 3 页到第 6 页
    const pages = [1]
	//const pages = [1,2,3,4,5,6,7,8,9,10,11,12]
    // 需要获取的竞赛 ID,可以通过每个比赛的链接处获取
    // 比如 https://leetcode-cn.com/contest/biweekly-contest-68/ 这是第 68 场双周赛的链接,其中 biweekly-contest-68 就是需要的部分
	const contestId = 'biweekly-contest-68'

    let res = `` //`# ${contestId}\n`
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
      download(res, `codes.h`)
    } catch (error) {
      console.log(error.message)
      download(res, `codes_partial.h`)
    }
  })()

  /**
   *
   * @param submissionId 提交id
   * @returns {{code:string,contest_submission:number,id:number,lang:string}}
   */
  function getCode(submissionId, retry = 1) {
    return fetch(`https://`+website+`.com/api/submissions/${submissionId}/`, {
      headers: {
        'content-type': 'application/json',
      },
      referrer: 'https://'+website+'.com/contest/',
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
      `https://`+website+`.com/contest/api/ranking/${contestId}/?pagination=${page}&region=local`,
      {
        headers: {
          'content-type': 'application/json',
        },
        referrer: 'https://'+website+'.com/contest/',
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

    let res = ''
    for (let i = 0; i < submissions.length; i++) {
      const { username, real_name } = total_rank[i]

      const submission = submissions[i]

      for (let j = 0; j < questionIds.length; j++) {
        if (!questionSelect.has(j + 1)) continue

        const questionId = questionIds[j]

        if (!submission[questionId]) {
          //res += '\n无\n\n'
          continue
        }

        const { submission_id, lang } = submission[questionId]

        const code = await getCode(submission_id)
        if (lang==`cpp`) {
			let id = (page-1)*25+i+1;
			res += `//-----*****-----
//${real_name}\n`
			res += `namespace space${id}{\n`
			let s = code.code
			pos = s.indexOf(`class Solution`)
			if (pos==-1){throw new Error('no class')}
			s = s.substring(0,pos) + `class Solution${id}: public Solution` + s.substring(pos+14,s.length)
			
			let tail = ``
			let l = s.length
			pos = -1
			while (1){
				pos = s.indexOf(`#define`, pos+1)
				if (pos==-1)break;
				let pos1 = pos+7
				while (pos1<l&&s[pos1]==' '&&s[pos1]!='\n')++pos1;
				if (pos1>=l||s[pos1]=='\n')break;
				let pos2 = pos1
				while (pos2<l&&s[pos2]!=' '&&s[pos2]!='\n'&&s[pos2]!='(')++pos2;
				tail += `#undef `+s.substring(pos1,pos2)+`\n`
			}
			
			res += `${s}\n`
			res += tail+`int _init${id}=[](){ptr[${id}] = new Solution${id}(); return 0;}();\n`+`}\n\n`
		}
      }
      // await sleep(100)
    }
    return res
  }
}