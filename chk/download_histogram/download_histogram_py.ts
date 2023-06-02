//credit to @XYShaoKang
function sleep(time: number): Promise<void> {
  return new Promise(function (resolve) {
    setTimeout(resolve, time)
  })
}

function graphqlApi(
  REGION_URL: string,
  { method, body }: { method?: string; body?: unknown },
  retry = 1
): Promise<unknown> {
  method = method || 'POST'
  const RETRY_TIME = 3000,
    RETRY_COUNT = 5
  return fetch(`${REGION_URL}/graphql/`, {
    headers: {
      'content-type': 'application/json',
    },
    referrer: `${REGION_URL}/`,
    referrerPolicy: 'strict-origin-when-cross-origin',
    body: JSON.stringify(body),
    method,
    mode: 'cors',
    credentials: 'include',
  }).then(res => {
    if (res.status === 200) {
      return res.json()
    }

    if (res.status === 429) {
      console.log(`超出接口限制,休息一下,等待第${retry}次重试...`)
      if (retry > RETRY_COUNT) {
        throw new Error(
          `已重试 ${RETRY_COUNT} 次,仍然无法获取,可能力扣君生气了,晚点在试试吧...`
        )
      }
      // 触发限制之后,等一会儿在进行请求
      return sleep(RETRY_TIME).then(() =>
        graphqlApi(REGION_URL, { method, body }, retry + 1)
      )
    }

    throw new Error(`未知状态: ${res.status}`)
  })
}

function isObject(obj: any): obj is object {
  return typeof obj === 'object' && obj !== null
}

function baseApi(
  REGION_URL: string,
  url: string,
  method = 'GET',
  body: null | object = null,
  retry = 1
): Promise<any> {
  const RETRY_TIME = 20000,
    RETRY_COUNT = 10

  method = method.toUpperCase()
  let bodyStr: null | string

  if (method === 'GET') {
    bodyStr = null
  } else {
    bodyStr = isObject(body) ? JSON.stringify(body) : body
  }

  return fetch(REGION_URL + url, {
    headers: {
      accept: 'application/json, text/plain, */*',
    },
    referrer: `REGION_URL`,
    referrerPolicy: 'strict-origin-when-cross-origin',
    body: bodyStr,
    method,
    mode: 'cors',
    credentials: 'include',
  }).then(res => {
    if (res.status === 200) {
      return res.json()
    }

    if (res.status === 429) {
      console.log(`超出接口限制,休息一下,等待第${retry}次重试...`)
      if (retry > RETRY_COUNT) {
        throw new Error(
          `已重试 ${RETRY_COUNT} 次,仍然无法获取,可能力扣君生气了,晚点在试试吧...`
        )
      }
      // 触发限制之后,等一会儿在进行请求
      return sleep(RETRY_TIME).then(() =>
        baseApi(REGION_URL, url, method, body, retry + 1)
      )
    }

    throw new Error(`未知状态: ${res.status}`)
  })
}

function globalGetStatusText(e: number): string {
  switch (e) {
    case 10:
      return 'Accepted'
    case 11:
      return 'Wrong Answer'
    case 12:
      return 'Memory Limit Exceeded'
    case 13:
      return 'Output Limit Exceeded'
    case 14:
      return 'Time Limit Exceeded'
    case 15:
      return 'Runtime Error'
    case 16:
      return 'Internal Error'
    case 20:
      return 'Compile Error'
    case 21:
      return 'Unknown Error'
    case 30:
      return 'Timeout'
    default:
      return 'Invalid Error Code'
  }
}

interface GlobalSubmissionDetail {
  submissionData: {
    status_code: number
    runtime: string
    memory: string
    total_correct: string
    total_testcases: string
    compare_result: string
    input_formatted: string
    input: string
    expected_output: string
    code_output: string
    last_testcase: string
  }
  questionId: string
  submissionId: string
  sessionId: string
  getLangDisplay: string
  submissionCode: string
  editCodeUrl: string
  checkUrl: string
  runtimeDistributionFormatted: string
  memoryDistributionFormatted: string
  langs: []
  runtime: string
  memory: string
  enableMemoryDistribution: string
  nonSufficientMsg: string
}

class LeetCodeApi {
  public graphqlApi: (
    { method, body }: { method?: string; body?: unknown },
    retry?: number
  ) => Promise<any>
  public baseApi: (
    url: string,
    method?: string | undefined,
    body?: object | null | undefined,
    retry?: number | undefined
  ) => Promise<any>
  public REGION_URL: string

  public constructor(REGION_URL: string) {
    this.REGION_URL = REGION_URL
    this.graphqlApi = graphqlApi.bind(null, REGION_URL)
    this.baseApi = baseApi.bind(null, REGION_URL)
  }

