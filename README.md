# ![logo-UCA](C:\Users\Peral\Pictures\Imágenes)  

### Proyecto presentado por:
- Fidel Ignacio Peralta Rivas
- Oscar Remberto Soriano Lopez


# Manual de Usuario
El programa define un sistema para gestionar un árbol genealógico utilizando una estructura jerárquica basada en las clases `Miembro` y `ArbolFamiliar`. Este código incluye varias funcionalidades como inserción, eliminación, búsqueda, visualización y manejo de archivos (exportación e importación).

---

## Guía de Instalación

### Requisitos previos:
- **Compilador:** MinGW o un compilador con soporte para C++.
- **IDE:** VS Code (opcional).
- **Espacio en disco:** Al menos 225 KB.
- **Otros:** Familiaridad mínima con la terminal.

### Instrucciones de Instalación
1. Descarga el código fuente desde el repositorio.
2. Instala MinGW y asegúrate de agregarlo al `PATH`.
3. Compila el programa desde la terminal con el comando:  
   ```bash
   g++ -o ArbolGenealogico main.cpp

4. Ejecuta el programa con un comando como:
    ```bash
    ./ArbolGenealogico
    
## Explicación de las Clases

### Clase `Miembro`
- **Propósito:** Representa un miembro único del árbol genealógico.
- **Atributos privados:**
  - `name`: Nombre del miembro.
  - `madre` y `padre`: Punteros a los nodos madre y padre.
- **Métodos:**
  - **Getters/Setters:** Para acceder y modificar los atributos.
  - **Constructor parametrizado:** Inicializa `name`, `madre` y `padre`.

### Clase `ArbolFamiliar`
- **Propósito:** Administra la estructura completa del árbol genealógico.
- **Atributo principal:**
  - `arbol`: Puntero a la raíz del árbol.
- **Métodos principales:**
  - **Gestión básica:** `InsertarMiembro`, `EliminarMiembro`, `BuscarMiembro`.
  - **Visualización:** `MostrarArbol`, `MostrarRelacionMiembro`.
  - **Manejo de archivos:**  
    - `ExportarArbol`: Exporta el árbol a un archivo.  
    - `ImportarArbol`: Reconstruye el árbol desde un archivo.
  - **Gestión de memoria:**  
    - `LiberarMemoria` y **destructor** para evitar fugas de memoria.
- **Otros métodos:**  
  - **Getters/Setters:** Para acceder y modificar atributos.
  - **Constructor:** Inicializa la raíz del árbol en `nullptr`.
  
  ## Menú Principal

El programa interactivo dentro de la consola incluye un menú para realizar las siguientes operaciones:

- **Agregar un miembro**: Permite añadir un nuevo miembro al árbol, verificando relaciones como madre o padre.
- **Eliminar un miembro**: Remueve un nodo específico del árbol (con manejo adecuado de referencias).
- **Buscar un miembro**: Indica si existe un miembro en el árbol.
- **Mostrar el árbol completo**: Visualiza el árbol en formato jerárquico.
- **Mostrar relaciones**: Lista las relaciones familiares de cada miembro.
- **Exportar el árbol**: Guarda la estructura del árbol en un archivo de texto.
- **Importar un árbol**: Carga la estructura desde un archivo para reconstruir el árbol.

## Características de las Funciones Principales

- **Inserción**:  
  El usuario puede especificar si el miembro añadido es madre o padre de otro existente, evitando duplicados.

- **Eliminación**:  
  El usuario puede eliminar un miembro del árbol ingresando el nombre. Si el miembro es la raíz, se eliminará el árbol completo.

- **Mostrar el árbol completo**:  
  Visualiza el árbol en formato consola partiendo de la raíz.

- **Visualizar relaciones entre miembros**:  
  Imprime en consola, a partir de la raíz, cada miembro y sus respectivos padres. Para aquellos miembros del árbol que aún no poseen un padre o madre, únicamente se imprimirá su nombre.

- **Exportar/Importar**:  
  - Exportar: Permite guardar diferentes versiones del árbol en un archivo de texto   visualizandolo de forma esquemática (arbol_familiar.txt)  y un archivo secundario (jerarquia_familiar.txt) que representa el arbol familiar en una jerarquía preorden.
  - Importar: Permite cargar un árbol ya existente desde un archivo de texto representado de forma jerárquica y lineal con un recorrido “preorden”. Usted podría generar un árbol personalizado desde el archivo (jerarquia_familiar.txt) siempre y cuando entienda el funcionamiento de este recorrido en profundidad. Importar el árbol de esta manera implica poder construir sobre este árbol, eliminar, buscar y todas las demás funcionalidades ya especificadas, incluso volver a exportarlo una vez modificado dentro del código. Debe tener cuidado ya que se sobreescribirá sobre los dos archivos ya mencionados.

### Otras Características

- **Recursividad**:  
  Utilizada extensivamente para explorar y gestionar los nodos del árbol, tanto para inserción como para visualización y eliminación y otras funciones secundarias.

- **Manejo de errores**:  
  - Validaciones en el menú para evitar entradas incorrectas: Algunas de las más importantes son:
- No permite sustituir el padre/madre de un miembro que ya posee uno, deberá primero eliminar el padre/madre actual y luego insertar el nuevo padre/madre
- No permite insertar dos miembros con el mismo nombre, cada miembro familiar dentro del árbol debe ser único.
  - Comprobación de existencia de archivos para importación/exportación.



