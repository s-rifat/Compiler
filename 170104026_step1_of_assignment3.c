#include<stdio.h>
int main()
{
    FILE *p1 = fopen("input.txt", "a");
    fputc(' ',p1);
    fclose(p1);
    p1 = fopen("input.txt", "r");
    FILE *p2 = fopen("output.txt","w");
    char s[100];
    int space = 0;
    int i = 0;
    char c;
    while( (c = fgetc(p1)) != EOF )
    {
        if(c==' ')
        {
            space++;
            if(space==2)
            {
                space  = 0;
                if(strlen(s)>=3 && s[1] == 'i' && s[2] == 'd')
                {
                    int j;
                    for(j = 0;j<strlen(s);j++)
                    {
                        fputc(s[j],p2);
                    }
                    fputc(' ',p2);
                }
                else
                {
                    fputc('[',p2);
                    int bl = 0;
                    int j;
                    for(j = 0;j<strlen(s);j++)
                    {
                        if(s[j]==' ')
                        {
                            bl = 1;
                            continue;
                        }
                        if(bl)
                        {
                            fputc(s[j],p2);
                        }
                    }
                    fputc(' ',p2);
                }
                int j;
                for(j=0;j<100;j++)
                    s[j] = '\0';
                i = 0;
            }
            else if(space == 1)
            {
                s[i] = c;
                i++;
            }
        }
        else
        {
            s[i] = c;
            i++;
        }
    }
    fclose(p1);
    fclose(p2);
    p2 = fopen("output.txt","r");
    while( (c = fgetc(p2)) != EOF )
    {
        printf("%c",c);
    }
    fclose(p2);
}
