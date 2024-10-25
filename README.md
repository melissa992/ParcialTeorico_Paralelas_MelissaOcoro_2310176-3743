Parcial practico Angie Melissa Ocoro Hurtado 2310176-3743

ejecucion programa secuencial  secuencial Promedio ( 39,299 )
39,299
39,461
39,104
37,139 - (x)
49,801 + (x)


numero de nucleos 2 Promedio	(34,729 )
38,851 + (x)
38,629
27,438
25,656 - (x)
38,120

numero de nucleos 4 Promedio	(37,942 )
36,521
35,574 - (x)
40,173
37,131
43,959 + (x)


Speedup 2 hilos 1,131
Speedup 4 hilos 1,035

Eficiencia 2 hilos 56,6 % 
Eficiencia 4 hilos 25,9 %

Analisis de resultado:
Al analizar los resultados de mi programa, empecé observando el tiempo de ejecución en modo secuencial, que fue de 39,288 ms. Este valor me sirvió como
referencia para evaluar el rendimiento de las versiones paralelas.Cuando ejecuté el programa utilizando 2 núcleos, el tiempo de ejecución promedio disminuyó a
 34,729 ms. Esto representa una mejora significativa en comparación con la ejecución secuencial, lo que indica que la paralelización fue efectiva al aprovechar 
los recursos de hardware disponibles. El speedup obtenido con 2 hilos fue de 1,131, lo que significa que el programa se volvió 1.13 veces más rápido 
en comparación con la versión secuencial.Pero al aumentar el número de núcleos a 4, observé que el tiempo de ejecución promedio aumentó a 37,942 ms. Este incremento fue inesperado, 
ya que normalmente se esperaría que utilizar más núcleos redujera aún más el tiempo de ejecución. Este comportamiento se por la sobrecarga asociada 
con la gestión de hilos, así como la competencia por recursos compartidos, como la memoria, pueden haber afectado negativamente el rendimiento.
Al calcular la eficiencia de los hilos, encontré que con 2 hilos era del 56,6%, lo que indica que más de la mitad de la capacidad de procesamiento de
los núcleos se utilizó de manera efectiva. la eficiencia con 4 hilos cayó al 25,9%. Esta disminución refuerza la idea de que al aumentar
el número de hilos, la sobrecarga de gestión y la competencia por recursos pueden contrarrestar las ventajas que la paralelización debería ofrecer.
los resultados muestran que la paralelización con 2 hilos tiene mas ventaja en a la hora de tiempo de ejecución, mientras que el uso de 4 hilos 
resultó en un rendimiento decreciente. Esto muestra la importancia no solo la tener en cuenta la cantidad de hilos, sino también la naturaleza del problema
 y la forma en que se gestionan los recursos a la hora de hacer la paralelización.



