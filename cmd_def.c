#include "cmd_def.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMMAND_LEN			2		//�����ж��������� 
#define MAX_COMMAND_LEN		20		//�������� ��󳤶� 

typedef struct FUN_NODE{
	void (*function_p)(); 
	char function_name[MAX_COMMAND_LEN];
//	viod flag_0;
//	viod flag_1;
//	struct FUN_NODE *next_fun_node;	//ָ�� ��һ���ڵ�
}Fun_node;

void add(int a,int b) {
	printf("%d\n", a+b);
}
void dec(int a,int b) {
	printf("%d\n", a-b);
}

Fun_node fun_tab[COMMAND_LEN]= {		//����ע���  �ڴ˴������������ 
	&add,"add",
	&dec,"dec",
};


//int register_cmd(char *function_name, char *flag) {
//	static unsigned char len=0;
////	function_p[len]=add;
////	fun_head.function_p=&add;		//����ָ�� 
////	strcpy(fun_head.function_name,"add");
////	fun_head.flag_0=flag[0];
////	fun_head.flag_1=flag[1];
//	
////	function_name[len]=function_name;	//���������ִ������ 
////										//������������� 
////	len++;
////	if(len > 50) {
////		printf("no space for command\n");
////		return NO_space;
////	} 
//	return 0;
//}


char do_CMD(char *command, char **flag) {	/*ƥ������*/
	char i=0;
	for(i=0;i<COMMAND_LEN;i++){
#ifdef Debug 
		printf("fun_tab[%d].function_name=%s\n",i,fun_tab[i].function_name);
#endif
		if(strcmp(command,fun_tab[i].function_name)==0){	//�Ƚ�����ͱ���ע�� 
			fun_tab[i].function_p(*flag[2]-'0',*flag[3]-'0');		//ƥ��ɹ���ִ�к��� 		
			return 0;
		}
	}
	printf("can't find this command\n");
//	return NO_COMMAND;
	return -1;
} 
