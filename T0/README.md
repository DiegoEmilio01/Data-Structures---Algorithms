# Tarea 0 2021-1

La base de python se ejecuta con 
``` python3 ./python/main.py tests/test.txt out.txt```
``` python3 python/main.py tests/testIn.txt tests/testOut.txt ```

El programa en c se compila con ```make``` y se ejecuta con

``` ./kevin-21 tests/test.txt out.txt```
``` ./kevin-21 tests/testIn.txt tests/testOut.txt ```

Se comprueba la correctitud de un test con:

``` diff -b "archivo1.txt" "archivo2.txt" ```