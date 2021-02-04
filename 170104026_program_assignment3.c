#include<stdio.h>
#include<string.h>
///slno.->0 name->1 idtype->2 datatype->3 scope->4 value->5
char heading[] = "Sl.No.\t\tName\t\tIdType\t\tDataTp\t\tScope\t\tValue";
char table[50][50][50];
int slno = 0;
void ClearTable()
{
    int i, j, k;
    for(i = 0;i<50;i++)
    {
        for(j = 0;j<50;j++)
        {
            for(k = 0;k<50;k++)
            {
               table[i][j][k] = '\0';
            }
        }
    }
}
void Clear(char* s)
{
    int i;
    for(i = 0;i<50;i++)
    {
        s[i] = '\0';
    }
}
int isdatatype(char s[])
{
    int n = 5;
    char s2[5][20] = {"int","float","double","char", "void"};
    int i;
    for(i = 0;i<n;i++)
    {
        if(strcmp(s,s2[i])==0)
            return 1;
    }
    return 0;
}
int isid(char s[])
{
    if(strlen(s)>3 && s[0]=='i' && s[1]=='d' && s[2]==' ')
        return 1;
    return 0;
}
int isval(char s[])
{
    int bl = 0;
    int cnt = 0;
    int i;
    for(i = 0;i<strlen(s);i++)
    {
        if(s[i]>='0' && s[i]<='9')
            continue;
        if(s[i]=='.')
        {
            bl = 1;
            cnt++;
            continue;
        }
        return 0;
    }
    if( (bl && strlen(s)<=1) || cnt>1 )
        return 0;
    return 1;
}
void Mov(char* s1, char* s2)
{
    int i;
    Clear(s1);
    for(i = 0;i<strlen(s2);i++)
    {
        s1[i] = s2[i];
    }
}
void Mov2(char* s1, char* s2)
{
    int i;
    int j;
    Clear(s1);
    for(i = 3,j = 0;i<strlen(s2);i++,j++)
    {
        s1[j] = s2[i];
    }
}
void insert3(int i, int j,int slno)
{
    int x = slno;
    int cnt = 0;
    while(slno!=0)
    {
        slno/=10;
        cnt++;
    }
    int k;
    for(k = cnt-1;k>=0;k--)
    {
        table[i][j][k] = (x%10)+48;
        x/=10;
    }
    table[i][j][cnt]  = '\0';
}
void insert2(int i, int j, char s2[])
{
    int k;
    for(k = 0;k<strlen(s2);k++)
    {
        table[i][j][k] = s2[k];
    }
    table[i][j][k]  = '\0';
}
void Insert(int slno, char name[],char idtype[],char datatype[],char scope[])
{
    insert3(slno,0,slno+1);
    insert2(slno,1,name);
    insert2(slno,2,idtype);
    insert2(slno,3,datatype);
    insert2(slno,4,scope);
}
int Search(char s[], char scope[])
{
   int i,k;
   for(i = 0;i<slno;i++)
   {
       int bl = 1;
       char s2[50], s3[50];
       Clear(s2); Clear(s3);
       for(k = 0;table[i][1][k]!='\0';k++)
       {
           s2[k] =  table[i][1][k];
       }
       for(k = 0;table[i][4][k]!='\0';k++)
       {
           s3[k] =  table[i][4][k];
       }
       if(strcmp(s,s2)==0 && strcmp(scope,s3)==0)
           return i;
   }
   return -1;
}
void Update2(char s1[], char s2[], char scope[])
{
    int i1 = Search(s1,scope);
    int k;
    if(i1!=-1)
    {
        for(k = 0;k<strlen(s2);k++)
        {
            table[i1][2][k] = s2[k];
        }
        table[i1][2][k]  = '\0';
    }
}
void Update(char s1[], char s2[], char scope[])
{
    int i1 = Search(s1,scope);
    int i2 = Search(s2,scope);
    int k;
    if(i1!=-1)
    {
        for(k = 0;table[i2][5][k]!='\0';k++)
        {
            table[i1][5][k] = table[i2][5][k];
        }
        table[i1][5][k]  = '\0';
    }
    else
    {
        i1 = Search(s1,"global");
        if(i1 != -1)
        {
            for(k = 0;table[i2][5][k]!='\0';k++)
            {
                table[i1][5][k] = table[i2][5][k];
            }
            table[i1][5][k]  = '\0';
        }
    }
}
void Delete(int slno)
{
    if(slno<1)
        return;
    int i = slno-1, j, k;
    for(j = 0;j<50;j++)
    {
        for(k = 0;k<50;k++)
        {
            table[i][j][k] = '\0';
        }
    }
}
void Display()
{
    int i,j;
    printf("%s\n",heading);
    for(i = 0;i<slno;i++)
    {
        int bl = 0;
        int k;
        char s[50];
        Clear(s);
        for(k = 0;table[i][2][k]!='\0';k++)
        {
            s[k] = table[i][2][k];
        }
        if(strcmp("func",s)==0)
            bl = 1;
        for(j = 0;j<6;j++)
        {
            if(bl==1 && j==5)
                continue;
            printf("%s\t\t",table[i][j]);
        }
        printf("\n");
    }
}
void copy_to_file()
{
    FILE *p = fopen("step2_170104026_assignment3.txt","w");
    int i,j;
    for(i =0 ;i<strlen(heading);i++)
    {
        fputc(heading[i],p);
    }
    fputc('\n',p);
    for(i = 0;i<slno;i++)
    {
        int bl = 0;
        int k;
        char s[50];
        Clear(s);
        for(k = 0;table[i][2][k]!='\0';k++)
        {
            s[k] = table[i][2][k];
        }
        if(strcmp("func",s)==0)
            bl = 1;
        for(j = 0;j<6;j++)
        {
            if(bl==1 && j==5)
                continue;
            fprintf(p,"%s\t\t",table[i][j]);
        }
        fputc('\n',p);
    }
    fclose(p);
}
void display_through_file()
{
    FILE* p = fopen("step2_170104026_assignment3.txt","r");
    char c;
    while( (c = fgetc(p)) != EOF)
    {
        printf("%c",c);
    }
    fclose(p);
}
int main()
{
    ClearTable();
    printf("input:\n\n");
    FILE* p1 = fopen("input_170104026_assignment3.txt","r");
    char c;
    while( (c = fgetc(p1)) != EOF)
    {
        printf("%c",c);
    }
    fclose(p1);
    p1 = fopen("input_170104026_assignment3.txt","r");
    FILE* p2 = fopen("step1_170104026_assignment3.txt","w");
    char s[50];
    Clear(s);
    int cnt = 0;
    int i = 0;
    while( (c = fgetc(p1)) != EOF)
    {
       if(c==' ')
       {
           if(cnt%2==0)
           {
                if(strlen(s)==3 && s[0] =='[' && s[1]=='i' && s[2] == 'd')
                {
                    fputc(s[0],p2); fputc(s[1],p2); fputc(s[2],p2); fputc(c,p2);
                }
                else
                {
                     fputc(s[0],p2);
                }
                while(c!=']')
                {
                    c = fgetc(p1);
                    fputc(c,p2);
                }
           }
           else
           {
                fputc(c,p2);
           }
           cnt++;
           Clear(s);
           i = 0;
       }
       else
       {
          s[i] = c;
          i++;
       }
    }
    printf("\n\nstep1:\n\n");
    fclose(p2);
    p2 = fopen("step1_170104026_assignment3.txt", "r");
    while( (c = fgetc(p2)) != EOF)
    {
        printf("%c",c);
    }
    fclose(p2);
    p2 = fopen("step1_170104026_assignment3.txt", "r");
    char slno2[50], name[50], datatype[50], scope[50], value[50], last[50];
    Clear(slno2); Clear(name); Clear(datatype); Clear(scope); Clear(value), Clear(last);
    Mov(scope,"global");
    cnt = 0;
    Clear(s);
    i = 0;
    printf("\n");
    while( (c = fgetc(p2)) != EOF)
    {
        if(c=='[')
        {
            while(1)
            {
                c = fgetc(p2);
                if(c==']')
                    break;
                s[i] = c;
                i++;
            }
            if(isid(s))
            {
               /*
               check if id already exist
               if not insert slno, name, datatype, scope, idtype
               else check last
                  if last equals =
                      update ids value to value of row of name
                  if last equals to return
                      update ids value to value of  row of name which is equal to scope
               */
               char tmp[50]; Mov2(tmp,s);
               if(Search(tmp,scope)==-1 && strcmp(last,"=")!=0 ) //not found
               {
                   Insert(slno,tmp,"var",datatype, scope);
                   slno++;
               }
               else //found
               {
                   if(strcmp(last,"=")==0)
                   {
                      Update(name,tmp,scope);
                   }
                   else if(strcmp(last,"return")==0)
                   {
                      Update(scope,tmp,scope);
                   }
               }
               Mov2(name,s);
            }
            else if(isdatatype(s))
            {
               Mov(datatype,s);
            }
            else if(isval(s))
            {
               /*
               if last equals return
                  insert value to value of row of name which is equal to scope
               if last equals =
                  insert value to value of row of name
               */
               if(strcmp(last,"=")==0)
               {
                   if(Search(name,scope)!=-1)
                   {
                       insert2(Search(name,scope),5,s);
                   }
                   else if(Search(name,"global")!=-1 )
                   {
                       insert2(Search(name,"global"),5,s);
                   }
               }
               else if(strcmp(last,"return")==0)
               {
                   if(Search(scope,"global")!=-1)
                        insert2(Search(scope,"global"),5,s);
               }
               Mov(value,s);
            }
            else if(strlen(s)==1)
            {
                if(s[0]=='(')
                {
                    /*
                    check last
                    if last is a id
                        update names idtype to func
                        update scope variable
                    */
                    if(isid(last))
                    {
                        if(cnt==0)
                        {
                            Mov(scope,name);
                            Update2(name,"func","global");
                        }
                    }
                }
                ///else if(s[0]==')'){}else if(s[0]=='='){}else if(s[0]==';'){}
                else if(s[0]=='{')
                {
                    cnt++;
                }
                else if(s[0]=='}')
                {
                    cnt--;
                    /*
                    if cnt equals 0
                        update scope variable to global
                    */
                    if(cnt==0)
                        Mov(scope,"global");
                }
            }
            Mov(last,s);
        }
        else
        {
            Clear(s); i = 0;
        }
    }
    fclose(p2);
    printf("\nstep 2:\n\n");
    ///Display();
    copy_to_file();
    display_through_file();
    p2 = fopen("step1_170104026_assignment3.txt","r");
    FILE *p3 = fopen("step4_170104026_assignment3.txt", "w");
    Clear(s); i = 0; cnt = 0; Clear(scope); Clear(last); Clear(name); Mov(scope,"global");
    while( (c = fgetc(p2)) != EOF)
    {
        if(c=='[')
        {
            while(1)
            {
                c = fgetc(p2);
                if(c==']')
                    break;
                s[i] = c; i++;
            }
            if(isid(s))
            {
                char tmp[50]; Clear(tmp); Mov2(tmp,s);
                fputc('[',p3); fputc('i',p3); fputc('d',p3);
                if(Search(tmp,scope)!=-1)
                    fprintf(p3," %d",Search(tmp,scope)+1);
                else
                    fprintf(p3," %d",Search(tmp,"global")+1);
                fputc(']',p3);
                Mov2(name,s);
            }
            else if(strlen(s)==1)
            {
                if(s[0]=='(')
                {
                    if(isid(last))
                    {
                        if(cnt==0)
                        {
                            Mov(scope,name);
                        }
                    }
                }
                else if(s[0]=='{')
                {
                    cnt++;
                }
                else if(s[0]=='}')
                {
                    cnt--;
                    if(cnt==0)
                        Mov(scope,"global");
                }
                fputc('[',p3); fputc(s[0],p3); fputc(']',p3);
            }
            else
            {
                fputc('[',p3); fprintf(p3,"%s",s); fputc(']',p3);
            }
            Mov(last,s);
        }
        else
        {
            fputc(c,p3); Clear(s); i = 0;
        }
    }
    fclose(p2);
    fclose(p3);
    p3 = fopen("step4_170104026_assignment3.txt","r");
    printf("\nstep 4:\n\n");
    while( (c = fgetc(p3)) != EOF)
    {
        printf("%c",c);
    }
    fclose(p3);
    printf("\n");
    return 0;
}
