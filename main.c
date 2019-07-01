#include <stdio.h>
#include <stdlib.h>
#include "cmd_def.h" 
#include <string.h>
//#define Debug

int main(int argc, char *argv[]) {
	int i;
#ifdef Debug	
	printf("argc=%d\n",argc);
	for(i=1;i<argc;i++)
		printf("argv[%d]=%s\n",i,argv[i]);
#endif	
	if(argc>2)
		do_CMD(argv[1],argv);
	return 0;
}
