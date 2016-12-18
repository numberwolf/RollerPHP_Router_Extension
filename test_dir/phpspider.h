#ifndef PHPSPIDER_C
#define PHPSPIDER_C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <malloc.h>
#include <regex.h>
#include <memory.h>
#include <sys/types.h>

#define POSTURL    				"http://www.nrg.com/login"
#define POSTFIELDS 				""
#define FILENAME   				"response.log"
#define HEADERS_COUNT 			6
#define HEADERS_ELEMENT_LENGTH  1024
#define CURL_RESULT 			int
#define BOOL_VAL 				int
#define BOOL_TRUE				1
#define BOOL_FALSE				0

#define IS_REFERER				1
#define IS_UA					2
#define IS_HOST					3
#define IS_COOKIE				4
#define IS_ACCEPT				5
#define IS_ACC_LAU				6
#define IS_ACC_EOD				7
#define IS_CONNECT				8
#define IS_KEEP					9
#define IS_CONT_TYPE			10
#define IS_ACC_CHAR				11
#define IS_CON_LEN				12

#define REGEX_REFERER 			"Referer.{0,}:"
#define REGEX_UA				"User-Agent.{0,}:"
#define REGEX_HOST				"Host.{0,}:"
#define REGEX_COOKIE			"Cookie.{0,}:"
#define REGEX_ACCEPT			"Accept.{0,}:"
#define REGEX_ACC_LAU			"Accept-Language.{0,}:"
#define REGEX_ACC_EOD			"Accept-Encoding.{0,}:"
#define REGEX_CONNECT			"Connection.{0,}:"
#define REGEX_KEEP				"Keep-Alive.{0,}:"
#define REGEX_CONT_TYPE			"Content-Type.{0,}:"
#define REGEX_ACC_CHAR			"Accept-Charset.{0,}:"
#define REGEX_CON_LEN			"Content-Length.{0,}:"

/**
 * 定义头部结构体
 */
typedef struct http_headers {
	char Accept[128];
	char Accept_Language[128];
	char Accept_Encoding[128];
	char Accept_Charset[128];
	char Content_Type[128];
	char Connection[128];
	char Content_Length[128];
	char Keep_Alive[128];
	char Host[512];
	char User_Agent[512];
	char Referer[2803];
	char Cookie[4096];
} http_headers;

struct curl_slist *headers = NULL; 
struct http_headers *http_h = NULL;
char *content = NULL;

void release_curl() {
	//printf("free start===>\n");
	if(content != NULL || strlen(content) < 1) {
		//printf("%s\nfree\n",content);
		free(content);
		content = NULL;
	}

	//printf("free over\n");

	free(headers);
	headers = NULL;

	free(http_h);
	http_h = NULL;
}

void init_curl_slist() {
	if(http_h == NULL) http_h = (http_headers*)malloc(1*sizeof(http_headers));
	if(strlen(http_h->Cookie) > 1) curl_slist_append(headers, http_h->Cookie);
	if(strlen(http_h->Referer) > 1) curl_slist_append(headers, http_h->Referer);
	if(strlen(http_h->User_Agent) > 1) curl_slist_append(headers, http_h->User_Agent);
	if(strlen(http_h->Host) > 1) curl_slist_append(headers, http_h->Host);
	if(strlen(http_h->Keep_Alive) > 1) curl_slist_append(headers, http_h->Keep_Alive);
	if(strlen(http_h->Content_Length) > 1) curl_slist_append(headers, http_h->Content_Length);
	if(strlen(http_h->Connection) > 1) curl_slist_append(headers, http_h->Connection);
	if(strlen(http_h->Content_Type) > 1) curl_slist_append(headers, http_h->Content_Type);
	if(strlen(http_h->Accept_Encoding) > 1) curl_slist_append(headers, http_h->Accept_Encoding);
	if(strlen(http_h->Accept_Language) > 1) curl_slist_append(headers, http_h->Accept_Language);
	if(strlen(http_h->Accept) > 1) curl_slist_append(headers, http_h->Accept);
}

size_t write_data(void* buffer,size_t size,size_t nmemb,char *stream) {
	if(content == NULL) {
		content = (char*)malloc(strlen(buffer)*sizeof(char));
		strcpy(content,buffer);
		return size*nmemb;
	}

	size_t size_n = size*nmemb + strlen(content);
	content = (char*)realloc(content,size_n*sizeof(char));
	content = strcat(content,buffer);
	//printf("stream:%s",content);

	return size*nmemb;
}

char *list_href(char *content) {
	return NULL;
}

char* init_curl(char *url, BOOL_VAL isPost,char *post_fields) {
	//printf("START\r\n");
	content = NULL;
	CURL *curl = curl_easy_init(); 
	if (!curl) {  
		return NULL;  
	}  

	init_curl_slist();

	curl_easy_setopt(curl,CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(curl,CURLOPT_URL,url); //url地址
	if(isPost == 1) {
		curl_easy_setopt(curl,CURLOPT_POSTFIELDS,post_fields); //post参数
	}
	curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,write_data); //对返回的数据进行操作的函数地址
	//curl_easy_setopt(curl,CURLOPT_WRITEDATA,content); //这是write_data的第四个参数值
	curl_easy_setopt(curl,CURLOPT_POST,isPost); //设置问非0表示本次操作为post
	curl_easy_setopt(curl,CURLOPT_VERBOSE,0); //打印调试信息
	curl_easy_setopt(curl,CURLOPT_HEADER,1); //将响应头信息和相应体一起传给write_data
	curl_easy_setopt(curl,CURLOPT_FOLLOWLOCATION,1); //设置为非0,响应头信息location
	//curl_easy_setopt(curl,CURLOPT_COOKIEFILE,"/Users/zhu/CProjects/curlposttest.cookie");
	CURLcode res = curl_easy_perform(curl);
	//printf("============>>>>>>>>res:%d\r\n",res);
	//printf("============>>>>>>>>content:%s\r\n",content);
	curl_easy_cleanup(curl);


	if (res != CURLE_OK)
	{
		return NULL;
	}
	return content;
}

