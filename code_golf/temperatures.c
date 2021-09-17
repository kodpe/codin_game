#include <stdio.h>
int main(){int n,s,t,i,m=5527;scanf("%d",&n);for(i=0; i<n;i++){scanf("%d",&t);
if(abs(t)<m+s){m=abs(t);if(t<0)s=1;else s=0;}}if(m==5527)m=0;if(s==1)m=-m;printf("%d\n",m);}
