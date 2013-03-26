#include <php.h>
#include <extractor.h>
#include "php_extractor.h"

/* Define functs we want to add */
zend_function_entry extractor_functions[] = {
    PHP_FE(extractor_get_keywords, NULL)
    {NULL, NULL, NULL}
};

/* Module entry definitions */
zend_module_entry extractor_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_EXTRACTOR_EXTNAME,
    extractor_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    PHP_EXTRACTOR_VERSION,
    STANDARD_MODULE_PROPERTIES
};

/* Install module */
ZEND_GET_MODULE(extractor)

static int process_keyword (void *cls, const char *plugin_name, 
                     enum EXTRACTOR_MetaType type, 
                     enum EXTRACTOR_MetaFormat format, 
                     const char *data_mime_type, 
                     const char *data, size_t data_len) {
    
    zval *keywords, **subarray;
    const char *ktype = EXTRACTOR_metatype_to_string(type);
    const char *kval  = estrndup(data, data_len);
    
    ALLOC_INIT_ZVAL(keywords);
    array_init(keywords);

    if (zend_hash_find(Z_ARRVAL_P((zval*) cls), ktype, strlen(ktype) + 1, (void**) &subarray) == SUCCESS) {
        add_next_index_string(*subarray, kval, 1);
        return 0;
    }
    
    add_next_index_string(keywords, kval, 1);
    add_assoc_zval(cls, ktype, keywords);

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
