PHP_ARG_WITH(php-extractor, whether to enable PHP-Extractor extension,
[  --enable-php-extractor   Enable PHP-Extractor extension])

if test "$PHP_EXTRACTOR" != "no"; then
    AC_MSG_CHECKING([for extractor headers])
    for i in /usr/local /usr; do
        if test -r "$i/include/extractor.h"; then
            PHP_EXTRACTOR_DIR=$i
            AC_MSG_RESULT([found in $i])
            break
        fi
    done
    if test -z "$PHP_EXTRACTOR_DIR"; then
        AC_MSG_RESULT([not found])
        AC_MSG_ERROR([please install >=libextractor-0.6.3 ])
    fi
    
    PHP_ADD_INCLUDE($PHP_EXTRACTOR_DIR/include)
    AC_CHECK_HEADER([extractor.h], [], AC_MSG_ERROR['extractor.h' header not found])
    PHP_ADD_LIBRARY(extractor, 1, EXTRACTOR_SHARED_LIBADD)

    dnl May need this at some point
    dnl PHP_ADD_LIBRARY_WITH_PATH(extract, $PHP_EXTRACTOR_DIR/lib, EXTRACTOR_SHARED_LIBADD)
    dnl 

    AC_CHECK_LIB(extractor, EXTRACTOR_plugin_add_defaults, 
    [
        AC_DEFINE(HAVE_EXTRACTORLIB, 1, [ ])
    ], [
        AC_MSG_ERROR([extractor library not found please install >=libextractor-0.6.3])
    ],)

    PHP_SUBST(EXTRACTOR_SHARED_LIBADD)
    PHP_NEW_EXTENSION(extractor, php_extractor.c, $ext_shared)
fi
