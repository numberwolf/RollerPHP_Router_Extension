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

/********* DEFINE URL STRUCT **********/
typedef struct url_parser_struct {
	char home[50];
	char controller[50];
	char method[50];
} url_parser_struct;

// @mark 得到url主要元素
url_parser_struct *roller_parser_url(char *url) {
	return NULL;
}


#endif

