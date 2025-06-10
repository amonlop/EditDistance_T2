# EditDistance_T2

Este proyecto implementa distintos enfoques para calcular la distancia de mínima de edición entre dos cadenas, utilizando métodos recursivos, recursivo con memoization y programación dinámica.

## Compilación del Proyecto

Para compilar los ejecutables, sigue estos pasos:

### **Ejecuta make en la terminal**
```bash
make 
```
## Ejecutables generados

Después de ejecutar el comando anterior, los siguientes binarios estarán disponibles en el directorio `build/`:

- `main`
- `experimento_algo1`
- `experimento_algo2`
- `experimento_algo3`
- `experimento_algo4`
  
Cada uno de estos ejecutables corresponde a una variante de cálculo de distancia de edición:
- `experimento_algo1` corresponde al algoritmo recursivo.
- `experimento_algo2` corresponde al algoritmo recursivo con memoización.
- `experimento_algo3` corresponde al algoritmo con programación dinámica.
- `experimento_algo4` corresponde al algoritmo optimizado.
  
El main testea los casos de prueba iniciales ("kitten", "sitting", "listen", "silent").

## Ejecutar
Para ejecutar los binarios experimento_algoX, con X = 1,2,3,4, usa el siguiente formato:
```bash
./build/experimento_algoX <archivo1.txt> <archivo2.txt>
```
o en su defecto:
```bash
./build/experimento_algoX <string_a> <string_b>
```
Para ejecutar el main, simplemente usa:
```bash
./main
```
