#include<stdio.h>

int n,i;
char s[100];

int stat();
int asgn_stat();
int expn();
int extn();
int dcsn_stat();
int extn1();
int loop_stat();
int relop();
int FACTOR();
int TERM();
int smpl_expn();

int FACTOR()
{
   if(s[i]=='(')
   {
        i++;
        if(smpl_expn())
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
int smpl_expn()
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
int relop()
{
    if(s[i]=='=' || s[i] == '!')
    {
        i++;
        if(s[i]=='=')
        {
            i++;
            return 1;
        }
        return 0;
    }
    if(s[i]=='<' || s[i] == '>')
    {
        i++;
        if(s[i]=='=')
        {
            i++;
            return 1;
        }
        return 1;
    }
    return 0;
}
int loop_stat()
{
    if(s[i]=='w')
    {
        i++;
        if(s[i]=='h')
        {   i++;
            if(s[i]=='i')
            {
                i++;
                if(s[i]=='l')
                {
                    i++;
                    if(s[i]=='e')
                    {
                        i++;
                        if(s[i]=='(')
                        {
                            i++;
                            if(expn())
                            {
                                if(s[i]==')')
                                {
                                    i++;
                                    return stat();
                                }
                                return 0;
                            }
                            return 0;
                        }
                        return 0;
                    }
                    return 0;
                }
                return 0;
            }
            return 0;
        }
        return 0;
    }
    if(s[i]=='f')
    {
        i++;
        if(s[i]=='o')
        {
            i++;
            if(s[i]=='r')
            {
                i++;
                if(s[i]=='(')
                {
                    i++;
                    if(asgn_stat())
                    {
                        if(s[i]==';')
                        {
                            i++;
                            if(expn())
                            {
                                if(s[i]==';')
                                {
                                    i++;
                                    if(asgn_stat())
                                    {
                                        if(s[i]==')')
                                        {
                                            i++;
                                            return stat();
                                        }
                                        return 0;
                                    }
                                    return 0;
                                }
                                return 0;
                            }
                            return 0;
                        }
                        return 0;
                    }
                    return 0;
                }
                return 0;
            }
            return 0;
        }
        return 0;
    }
    return 0;
}
int extn1()
{
    if(s[i]=='e')
    {
        i++;
        if(s[i]=='l')
        {
            i++;
            if(s[i]=='s')
            {
                i++;
                if(s[i]=='e')
                {
                    i++;
                    return stat();
                }
                return 0;
            }
            return 0;
        }
        return 0;
    }
    return 1;
}
int dcsn_stat()
{
    if(s[i]=='i')
    {
        i++;
        if(s[i]=='f')
        {
            i++;
            if(s[i]=='(')
            {
                i++;
                if(expn())
                {
                    if(s[i]==')')
                    {
                        i++;
                        if(stat())
                            return extn1();
                        return 0;
                    }
                    return 0;
                }
                return 0;
            }
            return 0;
        }
        return 0;
    }
    return 0;
}
int extn()
{
    if(relop())
        return smpl_expn();
    return 1;
}
int expn()
{
    if(smpl_expn())
        return extn();
    return 0;
}
int asgn_stat()
{
    if(s[i]>='a' && s[i]<='e')
    {
        i++;
        if(s[i]=='=')
        {
            i++;
            return expn();
        }
        return 0;
    }
    return 0;
}
int stat()
{
    if(asgn_stat() || dcsn_stat() || loop_stat())
        return 1;
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
        int x = stat();
        printf("Output: ");
        if(i==n && x)
            printf("accepted\n");
        else
            printf("rejected\n");
    }
    return 0;
}
/*
8
a=5
for(a=1;a<5;a=a+1)a=2
while(a<3)b=7
if(a>=5)a=5
if(a>=5)a=5elseb=6
if(a<=5)if(a<5)a=9
if(a<=5)for(b=1;b<9;b=1+1)c=c+1
for(a=1;a<5;a=a+1)for(a=1;a<5;a=a+1)for(a=1;a<5;a=a+1)for(a=1;a<5;a=a+1)a=9
*/