  public async getAllQuestions(): Promise<
    {
      translatedTitle: string
      title: string
      questionFrontendId: string
      titleSlug: string
      questionId: string
      categoryTitle: string
      isPaidOnly: boolean
      status: string
      difficulty: string
      __typename: string
    }[]
  > {
    const cache = localStorage.getItem('lc-extend:allQuestions')
    if (cache) {
      try {
        const res = JSON.parse(cache)
        return res
      } catch (error) {
        console.log('解析缓存失败')
      }
    }
    const body = {
      operationName: 'allQuestions',
      variables: {},
      query: /* GraphQL */ `
        query allQuestions {
          allQuestions {
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
        }
      `,
    }

    return this.graphqlApi({ body }).then(data => {
      const res = data?.data?.allQuestions
      if (res) {
        localStorage.setItem('lc-extend:allQuestions', JSON.stringify(res))
        return res
      }
      throw new Error('获取题目列表失败,返回结果为: ' + JSON.stringify(data))
    })
  }

  public async getSubmissions(
    questionSlug: string,
    limit = 40,
    offset = 0
  ): Promise<{
    lastKey: string
    hasNext: boolean
    submissions: {
      id: string
      statusDisplay: string
      lang: string
      runtime: string
      timestamp: string
      url: string
      isPending: string
      memory: string
      submissionComment: {
        comment: string
        flagType: string
        __typename: string
      }
      __typename: string
    }[]
    __typename: string
  }> {
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
        ) {
          submissionList(
            offset: $offset
            limit: $limit
            lastKey: $lastKey
            questionSlug: $questionSlug
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
              __typename
            }
            __typename
          }
        }
      `,
    }
    return this.graphqlApi({ body })
      .then(d => {
        console.log(d)
        return d
      })
      .then(({ data }) => data.submissionList)
  }

  private async getSubmissionDetailByLocal(submissionId: string): Promise<{
    id: string
    code: string
    runtime: string
    memory: string
    rawMemory: string
    statusDisplay: string
    timestamp: number
    lang: string
    passedTestCaseCnt: number
    totalTestCaseCnt: number
    sourceUrl: string
    question: {
      titleSlug: string
      title: string
      translatedTitle: string
      questionId: string
      __typename: string
    }
    outputDetail: {
      codeOutput: string
      expectedOutput: string
      input: string
      compileError: string
      runtimeError: string
      lastTestcase: string
      __typename: string
    }
    __typename: string
    submissionComment: null
  }> {
    const body = {
      operationName: 'mySubmissionDetail',
      variables: { id: submissionId },
      query: /* GraphQL */ `
        query mySubmissionDetail($id: ID!) {
          submissionDetail(submissionId: $id) {
            id
            code
            runtime
            memory
            rawMemory
            statusDisplay
            timestamp
            lang
            passedTestCaseCnt
            totalTestCaseCnt
            sourceUrl
            question {
              titleSlug
              title
              translatedTitle
              questionId
              __typename
            }
            ... on GeneralSubmissionNode {
              outputDetail {
                codeOutput
                expectedOutput
                input
                compileError
                runtimeError
                lastTestcase
                __typename
              }
              __typename
            }
            submissionComment {
              comment
              flagType
              __typename
            }
            __typename
          }
        }
      `,
    }

    return this.graphqlApi({ body }).then(({ data }) => data.submissionDetail)
  }
  private async getDistributionLocal(submissionId: string): Promise<{
    runtimeDistribution?: { lang: string; distribution: [string, number][] }
    memoryDistribution?: { lang: string; distribution: [string, number][] }
  }> {
    const runtimeApi = `/submissions/api/runtime_distribution/${submissionId}/`
    const runtimeDistribution = await this.baseApi(runtimeApi).then(data =>
      JSON.parse(data.runtime_distribution_formatted)
    )
    const memoryApi = `/submissions/api/memory_distribution/${submissionId}/`
    const memoryDistribution = await this.baseApi(memoryApi).then(data =>
      JSON.parse(data.memory_distribution_formatted)
    )

    return { runtimeDistribution, memoryDistribution }
  }

  private async getSubmissionDetailByGlobal(
    submissionId: string
  ): Promise<GlobalSubmissionDetail> {
    const text = await fetch(
      `https://leetcode.com/submissions/detail/${submissionId}/`,
      {
        headers: {
          accept:
            'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9',
        },
        referrer: 'https://leetcode.com/',
        referrerPolicy: 'strict-origin-when-cross-origin',
        body: null,
        method: 'GET',
        mode: 'cors',
        credentials: 'include',
      }
    ).then(res => res.text())

    const dataText = text.match(/var pageData = ([\d\D]+?});/)?.[1]

    const data = eval(`(function (){return ${dataText}})()`)

    return data
  }

  public async getSubmissionDetail(submissionId: string): Promise<{
    id: string // submissionId
    code: string // submissionCode
    runtime: string // runtime
    memory: string // submissionData.memory
    rawMemory: string // memory
    statusDisplay: string // status_code
    // timestamp: string
    lang: string // getLangDisplay
    passedTestCaseCnt: number // submissionData.total_correct
    totalTestCaseCnt: number // submissionData.total_testcases
    sourceUrl: string // editCodeUrl
    questionId: string
    runtimeDistribution?: { lang: string; distribution: [string, number][] }
    memoryDistribution?: { lang: string; distribution: [string, number][] }
  }> {
    if (/leetcode\.cn/.test(this.REGION_URL)) {
      const data = await this.getSubmissionDetailByLocal(submissionId)
      const { runtimeDistribution, memoryDistribution } =
        await this.getDistributionLocal(submissionId)
      return {
        ...data,
        questionId: data.question.questionId,
        runtimeDistribution,
        memoryDistribution,
      }
    } else {
      const data = await this.getSubmissionDetailByGlobal(submissionId)
      return {
        id: data.submissionId,
        code: data.submissionCode,
        runtime: data.runtime,
        memory: data.submissionData.memory,
        rawMemory: data.memory,
        statusDisplay: globalGetStatusText(data.submissionData.status_code),
        lang: data.getLangDisplay,
        passedTestCaseCnt: Number(data.submissionData.total_correct),
        totalTestCaseCnt: Number(data.submissionData.total_testcases),
        sourceUrl: data.editCodeUrl,
        questionId: data.questionId,
        runtimeDistribution: JSON.parse(data.runtimeDistributionFormatted),
        memoryDistribution: JSON.parse(data.memoryDistributionFormatted),
      }
    }
  }

  public getCodeByTime(
    lang: string,
    questionId: string,
    time: string
  ): Promise<string> {
    const api = `/submissions/api/detail/${questionId}/${lang}/${time}/`

    return this.baseApi(api).then(data => data.code)
  }

  public getCodeByMemory(
    lang: string,
    questionId: string,
    memory: string
  ): Promise<string> {
    const api = `/submissions/api/detail/${questionId}/${lang}/memory/${memory}/`
    // submissions/api/detail/1/javascript/memory/39400/

    return this.baseApi(api).then(data => data.code)
  }
}

