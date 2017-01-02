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
	int  paramCount;
} url_main_is_default;

typedef struct params_kv {
	char key[50];
	char value[256];
	struct params_kv *next;
} params_kv;

url_main_is_default *global_bool_main_default;
params_kv *p_kv;

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
	global_bool_main_default->paramCount = 0;
 
    while( result != NULL ) {
		global_bool_main_default->paramCount++;

		ptr->next = (url_param_link_list*)malloc(sizeof(url_param_link_list));
		ptr = ptr->next;
		memcpy(ptr->param, result, strlen(result)+1);
		//ptr->param[strlen(result)] = '\0';
		//ptr = ptr->next;

        printf( "result is \"%s\"\n", ptr->param);
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

	//printf("paramCount:%d\n",global_bool_main_default->paramCount);
	BOOL isSingleCount = FALSE; // 参数是否为单数
	BOOL noneRouteParam = FALSE; // 是否没有路由参数，只有值参数
	if(global_bool_main_default->paramCount%2 != 0) {
		isSingleCount = TRUE;
	}
	if(global_bool_main_default->isHomeNull == TRUE && global_bool_main_default->isContNull == TRUE &&global_bool_main_default->isMethNull == TRUE) {
		noneRouteParam = TRUE;
	}

	//printf("%s\n",url_param->next->param);
	p_kv = (params_kv*)malloc(sizeof(params_kv));
	params_kv *ptr_kv = NULL;
	ptr_kv = p_kv;

	url_param_link_list *ptr = url_param->next;
	/****  目前处理方式，路由参数要么都传，要么都不传 ****/
	BOOL meth_key_showed = FALSE;
	i = 0;
	while(ptr != NULL) {

		if(isSingleCount == TRUE && i == 0) { 
			ptr = ptr->next;
			i = 2;
			continue; // 如果为单数，则忽略第一个
		}
		//printf("%s\n",ptr->param);
		//ptr = ptr->next;
		//continue;

		//printf("ptr-> %s,%s\n",ptr->param,HOME_KEY);
		//if(0 == strcmp(ptr->param , HOME_KEY)) //printf("==is equal==\n");
		//printf("len:%d,%d\n",(int)strlen(ptr->param),(int)strlen(HOME_KEY));

		if(noneRouteParam == FALSE && meth_key_showed == FALSE) {
			if(0 == strcmp(ptr->param , HOME_KEY)) memcpy(return_parser->home , ptr->next->param,strlen(ptr->next->param)); 
			if(0 == strcmp(ptr->param , CONT_KEY)) memcpy(return_parser->controller , ptr->next->param,strlen(ptr->next->param)); 
			if(0 == strcmp(ptr->param , METH_KEY)) {
				memcpy(return_parser->method , ptr->next->param,strlen(ptr->next->param)); 
				meth_key_showed = TRUE;
				//break;
			}

			ptr = ptr->next->next;
			i+=2;
			continue;
		} else {
			meth_key_showed = TRUE;
		}

		if(meth_key_showed == TRUE && i%2 == 0) {
			ptr_kv->next = (params_kv*)malloc(sizeof(params_kv));
			ptr_kv = ptr_kv->next;
			memcpy(ptr_kv->key , ptr->param,strlen(ptr->param));
			memcpy(ptr_kv->value , ptr->next->param,strlen(ptr->next->param));
		}
		i++;

		ptr = ptr->next;
	}

	ptr_kv->next = NULL;

	return return_parser;
}
int main() {
	//url = '/RollerPHP_framework/index.php/hm/Index/ct/index/mt/start';
	url_parser_struct *url_parser = roller_parser_url("/RollerPHP_framework/index.php/hm/Index/ct/index/mt/start");
	if(url_parser != NULL) {
		printf("home:%s,controller:%s,method:%s\r\n",url_parser->home,url_parser->controller,url_parser->method);
	}

	//printf("\nfinished\n");

	/*
	params_kv *ptr_par = NULL;
	ptr_par = p_kv->next;
	while(ptr_par != NULL) {
		//printf("key:%s => value:%s\n",ptr_par->key,ptr_par->value);
		ptr_par = ptr_par->next;
	}
	*/

	return 1;
}

#endif

