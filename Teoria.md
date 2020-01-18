# Notas teóricas
**Fuente: [10.2 B Trees and B+ Trees. How they are useful in Databases
](https://www.youtube.com/watch?v=aZjYr87r1b8)**

## Árboles m-arios

* Son la estructura previa al Btree
* Tienen el problema de que no tienen un control sobre la forma en que se insertan las llaves
* Si quiero insertar n nodos, la altura del arbol podrias ser n


### Ejemplo:
```text
Sup un arbol de grado 10
Llaves a insertar: [10,20,30,....n]

Resultado:
[10           ]
   \
    [20            ]
     \ 
      [30              ]
       \
         ...
```

## Btrees
Son arboles m-arios con ciertas reglas.
### Reglas:
* Cada nodo debe ocupar la mitad del grado. ``` al menos ceil(m/2) hijos ```
    * Ej: un btree de grado 10 debe tener 5 llaves por nodo.
    * Sólo se puede añadir un nodo si el nodo actual esta lleno hasta la mitad.
* Root debe tener mínimo 2 hijos
* Todos los nodos hojas deben tener el mismo nivel
* Se crean de abajo para arriba

### Ejemplo:
```text
m = 4
keys: 10,20,40,50,60,70,80,30,35,5,15
Insertar 10:
[10| | ]
Insertar 20:
[10|20| ]
Insertar 40:
[10|20|40]
Insertar 50:
   [40]
   /    \
[10|20] [50 ]
Insertar 60:
   [40]
   /    \
[10|20] [50|60]
Insertar 70:
   [40]
   /    \
[10|20] [50|60|70]
Insertar 80:
   [40|70]
   /   \        \
[10|20] [50|60]  [80| | ]
Insertar 30: (min 32:25)
   [40|70]
   /   \        \
[10|20|30] [50|60]  [80| | ]
Insertar 35:
      [30  |40  | 70       ]
      /     /     \        \
[10|20][35||  ] [50|60]  [80| | ]
Insertar 5:
      [30  |40  | 70       ]
      /     /     \        \
[5|10|20][35||  ] [50|60]  [80| | ]
Insertar 15:
      [30  |40  | 70       ]
      /     /     \        \
[5|10|20][35||  ] [50|60]  [80| | ]


```
## Btree+
Igual que btrees nada más que la información está en los nodos hoja. Representa exactamente índices multinivel
* Cada llave estará presente en los nodos hoja
* Los nodos hoja están conectados