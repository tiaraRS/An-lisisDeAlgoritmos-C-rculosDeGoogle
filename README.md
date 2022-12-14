# Analizando círculos de Google+ - Proyecto final Análisis de Algoritmos
Para correr los archivos se debe tener la carpeta `gplus` (con los archivos .edge) en la misma carpeta que los `.cpp` y `.exe`.

## Crear el grafo de usuarios y conexiones
Para responder a todas las preguntas, se recorrio a cargar el grafo desde los archivos `.edges`. Para eso se creo la libreria [`createGraph.h`](/createGraph.h) para reutilizar el código de lectura de los archivos.

### Número total de usuarios y conexiones en la red
Resuelto en [`usersAndConections.cpp`](/usersAndConections.cpp) \
Resutlado
```
El número total de usuarios en la red 102119
El número total de conexiones en la red 13667810
```

### Distancia máxima entre dos usuarios en la red

```
La distancia máxima entre dos usuarios cualquiera de la red es 6
```

### Distancia promedio entre dos usuarios de la red
```
La distancia promedio entre dos usuarios cualquiera de la red es 2.82836
```

### Cantidad de componentes fuertemente conexas en el grafo
Para compilar el archivo ...
es necesario utilizar el comando
```
g++ -O2 -std=c++11 -Wall "-Wl,--stack=268435456" numberOfScc.cpp -o numberOfScc.exe
```
para garantizar la obtencion del resultado, evitando un desborde del stack.

```
La red tiene 32307 componentes fuertemente conexas
```

### Clique más grande encontrado en el grafo
