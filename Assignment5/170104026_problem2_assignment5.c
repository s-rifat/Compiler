#include<stdio.h>
int n,i;
char s[100];
int EXP();
int FACTOR()
{
   if(s[i]=='(')
   {
        i++;
        if(EXP())
        {
            if(s[i]==')')
            {
                i++;
                return 1;
            }
            i++;
            return 0;
        }
        return 0;
   }
   if( (s[i]>='0' && s[i]<='9') || (s[i]>='a' && s[i]<='e') )
   {
       i++;
       return 1;
   }
   return 0;
}
int TERM()
{
    if(FACTOR())
    {
        if( s[i]=='*' || s[i]=='/')
        {
            i++;
            return FACTOR();
        }
        return 1;
    }
    return 0;
}

int EXP()
{
    if(TERM())
    {
        if( s[i]=='+' || s[i]=='-')
        {
            i++;
            return TERM();
        }
        return 1;
    }
    return 0;
}
int main()
{
    int m;
    printf("Enter Number of test cases:\n");
    scanf("%d",&m);
    while(m--)
    {
        printf("Enter input string: ");
        scanf("%s",&s);
        n = strlen(s);
        i = 0;
        int x = EXP();
        printf("Output: ");
        if(i==n && x)
            printf("accepted\n");
        else
            printf("rejected\n");
    }
    return 0;
}
/*
11
0
9
a
e
a*a
a*a+a*a
(a*a+a*a)
(a*a+a*a)*9+(a*a+a*a)*9
(a*a+a*a)*9+(a*a+a*a)*9gh
((a*a+a*a)*9+(a*a+a*a)*9)/(a*a+a*a)-((a*a+a*a)*9+(a*a+a*a)*9)/(a*a+a*a)
(a*a+a*a)+9
*/




