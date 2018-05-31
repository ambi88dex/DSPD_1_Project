  #include<stdio.h>
#include<string.h>
#define MAX_BOOKS 1000

typedef enum { FAILURE, SUCCESS}STATUS_CODE ;
//STATUS_CODE status ;
typedef struct {
        char bookName[50];
        char author[50];
        int yrOfPub;
        int availCopies ;
    } Book ;

/*-----------------------------INITIALISATION ---------------------------------
------------------------------------------------------------------------------*/
void initialise(Book* ls)
{
    int i;
    for(i=0;i<MAX_BOOKS;i++)
    {
        int yrOfPub;
        ls[i].bookName[0]='\0';
        ls[i].author[0]='\0';
        ls[i].yrOfPub=0;
        ls[i].availCopies=0;
    }
}
/*------------------------------------MERGE SORT IMPLEMENTATION ---------------------------------
---------------------------------------------------------------------------------------------------*/
void mergeAut(Book *ls, int low ,int mid,int high , Book *temp)
{
int i1=low,i2=mid+1,i3=low;
    while(i1<=mid && i2 <=high)
    {
          if(strcmp(ls[i1].author,ls[i2].author)>0)
          {
            temp[i3]=ls[i2];
            i2++;
            i3++;
          }
          else //if(strcmp(ls[i1].author,ls[i2].author)<0)
          {
            temp[i3]=ls[i1];
            i1++;
            i3++;
          }

    }
      while(i2<=high)
      {
        temp[i3]=ls[i2];
        i2++;
        i3++;
      }
      while(i1<=mid)
      {
        temp[i3]=ls[i1];
        i1++;
        i3++;
      }
      // showData(ls,lastIndex1);
      // showData(ls,lastIndex2);
      printf("\n");
      for( i1 =low;i1<=high;i1++)
      {
        ls[i1]=temp[i1];
      }
      //showData(ls,i3-1);

}
/////////////////////////////////////////////////////////
void mergeAutWise( Book *ls,int low ,int high , Book *temp)
{
  int mid= (low + high)/2;
  if (low == high )
  {
      return ;
  }
  else
  {
    mergeAutWise(ls,low,mid,temp);
    mergeAutWise(ls,mid+1,high,temp);
    mergeAut(ls,low,mid,high,temp);
  }
}
/*--------------------------------------------------------*/
void merge(Book *ls, int low ,int mid,int high , Book *temp)
{
int i1=low,i2=mid+1,i3=low;
    while(i1<=mid && i2 <=high)
    {
          if(strcmp(ls[i1].bookName,ls[i2].bookName)>0)
          {
              temp[i3]=ls[i2];
              i2++;
              i3++;
          }
          else if(strcmp(ls[i1].bookName,ls[i2].bookName)<0)
          {
            temp[i3]=ls[i1];
            i1++;
            i3++;
          }
          else if(strcmp(ls[i1].author,ls[i2].author)>0)
          {
            temp[i3]=ls[i2];
            i2++;
            i3++;
          }
          else if(strcmp(ls[i1].author,ls[i2].author)<0)
          {
            temp[i3]=ls[i1];
            i1++;
            i3++;
          }
          else if(strcmp(ls[i1].author,ls[i2].author)==0)
          {
             if(ls[i1].yrOfPub > ls[i2].yrOfPub)
             {
               temp[i3]=ls[i1];
               i1++;
               i2++;
               i3++;
             }
             else
             {
               temp[i3]=ls[i2];
               if(ls[i1].yrOfPub == ls[i2].yrOfPub)
               {
                 temp[i3].availCopies=ls[i1].availCopies + ls[i2].availCopies;
               }
               i1++;
               i2++;
               i3++;
             }
          }
    }
      while(i2<=high)
      {
        temp[i3]=ls[i2];
        i2++;
        i3++;
      }
      while(i1<=mid)
      {
        temp[i3]=ls[i1];
        i1++;
        i3++;
      }
      // showData(ls,lastIndex1);
      // showData(ls,lastIndex2);
      printf("\n");
      for( i1 =low;i1<=high;i1++)
      {
        ls[i1]=temp[i1];
      }
      //showData(ls,i3-1);

}
/////////////////////////////////////////////////////////
void mergeSortKeyWise( Book *ls,int low ,int high , Book *temp)
{
  int mid= (low + high)/2;
  if (low == high )
  {
      return ;
  }
  else
  {
    mergeSortKeyWise(ls,low,mid,temp);
    mergeSortKeyWise(ls,mid+1,high,temp);
    merge(ls,low,mid,high,temp);
  }
}

