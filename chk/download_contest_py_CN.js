var id = new Array();
{
  void (async function main() {
    const questions = [1,2,3,4]
    const pages = 50
    const contestId = 'weekly-contest-328'

		var codes=new Array();
		let n = questions.length;
		for (let i = 0; i < n; i++)
			codes[i]=`# ${contestId} P${questions[i]}
from string import *
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
_copy=copy; _random=random; _time=time; _bisect=bisect\n\n`;

		for (let i = 0; i < n; i++)id[i]=0;
		try {
			for (let i = 1; i <= pages; i++) {
					res = await getContest(questions, contestId, i)
					for (let j = 0; j < n; j++)codes[j] += res[j];
			}
			for (let j = 0; j < n; j++){
				codes[j] += "NUM_CODES=".concat(id[j], "\n");
				download(codes[j], `${contestId}_P${questions[j]}.py`)
			}
			console.log(`finished`)
		} catch (error) {
			console.log(error.message)
			//download(codes[0], `${contestId} - 目前已完成部分.md`)
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
    const { submissions, total_rank, questions } = await getRankData(
      contestId,
      page
    )
    const questionIds = questions.map(({ question_id }) => question_id)

    var res=new Array();
		for (let i = 0; i < questionsArr.length; i++) res[i]= ``
    for (let i = 0; i < submissions.length; i++) {
      const { username, real_name } = total_rank[i]

      const submission = submissions[i]

      for (let k = 0; k < questionsArr.length; k++) {
				let j=questionsArr[k]-1
        const questionId = questionIds[j]
        if (!submission[questionId]) {
          //res[j] += '\n# empty\n\n'
          continue
        }

        const { submission_id, lang } = submission[questionId]
				
				if (lang=='python3'){ // || lang=='python'
					const code = await getCode(submission_id)
					id[k] += 1
					code1 = process_py(code.code, id[k])
					res[k] += `# -----*****-----\n`
					res[k] += `# ${real_name}, ${(page-1)*25+i+1}\n`
					res[k] += `${code1}\n\n`
				}
      }
      // await sleep(100)
    }
    return res
  }
	
	
	function process_py(s, id) {
			s = s.replaceAll('class Solution', "class Solution".concat(id));
			return s;
	}
}
