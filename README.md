cc7-lab09
--------

## Requisitos ##

 - Uso de PThreads para:
	 - Joining
	 - Locks y Conditions

## Preguntas ##

Diferencias entre JAVA y C en la definición de Threads.

 **-Creación y definición de un Thread.**
La diferencia entre la creación de Threads no es tan grande. En Java un Thread ejecuta un objeto que implemente un Runnable, en C cualquier puntero a una función. Que en términos generales es lo mismo. 

Tal vez la diferencia más sustancial es que al usar PThread con una función, uno puede enviar como parámetro un puntero hacia los parámetros que la función paralelizada necesita. En Java debería hacerse un objeto global para que los Threads pueden acceder a ellos.

 **- Implementación de Locks**
Esta diferencia sí es bastante distinta, pues en Java cada vez que sincronizamos un bloque de código sabemos que existe un lock, pero no tenemos acceso directo a él. En cambio en C uno puede crear cuantos locks quiera. En Java se supone que existe un sólo lock.

 **- Implementación de Variables de Condición.**
 El implementar monitores en C es mucho más fácil que en C, no por la implementación sino por el control que uno tiene sobre él. En Java sólo necesitábamos usar la palabra reservada **synchronized**, para hacer un código atómico. Acá se entiende que existe un monitor asociado, pero como en el caso de los Locks, es inaccesible por nosotros. En cambio en C uno puede crear la función de los monitores con mucho más control, es C no podíamos esperar menos :D

----------

**Galileo University**
**2016**