/*----------------------------------INSERTION FUNCTION ---------------------------------------------
---------------------------------------------------------------------------------------------------*/
STATUS_CODE insert(Book* ls, char* bookName , char* author , int yrOfPub , int* ctptr, int* lastIndexPtr)
{

    int elemFound =0;
    STATUS_CODE status =SUCCESS;
    int i=0;
    int cmp;
    while(ls[i].bookName[0]!='\0' && elemFound == 0/*&& ls[i].author[0]!='\0' */ ) //search till hole
    {
       // If duplicate is inputed
       if (!(strcmp(ls[i].bookName,bookName) || strcmp(ls[i].author,author) )) // if key is found
       {
            elemFound =1;
       }
       i++;
    }
    if(elemFound == 0) //if element is not found
    {
           if(i < MAX_BOOKS)
           {
                (*ctptr)++;
                (*lastIndexPtr)++;
                strcpy(ls[i].bookName,bookName);
                strcpy(ls[i].author,author);
                ls[i].yrOfPub=yrOfPub;
                ls[i].availCopies=1;
           }
           else
           {
            status = FAILURE;
           }
    }
    else
    {
        ls[i-1].availCopies++;
    }
    return status;
}
/*----------------------------------------------------SHOW DATA ----------------------------------
-----------------------------------------------------------------------------------------------*/

void showData(Book* ls ,int lastIndex)
{
   int i;
   for(i=0;i<=lastIndex;i++)
   {
        if(ls[i].bookName[0]!='\0')
        {
            printf("%s\t%s\t%d\t%d\t",ls[i].bookName,ls[i].author,ls[i].yrOfPub,ls[i].availCopies);
            printf("\n");
        }

   }
}
/*--------------------------------------------DELETION OF AN ELEMENT-----------------------------
-----------------------------------------------------------------------------------------------*/
STATUS_CODE deletion(Book* ls, char* bookName, char* author ,int* ctptr ,int lastIndex)
{
    int i;
    STATUS_CODE ret_val=SUCCESS;
    int flag= 0;
    for(i=0;i<=lastIndex && flag==0;i++)
    {
        if(!(strcmp(ls[i].bookName, bookName) ||  strcmp(ls[i].author,author) )) // if the key is matched
        {
            flag=1;
            if(ls[i].availCopies>1)
            {
                ls[i].availCopies--;
            }
            else
            {
                ls[i].bookName[0]='\0';
                ls[i].author[0]='\0';
                ls[i].yrOfPub=0;
                ls[i].availCopies=0;
                (*ctptr)--;
            }
        }
    }
    if (flag == 0)
    {
        ret_val = FAILURE;
    }
    return ret_val;
}
/*------------------------------------------------GET-TOPMOST BOOK AUTHOR -----------------------
-----------------------------------------------------------------------------------------------*/
void topMostAuthor(Book* ls, char* author,char* BookName , int lastIndex)
{
    int i=0;
    int mx=0;
    while(i <= lastIndex)
    {
          if(strcmp(ls[i].bookName, BookName)==0)
          {
                if(mx < ls[i].availCopies)
                {
                    mx=ls[i].availCopies;

                    strcpy(author,ls[i].author);
                }
                else if( mx == ls[i].availCopies)
                {
                    strcat(author," , ");
                    strcat(author,ls[i].author);
                }
          }
          i++;
    }

}
/*--------------------------SWAP STRUCUTURES -------------
---------------------------------------------------------*/

void swap_structures(Book* ls1ptr, Book* ls2ptr )
{
    Book temp;
    strcpy(temp.bookName,ls1ptr->bookName);
    strcpy(temp.author,ls1ptr->author);
    temp.yrOfPub=ls1ptr->yrOfPub;
    temp.availCopies=ls1ptr->availCopies;

    strcpy(ls1ptr->bookName,ls2ptr->bookName);
    strcpy(ls1ptr->author,ls2ptr->author);
    ls1ptr->yrOfPub=ls2ptr->yrOfPub;
    ls1ptr->availCopies=ls2ptr->availCopies;

    strcpy(ls2ptr->bookName,temp.bookName);
    strcpy(ls2ptr->author,temp.author);
    ls2ptr->yrOfPub=temp.yrOfPub;
    ls2ptr->availCopies=temp.availCopies;

}

