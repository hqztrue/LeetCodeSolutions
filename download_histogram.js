//credit to @XYShaoKang
var func_str = 'string run(int left, int right)';
var func_name = 'abbreviateProduct';
var func_arg = 'left, right';
var __assign = (this && this.__assign) || function () {
    __assign = Object.assign || function(t) {
        for (var s, i = 1, n = arguments.length; i < n; i++) {
            s = arguments[i];
            for (var p in s) if (Object.prototype.hasOwnProperty.call(s, p))
                t[p] = s[p];
        }
        return t;
    };
    return __assign.apply(this, arguments);
};
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
var __generator = (this && this.__generator) || function (thisArg, body) {
    var _ = { label: 0, sent: function() { if (t[0] & 1) throw t[1]; return t[1]; }, trys: [], ops: [] }, f, y, t, g;
    return g = { next: verb(0), "throw": verb(1), "return": verb(2) }, typeof Symbol === "function" && (g[Symbol.iterator] = function() { return this; }), g;
    function verb(n) { return function (v) { return step([n, v]); }; }
    function step(op) {
        if (f) throw new TypeError("Generator is already executing.");
        while (_) try {
            if (f = 1, y && (t = op[0] & 2 ? y["return"] : op[0] ? y["throw"] || ((t = y["return"]) && t.call(y), 0) : y.next) && !(t = t.call(y, op[1])).done) return t;
            if (y = 0, t) op = [op[0] & 2, t.value];
            switch (op[0]) {
                case 0: case 1: t = op; break;
                case 4: _.label++; return { value: op[1], done: false };
                case 5: _.label++; y = op[1]; op = [0]; continue;
                case 7: op = _.ops.pop(); _.trys.pop(); continue;
                default:
                    if (!(t = _.trys, t = t.length > 0 && t[t.length - 1]) && (op[0] === 6 || op[0] === 2)) { _ = 0; continue; }
                    if (op[0] === 3 && (!t || (op[1] > t[0] && op[1] < t[3]))) { _.label = op[1]; break; }
                    if (op[0] === 6 && _.label < t[1]) { _.label = t[1]; t = op; break; }
                    if (t && _.label < t[2]) { _.label = t[2]; _.ops.push(op); break; }
                    if (t[2]) _.ops.pop();
                    _.trys.pop(); continue;
            }
            op = body.call(thisArg, _);
        } catch (e) { op = [6, e]; y = 0; } finally { f = t = 0; }
        if (op[0] & 5) throw op[1]; return { value: op[0] ? op[1] : void 0, done: true };
    }
};
//const targetLang = 'cpp'
//const questionSlug = 'abbreviating-the-product-of-a-range'
//todo:
//constructor: Solution()
//Solution::
function sleep(time) {
    return new Promise(function (resolve) {
        setTimeout(resolve, time);
    });
}
function graphqlApi(REGION_URL, _a, retry) {
    var method = _a.method, body = _a.body;
    if (retry === void 0) { retry = 1; }
    method = method || 'POST';
    var RETRY_TIME = 3000, RETRY_COUNT = 5;
    return fetch("".concat(REGION_URL, "/graphql/"), {
        headers: {
            'content-type': 'application/json'
        },
        referrer: "".concat(REGION_URL, "/"),
        referrerPolicy: 'strict-origin-when-cross-origin',
        body: JSON.stringify(body),
        method: method,
        mode: 'cors',
        credentials: 'include'
    }).then(function (res) {
        if (res.status === 200) {
            return res.json();
        }
        if (res.status === 429) {
            console.log("\u8D85\u51FA\u63A5\u53E3\u9650\u5236,\u4F11\u606F\u4E00\u4E0B,\u7B49\u5F85\u7B2C".concat(retry, "\u6B21\u91CD\u8BD5..."));
            if (retry > RETRY_COUNT) {
                throw new Error("\u5DF2\u91CD\u8BD5 ".concat(RETRY_COUNT, " \u6B21,\u4ECD\u7136\u65E0\u6CD5\u83B7\u53D6,\u53EF\u80FD\u529B\u6263\u541B\u751F\u6C14\u4E86,\u665A\u70B9\u5728\u8BD5\u8BD5\u5427..."));
            }
            // 触发限制之后,等一会儿在进行请求
            return sleep(RETRY_TIME).then(function () {
                return graphqlApi(REGION_URL, { method: method, body: body }, retry + 1);
            });
        }
        throw new Error("\u672A\u77E5\u72B6\u6001: ".concat(res.status));
    });
}
function isObject(obj) {
    return typeof obj === 'object' && obj !== null;
}
function baseApi(REGION_URL, url, method, body, retry) {
    if (method === void 0) { method = 'GET'; }
    if (body === void 0) { body = null; }
    if (retry === void 0) { retry = 1; }
    var RETRY_TIME = 20000, RETRY_COUNT = 10;
    method = method.toUpperCase();
    var bodyStr;
    if (method === 'GET') {
        bodyStr = null;
    }
    else {
        bodyStr = isObject(body) ? JSON.stringify(body) : body;
    }
    return fetch(REGION_URL + url, {
        headers: {
            accept: 'application/json, text/plain, */*'
        },
        referrer: "REGION_URL",
        referrerPolicy: 'strict-origin-when-cross-origin',
        body: bodyStr,
        method: method,
        mode: 'cors',
        credentials: 'include'
    }).then(function (res) {
        if (res.status === 200) {
            return res.json();
        }
        if (res.status === 429) {
            console.log("\u8D85\u51FA\u63A5\u53E3\u9650\u5236,\u4F11\u606F\u4E00\u4E0B,\u7B49\u5F85\u7B2C".concat(retry, "\u6B21\u91CD\u8BD5..."));
            if (retry > RETRY_COUNT) {
                throw new Error("\u5DF2\u91CD\u8BD5 ".concat(RETRY_COUNT, " \u6B21,\u4ECD\u7136\u65E0\u6CD5\u83B7\u53D6,\u53EF\u80FD\u529B\u6263\u541B\u751F\u6C14\u4E86,\u665A\u70B9\u5728\u8BD5\u8BD5\u5427..."));
            }
            // 触发限制之后,等一会儿在进行请求
            return sleep(RETRY_TIME).then(function () {
                return baseApi(REGION_URL, url, method, body, retry + 1);
            });
        }
        throw new Error("\u672A\u77E5\u72B6\u6001: ".concat(res.status));
    });
}
function globalGetStatusText(e) {
    switch (e) {
        case 10:
            return 'Accepted';
        case 11:
            return 'Wrong Answer';
        case 12:
            return 'Memory Limit Exceeded';
        case 13:
            return 'Output Limit Exceeded';
        case 14:
            return 'Time Limit Exceeded';
        case 15:
            return 'Runtime Error';
        case 16:
            return 'Internal Error';
        case 20:
            return 'Compile Error';
        case 21:
            return 'Unknown Error';
        case 30:
            return 'Timeout';
        default:
            return 'Invalid Error Code';
    }
}
var LeetCodeApi = /** @class */ (function () {
    function LeetCodeApi(REGION_URL) {
        this.REGION_URL = REGION_URL;
        this.graphqlApi = graphqlApi.bind(null, REGION_URL);
        this.baseApi = baseApi.bind(null, REGION_URL);
    }
    LeetCodeApi.prototype.getAllQuestions = function () {
        return __awaiter(this, void 0, void 0, function () {
            var cache, res, body;
            return __generator(this, function (_a) {
                cache = localStorage.getItem('lc-extend:allQuestions');
                if (cache) {
                    try {
                        res = JSON.parse(cache);
                        return [2 /*return*/, res];
                    }
                    catch (error) {
                        console.log('解析缓存失败');
                    }
                }
                body = {
                    operationName: 'allQuestions',
                    variables: {},
                    query: /* GraphQL */ "\n        query allQuestions {\n          allQuestions {\n            title\n            titleSlug\n            translatedTitle\n            questionId\n            questionFrontendId\n            status\n            difficulty\n            isPaidOnly\n            categoryTitle\n            __typename\n          }\n        }\n      "
                };
                return [2 /*return*/, this.graphqlApi({ body: body }).then(function (data) {
                        var _a;
                        var res = (_a = data === null || data === void 0 ? void 0 : data.data) === null || _a === void 0 ? void 0 : _a.allQuestions;
                        if (res) {
                            localStorage.setItem('lc-extend:allQuestions', JSON.stringify(res));
                            return res;
                        }
                        throw new Error('获取题目列表失败,返回结果为: ' + JSON.stringify(data));
                    })];
            });
        });
    };
    LeetCodeApi.prototype.getSubmissions = function (questionSlug, limit, offset) {
        if (limit === void 0) { limit = 40; }
        if (offset === void 0) { offset = 0; }
        return __awaiter(this, void 0, void 0, function () {
            var body;
            return __generator(this, function (_a) {
                body = {
                    operationName: 'submissions',
                    variables: {
                        offset: offset,
                        limit: limit,
                        lastKey: null,
                        questionSlug: questionSlug
                    },
                    query: /* GraphQL */ "\n        query submissions(\n          $offset: Int!\n          $limit: Int!\n          $lastKey: String\n          $questionSlug: String!\n        ) {\n          submissionList(\n            offset: $offset\n            limit: $limit\n            lastKey: $lastKey\n            questionSlug: $questionSlug\n          ) {\n            lastKey\n            hasNext\n            submissions {\n              id\n              statusDisplay\n              lang\n              runtime\n              timestamp\n              url\n              isPending\n              memory\n              __typename\n            }\n            __typename\n          }\n        }\n      "
                };
                return [2 /*return*/, this.graphqlApi({ body: body })
                        .then(function (d) {
                        console.log(d);
                        return d;
                    })
                        .then(function (_a) {
                        var data = _a.data;
                        return data.submissionList;
                    })];
            });
        });
    };
    LeetCodeApi.prototype.getSubmissionDetailByLocal = function (submissionId) {
        return __awaiter(this, void 0, void 0, function () {
            var body;
            return __generator(this, function (_a) {
                body = {
                    operationName: 'mySubmissionDetail',
                    variables: { id: submissionId },
                    query: /* GraphQL */ "\n        query mySubmissionDetail($id: ID!) {\n          submissionDetail(submissionId: $id) {\n            id\n            code\n            runtime\n            memory\n            rawMemory\n            statusDisplay\n            timestamp\n            lang\n            passedTestCaseCnt\n            totalTestCaseCnt\n            sourceUrl\n            question {\n              titleSlug\n              title\n              translatedTitle\n              questionId\n              __typename\n            }\n            ... on GeneralSubmissionNode {\n              outputDetail {\n                codeOutput\n                expectedOutput\n                input\n                compileError\n                runtimeError\n                lastTestcase\n                __typename\n              }\n              __typename\n            }\n            submissionComment {\n              comment\n              flagType\n              __typename\n            }\n            __typename\n          }\n        }\n      "
                };
                return [2 /*return*/, this.graphqlApi({ body: body }).then(function (_a) {
                        var data = _a.data;
                        return data.submissionDetail;
                    })];
            });
        });
    };
    LeetCodeApi.prototype.getDistributionLocal = function (submissionId) {
        return __awaiter(this, void 0, void 0, function () {
            var runtimeApi, runtimeDistribution, memoryApi, memoryDistribution;
            return __generator(this, function (_a) {
                switch (_a.label) {
                    case 0:
                        runtimeApi = "/submissions/api/runtime_distribution/".concat(submissionId, "/");
                        return [4 /*yield*/, this.baseApi(runtimeApi).then(function (data) {
                                return JSON.parse(data.runtime_distribution_formatted);
                            })];
                    case 1:
                        runtimeDistribution = _a.sent();
                        memoryApi = "/submissions/api/memory_distribution/".concat(submissionId, "/");
                        return [4 /*yield*/, this.baseApi(memoryApi).then(function (data) {
                                return JSON.parse(data.memory_distribution_formatted);
                            })];
                    case 2:
                        memoryDistribution = _a.sent();
                        return [2 /*return*/, { runtimeDistribution: runtimeDistribution, memoryDistribution: memoryDistribution }];
                }
            });
        });
    };
    LeetCodeApi.prototype.getSubmissionDetailByGlobal = function (submissionId) {
        var _a;
        return __awaiter(this, void 0, void 0, function () {
            var text, dataText, data;
            return __generator(this, function (_b) {
                switch (_b.label) {
                    case 0: return [4 /*yield*/, fetch("https://leetcode.com/submissions/detail/".concat(submissionId, "/"), {
                            headers: {
                                accept: 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9'
                            },
                            referrer: 'https://leetcode.com/',
                            referrerPolicy: 'strict-origin-when-cross-origin',
                            body: null,
                            method: 'GET',
                            mode: 'cors',
                            credentials: 'include'
                        }).then(function (res) { return res.text(); })];
                    case 1:
                        text = _b.sent();
                        dataText = (_a = text.match(/var pageData = ([\d\D]+?});/)) === null || _a === void 0 ? void 0 : _a[1];
                        data = eval("(function (){return ".concat(dataText, "})()"));
                        return [2 /*return*/, data];
                }
            });
        });
    };
    LeetCodeApi.prototype.getSubmissionDetail = function (submissionId) {
        return __awaiter(this, void 0, void 0, function () {
            var data, _a, runtimeDistribution, memoryDistribution, data;
            return __generator(this, function (_b) {
                switch (_b.label) {
                    case 0:
                        if (!/leetcode-cn\.com/.test(this.REGION_URL)) return [3 /*break*/, 3];
                        return [4 /*yield*/, this.getSubmissionDetailByLocal(submissionId)];
                    case 1:
                        data = _b.sent();
                        return [4 /*yield*/, this.getDistributionLocal(submissionId)];
                    case 2:
                        _a = _b.sent(), runtimeDistribution = _a.runtimeDistribution, memoryDistribution = _a.memoryDistribution;
                        return [2 /*return*/, __assign(__assign({}, data), { questionId: data.question.questionId, runtimeDistribution: runtimeDistribution, memoryDistribution: memoryDistribution })];
                    case 3: return [4 /*yield*/, this.getSubmissionDetailByGlobal(submissionId)];
                    case 4:
                        data = _b.sent();
                        return [2 /*return*/, {
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
                                memoryDistribution: JSON.parse(data.memoryDistributionFormatted)
                            }];
                }
            });
        });
    };
    LeetCodeApi.prototype.getCodeByTime = function (lang, questionId, time) {
        var api = "/submissions/api/detail/".concat(questionId, "/").concat(lang, "/").concat(time, "/");
        return this.baseApi(api).then(function (data) { return data.code; });
    };
    LeetCodeApi.prototype.getCodeByMemory = function (lang, questionId, memory) {
        var api = "/submissions/api/detail/".concat(questionId, "/").concat(lang, "/memory/").concat(memory, "/");
        // submissions/api/detail/1/javascript/memory/39400/
        return this.baseApi(api).then(function (data) { return data.code; });
    };
    return LeetCodeApi;
}());
function download(str, filename) {
    if (filename === void 0) { filename = 'contest.md'; }
    var blob = new Blob([str], { type: 'text/plain' });
    var url = URL.createObjectURL(blob);
    var a = document.createElement('a');
    a.href = url;
    a.download = filename;
    document.body.appendChild(a);
    a.click();
    document.body.removeChild(a);
}
{
    void (function main() {
        return __awaiter(this, void 0, void 0, function () {
            var autoCreateSubmission, pathnames, leetCodeApi, data, allQuestions, questionId, lang, question, res, cache, id, time, lang_1, distribution, _i, distribution_1, t, code, memory, lang_2, distribution, _a, distribution_2, m, code;
            return __generator(this, function (_b) {
                switch (_b.label) {
                    case 0:
                        autoCreateSubmission = false;
                        pathnames = location.pathname.split('/').filter(Boolean);
                        leetCodeApi = new LeetCodeApi(location.origin);
                        return [4 /*yield*/, leetCodeApi.getSubmissionDetail(pathnames[pathnames.length - 1])];
                    case 1:
                        data = _b.sent();
                        return [4 /*yield*/, leetCodeApi.getAllQuestions()];
                    case 2:
                        allQuestions = _b.sent();
                        questionId = data.questionId, lang = data.lang;
                        question = allQuestions.find(function (q) { return q.questionId === questionId; });
                        res = "//".concat(question === null || question === void 0 ? void 0 : question.title, " - ").concat(lang, "\n\n");
                        cache = new Set();
                        id = 0;
                        if (location.origin.search('cn') != -1)
                            id += 1000;
                        time = data.runtimeDistribution;
                        res += "//time\n\n";
                        if (!time) return [3 /*break*/, 6];
                        lang_1 = time.lang, distribution = time.distribution;
                        _i = 0, distribution_1 = distribution;
                        _b.label = 3;
                    case 3:
                        if (!(_i < distribution_1.length)) return [3 /*break*/, 6];
                        t = distribution_1[_i][0];
                        return [4 /*yield*/, leetCodeApi.getCodeByTime(lang_1, questionId, t)];
                    case 4:
                        code = _b.sent();
                        if (cache.has(code))
                            return [3 /*break*/, 5];
                        cache.add(code);
                        id += 1;
                        code = process_cpp(code, id);
                        res += "//-----*****-----\n";
                        res += "//".concat(t, "ms\n").concat(code);
                        _b.label = 5;
                    case 5:
                        _i++;
                        return [3 /*break*/, 3];
                    case 6:
                        memory = data.memoryDistribution;
                        res += "//memory\n\n";
                        if (!memory) return [3 /*break*/, 10];
                        lang_2 = memory.lang, distribution = memory.distribution;
                        _a = 0, distribution_2 = distribution;
                        _b.label = 7;
                    case 7:
                        if (!(_a < distribution_2.length)) return [3 /*break*/, 10];
                        m = distribution_2[_a][0];
                        return [4 /*yield*/, leetCodeApi.getCodeByMemory(lang_2, questionId, m)];
                    case 8:
                        code = _b.sent();
                        if (cache.has(code))
                            return [3 /*break*/, 9];
                        cache.add(code);
                        id += 1;
                        code = process_cpp(code, id);
                        res += "//-----*****-----\n";
                        res += "//".concat(m, "kb\n").concat(code);
                        _b.label = 9;
                    case 9:
                        _a++;
                        return [3 /*break*/, 7];
                    case 10:
                        download(res, "codes.h");
                        return [2 /*return*/];
                }
            });
        });
    })();
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
        //s = s.replaceAll(/class\s+Solution/g, 'class Solution')
        var pos = s.indexOf("class Solution");
        while (pos != -1) {
            /*let flag=1
            let pos1 = pos
            while (pos1>=0&&s[pos1]!='\n'){
                if (s[pos1]=='/'&&s[pos1+1]=='/')flag=0;
                --pos1;
            }
            if (flag)break;*/
            var pos1 = pos + 14;
            if (pos1 < s.length && [' ', '\t', '\n', '\r', '{'].includes(s[pos1]) && !is_comment(s.substring(0, pos + 1)))
                break;
            pos = s.indexOf("class Solution", pos + 1);
        }
        if (pos == -1) {
            throw new Error('no class');
        }
        s = s.substring(0, pos) + "class Solution".concat(id, ": public Solution") + s.substring(pos + 14, s.length);
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
            var pos1 = pos - 1;
            while (pos1 >= 0 && (s[pos1] == ' ' || s[pos1] == '\t'))
                --pos1;
            if (pos1 < 0 || s[pos1] != '#')
                continue;
            pos1 = pos + 6;
            if (s[pos1] != ' ' && s[pos1] != '\t')
                continue;
            while (pos1 < l && (s[pos1] == ' ' || s[pos1] == '\t') && s[pos1] != '\n')
                ++pos1;
            if (pos1 >= l || s[pos1] == '\n')
                continue;
            var pos2 = pos1;
            while (pos2 < l && s[pos2] != ' ' && s[pos2] != '\t' && s[pos2] != '\n' && s[pos2] != '\r' && s[pos2] != '(')
                ++pos2;
            tail += "#undef " + s.substring(pos1, pos2) + "\n";
        }
        //pragma
        pos = -1;
        while (1) {
            pos = s.indexOf("pragma", pos + 1);
            if (pos == -1)
                break;
            var pos1 = pos - 1;
            while (pos1 >= 0 && (s[pos1] == ' ' || s[pos1] == '\t'))
                --pos1;
            if (pos1 < 0 || s[pos1] != '#')
                continue;
            if (pos + 6 >= s.length || s[pos + 6] != ' ' && s[pos + 6] != '\t')
                continue;
            s = s.substring(0, pos1) + '//' + s.substring(pos1, s.length);
            pos += 2;
        }
        res += "".concat(s, "\n");
        res += tail + "int _init".concat(id, "=[](){ptr[").concat(id, "] = new Solution").concat(id, "(); return 0;}();\n") + "}\n\n";
        return res;
    }
}