function download(str: string, filename = 'contest.md'): void {
  const blob = new Blob([str], { type: 'text/plain' })
  const url = URL.createObjectURL(blob)

  const a = document.createElement('a')
  a.href = url
  a.download = filename
  document.body.appendChild(a)
  a.click()

  document.body.removeChild(a)
}

{
  void (async function main() {
    // 是否开启自动创建提交
    // 必须要有对应的提交,才能获取到时间或者内存分布的数据
    // 如果需要获取的题目中没有对应语言的提交,可以通过代码自动创建一个空提交
    // 当然这样会弄乱提交记录.所以最好是开一个新的进度,或者开一个小号来进行操作
    const autoCreateSubmission = false
    
    const pathnames = location.pathname.split('/').filter(Boolean)
		const leetCodeApi = new LeetCodeApi(location.origin)
		const data = await leetCodeApi.getSubmissionDetail(
      pathnames[pathnames.length - 1]
    )
		const isCN=location.origin.search('cn')!=-1
    const allQuestions = await leetCodeApi.getAllQuestions()
    const { questionId, lang } = data
		const question = (isCN?allQuestions["questions"]:allQuestions).find(q => q.questionId === questionId)
    let res = `# ${question?.title} - ${lang}\n\n`
		const cache = new Set<string>()
		let id = 0
		//if (isCN)id+=1000
		
		res += `from string import *
from re import *
from datetime import *
from collections import *
from heapq import *
from bisect import *
from copy import *
from math import *
from random import *
from statistics import *
from itertools import *
from functools import *
from operator import *
from io import *
from sys import *
from json import *
from builtins import *

import sys,os,string,re,datetime,time,collections,heapq,bisect,copy, \\
    numpy,math,random,statistics,itertools,functools,operator,io,json

from typing import *
_copy=copy; _random=random; _time=time; _bisect=bisect
def empty_func(*args,**kwargs): pass
print1=print
print=empty_func
os.system=empty_func\n\n`
		
    {
      const time = data.runtimeDistribution
      res += `\n# time\n\n`
      if (time) {
        const { lang, distribution } = time
        for (const [t] of distribution) {
          let code = await leetCodeApi.getCodeByTime(lang, questionId, t)
					if (cache.has(code)) continue
					cache.add(code)
					id += 1
					code = process_py(code, id)
          res += `# -----*****-----\n`
          res += `# ${t}ms\n${code}\n`
        }
      }
    }
    {
      const memory = data.memoryDistribution
      res += `# memory\n\n`
      if (memory) {
        const { lang, distribution } = memory
        for (const [m] of distribution) {
          let code = await leetCodeApi.getCodeByMemory(lang, questionId, m)
          if (cache.has(code)) continue
					cache.add(code)
					id += 1
					code = process_py(code, id)
          res += `# -----*****-----\n`
          res += `# ${m}kb\n${code}\n`
        }
      }
    }
		
		//if (location.origin.search('cn')!=-1)id-=1000
		res+=`NUM_CODES=${id}\n`
    download(res, `codes.py`)
  })()
	
	function process_py(s, id){
		s = s.replaceAll('class Solution', `class Solution${id}`)
		return s
	}
}

