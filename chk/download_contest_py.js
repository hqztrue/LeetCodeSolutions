var id = new Array();
{
  void (async function main() {
    const questions = [4]
    const pages = 2
    const contestId = 'weekly-contest-328'
		const region = 'local'  //'local', 'global'
		// 指定要获取的语言. 如果要获取所有语言,在数组中包含星号'*'
    // 如果只要获取某几种语言的,则去掉星号'*',填入要获取的语言,比如['java','cpp']
    const lang = ['python3']

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
					res = await getContest(lang, region, questions, contestId, i)
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
	 * @param data_region 所属的地区,"CN"或者"US"
   * @param submissionId 提交id
   * @returns {{code:string,contest_submission:number,id:number,lang:string}}
   */
  function getCode(data_region, submissionId, retry = 1) {
		const regionApi = data_region === 'CN' ? 'leetcode.cn' : 'leetcode.com'
    return fetch(`https://${regionApi}/api/submissions/${submissionId}/`, {
      headers: {
        'content-type': 'application/json',
      },
      referrer: 'https://leetcode.cn/contest/',
      referrerPolicy: 'strict-origin-when-cross-origin',
      body: null,
      method: 'GET',
      mode: 'cors',
      credentials: 'omit',
    }).then((res) => {
      if (res.status === 429) {
        console.log(`超出接口限制,休息一下,等待第${retry}次重试...`)
        if (retry > 5) {
          throw new Error(
            '已重试 5 次,仍然无法获取,可能力扣君生气了,晚点在试试吧...'
          )
        }
        // 请求太频繁的限制
        return sleep(3000).then(() => getCode(data_region, submissionId, retry + 1))
      }
      return res.json()
    })
  }

  /**
   * 获取比赛的数据
	 * @param region 所属的地区: 国服:"local";外服:"global"
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
  function getRankData(region = 'local', contestId, page = 1) {
    if (region !== 'local' && region !== 'global') region = 'local'
    return fetch(
      `https://leetcode.cn/contest/api/ranking/${contestId}/?pagination=${page}&region=${region}`,
      {
        headers: {
          'content-type': 'application/json',
        },
        referrer: 'https://leetcode.cn/contest/',
        referrerPolicy: 'strict-origin-when-cross-origin',
        body: null,
        method: 'GET',
        mode: 'cors',
        credentials: 'omit',
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

  async function getContest(lang, region, questionsArr, contestId, page) {
		lang_set = new Set(lang)
    console.log(`正在下载第 ${page} 页`)
    const { submissions, total_rank, questions } = await getRankData(
		  region,
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

				var cur_lang=''
				var code=''
				var cur_submission_id=''
        if (region=='local'){
					const { submission_id, lang } = submission[questionId]
					cur_submission_id=submission_id
					cur_lang = lang
				}
				else {
					const { submission_id, data_region } = submission[questionId]
					code = await getCode(data_region, submission_id)
					cur_lang=code.lang
				}
				if (lang_set.has('*') || lang_set.has(cur_lang)) {
					if (region=='local')code = await getCode('CN', cur_submission_id)
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
