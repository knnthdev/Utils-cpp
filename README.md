<style>
    section {
        font-family:"Cascadia Code", "Monospace";
        font-size: 15px;
        background: #101d22;
        padding: 8px;
        max-width: 40em;
    }
    obj {
        color: limegreen;
    }
    var {
        color: lightblue;
    }
    type {
        color:blue;
    }
    num {
        color: greenyellow;
    }
    func {
        color: khaki;
    }
    symb {
        color: mediumvioletred;
    }
    str{
        color: salmon;
    }
    .indent {
        padding-left: 2em;
    }
</style>
# Utils-cpp

## Librería C++ con herramientas útiles para el desarrollo

**Descripción:**

Este repositorio contiene dos archivos de encabezado `(*.h)` escritos en `C++` que proveen diversas herramientas para facilitar el desarrollo de software. Las herramientas disponibles son:

### Tupla con instancia no estática:

> - Permite obtener o crear una tupla con una instancia no estática.
> - Utiliza plantillas variádicas para almacenar los valores en una clase `stringstream`.
> - Devuelve argumentos ingresados a funciones y los indiza.

### Listado con nodos "`Belly\<typename>`"

> - Similar a la clase `vector`, pero sin heredar sus métodos.
> - Proporciona la habilidad de `mapear` y `filtrar` datos usando funciones `lambda`.
> - Utiliza enlazamientos de nodos, de este modo el crecimiento de la memoria es dinámica y administrada.
> - Permite `Crear`, `Actualizar`, `Modificar`, `Insertar` y `Eliminar` valores ingresados.
> - Permite al desarrollador jugar con los datos a su gusto.

### Herramienta "`print(std::string, ...)`"

> - Método de función que recibe dos argumentos:
>   > - Mensaje a imprimir.
>   > - Argumento con expansión de plantillas.

> - Imprime un mensaje en la consola concatenando los datos almacenados en variables dentro del texto a imprimir.
Ejemplo: <code><func>print</func>(<str>"size: {0}"</str>, <var>list</var>.<func>size</func>());</code>;


### Ejemplo:
<section>
<type>int</type> <func>main</func>()
<br />{<br/>
<section class="indent">
<obj>Belly</obj><<type>int</type>><var>list</var> = {<num>23</num>, <num>42</num>, <num>2</num>, <num>452</num>, <num>908</num>, <num>28399</num>, <num>654</num>, <num>8</num>};<br />
<var>list</var>.<func>Print</func>();<br />
<var>list</var>.<func>Map</func><int>([](<type>auto</type> <var>it</var>) -><type>int</type> {<br />
<symb>return</symb> <var>it</var> - <num>2</num>;<br />
}).<func>Filter</func>([](<type>auto</type> <var>it</var>){<br />
<symb>return</symb> <var>it</var> % <num>2</num> == <num>0</num>;<br />
}).<func>Print</func>();<br />
<symb>return</symb> <obj>utils</obj>::<func>print</func>(<str>"size: {0}"</str>, <var>list</var>.<func>size</func>());
</section>
}
</section>
---
<section>
output <br />
0: 23 <br />
1: 42 <br />
2: 2 <br />
3: 452 <br />
4: 908 <br />
5: 28399 <br />
6: 654 <br />
7: 8 <br />
0: 40 <br />
1: 0 <br />
2: 450 <br />
3: 906 <br />
4: 652 <br />
5: 6 <br />
size: 8
</section>

### Conoce más de mí:
<https://about.me/kennethbriones/>
