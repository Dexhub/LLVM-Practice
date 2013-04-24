#include<stdio.h>
int main()
{
  int i=0;
  do
    {
      if( i%10 == 0)
      {     printf("\n");
            i++;
            continue;
       }
    else
       {
            printf(" %d", i);
            i++;
       }
    }while(i<20);

    int j=i+50;
    i= j+i*j;

return 0;
}
