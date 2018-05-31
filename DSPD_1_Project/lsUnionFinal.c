// high = lastIndex in main
#include<stdio.h>
#include<string.h>
#define MAX_BOOKS 100

typedef enum { FAILURE, SUCCESS}STATUS_CODE ;
//STATUS_CODE status ;
typedef struct {
        char bookName[50];
        char author[50];
        int yrOfPub;
        int availCopies ;
    } Book ;

    void initialise(Book* ls)
    {
        int i;
        for(i=0;i<MAX_BOOKS;i++)
        {
            ls[i].bookName[0]='\0';
            ls[i].author[0]='\0';
            ls[i].yrOfPub=0;
            ls[i].availCopies=0;
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
        while(ls[i].bookName[0]!='\0' && elemFound == 0 ) //search till hole
        {
           // If duplicate is inputed
           if (!strcmp(ls[i].bookName,bookName) && !strcmp(ls[i].author,author) ) // if key is found
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
//
///
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
/////////////////////////////////////////////////////////////////
void lsUnion(Book* ls1,Book* ls2, int lastIndex1, int lastIndex2, Book* lsmerge)
{
  int i1=0,i2=0,i3=0;
      while(i1<=lastIndex1 && i2 <= lastIndex2)
      {
            if(strcmp(ls1[i1].bookName,ls2[i2].bookName)>0)
            {
                lsmerge[i3]=ls2[i2];
                i2++;
                i3++;
            }
            else if(strcmp(ls1[i1].bookName,ls2[i2].bookName)<0)
            {
              lsmerge[i3]=ls1[i1];
              i1++;
              i3++;
            }
            else if(strcmp(ls1[i1].author,ls2[i2].author)>0)
            {
              lsmerge[i3]=ls2[i2];
              i2++;
              i3++;
            }
            else if(strcmp(ls1[i1].author,ls2[i2].author)<0)
            {
              lsmerge[i3]=ls1[i1];
              i1++;
              i3++;
            }
            else if(strcmp(ls1[i1].author,ls2[i2].author)==0)
            {
               if(ls1[i1].yrOfPub > ls2[i2].yrOfPub)
               {
                 lsmerge[i3]=ls1[i1];
                 i1++;
                 i2++;
                 i3++;
               }
               else
               {
                 lsmerge[i3]=ls2[i2];
                 if(ls1[i1].yrOfPub == ls2[i2].yrOfPub)
                 {
                   lsmerge[i3].availCopies=ls1[i1].availCopies + ls2[i2].availCopies;
                 }
                 i1++;
                 i2++;
                 i3++;
               }
            }
      }
        while(i2<=lastIndex2)
        {
          lsmerge[i3]=ls2[i2];
          i2++;
          i3++;
        }
        while(i1<=lastIndex1)
        {
          lsmerge[i3]=ls1[i1];
          i1++;
          i3++;
        }
        // showData(ls1,lastIndex1);
        // showData(ls2,lastIndex2);
        printf("\n");
        showData(lsmerge,i3-1);
}
/////////////////////////////////////////////////////
void lsDiff(Book* ls1, Book* ls2,int lastIndex1,int lastIndex2, Book* lsSub)
{
  int i1,i2,i3=0;
  int flag=0;
  for(i1=0;i1<=lastIndex1;i1++)
  {
        flag =0 ;
        i2=0;
        while(strcmp(ls1[i1].bookName,ls2[i2].bookName)>0 && i2<=lastIndex2)
        {
            i2++;
        }
        if( i2 >lastIndex2)
        {
            lsSub[i3]=ls1[i1];
            i3++;
        }
        else
        {
          if( strcmp(ls1[i1].bookName,ls2[i2].bookName)<0)
          {
              lsSub[i3]=ls1[i1];
              i3++;
          }
          else
          {
              while((strcmp(ls1[i1].author,ls2[i2].author)>0) && (strcmp(ls1[i1].bookName,ls2[i2].bookName)== 0 ) && i2<=lastIndex2)
              {
                  i2++;
              }
              if( i2 >lastIndex2 || (strcmp(ls1[i1].bookName,ls2[i2].bookName)!= 0 ))
              {
                  lsSub[i3]=ls1[i1];
                  i3++;
              }
              else
              {
                  if((strcmp(ls1[i1].author,ls2[i2].author)<0) && (strcmp(ls1[i1].bookName,ls2[i2].bookName)== 0 ) && i1<=lastIndex1)
                  {
                      lsSub[i3]=ls1[i1];
                      i3++;
                  }
                  else if((strcmp(ls1[i1].author,ls2[i2].author)==0) && (strcmp(ls1[i1].bookName,ls2[i2].bookName)== 0 ))
                  {
                      if(ls1[i1].availCopies -  ls2[i2].availCopies > 0)
                      {
                         lsSub[i3]=ls1[i1];
                         lsSub[i3].availCopies=ls1[i1].availCopies-ls2[i2].availCopies;
                         i3++;
                      }
                  }
              }

          }

      }

    }
    printf("\n");
  showData(lsSub,i3-1);

}
////////////////////////////////////////////////

  int main()
  {
    STATUS_CODE sc;
    Book ls1[100];
    Book ls2[100];
    Book lsmerge[100];
    Book lsSub[100];
    int ct1=0,lastIndex1=-1;
    int ct2=0,lastIndex2=-1;
    int i;
    int flag1=0,flag2=0;
    FILE *f1;
    FILE *f2;
    f1 = fopen("data.txt" , "r");
    f2 = fopen("data2.txt" , "r");
    initialise(ls1);
    initialise(ls2);
    initialise(lsmerge);
    while(flag1==0)
    {
      printf("To Insert database in list 1 press 1. else press 2\n");
      scanf("%d",&i);
      if(i==1)
      {
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
                    sc =insert(ls1,bookName,author,yrOfPub,&ct1,&lastIndex1);

                }
              }

            }
            c=getc(f1);

          }
          //printf("%d\n",yrOfPub);

          printf("Insertion Status = %d\n",sc);
          showData(ls1,lastIndex1);
      }
      else
      {
         flag1=1;
      }
    }


    //flag=0;

    while(flag2==0)
    {
      printf("To Insert database in list 1 press 1. else press 2\n");
      scanf("%d",&i);
      if(i==1)
      {
          char bookName[50];
          char author[50];
          int yrOfPub ;
          char c;
          c=getc(f2);
          while( c!= EOF)
          {
            if(fscanf(f2,"%s",bookName)==1)
            {
              if(fscanf(f2,"%s",author)==1)
              {
                if(fscanf(f2,"%d",&yrOfPub)==1)
                {
                    sc =insert(ls2,bookName,author,yrOfPub,&ct2,&lastIndex2);

                }
              }

            }
            c=getc(f2);

          }
          //printf("%d\n",yrOfPub);

          printf("Insertion Status = %d\n",sc);
          showData(ls2,lastIndex2);
      }
      else
      {
         flag2=1;
      }
    }
    mergeSortKeyWise(ls1,0,lastIndex1,lsmerge);
    showData(ls1,lastIndex1);
    mergeSortKeyWise(ls2,0,lastIndex2,lsmerge);
    showData(ls2,lastIndex2);
    lsUnion(ls1,ls2,lastIndex1,lastIndex2,lsmerge);
    FILE *f3;
    f3=fopen("data3.txt","w");
    for(int i=0;i<=lastIndex1+lastIndex2;i++)
    {
      if(lsmerge[i].bookName[0]!='\0')
      {
        fprintf( f3, "%s\t",lsmerge[i].bookName );
        fprintf( f3, "%s\t",lsmerge[i].author );
        fprintf( f3, "%d\t",lsmerge[i].yrOfPub );
        fprintf( f3, "%d\n",lsmerge[i].availCopies );
        fprintf(f3,"\n");
      }

    }
    fprintf(f3,"\n");

    lsDiff(ls1,ls2,lastIndex1,lastIndex2,lsSub);
    for(int i=0;i<=lastIndex1;i++)
    {
      if(lsSub[i].bookName[0]!='\0')
      {
        fprintf( f3, "%s\t",lsSub[i].bookName );
        fprintf( f3, "%s\t",lsSub[i].author );
        fprintf( f3, "%d\t",lsSub[i].yrOfPub );
        fprintf( f3, "%d\n",lsSub[i].availCopies );
        fprintf(f3,"\n");
      }
    }
    return 0;
  }