void delloc_dimension_two_arr(char **curl_arr, int count) {
	int i;
	for(i=0;i<count;i++) {  
		//printf("===%s \r\n",curl_arr[i]); 
		if(curl_arr[i] != NULL) {
			free(curl_arr[i]);//释放第二维指针 
			curl_arr[i] = NULL;
		}
		//printf("%s,%p\r\n",curl_arr[i],&curl_arr[i]);
	} 
	if(curl_arr != NULL) {
		free(curl_arr);//释放第一维指针 
	}
	curl_arr = NULL;
}

BOOL_VAL set_headers(char *element) {
	if(http_h == NULL) http_h = (http_headers*)malloc(1*sizeof(http_headers));
	//char *pattern_referer = "Referer.{0,}:";
	regex_t reg;
	int err,nm = 10;
	regmatch_t pmatch[nm];

	regcomp(&reg,REGEX_REFERER,REG_EXTENDED);
	/** 0 为正常匹配 **/
	if(regexec(&reg,element,nm,pmatch,0) == 0) {
		strcpy(http_h->Referer, element);
		return IS_REFERER;
	}
	regcomp(&reg,REGEX_UA,REG_EXTENDED);
	if(regexec(&reg,element,nm,pmatch,0) == 0) {
		strcpy(http_h->User_Agent , element);
		return IS_UA;
	}
	regcomp(&reg,REGEX_HOST,REG_EXTENDED);
	if(regexec(&reg,element,nm,pmatch,0) == 0) {
		strcpy(http_h->Host , element);
		return IS_HOST;
	}
	regcomp(&reg,REGEX_COOKIE,REG_EXTENDED);
	if(regexec(&reg,element,nm,pmatch,0) == 0) {
		strcpy(http_h->Cookie , element);
		return IS_COOKIE;
	}
	regcomp(&reg,REGEX_ACCEPT,REG_EXTENDED);
	if(regexec(&reg,element,nm,pmatch,0) == 0) {
		strcpy(http_h->Accept , element);
		return IS_ACCEPT;
	}
	regcomp(&reg,REGEX_ACC_LAU,REG_EXTENDED);
	if(regexec(&reg,element,nm,pmatch,0) == 0) {
		strcpy(http_h->Accept_Language , element);
		return IS_ACC_LAU;
	}
	regcomp(&reg,REGEX_ACC_EOD,REG_EXTENDED);
	if(regexec(&reg,element,nm,pmatch,0) == 0) {
		strcpy(http_h->Accept_Encoding , element);
		return IS_ACC_EOD;
	}
	regcomp(&reg,REGEX_CONNECT,REG_EXTENDED);
	if(regexec(&reg,element,nm,pmatch,0) == 0) {
		strcpy(http_h->Connection , element);
		return IS_CONNECT;
	}
	regcomp(&reg,REGEX_KEEP,REG_EXTENDED);
	if(regexec(&reg,element,nm,pmatch,0) == 0) {
		strcpy(http_h->Keep_Alive ,element);
		return IS_KEEP;
	}
	regcomp(&reg,REGEX_CONT_TYPE,REG_EXTENDED);
	if(regexec(&reg,element,nm,pmatch,0) == 0) {
		strcpy(http_h->Content_Type , element);
		return IS_CONT_TYPE;
	}
	regcomp(&reg,REGEX_ACC_CHAR,REG_EXTENDED);
	if(regexec(&reg,element,nm,pmatch,0) == 0) {
		strcpy(http_h->Accept_Charset , element);
		return IS_ACC_CHAR;
	}
	regcomp(&reg,REGEX_CON_LEN,REG_EXTENDED);
	if(regexec(&reg,element,nm,pmatch,0) == 0) {
		strcpy(http_h->Content_Length, element);
		return IS_CON_LEN;
	}
	return 0;

}
/*
int main() {
	BOOL_VAL regex_result = set_headers_element("User-Agent:https://www.baidu.com");
	printf("regex_result:%d\r\n",regex_result);

	printf("accept:%s\r\n",http_h->Accept);
	printf("accept_language:%s\r\n",http_h->Accept_Language);
	printf("accept_encoding:%s\r\n",http_h->Accept_Encoding);
	printf("accept_charset:%s\r\n",http_h->Accept_Charset);
	printf("content_type:%s\r\n",http_h->Content_Type);
	printf("connection:%s\r\n",http_h->Connection);
	printf("content_length:%s\r\n",http_h->Content_Length);
	printf("keep_alive:%s\r\n",http_h->Keep_Alive);
	printf("host:%s\r\n",http_h->Host);
	printf("user_agent:%s\r\n",http_h->User_Agent);
	printf("referer:%s\r\n",http_h->Referer);
	printf("cookie:%s\r\n",http_h->Cookie);
	//return 0;
	char* res = init_curl("http://numberwolf.top",BOOL_FALSE,NULL);
	printf("%s",res);
	free(res);
	res = NULL;

	release_curl();

}
*/

#endif

