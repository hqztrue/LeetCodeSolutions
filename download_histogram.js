//credit to @XYShaoKang
{
  const func = 'int run(vector<int>& arr, int target)'
  const name = 'closestToTarget'
  const arg = 'arr, target'
  void (async function main() {
    // 需要下载的语言 slug,可以查看最后面的 getAllLangs 中定义的语言 slug
    const langs = ['cpp']
    // 需要下载代码的题目列表
    //const questionSlugs = ['abbreviating-the-product-of-a-range']
	const questionSlugs = ['find-a-value-of-a-mysterious-function-closest-to-target']
    // 是否开启自动创建提交
    // 必须要有对应的提交,才能获取到时间或者内存分布的数据
    // 如果需要获取的题目中没有对应语言的提交,可以通过代码自动创建一个空提交
    // 当然这样会弄乱提交记录.所以最好是开一个新的进度,或者开一个小号来进行操作
    const autoCreateSubmission = false

    const allLangs = getAllLangs()
    const unknowLangs = langs.filter(
      (lang) => !Object.prototype.hasOwnProperty.call(allLangs, lang),
    )
    if (unknowLangs.length) {
      console.log(`发现未知语言类型: ${unknowLangs.join(',')}`)
      return
    }

    const allQuestions = await getAllQuestions()

    for (const questionSlug of questionSlugs) {
      const question = allQuestions.find(
        ({ titleSlug }) => titleSlug === questionSlug,
      )
      const { submissions } = await getSubmissions(questionSlug)
      for (const lang of langs) {
        const { questionFrontendId, translatedTitle, questionId } = question

        let res = `//${questionFrontendId}. ${translatedTitle} - ${lang}\n\n`
        const submission = submissions.find((s) => s.lang === lang)
        let submissionId
        if (!submission) {
          if (autoCreateSubmission) {
            const submit = await createSubmit(questionSlug, questionId, lang)
            submissionId = submit.submission_id
          } else {
            console.log(`未找到提交,不使用自动创建提交,跳过`)
            continue
          }
        } else {
          submissionId = submission.id
        }

        const runtimeData = await getRuntimeDistribution(submissionId)
		
		let id = 0
        for (const [time] of runtimeData.distribution) {
		  id += 1
          code = await getSubmissionDetail(lang, questionId, time)
		  code = process_cpp(code, id)
		  res += `//-----*****-----\n`
          res += `//${time}ms\n${code}`
        }
        download(res, 'codes.h')  //`${questionSlug}-${lang}.md`
      }
    }
  })()

  function sleep(time) {
    return new Promise(function (resolve, reject) {
      setTimeout(resolve, time)
    })
  }
  
  function process_cpp(s, id){
    let res = ''
    res += `namespace space${id}{\n`
    let pos = s.indexOf(`class Solution`)
    if (pos==-1){throw new Error('no class')}
    s = s.substring(0,pos) + `class Solution${id}: public Solution` + s.substring(pos+14,s.length)
	
	//run
	pos = s.indexOf( '{', pos)
	s = s.substring(0,pos) + '\n\t' + func + ` {return Solution${id}().${name}(${arg});}\n` + s.substring(pos,s.length)
    
    //undef
    let tail = ``
    let l = s.length
    pos = -1
    while (1){
        pos = s.indexOf(`define`, pos+1)
        if (pos==-1)break;
        let pos1 = pos-1
        while (pos1>=0&&(s[pos1]==' '||s[pos1]=='\t'))--pos1;
        if (pos1<0||s[pos1]!='#')continue;
        pos1 = pos+6
        if (s[pos1]!=' '&&s[pos1]!='\t')continue;
        while (pos1<l&&(s[pos1]==' '||s[pos1]=='\t')&&s[pos1]!='\n')++pos1;
        if (pos1>=l||s[pos1]=='\n')continue;
        let pos2 = pos1
        while (pos2<l&&s[pos2]!=' '&&s[pos2]!='\t'&&s[pos2]!='\n'&&s[pos2]!='\r'&&s[pos2]!='(')++pos2;
        tail += `#undef `+s.substring(pos1,pos2)+`\n`
    }
    
    //pragma
    pos = -1
    while (1){
        pos = s.indexOf(`pragma`, pos+1)
        if (pos==-1)break;
        let pos1 = pos-1
        while (pos1>=0&&(s[pos1]==' '||s[pos1]=='\t'))--pos1;
        if (pos1<0||s[pos1]!='#')continue;
        if (pos+6>=s.length||s[pos+6]!=' '&&s[pos+6]!='\t')continue;
        s = s.substring(0,pos1)+'//'+s.substring(pos1,s.length)
        pos += 2
    }
    
    res += `${s}\n`
    res += tail+`int _init${id}=[](){ptr[${id}] = new Solution${id}(); return 0;}();\n`+`}\n\n`
    return res
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
  function graphqlApi({ method, body }, retry = 1) {
    method = method || 'POST'
    return fetch(`https://leetcode-cn.com/graphql/`, {
      headers: {
        'content-type': 'application/json',
      },
      referrer: `https://leetcode-cn.com/`,
      referrerPolicy: 'strict-origin-when-cross-origin',
      body: JSON.stringify(body),
      method,
      mode: 'cors',
      credentials: 'include',
    }).then((res) => {
      if (res.status === 200) {
        return res.json()
      }

      if (res.status === 429) {
        console.log(`超出接口限制,休息一下,等待第${retry}次重试...`)
        if (retry > 5) {
          throw new Error(
            '已重试 5 次,仍然无法获取,可能力扣君生气了,晚点在试试吧...',
          )
        }
        // 触发限制之后,等一会儿在进行请求
        return sleep(3000).then(() => graphqlApi({ method, body }, retry + 1))
      }

      throw new Error(`未知状态: ${res.status}`)
    })
  }

  /**
   * 获取提交记录
   *
   * @param {string} questionSlug
   * @param {number} limit
   * @param {number} offset
   * @returns {Promise<{
   *    lastKey: string
   *    hasNext: boolean
   *    submissions: {
   *      id: string
   *      statusDisplay: string
   *      lang: string
   *      runtime: string
   *      timestamp: string
   *      url: string
   *      isPending: string
   *      memory: string
   *      submissionComment: {
   *        comment: string
   *        flagType: string
   *        __typename: string
   *      }
   *      __typename: string
   *    }[]
   *    __typename: string
   * }>}
   */
  function getSubmissions(questionSlug, limit = 40, offset = 0) {
    const body = {
      operationName: 'submissions',
      variables: {
        offset,
        limit,
        lastKey: null,
        questionSlug,
      },
      query: /* GraphQL */ `
        query submissions(
          $offset: Int!
          $limit: Int!
          $lastKey: String
          $questionSlug: String!
          $markedOnly: Boolean
          $lang: String
        ) {
          submissionList(
            offset: $offset
            limit: $limit
            lastKey: $lastKey
            questionSlug: $questionSlug
            markedOnly: $markedOnly
            lang: $lang
          ) {
            lastKey
            hasNext
            submissions {
              id
              statusDisplay
              lang
              runtime
              timestamp
              url
              isPending
              memory
              submissionComment {
                comment
                flagType
                __typename
              }
              __typename
            }
            __typename
          }
        }
      `,
    }

    return graphqlApi({ body }).then(({ data }) => data.submissionList)
  }

  /**
   * 获取所有题目信息
   *
   * @returns {Promise<{
   *    translatedTitle: string
   *    title: string
   *    questionFrontendId: string
   *    titleSlug: string
   *    __typename: string
   *    questionId: string
   *    categoryTitle: string
   *    isPaidOnly: boolean
   *    status: string
   *    difficulty: string
   * }[]>}
   */
  function getAllQuestions() {
    const body = {
      operationName: 'allQuestions',
      variables: {},
      query: /* GraphQL */ `
        query allQuestions {
          allQuestionsBeta {
            ...questionSummaryFields
            __typename
          }
        }

        fragment questionSummaryFields on QuestionNode {
          title
          titleSlug
          translatedTitle
          questionId
          questionFrontendId
          status
          difficulty
          isPaidOnly
          categoryTitle
          __typename
        }
      `,
    }

    return graphqlApi({ body }).then(({ data }) => data.allQuestionsBeta)
  }

  function isObject(obj) {
    return typeof obj === 'object' && obj !== null
  }

  function baseApi(url, method = 'GET', body = null, retry = 1) {
    method = method.toUpperCase()

    if (method === 'GET') {
      body = null
    } else {
      body = isObject(body) ? JSON.stringify(body) : body
    }

    return fetch(url, {
      headers: {
        accept: 'application/json, text/plain, */*',
      },
      referrer: 'https://leetcode-cn.com',
      referrerPolicy: 'strict-origin-when-cross-origin',
      body,
      method,
      mode: 'cors',
      credentials: 'include',
    }).then((res) => {
      if (res.status === 200) {
        return res.json()
      }

      if (res.status === 429) {
        console.log(`超出接口限制,休息一下,等待第${retry}次重试...`)
        if (retry > 10) {
          throw new Error(
            `已重试 10 次,仍然无法获取,可能力扣君生气了,晚点在试试吧...`,
          )
        }
        // 触发限制之后,等一会儿在进行请求
        return sleep(20000).then(() => baseApi(url, method, body, retry + 1))
      }

      throw new Error(`未知状态: ${res.status}`)
    })
  }

  /**
   * 获取时间分布数据
   *
   * @param {string} submissionId
   * @returns {Promise<{
   *    lang: string
   *    distribution: [string,number][]
   * }>}
   */
  function getRuntimeDistribution(submissionId) {
    const url = `https://leetcode-cn.com/submissions/api/runtime_distribution/${submissionId}/`
    return baseApi(url).then((data) =>
      JSON.parse(data.runtime_distribution_formatted),
    )
  }

  /**
   * 获取内存分布数据
   *
   * @param {string} submissionId
   * @returns {Promise<{
   *    lang: string
   *    distribution: [string,number][]
   * }>}
   */
  function getMemoryDistribution(submissionId) {
    const url = `https://leetcode-cn.com/submissions/api/memory_distribution/${submissionId}/`
    return baseApi(url)
  }

  /**
   * 获取详细代码
   *
   * @param {string} lang 语言类型
   * @param {string} questionId 题目的 ID
   * @param {string} time 时间
   * @returns
   */
  function getSubmissionDetail(lang, questionId, time) {
    const url = `https://leetcode-cn.com/submissions/api/detail/${questionId}/${lang}/${time}/`

    return baseApi(url).then((data) => data.code)
  }

  /**
   * 创建提交
   *
   * @param {string} questionSlug
   * @param {string} questionId
   * @param {string} lang
   * @returns {Promise<{submission_id: string}>}
   */
  function createSubmit(questionSlug, questionId, lang) {
    const body = {
      question_id: questionId,
      lang: lang,
      typed_code: ``,
      test_mode: false,
      test_judger: '',
      questionSlug,
    }
    return baseApi(
      `https://leetcode-cn.com/problems/${questionSlug}/submit/`,
      'POST',
      body,
    )
  }

  function getAllLangs(params) {
    const LANG_TYPES = [
      {
        slug: 'cpp',
        lang: 'C++',
      },
      {
        slug: 'java',
        lang: 'Java',
      },
      {
        slug: 'python',
        lang: 'Python',
      },
      {
        slug: 'mysql',
        lang: 'MySQL',
      },
      {
        slug: 'c',
        lang: 'C',
      },
      {
        slug: 'csharp',
        lang: 'C#',
      },
      {
        slug: 'javascript',
        lang: 'JavaScript',
      },
      {
        slug: 'ruby',
        lang: 'Ruby',
      },
      {
        slug: 'bash',
        lang: 'Bash',
      },
      {
        slug: 'swift',
        lang: 'Swift',
      },
      {
        slug: 'golang',
        lang: 'Go',
      },
      {
        slug: 'python3',
        lang: 'Python3',
      },
      {
        slug: 'scala',
        lang: 'Scala',
      },
      {
        slug: 'kotlin',
        lang: 'Kotlin',
      },
      {
        slug: 'rust',
        lang: 'Rust',
      },
      {
        slug: 'php',
        lang: 'PHP',
      },
      {
        slug: 'typescript',
        lang: 'TypeScript',
      },
      {
        slug: 'racket',
        lang: 'Racket',
      },
      {
        slug: 'erlang',
        lang: 'Erlang',
      },
      {
        slug: 'elixir',
        lang: 'Elixir',
      },
    ]
    let res = {}
    for (const { slug, lang } of LANG_TYPES) {
      res[slug] = lang
    }
    return res
  }
}

