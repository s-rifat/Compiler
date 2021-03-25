#include<stdio.h>
int n,i;
char s[100];
int X()
{
    if(s[i]=='b')
    {
        i++;
        if(s[i]=='b' || s[i]=='c')
        {
            i++;
            return X();
        }
        return 0;
    }
    return 1;
}
int A()
{
    if(s[i]=='a')
    {
        i++;
        if(X())
        {
            if(s[i]=='d')
            {
                i++;
                return 1;
            }
            return 0;
        }
        return 0;
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
        int x = A();
        printf("Output: ");
        if( i==n && x)
            printf("accepted\n");
        else
            printf("rejected\n");
    }
    return 0;
}
/*
6
a
d
ad
abbd
abbda
abbbd
*/
