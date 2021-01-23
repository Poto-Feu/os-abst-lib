# OsAbstLibrary
Simple Platform abstraction library made in C.

Please note that this library is not ready for production use yet.

## Compatibility
OsAbstLibrary is officially compatible with the following OSes :

* FreeBSD
* GNU/Linux
* Windows NT

Most functions are compatible with all POSIX-compliant systems but some relies on specific OSes implementation. A warning will be displayed during building if a function is not available on your system.

## Building
```bash
mkdir build && cd build
cmake .. 
make
```

## Licensing
OsAbstLibrary is licensed under the GNU LGPL Version 3.