/*--------------------------SORTING_AUTHOR_WISE---------
--------------------------------------------------------*/

/*--------------------------------FindMostPopularAuthor-------------------------
---------------------------------------------------------------------------------*/

void findMostPopularAuthor(Book* ls,char* str,int ct,int lastIndex)
{
    int i=lastIndex-ct+1;
    int sum=0;
    int flag=0;
    int mx=0;
    while(i<lastIndex)
    {
        sum=ls[i].availCopies;
        flag=0;
        while(flag==0 && i <lastIndex)
        {
            if(strcmp(ls[i].author,ls[i+1].author)== 0)
            {
                sum+= ls[i+1].availCopies;
                i++;
            }
            else
            {
                flag =1;
            }
        }
        if(sum>mx)
        {
            mx=sum;
            strcpy(str,ls[i].author);
        }
        i++;
    }
}
/*---------------------------------------SORTBOOKCOPYWISE-----------------
------------------------------------------------------------------------*/
void KsortBookPopWise(Book* ls,int lastIndex ,int k )
{
    int i,j;
    int flag=0;
    for(i=0;i<=k && flag==0;i++)
    {
        flag = 1;
        for(j=0;j<=lastIndex-i-1;j++)
        {
            if(ls[j].availCopies<ls[j+1].availCopies)
            {
                swap_structures(&ls[j],&ls[j+1]);
                flag = 0;
            }
        }
    }
}

