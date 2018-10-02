#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#define timing 180
#define delay 3

char game[11][11],name[12],w[10],stack[10][10],queue[10][10];
int top=-1,front=-1,rear=-1;
FILE *P;
struct leader
{
    char name[12];
    int marks;
}temp2;
struct words
{
    char word [10];
}temp;
struct node
{
    char name[12];
    int marks;
    struct node* next;
}*head,*var,*trav;
void insert_list(int marks, char name[])
{
     var=(struct node *)malloc(sizeof (struct node));
     var->marks=marks;
     strcpy(var->name,name);
     if(head==NULL)
     {
         head=var;
         var->next=NULL;
     }
     else
     {
         var->next=head;
         head=var;
     }
}
void display_list()
{
    int i=0;
     trav=head;
     if(trav==NULL)
     {
          printf("\nNo History Available \n\n");
     }
     else
     {
          printf("\nHISTORY : \n\n");
          printf("NAME \t Marks \n\n");
          while(trav!=NULL && i<50)
          {
               printf("%s \t %d\n",trav->name,trav->marks);
               trav=trav->next;
               i++;
          }
      printf("\n");
      }
}
void push(char pk[])
{
    top++;
    strcpy(stack[top],pk);
}
char* pop()
{
    return(stack[top--]);
}
void traverse()
{
    int i,a=top;
    printf("\t\t   WORDS TO BE FOUND \n\n\t ");
    for(i=a;i>=0;i--)
    {
        printf("%-9s ",stack[i]);
        if (i==(int)(a/2 + 1))
        {
            printf("\n\t ");
        }
    }
    printf("\n\n");
}
void emptystack()
{
    while(top!=-1)
    {
        pop();
    }
}
void enqueue(char x[])
{
    if(rear==-1 && front==-1)
    {
        rear=0;
        front=0;
    }
    else
    {
        rear++;
    }
    strcpy(queue[rear],x);
    //printf("Queue - %s\n",queue[rear]);

}
int dequeue()
{
    char x[10];
    if(front>rear)
    {
        front=-1;
        rear=-1;
        return 0 ;
    }
    else
    {
        strcpy(x,queue[front]);
        front++;
        printf("%s\n",x);
        return 1;
    }
}
char* fill(int p,int q,int r,int s)
{
    char x[10];
    int i,j=0;
    if (q==0)
    {
        for(i=r-1;i<s;i++)
        {
            //printf("%c - %c - %s \n",x[j],game[p-1][i],x);
            x[j]=game[p-1][i];
            j++;
        }
        x[j]='\0';
    }
    else if(s==0)
    {
        for(i=p-1;i<q;i++)
        {
            x[j]=game[i][r-1];
            j++;
        }
        x[j]='\0';
    }
    enqueue(x);
    return(x);
}
int check(char x[])
{
    int i,a;
    char*y;
    if(top==-1)
    {
        //printf("empty");
        return(0);
    }
    y=pop();
    //printf("%s - %s \n",x,y);
    if(strcmpi(x,y)==0)
    {
        //printf("Found");
        return(1);
    }
    a=check(x);
    push(y);
    return(a);
}
void change(int p,int q,int r,int s)
{
    char x[10];
    int i,j;
    if(q==0)
    {
        for(i=r-1;i<s;i++)
        {
            game[p-1][i]=' ';
        }
    }
    else if (s==0)
    {
        for(i=p-1;i<q;i++)
        {
            game[i][r-1]=' ';
        }
    }
}
int input()
{
    int p=0,q=0,r=0,s=0,pk,trig;
    char* x;
    char a,b;
    printf("\n\nEnter 1 if you found a word \n");
    printf("Enter 2 if you end up finding the words \n\n");
    printf("Enter your choice ");
    fflush(stdin);
    scanf("%c",&a);
    printf("\n");
    switch(a)
    {
        case '1':
            printf("Press 1 for Horizontal \n");
            printf("Press 2 for Vertical \n");
            fflush(stdin);
            scanf("%c",&b);
            printf("\n");
            switch(b)
            {
                case '1':
                    printf("Enter Row ");
                    scanf("%d",&p);
                    printf("Enter Column in 'a-b' format ");
                    scanf("%d-%d",&r,&s);
                    if ( p<1 || p>10 || r<1 || r>10 || s<1 || s>10 )
                    {
                        printf("Arghhh Out of bound Coordinates ");
                        break;
                    }
                    x=fill(p,q,r,s);
                    pk=check(x);
                    //printf("\n%d - %s \n",pk,x);
                    if (pk==1)
                    {
                        change(p,q,r,s);
                        return(1);
                    }
                    break;
                case '2':
                    printf("Enter Column ");
                    scanf("%d",&r);
                    printf("Enter Row in 'a-b' format ");
                    scanf("%d-%d",&p,&q);
                    if ( p<1 || p>10 || r<1 || r>10 || q<1 || q>10 )
                    {
                        printf("Arghhh Out of bound Coordinates ");
                        break;
                    }
                    x=fill(p,q,r,s);
                    pk=check(x);
                    //printf("\n%d - %s \n",pk,x);
                    if(pk==1)
                    {
                        change(p,q,r,s);
                        return(1);
                    }
                    break;
                default:
                    printf("Arghhh !! Wrong Input ! \n");
                    return(0);
            }
            break;
        case '2':
            printf("\nYour Entered words are \n");
            while(1)
            {
                trig=dequeue();
                if(trig==0)
                {
                    break;
                }
            }
            return (-1);
            break;
        default:
        printf("Arghhhh !! Wrong Input ! \n");
        return(0);
    }

}
void display(char game[][11])
{
    int i,j;
    printf("\n\n\t    ");
    for(i=0;i<10;i++)
    {
        printf("%d ",i+1);
    }
    printf("\n\t    ");
    for(i=0;i<20;i++)
    {
        printf("-");
    }
    printf("\n");
    for(i=0;i<10;i++)
    {
        if(i==9)
        {
            printf("\t%d| ",i+1);
        }
        else
        {
            printf("\t %d| ",i+1);
        }
        for(j=0;j<10;j++)
        {
            printf("%c ",game[i][j]);
        }
        printf("\n\t  | \n");
    }
    printf("\n\n");
}
int file_size()
{
    int size=0;
    P=fopen("Words.txt","rb");
    while(fread(&temp,sizeof(temp),1,P)!=NULL)
    {
        size++;
    }
    fclose(P);
    return size;
}
int check_stack(char x[])
{
    char y[10];
    int a;
    if(top==-1)
    {
        return 0;
    }
    strcpy(y,pop());
    //y=pop();
    //printf("Checking %s \t %s \n",y,x);
    if (strcmpi(y,x)==0)
    {
        push(y);
        return(1);
    };
    a=check_stack(x);
    push(y);
    return(a);
}
void assign(char game[][11])
{
    int i=0,size,t,a,b,c,cont,j,p;
    time_t end;
    printf("Words in File - %d\n\n",size=file_size());
    printf("\t Wait a Minute, Building Your Game \n\n");
    srand(time(NULL));
    P=fopen("Words.txt","rb");
    end=time(NULL)+2;
    while(i<10)
    {
        t=rand()%size;
        //printf("%d\n",t);
        fseek(P,t*sizeof(temp),SEEK_SET);
        fread(&temp,sizeof(temp),1,P);
        //printf("\n%s\n",temp.word);
        p=check_stack(temp.word);
        if(p==1)
        {
            continue;
        }
        while(1)
        {
           if(time(NULL)>end)
           {
               //printf("Hell Yeah");
               emptystack();
               fclose(P);
                for(i=0;i<10;i++)
                {
                    for(j=0;j<10;j++)
                    {
                        game[i][j]='1';
                    }
                    game[i][j]='\0';
                }
               assign(game);
               return;
           }
           else
           {
               printf("");
               //printf("Time ni hua %d \n",end-time(NULL));
           }
           a=rand()%2;
           cont=0;
           if (a==0)
           {
               b=rand()%10;
               c=rand()%(10-strlen(temp.word));
               for(j=0;j<strlen(temp.word);j++)
               {
                   if (game[b][c+j]!='1')
                   {
                       cont=0;
                       break;
                   }
                   cont=1;
               }
               if (cont==1)
               {
                    //printf("\nYES_Horizontal\n");
                    for(j=0;j<strlen(temp.word);j++)
                    {
                        game[b][c+j]=temp.word[j];
                    }
                    break;
               }
               if (cont==0)
               {
                   //printf("\nNo_Horizontal\n");
               }
           }
           else
           {
               c=rand()%10;
               b=rand()%(10-strlen(temp.word));
               for(j=0;j<strlen(temp.word);j++)
               {
                   if (game[b+j][c]!='1')
                   {
                       cont=0;
                       break;
                   }
                   cont=1;
               }
               if (cont==1)
               {
                    //printf("\nYES_Vertical\n");
                    for(j=0;j<strlen(temp.word);j++)
                    {
                        game[b+j][c]=temp.word[j];
                    }
                    break;
               }
               if (cont==0)
               {
                   //printf("\nNo_Vertical\n");
               }
           }
        }
        push(temp.word);
        i++;
        // Push temp.word in Stack
    }
    fclose(P);

}
void random(char game[][11])
{
    int i,j,v;
    srand(time(NULL));
    for(i=0;i<10;i++)
    {
        for (j=0;j<10;j++)
        {
            if(game[i][j] == '1')
            {
                v=65+(rand()%26);
                game[i][j]=(char)v;
            }
        }
    }
}
void insert_word(char w[])
{
    P=fopen("Words.txt","ab");
    strcpy(temp.word,w);
    fwrite(&temp,sizeof(temp),1,P);
    fclose(P);
}
int file_handle(char w[])
{
    if( access( "Words.txt", F_OK ) != -1 )
    {
        P=fopen("Words.txt","rb");
    }
    else
    {
        return(1);
    }
    while(fread(&temp,sizeof(temp),1,P)!=NULL)
    {
        if (strcmpi(temp.word,w)==0)
        {
            fclose(P);
            return(0);
        }
    }
    fclose(P);
    return(1);

}
int check_word(char w[])
{
    int x;
    x=strlen(w);
    //printf("%d\n",x);
    if ( x>9 || x<3)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
void insert_file(int marks, char name[])
{
    P=fopen("Leader.txt","ab");
    strcpy(temp2.name,name);
    temp2.marks=marks;
    fwrite(&temp2,sizeof(temp2),1,P);
    fclose(P);
}
void display_file()
{
    int i=1,m=10;
    //P=fopen("Leader.txt","rb");
    printf("Rank  Name\t Marks \n\n");
    while(i<=50)
    {
        P=fopen("Leader.txt","rb");
        while(fread(&temp2,sizeof(temp2),1,P)!=NULL)
        {
            if (temp2.marks==m)
            {
                printf("%-5d %-9s  %d \n",i,temp2.name,temp2.marks);
                i++;
            }
        }
        fclose(P);
        if (m==0)
        {
            break;
        }
        m--;
    }
}
int main()
{
    int a,i,j,n,b,c,d,p,marks=0,pk,trig;
    char ans[10],chh,ch;
    time_t end,curr;
    printf("\n\n\n\n");
    printf("\t\t\t\t WORDPLAY \n\n\n");
    for(i=0;i<5;i++)
    {
        end=time(NULL)+1;
        while(time(NULL)<end)
        {
        }
        for(j=0;j<5;j++)
        {
            printf("WORDPLAY\t");
        }
        printf("\n");
    }
    printf("\n\n Press any key to continue   - ");
    getch();
    system("cls");
    do
    {
        printf("\n\n\n\n");
        printf("\t 1. Play Game \n");
        printf("\t 2. Add Words \n");
        printf("\t 3. History \n");
        printf("\t 4. LeaderBoard \n");
        printf("\t 0. Exit \n\n");
        fflush(stdin);
        printf("\t Enter Your Choice - ");
        scanf("%c",&ch);
        printf("\n\n");
        switch(ch)
        {
            case '0':
                printf("\n\n Good Bye \n\n");
                ch='0';
                break;
            case '1':
                if (file_size()<10)
                {
                    printf("\nAt least 10 words required in Building the Game \n\n");
                    break;
                }
                printf("");
                printf("");
                printf("");
                printf("\n\n\n");
                printf("Enter Your Name to continue - ");
                fflush(stdin);
                gets(name);
                fflush(stdin);
                printf("\n\n");
                for(i=0;i<10;i++)
                {
                    for(j=0;j<10;j++)
                    {
                        game[i][j]='1';
                    }
                    game[i][j]='\0';
                }
                assign(game);
                random(game);
                system("cls");
                display(game);
                traverse();
                printf("\n\n");
                marks=0;
                end = time(NULL)+ timing;
                while(1)
                {
                    printf ("\nYou have %d seconds left to finish this \n\n",end - time(NULL));
                    pk=input();
                    if(time(NULL)>end)
                    {
                        system("cls");
                        printf("\n\nOoops !! TIME UP \n\n");
                        printf("\nYour Entered words are \n");
                        while(1)
                        {
                            trig=dequeue();
                            if(trig==0)
                            {
                                break;
                            }
                        }
                        break;
                    }
                    curr=time(NULL);
                    while (time(NULL)!=curr+delay);
                    system("cls");
                    if (pk==-1)
                    {
                        system("cls");
                        break;
                    }
                    if (pk==1)
                    {
                        marks+=pk;
                        printf("\n%d Words Found\n\n",marks);
                    }
                    else
                    {
                        printf("\nOoops !! This was not meant to be Searched \n\n");
                    }
                    display(game);
                    traverse();
                }
                printf("\n\nTotal Marks out of 10 - %d\n\n",marks);
                insert_list(marks,name);
                insert_file(marks,name);
                emptystack();
                printf("\nEnter any key to continue \n");
                getch();
                system("cls");
                break;
            case '2':
                system("cls");
                do
                {
                    printf("\n\nEnter Word - ");
                    fflush(stdin);
                    gets(w);
                    fflush(stdin);
                    p=check_word(strupr(w));
                    if (p==0)
                    {
                        printf("\nPlease Enter word of length 3-9 \n\n");
                    }
                    else
                    {
                        p=file_handle(strupr(w));
                        if (p==0)
                        {
                            printf("\nWord Already Exists In Database \n");
                        }
                        else
                        {
                            insert_word(strupr(w));
                            printf("\nWord Accepted \n");
                        }
                    }
                    printf("\n Enter Y to enter more words ");
                    scanf("%c",&chh);
                }while(chh == 'Y');
                system("cls");
                break;
            case '3':
                system("cls");
                printf("\n");
                display_list();
                printf("\nHistory for only current session will be showed \n\n\n");
                printf("Enter any key to continue \n");
                getch();
                system("cls");
                break;
            case '4':
                system("cls");
                printf("\n\n");
                if( access( "Leader.txt", F_OK ) == -1 )
                {
                    printf("NOT AVAILABLE \n\n");
                    break;
                }
                printf("\t LEADERBOARD \n\n");
                display_file();
                printf("\n\n* Upto 50 ranks only \n\n");
                printf("Enter any key to continue \n");
                getch();
                system("cls");
                break;
            default:
                printf("Arghh ! Wrong Input !! ");
        }

    }while(ch!='0');
    return(0);
}
