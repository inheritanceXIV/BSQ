#include <stdio.h>
#include <stdlib.h>

typedef struct guapi
{
	char a;
	char b;
}			t_guapi;

int main()
{
   int i = 0;
   int j = 0;
	
   t_guapi *gua = malloc(sizeof(t_guapi));
   gua->a = 'a';
   gua->b = 'b';
   while ( i < 1000 )
   {
   		j  = 0;
		while (j < 1000)
		{
			printf("%c", gua->a);
			printf("%c", gua->b);
			j++;
		}
		printf("\n");
		i++;
   }
    return 0;
}
