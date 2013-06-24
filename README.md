PHP-Extractor
=============

Libextractor binding for PHP

*"[GNU Libextractor](http://www.gnu.org/software/libextractor/) is a library used to extract 
meta data from files. The goal is to provide developers of file-sharing networks, browsers or 
WWW-indexing bots with a universal library to obtain simple keywords and meta data to match 
against queries and to show to users instead of only relying on filenames."*
   -- *Libextractor documentation*

Install
-------
You need to have `libextractor` pre-installed. You can fetch the latest version
from http://www.gnu.org/software/libextractor/.

      git clone https://github.com/mancmelou/php-extractor.git
      cd php-extractor

On some installs, you might need to install `php-dev`:

    sudo apt-get install php5-dev
    
Configure and build the extension:

    phpize
    ./configure
    make

Run the tests and [create an issue][] on github if some of the tests fail.

    make test

   [create an issue]: https://github.com/mancmelou/php-extractor/issues

Copy the extension (modules/extractor.so) to your php extensions directory and
edit your php.ini to load by default.
 
Usage
-----

A simple usage example.

```php
<?php
   $filepath = '/tmp/test.tgz';
   $keywords = extractor_get_keywords($filepath);
   
   print_r($keywords);
?>
```

This will output:
    
      Array
      (
          [embedded filename] => Array
              (
                  [0] => libextractor-1.0.0/
                  [1] => libextractor-1.0.0/ABOUT-NLS
                  [2] => libextractor-1.0.0/README
                  [3] => libextractor-1.0.0/compile
                  [4] => libextractor-1.0.0/config.guess
                  [5] => libextractor-1.0.0/doc/
                  [6] => libextractor-1.0.0/doc/Makefile.am
                  [7] => libextractor-1.0.0/doc/stamp-vti
                  [8] => libextractor-1.0.0/doc/libextractor.texi
                  [9] => libextractor-1.0.0/doc/libextractor.3
                  [10] => libextractor-1.0.0/doc/version.texi
              )
      
          [creation date] => Array
              (
                  [0] => 2012-09-25T19:29:45Z
              )
      
          [format version] => Array
              (
                  [0] => UNIX extended V7 TAR
              )
      
          [mimetype] => Array
              (
                  [0] => application/x-tar
              )
      )
    

Contributing
------------
Any help on this project is very welcome. Please feel free to fork, modify and 
make pull requests. Also make sure you check the TODO file. 

Author
------
Php-extractor was written by Vladimir Ivic (vladimir.ivic at icloud.com) and is
released under the BSD license. For details about Libextractor license, please
check http://www.gnu.org/software/libextractor/.
