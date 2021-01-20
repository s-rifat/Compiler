#include<stdio.h>
int is_keyword(char s[])
{
    int n = 32;
    char s2[32][20] = {"int","char","float","if","else","for", "while", "do",
    "return","double", "include", "auto", "break", "continue", "default", "long",
    "signed", "sizeof", "struct", "static", "switch", "typedef", "unsigned", "void",
    "case", "const", "short", "enum", "extern", "goto", "register", "volative"};
    int i, j;
    for(i=0;i<n;i++)
    {
        if(strcmp(s,s2[i])==0)
            return 1;
    }
    return 0;
}
int is_identifier(char s[])
{
    int a = 0;
    if( (s[0]>='a' && s[0]<='z') || (s[0]>='A' && s[0]<='Z') || (s[0]=='_') )
        a++;
    if(a!=1)
        return 0;
    int i;
    for(i=1;i<strlen(s);i++)
    {
        if( (s[i]>='a' && s[i]<='z') || (s[i]>='A' && s[i]<='Z') || (s[i]=='_') || (s[i]>='0' && s[i]<='9') )
            a++;
        if(a!=i+1)
            return 0;
    }
    return 1;
}
int is_number(char s[])
{
    int i;
    int bl = 0;
    for(i=0;i<strlen(s);i++)
    {
        if( (s[i]<='9' && s[i]>='0'))
            continue;
        if(s[i]=='.')
        {
            bl = 1;
            continue;
        }
        return 0;
    }
    if(bl == 1 && strlen(s)<=1)
        return 0;
    return 1;
}
int is_hash(char c)
{
    if(c=='#')
        return 1;
    return 0;
}
int is_operator(char c)
{
    if( c=='+' || c=='-' || c=='*' || c=='/' || c=='%' || c =='=' ||
       c == '>' || c == '<' || c=='!' || c=='|' || c=='^')
        return 1;
    return 0;
}
int is_operator2(char c1, char c2)
{
    if( (c1=='+' && c2=='+') || (c1=='-' && c2=='-') || (c1=='=' && c2=='=') || (c1=='!' && c2=='=') ||
       (c1=='>' && c2=='=') || (c1=='<' && c2=='=') || (c1=='&' && c2=='&') || (c1=='|' && c2=='|') ||
       (c1=='<' && c2=='<') || (c1=='>' && c2=='>'))
            return 1;
    return 0;
}
int is_separator(char c)
{
    if( c==';' || c==',')
        return 1;
    return 0;
}
int is_function(char s[])
{
    int n = 3;
    char s2[3][10] = {"printf","scanf","main"};
    int i, j;
    for(i=0;i<n;i++)
    {
        if(strcmp(s,s2[i])==0)
            return 1;
    }
    return 0;
}
int is_char(char s[])
{
   if(strlen(s)==3 && s[0] =='\'' && s[2] == '\'')
     return 1;
   return 0;
}
int is_paranthesis(char c)
{
    if( c=='(' || c==')' || c == '{' || c== '}')
        return 1;
    return 0;
}
int is_header(char s[])
{
    int n = strlen(s);
    if(strlen(s)>=3 && s[n-2] == '.')
        return 1;
    return 0;
}
int main()
{
    char c;
    FILE *p1 = fopen("170104026_input_assignment2.txt","r");
    printf("Sample Input:\n");
    while( (c = fgetc(p1)) !=EOF)
    {
        printf("%c",c);
    }
    printf("\n\n");
    fclose(p1);
    p1 = fopen("170104026_input_assignment2.txt","r");
    FILE *p2 = fopen("170104026_step1_assignment2.txt","w");
    if(p1==NULL)
    {
        printf("File can not be open");
        return 0;
    }
    int bl = 2;
    int lastSpace = 0;
    int first = 1;
    while( (c = fgetc(p1)) !=EOF)
    {
         if(c== '"')
         {
             c = fgetc(p1);
             while(c!='"')
             {
                c = fgetc(p1);
             }
             c = fgetc(p1);
         }
         if(is_operator(c))
         {
             char c2 = fgetc(p1);
             if(is_operator2(c,c2))
             {
                if(lastSpace == 0 && first == 0)
                {
                    fputc(' ',p2);
                }

                fputc(c,p2);
                fputc(c2,p2);
                bl = 1;
                first = 0;
                continue;
             }
             else
             {
                if(lastSpace == 0 && first == 0)
                    fputc(' ',p2);
                fputc(c,p2);
                bl = 1;
                c = c2;
                first = 0;
             }
             lastSpace = 0;
         }
         if(is_hash(c))
         {
             if(lastSpace == 0 && first == 0)
                fputc(' ',p2);
             fputc(c,p2);
             bl = 1;
             lastSpace = 0;
             first = 0;
             continue;
         }
         if(is_separator(c) || is_paranthesis(c) )
         {
             if(lastSpace == 0 && first == 0)
                fputc(' ',p2);
             fputc(c,p2);
             bl = 1;
             lastSpace = 0;
             first = 0;
             continue;
         }
         if(c==' ')
         {
             fputc(c,p2);
             bl = 2;
             lastSpace = 1;
             first = 0;
             continue;
         }
         if(bl==1)
         {
             if(first == 0)
                fputc(' ',p2);
             first = 0;
         }
         fputc(c,p2);
         bl = 2;
         lastSpace = 0;
         first = 0;
    }
    fputc(' ',p2);
    fclose(p1);
    fclose(p2);
    p2 = fopen("170104026_step1_assignment2.txt","r");
    printf("Step 1:\n");
    while( (c = fgetc(p2)) !=EOF)
    {
        printf("%c",c);
    }
    printf("\n\n");
    fclose(p2);
    p2 = fopen("170104026_step1_assignment2.txt","r");
    FILE *p3 = fopen("170104026_output_assignment2.txt", "w");
    char s[100];
    int i = 0;
    while( (c = fgetc(p2)) !=EOF)
    {
        if(c==' ')
        {
            if(is_keyword(s))
            {
                fputc('[',p3);
                fputc('k',p3);
                fputc('w',p3);
                fputc(' ',p3);
                int j;
                for(j = 0;j<strlen(s);j++)
                {
                    fputc(s[j],p3);
                }
                fputc(']',p3);
                fputc(' ',p3);
            }
            else if(is_function(s))
            {
                fputc('[',p3);
                fputc('f',p3);
                fputc('n',p3);
                fputc(' ',p3);
                int j;
                for(j = 0;j<strlen(s);j++)
                {
                    fputc(s[j],p3);
                }
                fputc(']',p3);
                fputc(' ',p3);
            }
            else if(is_number(s))
            {
                fputc('[',p3);
                fputc('n',p3);
                fputc('u',p3);
                fputc('m',p3);
                fputc(' ',p3);
                int j;
                for(j = 0;j<strlen(s);j++)
                {
                    fputc(s[j],p3);
                }
                fputc(']',p3);
                fputc(' ',p3);
            }
            else if(is_identifier(s))
            {
                fputc('[',p3);
                fputc('i',p3);
                fputc('d',p3);
                fputc(' ',p3);
                int j;
                for(j = 0;j<strlen(s);j++)
                {
                    fputc(s[j],p3);
                }
                fputc(']',p3);
                fputc(' ',p3);
            }
            else if(is_char(s))
            {
                fputc('[',p3);
                fputc('c',p3);
                fputc('h',p3);
                fputc(' ',p3);
                int j;
                for(j = 0;j<strlen(s);j++)
                {
                    fputc(s[j],p3);
                }
                fputc(']',p3);
                fputc(' ',p3);
            }
            else if(is_header(s))
            {
                fputc('[',p3);
                fputc('h',p3);
                fputc('d',p3);
                fputc(' ',p3);
                int j;
                for(j = 0;j<strlen(s);j++)
                {
                    fputc(s[j],p3);
                }
                fputc(']',p3);
                fputc(' ',p3);
            }
            else if(strlen(s)==2 && is_operator2(s[0], s[1]))
            {
                fputc('[',p3);
                fputc('o',p3);
                fputc('p',p3);
                fputc(' ',p3);
                int j;
                for(j = 0;j<strlen(s);j++)
                {
                    fputc(s[j],p3);
                }
                fputc(']',p3);
                fputc(' ',p3);
            }
            else if(strlen(s)==1 && is_paranthesis(s[0]))
            {
                fputc('[',p3);
                fputc('p',p3);
                fputc('a',p3);
                fputc('r',p3);
                fputc(' ',p3);
                int j;
                for(j = 0;j<strlen(s);j++)
                {
                    fputc(s[j],p3);
                }
                fputc(']',p3);
                fputc(' ',p3);
            }
            else if(strlen(s)==1 && is_operator(s[0]))
            {
                fputc('[',p3);
                fputc('o',p3);
                fputc('p',p3);
                fputc(' ',p3);
                int j;
                for(j = 0;j<strlen(s);j++)
                {
                    fputc(s[j],p3);
                }
                fputc(']',p3);
                fputc(' ',p3);
            }
            else if(strlen(s)==1 && is_separator(s[0]))
            {
                fputc('[',p3);
                fputc('s',p3);
                fputc('e',p3);
                fputc('p',p3);
                fputc(' ',p3);
                int j;
                for(j = 0;j<strlen(s);j++)
                {
                    fputc(s[j],p3);
                }
                fputc(']',p3);
                fputc(' ',p3);
            }
            else if(strlen(s)==1 && is_hash(s[0]))
            {
                fputc('[',p3);
                fputc('h',p3);
                fputc('s',p3);
                fputc(' ',p3);
                int j;
                for(j = 0;j<strlen(s);j++)
                {
                    fputc(s[j],p3);
                }
                fputc(']',p3);
                fputc(' ',p3);
            }
            else
            {
                fputc('[',p3);
                fputc('u',p3);
                fputc('n',p3);
                fputc('k',p3);
                fputc('n',p3);
                fputc(' ',p3);
                int j;
                for(j = 0;j<strlen(s);j++)
                {
                    fputc(s[j],p3);
                }
                fputc(']',p3);
                fputc(' ',p3);
            }
            int j;
            for(j = 0;j<100;j++)
            {
                s[j] = '\0';
            }
            i = 0;
        }
        else
        {
            s[i] = c;
            i++;
        }
    }
    fputc('$',p2);
    fclose(p2);
    fclose(p3);
    p3 = fopen("170104026_output_assignment2.txt","r");
    printf("Step 2:\n");
    while( (c = fgetc(p3)) !=EOF)
    {
        printf("%c",c);
    }
    printf("\n");
    fclose(p3);
    return 0;
}
