Libextractor binding for PHP
============================

Work in progress ... 

How to build this extension 
---------------------------
*(I'm sorry - it's quick, dirty and not user friendly)*

* Make sure first that you have installed php php-dev gcc packages on your system
* Clone the source then `cd` in
* Run the commands: 
    * phpize
    * ./configure
    * make
    * sudo make install 
    * Try php -d extension=extractor.so -r 'print_r(extract_keywords(""));' in your command line
