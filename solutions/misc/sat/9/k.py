import io,os
z,o,i=1e-6,len,io.BytesIO(os.read(0,os.fstat(0).st_size)).readline
q=lambda:tuple(map(int,i().split()))
x=lambda a,b,c,d,e,f:(c-a)*(f-b)-(d-b)*(e-a)
y=lambda x:x>=0
t=lambda a,b,c:(a*c,b*c)
p=lambda a,b,c,d:(a+c,b+d)
m=lambda a,b,c,d:(a-c,b-d)
l=lambda a,b,c,d,e:(a+(c-a)*e,b+(d-b)*e)
u=lambda a,b,c,d:((c-a)**2+(d-b)**2)**.5
v=lambda a,b:t(a,b,(c:=a*a+b*b)**-.5)
N,M=([q()for i in [0]*q()[0]]for i in"nm")
i,j,a,b,r=0,0,N[0],M[0],1e9
while i+1<o(N)and j+1<o(M):
 c,d,e,f=a,b,N[i+1],M[j+1]
 g,h=u(*a,*e),u(*b,*f)
 if g<h:
  i+=1
  a,b=e,p(*b,*t(*v(*m(*f,*b)),g))
 else:
  j+=1
  b,a=f,p(*a,*t(*v(*m(*e,*a)),h))
 L,R,A,B=0,1,0,0
 for I in range(50):
  E=(R-L)/3
  C,D=L+E,R-E
  A,B=u(*l(*c,*a,C),*l(*d,*b,C)),(u(*l(*c,*a,D),*l(*d,*b,D)))
  if A>B:
   L=C
  else:
   R=D
 r=min(r,A)
print(r)
