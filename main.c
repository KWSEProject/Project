#include <stdio.h>
#include "libseg.h"

int main()
{
	unsigned char x,result;

	printf("Input : ");
	scanf("%c",&x);

	result = Getsegcode(x);

	if( result == 63 ) // 0
		printf("HEX : %x\n",result);
	else if( result == 6 ) // 1 
		printf("HEX : %x\n",result);
	else if( result == 91 ) // 2 
		printf("HEX : %x\n",result);
	else if( result == 79 ) // 3 
		printf("HEX : %x\n",result);
	else if( result == 102 ) // 4 
		printf("HEX : %x\n",result);
	else if( result == 99 ) // 5 
		printf("HEX : %x\n",result);
	else if( result == 125 ) // 6 
		printf("HEX : %x\n",result);
	else if( result == 39 ) // 7 
		printf("HEX : %x\n",result);
	else if( result == 127 ) // 8 
		printf("HEX : %x\n",result);
	else if( result == 103 ) // 9
		printf("HEX : %x\n",result);
	else
		printf("Error\n");
		 
	return 0;
}
