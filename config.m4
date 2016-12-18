dnl $Id$
dnl config.m4 for extension rollerphp

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(rollerphp, for rollerphp support,
Make sure that the comment is aligned:
[  --with-rollerphp             Include rollerphp support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(rollerphp, whether to enable rollerphp support,
dnl Make sure that the comment is aligned:
dnl [  --enable-rollerphp           Enable rollerphp support])

if test "$PHP_ROLLERPHP" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-rollerphp -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/rollerphp.h"  # you most likely want to change this
  dnl if test -r $PHP_ROLLERPHP/$SEARCH_FOR; then # path given as parameter
  dnl   ROLLERPHP_DIR=$PHP_ROLLERPHP
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for rollerphp files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       ROLLERPHP_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$ROLLERPHP_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the rollerphp distribution])
  dnl fi

  dnl # --with-rollerphp -> add include path
  dnl PHP_ADD_INCLUDE($ROLLERPHP_DIR/include)

  dnl # --with-rollerphp -> check for lib and symbol presence
  dnl LIBNAME=rollerphp # you may want to change this
  dnl LIBSYMBOL=rollerphp # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $ROLLERPHP_DIR/lib, ROLLERPHP_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_ROLLERPHPLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong rollerphp lib version or lib not found])
  dnl ],[
  dnl   -L$ROLLERPHP_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(ROLLERPHP_SHARED_LIBADD)

  PHP_NEW_EXTENSION(rollerphp, rollerphp.c, $ext_shared)
fi
