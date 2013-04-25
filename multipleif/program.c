#include<stdio.h>
int main()
{
  int i=0,j=0,k=0;
  do
    {
      if ( ++i%10 != 0)
        {
            printf("%d",i);
            continue;
        }
      else
        {
            printf("\n");
        }

    printf("Next IF statement");

      if(i%2 == 0 || i%3 ==0)
        {
           j++;
        }
      else
        {
          k++;
        }
    printf("J : %d",j);
    printf("K : %d",k);
    }while(i<100);


return 0;
}
