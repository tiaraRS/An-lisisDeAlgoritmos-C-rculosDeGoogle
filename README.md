# Analizando círculos de Google+ - Proyecto final Análisis de Algoritmos
Para correr los archivos se debe tener la carpeta `gplus` (con los archivos .edges) en la misma carpeta que los `.cpp` y `.exe`.
- Pre requisito: tener instalado el compilador de C++

## Crear el grafo de usuarios y conexiones
Para responder a todas las preguntas, se recurrio a cargar el grafo desde los archivos `.edges`. Para eso se creo la libreria [`createGraph.h`](/createGraph.h) para reutilizar el código de lectura de los archivos.

### Número total de usuarios y conexiones en la red
Resuelto en [`usersAndConections.cpp`](/usersAndConections.cpp), se puede compilar y ejecutar el codigo corriendo los siguientes comandos, desde la carpeta raiz del repositorio:
```
g++ usersAndConections.cpp -o usersAndConections.exe
./usersAndConections.exe
```
```
El número total de usuarios en la red 102119
El número total de conexiones en la red 13667810
```

### Distancia máxima y distancia promedio entre dos usuarios en la red
Resuelto en [`maxAndAvgDistance.cpp`](/maxAndAvgDistance.cpp), se puede compilar y ejecutar el codigo corriendo los siguientes comandos, desde la carpeta raiz del repositorio:
```
g++ -O2 -std=c++11 -Wall "-Wl,--stack=268435456" maxAndAvgDistance.cpp -o maxAndAvgDistance.exe
./maxAndAvgDistance.exe
```
```
La distancia máxima entre dos usuarios cualquiera de la red es 6
```
```
La distancia promedio entre dos usuarios cualquiera de la red es 2.82836
```

### Cantidad de componentes fuertemente conexas en el grafo
Resuelto en [`numberOfScc.cpp`](/numberOfScc.cpp)
Para compilar es necesario utilizar el comando
```
g++ -O2 -std=c++11 -Wall "-Wl,--stack=268435456" numberOfScc.cpp -o numberOfScc.exe
```
Para garantizar la obtencion del resultado, evitando un desborde del stack.
Ejecución del archivo:
```
./numberOfScc.exe
```
```
La red tiene 32308 componentes fuertemente conexas
```

### Clique más grande encontrado en el grafo
Resuelto en [`maxClique.cpp`](/maxClique.cpp)\
Para compilar usar el comando
```
g++ -O2 -std=c++11 -Wall "-Wl,--stack=268435456" maxClique.cpp -o maxClique.exe
```
El ejecutable permite correr los tests con los grafos de prueba mostrados en el informe mediante el comando:
```
./maxClique.exe -t
```
Devolviendo las respuestas finales de esta manera:
```
-> Max clique size 4
-> 2 5 7 9
```
El ejecutable tambien permite buscar el maximo clique sobre el grafo de google+ mediante el comando:
```
./maxClique.exe
```
Este cargara el grafo en memoria y calculara el maximo clique. (no llego al resultado final en 8 hrs. de ejecución)
