# Documentacion-CMS-COMI
Guía de usuario para seteo de problemas en CMS.

Para setear un programa en CMS se requiere de 3 archivos, un manager, un stub y un .h que establezca una relacion entre el stub y el código del competidor.

# Manager
Este archivo recibirá desde el STDIN el input de cada caso de prueba, ademas de recibir un cierto número de archivos (definido segun el numero de llamadas, un par de archivos para problemas interactivos y dos pares de archivos para problemas de comunicación, cada par contiene un archivo de lectura y uno de escritura).

El manager guarda el testcase a través del STDIN y se lo comunica al stub a través de el archivo de escritura, luego el stub aqui llama a la funcion del usuario y retorna lo que sea que la funcion retorne, el manager recibe dicho retorno a través del archivo de lectura.

Para los problemas interactivos el manager solo maneja un par de archivos, lo que es una sola llamada al stub, para los problemas de comunicación manejará dos pares de archivos, para llamar dos veces al stub. Dichas llamadas son independientes una de otra, es decir, reiniciará el código del competidor para que el único medio de comunicación sea a través del manager.

En el manager debe declarar que se cierra el STDIN al terminar de leer el input al igual que cada llamada al stub al terminar sus procesos, tipicamente con la función fclose(archivo); (fclose(stdin); fclose(grader1in); fclose(grader1out); ...)

# Stub
Este archivo es el que mantendra comunicación con el código del competidor, inicialmente al stub se le comunica por default la cantidad de llamadas que se le harán, en este caso le haremos una o dos llamadas, el caso para cada una está bien definido en el template.

El stub recibe un par de archivos, uno de lectura y el otro de escritura.

Dentro de cada if se debe especificar lo que se desea hacer para cada llamada, el primer if es para la primera llamada y el segundo if es para la segunda, en caso de que haya una segunda. Cada llamada al stub debe hacerle flush al output a través de los archivos, típicamente con fflush(fout); (fout siendo el archivo de escritura). En caso de no hacer fflush o mantener en un estado estático al stub, el CMS se quedará evaluando infinitamente.

# Archivo .h
Este archivo almacenará el nombre de las funciones para que el código del competidor y el stub puedan acceder a ellas de ser necesario. Para acceder a dichas funciones es necesario colocar el header ' #include "problema.h" ' donde "problema" es el nombre asignado al archivo.
