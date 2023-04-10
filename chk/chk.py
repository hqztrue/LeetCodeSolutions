


from builtins import *
copy=_copy; random=_random; time=_time; bisect=_bisect
sys.setrecursionlimit(10**6)
sys.set_int_max_str_digits(10**7)
def rand_str(n,U=26):
    s=""
    for i in range(n): s+=chr(97+randint(0,U-1))
    return s
def rand_arr(n,L,R=-1): return rand_arr(n,0,L) if R==-1 else [randint(L,R) for i in range(n)]
def rand_arr2D(n,m,L,R=-1): return [rand_arr(m,L,R) for i in range(n)]
def rand_tree(n):
    I=list(range(n))
    shuffle(I)
    a=[[I[randint(0,i-1)],I[i]] for i in range(1,n)]
    for i in range(n-1):
        if randint(0,1): a[i][0],a[i][1]=a[i][1],a[i][0]
    return a
def rand_graph(n,m,directed=1,self_loop=1):
    s=set()
    e=[]
    for i in range(m):
        while 1:
            x=randint(0,n-1)
            y=randint(0,n-1)
            if not directed and x>y: x,y=y,x
            if (not self_loop and x==y) or (x,y) in s: continue
            s.add((x,y))
            e.append([x,y])
            break
    return e

def Print(*args,file=sys.stdout,end=''):
    if len(args)==1 and isinstance(args[0],str): print1('\"'+args[0]+'\"',file=file)
    else: print1(*args,file=file)
print=Print
os.system=empty_func
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
        #print1(user_name[x-1][2:].split(',')[0],end=' | ')
        print1(user_name[x-1][2:],end='')
    file.close()
    print()

def _check(*args):
    global print
    std=args[-1]
    args=args[:-1]
    for i in range(1,NUM_CODES+1):
        if i not in bad:
            #print(i)
            A=globals()['Solution%d'%i]()
            t=time.time()
            print=empty_func
            ans=getattr(A,func_name)(*copy.deepcopy(args))
            print=Print
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
    if T%1==0: print('T=',T)
    n=randint(1,100)
    #s=rand_str(n,3)
    #a=rand_arr(n,10000)
    
    #fout=open("1.txt","w")
    #print(a,file=fout)
    #fout.close()
    std=None
    for i in range(1,NUM_CODES+1):
        if i not in bad:
            #print(i)
            A=globals()['Solution%d'%i]()
            t1=time.time()
            #_a=copy.deepcopy(a)
            print=empty_func
            ans=getattr(A,func_name)(n)
            print=Print
            t1=time.time()-t1
            if t1>1:
                bad.add(i)
                print('TLE: %d %f'%(i,t1))
                continue
            if std==None: std=ans
            elif ans!=std:
                bad.add(i)
                print('WA: ',i,'ans=',ans,'std=',std)
                print(n)
