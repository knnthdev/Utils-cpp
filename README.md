# Utils-cpp

## Librería C++ con herramientas útiles para el desarrollo

**Descripción:**

Este repositorio contiene dos archivos de encabezado `(*.h)` escritos en `C++` que proveen diversas herramientas para facilitar el desarrollo de software. Las herramientas disponibles son:

### Tupla con instancia no estática:

* Permite obtener o crear una tupla con una instancia no estática.
* Utiliza plantillas variádicas para almacenar los valores en una clase `stringstream`.
* Devuelve argumentos ingresados a funciones y los indiza.

### Listado con nodos "`Belly\<typename>`"

* Similar a la clase `vector`, pero sin heredar sus métodos.
* Proporciona la habilidad de `mapear` y `filtrar` datos usando funciones `lambda`.
* Utiliza enlazamientos de nodos, de este modo el crecimiento de la memoria es dinámica y administrada.
* Permite `Crear`, `Actualizar`, `Modificar`, `Insertar` y `Eliminar` valores ingresados.
* Permite al desarrollador jugar con los datos a su gusto.

### Herramienta "`print(std::string, ...)`"

* Método de función que recibe dos argumentos:
> - Mensaje a imprimir.
> - Argumento con expansión de plantillas.

* Imprime un mensaje en la consola concatenando los datos almacenados en variables dentro del texto a imprimir.
Ejemplo: `print("size: {0}", list.size());`


### Ejemplo:
```cpp
int main()
{
    Belly<int> list = {23, 42, 2, 452, 908, 28399, 654, 8};
    list.Print();
    list.Map<int>([](auto it) ->int {
        return it - 2;
    }).Filter([](auto it){
        return it % 2 == 0;
    }).Print();
    
    return print("size: {0}", list.size());
}
```
---
```console
Output
0: 23
1: 42
2: 2
3: 452
4: 908
5: 28399
6: 654
7: 8
0: 40
1: 0
2: 450
3: 906
4: 652
5: 6
size: 8
```
---
### Conoce más de mí:
<https://about.me/kennethbriones/>
