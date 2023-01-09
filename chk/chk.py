


copy=_copy; random=_random; time=_time; bisect=_bisect
sys.setrecursionlimit(10**6)
def _print(*args): pass
print1=print; print=_print

bad=set([])
T=0
while True:
    T+=1
    if T%1000==0: print1('T=',T)
    n=random.randint(1,100)
    #s=""
    #for i in range(n): s+=chr(97+random.randint(0,3))
    #a=[random.randint(0,100000) for i in range(n)]
    std=None
    for i in range(1001,NUM_CODES+1001):
        if i not in bad:
            A=globals()['Solution%d'%i]()
            t=time.time()
            #_a=copy.deepcopy(a)
            ans=A.findIntegers(n)
            t=time.time()-t
            if t>1:
                bad.add(i)
                print1('TLE: %d %f'%(i,t))
                continue
            if std==None: std=ans
            elif ans!=std:
                bad.add(i)
                print1('WA: ',i,'ans=',ans,'std=',std)
                #print1(n)
                    
