
```md
# Tarea 1 - ANÁLISIS DE ALGORITMOS Y TEORÍA DE AUTÓMATAS (AATA)

Este repositorio contiene el código fuente y los archivos necesarios para compilar y ejecutar la **Tarea 1** del curso de ANÁLISIS DE ALGORITMOS Y TEORÍA DE AUTÓMATAS (AATA).

## Descripción de la Tarea

El problema principal consiste en implementar la multiplicación de matrices cuadradas de dimensión \(n \times n\) usando diferentes algoritmos y comparar sus rendimientos.

### Algoritmos implementados:

1. **Algoritmo tradicional**: Implementación directa de la multiplicación de matrices basado en la definición clásica. La complejidad de este algoritmo es \(O(n^3)\).
2. **DR1**: Algoritmo que utiliza la primera propiedad de la descomposición de las matrices en submatrices.
3. **DR2**: Algoritmo que aplica la segunda propiedad con una serie de productos parciales y combinaciones de submatrices.

El objetivo de la tarea es medir el rendimiento de estos algoritmos con matrices generadas aleatoriamente de diferentes tamaños y completar una tabla con los tiempos de ejecución. Además, se deben extraer conclusiones sobre el comportamiento de los algoritmos y realizar un análisis asintótico de su rendimiento.

### Tamaños de las matrices evaluadas:

- 32, 64, 128, 256, 512, 1024, 2048, 4096 (dependiendo del tiempo razonable de ejecución).

## Archivos

- **Tarea-1-AATA.cpp**: Código fuente en C++ que implementa los tres algoritmos de multiplicación de matrices (tradicional, DR1, y DR2).
- **Makefile**: Archivo para automatizar el proceso de compilación, limpieza y ejecución del programa.

## Instrucciones de Compilación y Ejecución

Para compilar y ejecutar el programa, sigue los siguientes pasos:

### Compilar el programa

En Linux o macOS:

```bash
make
```

En Windows (con un entorno de compilación compatible como MinGW):

```bash
make
```

### Ejecutar el programa

En Linux o macOS:

```bash
make run
```

En Windows:

```bash
make run
```

### Limpiar archivos generados

Para eliminar el ejecutable generado:

```bash
make clean
```

## Dependencias

- `g++`: Se utiliza como compilador C++.
- El programa es compatible tanto en sistemas Windows como en sistemas basados en Unix (Linux, macOS).

## Conclusiones Esperadas

Una vez completadas las pruebas con diferentes tamaños de matrices, se deben obtener al menos dos conclusiones sobre el rendimiento de los algoritmos en función de su complejidad y comportamiento asintótico.
