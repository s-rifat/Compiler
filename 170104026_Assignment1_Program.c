#include<stdio.h>
int main()
{
    FILE *p1, *p2;
    p1 = fopen("170104026_Assignment1_Input.cpp","r");
    p2 = fopen("170104026_Assignment1_Output.txt","w");
    char c;
    char print[6] = "printf"; //for checking printf as everything in printf will remain unchanged
    int i = 0;
    int space = 1; // space equals 1 means first space
    int first = 0; //beginning space
    int first2 = 0; //beginning tab
    int tab = 1;
    if(!p1)
        printf(  "File does not exist!\n");
    else
    {
        while( (c = fgetc(p1) )!=EOF)
        {
            if(first == 0 && c ==' ')
            {
                continue;
            }
            if(first2 == 0 && c =='\t')
            {
                continue;
            }
            first = 1;
            first2 = 1;
            if(i==6) // found a printf
            {
                i = 0;
                int space = 1;
                fputc(c,p2);
                if(c==' ') //checking space right after printf
                {
                    space = 2;
                    tab = 2;
                }
                else if(c=='\t')
                {
                     space = 2;
                     tab = 2;
                }
                int quot = 0;
                while(1)
                {
                    c = fgetc(p1);
                    if(c==';') // printf statement ends here
                    {
                        fputc(c,p2);
                        break;
                    }
                    if(c=='"') // checking if quotation is found
                        quot++;

                    if( c==' ' && quot == 0) // quot equals 0 means we are not inside quotation
                    {
                        if(space == 1) // space equals 1 means first space
                        {
                            fputc(c,p2);
                            space = 2; // space equals 2 //means not first space
                            tab = 2;
                        }
                    }
                    else if(c=='\t' && quot == 0)
                    {
                        if(tab == 1) // space equals 1 means first space
                        {
                            fputc(' ',p2);
                            space = 2; // space equals 2 means not first space
                            tab = 2;
                        }
                    }
                    else // all other cases except space and quotation
                    {
                        fputc(c,p2);
                        space = 1; // reassigned space to 1
                        tab = 1;
                        if(quot==2) //quotation ends here
                            quot = 0;
                    }
                }
            }
            else if(c==print[i])// matching with printf
            {
                fputc(c,p2);
                i++;
            }
            else if(c=='\n') // ignoring new line
            {
                i = 0;
                continue;
            }
            else if(c=='/') // it can be a comment
            {
                i = 0;
                char c2  = fgetc(p1);
                int bol = 1;
                if(c2=='/') // singe line comment found
                {
                    while(1)
                    {
                        c = fgetc(p1);
                        if(c=='\n') // single line comment ends here
                        {
                            bol = 2;
                            break;
                        }
                    }
                }
                if(bol==2)
                    continue;
                if(c2=='*') // multiple line comments starts
                {
                    while(1)
                    {
                        c = fgetc(p1);
                        if(c=='*')
                        {
                            char c2 = fgetc(p1);
                            if(c2=='/') // multiple line comments ends here
                            {
                                bol = 2;
                                break;
                            }
                        }
                    }
                }
                if(bol==2)
                    continue;
                fputc(c,p2); // it was not a comment
                fputc(c2,p2);// it was not a comment
            }
            else if(c == ' ') // space found
            {
                i = 0;
                if(space == 1) // space equals 1 means first space
                {
                    fputc(c,p2);
                    space = 2; // space equals 2 means not first space
                    tab = 2;
                }
            }
            else if(c=='\t')
            {
                i = 0;
                if(tab == 1) // space equals 1 means first space
                {
                    fputc(' ',p2);
                    space = 2; // space equals 2 means not first space
                    tab = 2;
                }
                continue;
            }
            else //all other cases except space, newline and printf
            {
                i = 0;
                fputc(c,p2);
                space = 1;
                tab = 1;
            }
        }
    }
    fclose(p1);
    fclose(p2);
    p1 = fopen("170104026_Assignment1_Input.cpp","r");
    while((c = fgetc(p1))!=EOF)
    {
        printf("%c",c);
    }
    printf("\n");
    p2 = fopen("170104026_Assignment1_Output.txt","r");
    while((c = fgetc(p2))!=EOF)
    {
        printf("%c",c);
    }
    fclose(p1);
    fclose(p2);
}
