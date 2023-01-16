


copy=_copy; random=_random; time=_time; bisect=_bisect
sys.setrecursionlimit(10**6)
sys.set_int_max_str_digits(10**7)
def rand_str(n,U):
    s=""
    for i in range(n): s+=chr(97+randint(0,U))
    return s
def rand_arr(n,L,R=-1): return rand_arr(n,0,L) if R==-1 else [randint(L,R) for i in range(n)]

def _print(*args): pass
print1=print
func_name=dir(Solution1())[-1]

bad=None
def print_name():
    print()
    file=open(__file__,"r",encoding="utf-8")
    lines=file.readlines()
    user_name=[]
    for i in range(len(lines)):
        if lines[i]=='# -----*****-----\n':
            user_name.append(lines[i+1])
    for x in sorted(bad):
        print(user_name[x-1][2:],end='')
    file.close()
    print()

def _check(*args):
    global print
    std=args[-1]
    args=args[:-1]
    for i in range(1,NUM_CODES+1):
        if i not in bad:
            A=globals()['Solution%d'%i]()
            t=time.time()
            print=_print
            ans=getattr(A,func_name)(*copy.deepcopy(args))
            print=print1
            t=time.time()-t
            if t>1:
                bad.add(i)
                print('TLE: %d %f'%(i,t))
                continue
            if ans!=std:
                bad.add(i)
                print('WA: ',i,'ans=',ans,'std=',std)
    print("check end")

bad=set([])
#print_name()
#seed(0)

#_check("1762",593445230,1)

T=0
while True:
    T+=1
    if T%1000==0: print('T=',T)
    n=randint(1,100)
    #s=rand_str(n,3)
    #a=rand_arr(n,10000)
    std=None
    for i in range(1,NUM_CODES+1):
        if i not in bad:
            #print(i)
            A=globals()['Solution%d'%i]()
            t=time.time()
            #_a=copy.deepcopy(a)
            print=_print
            ans=getattr(A,func_name)(n)
            print=print1
            t=time.time()-t
            if t>1:
                bad.add(i)
                print('TLE: %d %f'%(i,t))
                continue
            if std==None: std=ans
            elif ans!=std:
                bad.add(i)
                print('WA: ',i,'ans=',ans,'std=',std)
                #print('\"'+s+'\"')
                    
