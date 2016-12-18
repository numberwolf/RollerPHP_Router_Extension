/************************
  PHP 5.5
  GCC 4.8
  常炎隆
  porschegt23@foxmail.com
  RollerPHP_framework
  ***********************/
#ifndef ROUTER_C
#define ROUTER_C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <curl/curl.h>
#include <malloc.h>
#include <regex.h>
#include <memory.h>
#include <sys/types.h>

#include "include_common.h"

#define CONTROLLER_DIR				"Controller"
#define MODEL_DIR					"Models"
#define CONFIG_DIR					"Configs"
#define VIWES_DIR					"Views"
#define TEMPPLATES_DIR				"Templates"
#define SYSTEM_DIR					"System"
#define STORAGE_DIR					"Storage"

#define DEFAULT_HOME				"Index"
#define DEFAULT_CONTROLLER			"index"
#define DEFAULT_METHOD				"index"

#define HOME_KEY					"hm"
#define CONT_KEY					"ct"
#define METH_KEY					"mt"

/********* DEFINE URL STRUCT **********/
typedef struct url_parser_struct {
	char home[50];
	char controller[50];
	char method[50];
} url_parser_struct;

typedef struct url_param_link_list {
	char param[50];
	struct url_param_link_list *next;
} url_param_link_list;

typedef struct url_main_is_default {
	BOOL isHomeNull;
	BOOL isContNull;
	BOOL isMethNull;
} url_main_is_default;

url_main_is_default *global_bool_main_default;

url_param_link_list *roller_get_param(char *url) {
	global_bool_main_default = (url_main_is_default*)malloc(sizeof(url_main_is_default));
	global_bool_main_default->isHomeNull = TRUE;
	global_bool_main_default->isContNull = TRUE;
	global_bool_main_default->isMethNull = TRUE;

	char new_url[strlen(url)];
	memcpy(new_url,url,strlen(url)+1);
	new_url[strlen(url)] = '\0';
	char *result = NULL;
	char split[] = "/";

	result = strtok(new_url, split);
	url_param_link_list *return_list = (url_param_link_list*)malloc(sizeof(url_param_link_list));
	url_param_link_list *ptr = NULL;
	//ptr = return_list->next;
	ptr = return_list;
 
    while( result != NULL ) 
   	{
		ptr->next = (url_param_link_list*)malloc(sizeof(url_param_link_list));
		ptr = ptr->next;
		memcpy(ptr->param, result, strlen(result)+1);
		//ptr->param[strlen(result)] = '\0';
		//ptr = ptr->next;

        //printf( "result is \"%s\"\n", ptr->param);
		if(0 == strcmp(result , HOME_KEY)) global_bool_main_default->isHomeNull = FALSE;
		if(0 == strcmp(result , CONT_KEY)) global_bool_main_default->isContNull = FALSE;
		if(0 == strcmp(result , METH_KEY)) global_bool_main_default->isMethNull = FALSE;

        result = strtok( NULL, split);
    }

	ptr->next = NULL;

	return return_list;
}

// @mark 得到url主要元素
url_parser_struct *roller_parser_url(char *url) {
	int i,j;
	int length = strlen(url);
	//printf("%d\n",(int)length);

	int new_len = length;
	if(url[0] == '/') {
		//printf("0\n");
		i = 1;
		new_len--;
	}
	if(url[length-1] == '/') {
		//printf("length-1\n");
		length--;
		new_len--;
	}
	//printf("new_len:%d\n",new_len);

	char new_url[new_len+1];
	
	for(j = 0; i < length; i++, j++) {
		new_url[j] = url[i];
		//printf("new_url[%d] = %c\n",j,new_url[j]);
	}
	new_url[new_len] = '\0';// 必须补
	//printf("len:%d\n",(int)strlen(new_url));

	//printf("new_url:%s,last:%c,newlength:%d\n",new_url,new_url[strlen(new_url)-1],(int)strlen(new_url));

	url_param_link_list *url_param = roller_get_param(new_url);
	url_parser_struct *return_parser = (url_parser_struct*)malloc(sizeof(url_parser_struct));

	if(global_bool_main_default->isHomeNull == TRUE) memcpy(return_parser->home , DEFAULT_HOME,strlen(DEFAULT_HOME));
	if(global_bool_main_default->isContNull == TRUE) memcpy(return_parser->controller , DEFAULT_CONTROLLER,strlen(DEFAULT_CONTROLLER));
	if(global_bool_main_default->isMethNull == TRUE) memcpy(return_parser->method , DEFAULT_METHOD,strlen(DEFAULT_METHOD));

	//printf("%s\n",url_param->next->param);

	url_param_link_list *ptr = url_param->next;
	while(ptr->next != NULL) {
		//printf("ptr-> %s,%s\n",ptr->param,HOME_KEY);
		//if(0 == strcmp(ptr->param , HOME_KEY)) printf("==is equal==\n");
		//printf("len:%d,%d\n",(int)strlen(ptr->param),(int)strlen(HOME_KEY));

		if(0 == strcmp(ptr->param , HOME_KEY)) memcpy(return_parser->home , ptr->param,strlen(ptr->param)); 
		if(0 == strcmp(ptr->param , CONT_KEY)) memcpy(return_parser->controller , ptr->param,strlen(ptr->param)); 
		if(0 == strcmp(ptr->param , METH_KEY)) memcpy(return_parser->method , ptr->param,strlen(ptr->param)); 

		ptr = ptr->next;
	}

	return return_parser;
}
/*
int main() {
	url_parser_struct *url_parser = roller_parser_url("/RollerPHP_framework/hm/Index/ct/test/mt/init/a/1/b/2/c/3/");
	if(url_parser != NULL) {
		printf("home:%s,controller:%s,method:%s\r\n",url_parser->home,url_parser->controller,url_parser->method);
	}

	printf("\nfinished\n");
	return 1;
}
*/
#endif

