#include <php.h>
#include <extractor.h>
#include "php_extractor.h"

/* Define functs we want to add */
zend_function_entry php_extractor_functions[] = {
    PHP_FE(extractor_get_keywords, NULL)
    {NULL, NULL, NULL}
};

/* Module entry definitions */
zend_module_entry php_extractor_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_EXTRACTOR_EXTNAME,
    php_extractor_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    PHP_EXTRACTOR_VERSION,
    STANDARD_MODULE_PROPERTIES
};

/* Install module */
ZEND_GET_MODULE(php_extractor)

static int process_keyword (void *cls, const char *plugin_name, 
                     enum EXTRACTOR_MetaType type, 
                     enum EXTRACTOR_MetaFormat format, 
                     const char *data_mime_type, 
                     const char *data, size_t data_len) {
    
    zval *keywords;
    const char *ktype = EXTRACTOR_metatype_to_string(type);
    const char *kval  = estrndup(data, data_len);
    
    /*DEBUG: php_printf("%s - %s\n", ktype, kval);*/
    ALLOC_INIT_ZVAL(keywords);
    array_init(keywords);

    add_assoc_string(keywords, ktype, kval, 1);
    add_next_index_zval(cls, keywords);    
    
    return 0;
}

PHP_FUNCTION(extractor_get_keywords) {
    char *filepath = NULL;
    int argc = ZEND_NUM_ARGS();
    int filepath_len;
    
    struct EXTRACTOR_PluginList *plugins;
    EXTRACTOR_MetaDataProcessor processor = NULL;
    
    if (zend_parse_parameters(argc TSRMLS_CC, "s", &filepath, &filepath_len) == FAILURE) {
        return;
    }
    
    array_init(return_value);
    processor = &process_keyword;

    plugins = EXTRACTOR_plugin_add_defaults(EXTRACTOR_OPTION_DEFAULT_POLICY);
    EXTRACTOR_extract(plugins, filepath, NULL, 0, processor, return_value);
    
    EXTRACTOR_plugin_remove_all(plugins);
}
