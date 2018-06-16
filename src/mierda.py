#!/Library/Frameworks/Python.framework/Versions/3.6/bin/python3
from re import sub
from collections import Counter,deque

t=int(input())
for i in range(t):
  n,k=[int(x) for x in input().strip().split(" ")]
  l=deque()
  print("Case {}:".format(i+1))
  for _ in range(n):
    w=sub(r"[^a-z]","",input())
    if len(l)==k:
      l.pop()
    l.appendleft(w)  
    c=Counter(list(l))
    mx=min(c.items(),key=lambda it:(-it[1],it[0]))
    print("{} {}".format(mx[0],mx[1]))
