#include <iostream>
using namespace std;
typedef int LAST[255];

int find(char s[], char t[])
{
    LAST last;
	int i, j, slen = strlen(s), tlen = strlen(t);
	for(i=0;i<255;i++) last[i]=-1;
	
	for(i=0;i<tlen;i++)
	    last[ t[i]] = i;
	    
	j = 0; i =0;
	while(i<slen)
	{
	    if(s[i]==t[j])
        {
            j++; i++;
		    if(j==tlen) 
		       return i-j;
		}
		else
		{
		    if(last[s[i+tlen-j]]==-1)//can't find
		    {
                i= i+tlen-j+1;
                //printf("%d\n", i);
			}
			else  // found 
			{
			 	i = i+tlen-j - last[s[i+tlen-j]];
			}
			
			j=0;
			
		}
	}
	return -1;
}
		

int main()
{
    char s[255], t[255];    
	int i, j;	
	
    scanf("%s\n", s);
    scanf("%s\n", t);
    
	printf(" find\n%s\n in\n%s.\n", t, s);
	printf("pos: %d\n", find(s, t));
	return 0;
}
