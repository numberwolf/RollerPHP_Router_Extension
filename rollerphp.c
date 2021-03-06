/*
   +----------------------------------------------------------------------+
   | PHP Version 5                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2013 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author:                                                              |
   +----------------------------------------------------------------------+
 */

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_rollerphp.h"
#include "include_common.h"
#include "router.h"

/* If you declare any globals in php_rollerphp.h uncomment this:
   ZEND_DECLARE_MODULE_GLOBALS(rollerphp)
 */

/* True global resources - no need for thread safety here */
static int le_rollerphp;

/* {{{ rollerphp_functions[]
 *
 * Every user visible function must have an entry in rollerphp_functions[].
 */
// @TODO
ZEND_BEGIN_ARG_INFO(arg_roller_sname, 0)
ZEND_ARG_INFO(0, name)
ZEND_ARG_INFO(0, controller)
ZEND_ARG_INFO(0, home)
ZEND_ARG_INFO(0, method)
ZEND_END_ARG_INFO() const zend_function_entry rollerphp_functions[] = {
	PHP_ME(Roller, gname,     NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Roller, startup,     NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Roller, sname,     arg_roller_sname, ZEND_ACC_PUBLIC)
	PHP_ME(Roller, sayroute,     arg_roller_sname, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL} /* Must be the last line in rollerphp_functions[] */ 
};
/* }}} */

/* {{{ rollerphp_module_entry
 */
zend_module_entry rollerphp_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"rollerphp",
	rollerphp_functions,
	PHP_MINIT(rollerphp),
	PHP_MSHUTDOWN(rollerphp),
	PHP_RINIT(rollerphp),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(rollerphp),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(rollerphp),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_ROLLERPHP_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_ROLLERPHP
ZEND_GET_MODULE(rollerphp)
#endif

	/* {{{ PHP_INI
	 */
	/* Remove comments and fill if you need to have entries in php.ini
	   PHP_INI_BEGIN()
	   STD_PHP_INI_ENTRY("rollerphp.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_rollerphp_globals, rollerphp_globals)
	   STD_PHP_INI_ENTRY("rollerphp.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_rollerphp_globals, rollerphp_globals)
	   PHP_INI_END()
	 */
	/* }}} */

	/* {{{ php_rollerphp_init_globals
	 */
	/* Uncomment this function if you have INI entries
	   static void php_rollerphp_init_globals(zend_rollerphp_globals *rollerphp_globals)
	   {
	   rollerphp_globals->global_value = 0;
	   rollerphp_globals->global_string = NULL;
	   }
	 */
	/* }}} */

	/* {{{ PHP_MINIT_FUNCTION
	 */
	zend_class_entry *roller_ce;
PHP_MINIT_FUNCTION(rollerphp)
{
	/* If you have INI entries, uncomment these lines 
	   REGISTER_INI_ENTRIES();
	 */
	zend_class_entry roller; INIT_CLASS_ENTRY(roller, "Roller", rollerphp_functions);
	roller_ce = zend_register_internal_class_ex(&roller, NULL, NULL TSRMLS_CC);

	zend_declare_property_null(roller_ce, ZEND_STRL("_name"), ZEND_ACC_PUBLIC TSRMLS_CC); 
	zend_declare_property_null(roller_ce, ZEND_STRL("_controller"), ZEND_ACC_PUBLIC TSRMLS_CC); 
	zend_declare_property_null(roller_ce, ZEND_STRL("_home"), ZEND_ACC_PUBLIC TSRMLS_CC); 
	zend_declare_property_null(roller_ce, ZEND_STRL("_method"), ZEND_ACC_PUBLIC TSRMLS_CC); 
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(rollerphp)
{
	/* uncomment this line if you have INI entries
	   UNREGISTER_INI_ENTRIES();
	 */
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(rollerphp)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(rollerphp)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(rollerphp)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "rollerphp support", "enabled");
	php_info_print_table_row(2, "author" , "ChangYanlong");
	php_info_print_table_row(2, "RollerPHP_framework support" , "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	   DISPLAY_INI_ENTRIES();
	 */
}
/* }}} */


/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */

PHP_METHOD(Roller, gname) {
	zval *self, *name;
	self = getThis();
	name = zend_read_property(Z_OBJCE_P(self), self, ZEND_STRL("_name"), 0 TSRMLS_CC);
	RETURN_STRING(Z_STRVAL_P(name), 0);
}

/********************
  1. StartUP，启动路由，初始化一些数据
 ********************/
PHP_METHOD(Roller, startup) {
}

/***************
  2. 初始化路由参数等等
  @TODO
 **************/
PHP_METHOD(Roller, sayroute) {
	char *arg = NULL;
	int arg_len;

	zval *value_controller,*value_home,*value_method, *self;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	self = getThis();
	url_parser_struct *url_parser = roller_parser_url(arg);

	MAKE_STD_ZVAL(value_controller);
	MAKE_STD_ZVAL(value_home);
	MAKE_STD_ZVAL(value_method);

	ZVAL_STRINGL(value_controller, url_parser->controller, strlen(url_parser->controller), 0);
	ZVAL_STRINGL(value_home, url_parser->home, strlen(url_parser->home), 0);
	ZVAL_STRINGL(value_method, url_parser->method, strlen(url_parser->method), 0);

	SEPARATE_ZVAL_TO_MAKE_IS_REF(&value_controller);
	SEPARATE_ZVAL_TO_MAKE_IS_REF(&value_home);
	SEPARATE_ZVAL_TO_MAKE_IS_REF(&value_method);

	zend_update_property(Z_OBJCE_P(self), self, ZEND_STRL("_controller"), value_controller TSRMLS_CC);
	zend_update_property(Z_OBJCE_P(self), self, ZEND_STRL("_home"), value_home TSRMLS_CC);
	zend_update_property(Z_OBJCE_P(self), self, ZEND_STRL("_method"), value_method TSRMLS_CC);

	// start to get data arr : *p_kv
	params_kv *my_kv = get_data_arr_list()->next;
	array_init(return_value);
	while(my_kv != NULL) {
		//printf("key:%s => value:%s\n",ptr_par->key,ptr_par->value);
		add_assoc_string(return_value,my_kv->key,my_kv->value,1);
		my_kv = my_kv->next;
	}

	clean_data_arr_list();

	//RETURN_TRUE;
}

PHP_METHOD(Roller, sname) {
	char *arg = NULL;
	int arg_len;
	zval *value, *self;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		WRONG_PARAM_COUNT;
	}
	self = getThis();
	MAKE_STD_ZVAL(value);
	ZVAL_STRINGL(value, arg, arg_len, 0);
	SEPARATE_ZVAL_TO_MAKE_IS_REF(&value);
	zend_update_property(Z_OBJCE_P(self), self, ZEND_STRL("_name"), value TSRMLS_CC);
	RETURN_TRUE;
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