/*----------------------------------findLeastPopAuthor()---------
------------------------------------------------------------------*/
void findLeastPopAuthor(Book* ls, char* str_author ,int ct, int lastIndex ,int p ,int k)
{
  int i=lastIndex-ct+1;
  int flag=0;
  int pcount=0,tcount=0;
  float perc;
  str_author[0]='\0';
  while(i<lastIndex)
  {
      flag=0;
      pcount=0;
      tcount=0;
      if(ls[i].availCopies < p)
      {
        pcount++;
      }
      tcount++;
      while(flag==0 && i <lastIndex)
      {
          if(strcmp(ls[i].author,ls[i+1].author)== 0)
          {
              if(ls[i+1].availCopies < p)
              {
                pcount++;
              }
              i++;
              tcount++;
          }
          else
          {
              flag =1;
          }
      }
      perc=pcount/(tcount*1.0);
      perc*=100;
      if(perc>=k)
      {
          if(strlen(str_author)!=0)
          {
             strcat(str_author, " , ");
          }
          strcat(str_author,ls[i].author);

      }
      i++;
  }
}
/*------------------------------------------------------------------
------------------------------------------------------------------*/
int main()
{

    STATUS_CODE sc;
    Book book1;
    /*strcpy(book1.bookName,"Wren and Martin");
    strcpy(book1.author,"Wren and Martin");
    book1.yearOfPublication = 2001;
    book1.availCopies = 0;

    Book* ptr;
    ptr = &book1;
    ptr = &book1;
    printf("%s",ptr->bookName);
    */
    FILE* f1;
    Book ls[MAX_BOOKS];
    initialise(ls);
    int choice ;
    printf(" \
    1)To insert an element press 1 \n \
    2)To delete an element press 2\n \
    3)To get number of records int the library press 3\n \
    4)To check if the list is empty press 4 \n \
    5)To check if the list is full press 5 \n \
    6)To get the Top Rated Book Author press 6 \n \
    7)To get Most Popular Author press 7 \n \
    8)To find kth most popular Book press 8 \n \
    9)To find Least Popular Author press 9 \n \
    10) To exit. ");
    int numberOfEntries,ct=0,lastIndex=-1;
        scanf("%d",&numberOfEntries);
        while(numberOfEntries--)
        {

          scanf("%d",&choice);
          int flag1 =1,i;
          switch(choice){
  /* ---------------------------------------CASE - I ------------------------------------------------------
     ---------------------------------------INSERT--------------------------------------------------------
  */
            case 1:
            {
                //printf("To Insert database in list 1 press 1. else press 2\n");
                //scanf("%d",&i);

                f1= fopen("LibToDB.txt","r");
                    char bookName[50];
                    char author[50];
                    int yrOfPub ;
                    char c;
                    c=getc(f1);
                    while( c!= EOF)
                    {
                      if(fscanf(f1,"%s",bookName)==1)
                      {
                        if(fscanf(f1,"%s",author)==1)
                        {
                          if(fscanf(f1,"%d",&yrOfPub)==1)
                          {
                              sc =insert(ls,bookName,author,yrOfPub,&ct,&lastIndex);

                          }
                        }

                      }
                      c=getc(f1);

                    }
                    //printf("%d\n",yrOfPub);

                    printf("Insertion Status = %d\n",sc);
                    showData(ls,lastIndex);
                    fclose(f1);
            }
            break;
  /* ---------------------------------------CASE - II ------------------------------------------------------
     ---------------------------------------DELETION--------------------------------------------------------
  */
            case 2:
            {
                char bookName[50];
                char author[50];
                printf("Enter the name of the book\n");
                getchar();
                scanf("%[^\n]s  ",bookName);
                printf("Enter the name of the author\n");
                getchar();
                scanf("%[^\n]s",author);
                sc = deletion(ls,bookName,author,&ct,lastIndex);
                printf("Deletion Status = %d\n",sc);
                showData(ls,lastIndex);
            }
            break;
/* ---------------------------------------CASE - III ------------------------------------------------------
     ---------------------------------------GetNumRecords--------------------------------------------------------
  */
            case 3:
            {
                printf(" The number of active records = %d\n",ct);
                showData(ls,lastIndex);
            }
            break;
 /* ---------------------------------------CASE - IV ------------------------------------------------------
     ---------------------------------------isEmpty--------------------------------------------------------
  */
            case 4:
            {
                if(ct == 0)
                {
                    printf("The Database is Empty\n");
                }
                else
                {
                    printf("The Database is not Empty.\n");
                }
            }
            break;
/* ---------------------------------------CASE - V ------------------------------------------------------
     ---------------------------------------isFull--------------------------------------------------------
  */
            case 5:
            {
                if(ct == MAX_BOOKS)
                {
                    printf("The Database is Full\n");
                }
                else
                {
                    printf("The Database is not Full.\n");
                }
            }
            break;

/* ---------------------------------------CASE - VI ------------------------------------------------------
     ------------------------------------TopMostAuthor---------------------------------------------------------
*/
            case 6:
            {
                char str[50];
                char bookName[50];
                printf("Enter the bookName.\n");
                getchar();
                scanf("%[^\n]",bookName);
                topMostAuthor(ls,str,bookName,lastIndex);
                printf("%s\n",str);
            }
            break;
/* ---------------------------------------CASE - VII ------------------------------------------------------
     -------------------------------------MostPopularAuthor--------------------------------------------------------
*/
            case 7:
            {
                char str[50];
                Book temp[100];
                mergeAutWise(ls,0,lastIndex,temp);
                showData(ls,lastIndex);
                findMostPopularAuthor(ls,str,ct,lastIndex);
                printf("The Most Popular Author is = %s\n",str);
            }
            break;
/*---------------------------------------CASE - VIII-------------------------------------------------
-----------------------------------------KthPopular Book----------------------------------------------*/
            case 8:
            {
                int k;
                scanf("%d",&k);
                KsortBookPopWise(ls,lastIndex ,k);
                printf("%s\n",ls[k-1].bookName );
            }
            break;
/*------------ ----------------------CASE - IX -------------------------------------
-------------------------------------Least Popular Author -------------------------*/
            case 9:
            {
                int p,k;
                scanf("%d%d",&p,&k);
                char str_author[250];
                Book temp[100];
                mergeAutWise(ls,0,lastIndex,temp);
                findLeastPopAuthor(ls,str_author,ct,lastIndex, p ,k);
                printf("The list of Least Popular Authors is %s \n",str_author);
            }
            break;
/*--------------------CASE - X ---------------------------------
----------------------- List Union ----------------------------------*/
            case 10:
            {
               numberOfEntries =0;
               printf("\nBye!\n");
               //FILE *f1;
               f1=fopen("LibToDB.txt","w");
               for(i=0;i<=lastIndex;i++)
               {
                 if(ls[i].bookName[0] != '\0')
                 {
                    fprintf( f1, "%s\t",ls[i].bookName );
                    fprintf( f1, "%s\t",ls[i].author );
                    fprintf( f1, "%d\t",ls[i].yrOfPub );
                    fprintf( f1, "%d\n",ls[i].availCopies );

                 }

               }
               fclose(f1);
            }
        }
      }



}
