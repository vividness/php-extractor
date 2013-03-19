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
   
    <?php 
      
      $filepath = "/path/to/a/file.ext";
      $keywords = extractor_get_keywords($filepath);
      
      print_r($keywords);
    ?>

Contributing
------------
Any help on this project is very welcome. Please feel free to fork, modify and 
make pull requests. Also make sure you check the TODO file. 

Author
------
Php-extractor was written by Vladimir Ivic (vladimir.ivic at icloud.com) and is
released under the BSD license. For details about Libextractor license, please
check http://www.gnu.org/software/libextractor/.
