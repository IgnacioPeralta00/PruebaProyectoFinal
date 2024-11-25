// Declaracion de librerias
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>

#define COUNT                                                                  \
  10 // Variable definida en el preporcesador para la funion MostrarArbol

// codigos ANSI para cambiar los colores de la terminal
//  Funciona en la mayoria de terminales modernas de Windows y UNIX
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RED "\033[31m"

// Clase Miembro: Cada objeto representa un miembro familiar unico
class Member {
private:
  std::string name;
  struct Member *mother;
  struct Member *father;

public:
  Member(std::string); // Constructor parametrizado

  // Prototipos de metodos setter: Para acceder y modificar los atributos
  // privados
  void setName(std::string);
  void setMother(Member *);
  void setFather(Member *);

  // Prototipos de metodos getter: Para acceder y obtener los datos de los
  // atributos privados
  std::string getName() const;
  Member *getMother() const;
  Member *getFather() const;
};

// Definicion de constructor
Member::Member(std::string name_)
    : name(name_), mother(nullptr), father(nullptr) {}

// Definiciones de metodos setter y getter
void Member::setName(std::string name) { this->name = name; }
void Member::setMother(Member *mother) { this->mother = mother; }
void Member::setFather(Member *father) { this->father = father; }
std::string Member::getName() const { return this->name; }
Member *Member::getMother() const { return this->mother; }
Member *Member::getFather() const { return this->father; }

// Clase ArbolFamiliar: Cada objeto de este tipo puede gestionar un arbol
// familiar unico, conmpuesto por diferentes objetos tipo Miembro
class FamilyTree {
private:
  Member *root;

public:
  // Prototipos:

  FamilyTree(); // Constructor

  // Metodos setter y getter
  void setRoot(Member *);
  Member *getRoot();
  Member *CreateMember(std::string);
  Member *InsertMember(Member *, std::string);
  Member *InsertParents(Member *, std::string, std::string);
  Member *DeleteMember(Member *, std::string);
  bool SearchMember(Member *, std::string);
  std::string GenerateTree(const Member *, int, std::ostringstream &);
  std::string PrintTree(const Member *);
  void ShowMemberRelationship(const Member *);
  std::string GeneratePreorder(const Member *, std::ostringstream &);
  std::string PrintPreoder(const Member *);
  void ExportTree(Member *, std::ofstream &, std::ofstream &);
  void ExportTree(Member *, std::ofstream &, std::ofstream &);
  Member *ImportTree(std::ifstream &);
  void FreeMemory(Member *);
  void FreeMemory(Member *);
  ~FamilyTree(); // Destructor
};

// Definicion de metodos
FamilyTree::FamilyTree() : root(nullptr) {}

void FamilyTree::setRoot(Member *familiar) { this->root = familiar; }
Member *FamilyTree::getRoot() { return this->root; }

Member *FamilyTree::CreateMember(std::string name) {
  Member *new_member =
      new Member(name); // Gracias al constructor al crear una instancia
                        // miembro, papa y mama se inicializan como nullptr
  return new_member;
}

// Funcion para insertar miembro
Member *FamilyTree::InsertMember(Member *tree, std::string name) {
  // Condicional para evitar bucles infnitos en la funcion InsertParents
  if (name.empty()) {
    std::cout << "Nombre vacio. La insercion fallo. " << std::endl;
    return tree; // Retorna el arbol sin modificar
  }

  // Si el miembro ya existe no permite duplicados
  if (SearchMember(tree, name)) {
    std::cout << "El miembro: |" << name
              << "| ya existe en el arbol familiar. La insercion fallo. "
              << std::endl;
    return tree; // Retorna el arbol sin modificar
  }

  // Si el arbol esta vacio el nombre se agrega a la raiz del arbol
  if (tree == nullptr) {
    std::cout << "Agregando |" << name << "| a la raiz del arbol familiar. "
              << std::endl;
    Member *new_root = CreateMember(name);
    return new_root;
  }

  // Si el arbol no esta vacio encontrar a que miembro se le quiere agregar una
  // madre o padre
  std::string name_son;
  std::cout << "Quien es el hijo/a de: |" << name << "|" << std::endl;
  std::getline(std::cin, name_son);

  if (SearchMember(tree, name_son)) {
    Member *new_member = InsertParents(tree, name_son, name);
    return new_member;
  } else {
    std::cout << "No se encontro el miembro. " << std::endl;
  }
  return tree;
}

// Funcion auxiliar para insertar padres de un miembro
Member *FamilyTree::InsertParents(Member *tree, std::string name_son,
                                  std::string name) {
  if (tree == nullptr) { // Si el arbol esta vacio no podemos agregar padres
    return nullptr;
  }

  if (tree->getName() == name_son) { // Si el nodo que buscamos es el
                                     // actual agregamos madre/padre
    std::string relationship;
    // Bucle para que el usuario ingrese correctamente la palabra sin
    // necesidad de volver al menu
    do {
      std::cout << "|" << name << "| es (mama) o (papa) de "
                << "|" << name_son << "|. " << std::endl;
      std::getline(std::cin, relationship);

      if (relationship == "mama" || relationship == "papa") {
        break;
      }
      std::cout << "Entrada no valida. Solo puede ser (mama) o (papa). "
                << std::endl;
    } while (true); // Mientras el usuario no ingrese las unicas 2 posibles
                    // relaciones se repetira

    if (relationship == "mama") {
      if (tree->getMother() != nullptr) { // Si el puntero esta lleno no se
                                          // puede agregar una nueva mama
        std::cout << "|" << name_son << "| ya tiene mama: |"
                  << tree->getMother()->getName() << "|" << std::endl;
        std::cout
            << "Si deseas agregar una nueva mama debes eliminar la actual. "
            << std::endl;
      } else {
        std::cout << "Agregando a |" << name << "| como mama de |" << name_son
                  << "|. " << std::endl;
        tree->setMother(CreateMember(name));
      }
    } else if (relationship == "papa") {
      if (tree->getFather() != nullptr) { // Si el puntero esta lleno no se
                                          // puede agregar un nuevo papa
        std::cout << "|" << name_son << "| ya tiene papa: |"
                  << tree->getFather()->getName() << "|" << std::endl;
        std::cout
            << "Si deseas agregar una nuevo papa debes eliminar el actual. "
            << std::endl;
      } else {
        std::cout << "Agregando a |" << name << "| como papa de |" << name_son
                  << "|. " << std::endl;
        tree->setFather(CreateMember(name));
      }
    }
  } else { // Si el nodo actual no es el que buscamos recorremos el arbol de
           // manera recursiva
    tree->setMother(InsertParents(tree->getMother(), name_son, name));
    tree->setFather(InsertParents(tree->getFather(), name_son, name));
  }
  return tree; // Retornarmos en arbol sin modificar
}

// Funcion para eliminar un miembro del arbol
Member *FamilyTree::DeleteMember(Member *tree, std::string name) {
  static bool is_root = true;
  if (tree == nullptr && is_root) { // Si el arbol esta vacio no eliminamos nada
    std::cout << "El arbol esta vacio. " << std::endl;
    return nullptr;
  }

  if (!SearchMember(tree, name)) { // Si el miembro que se busca no existe
                                   // retornar el arbol sin modificar
    static bool member_found = false;
    if (!member_found && is_root) {
      std::cout
          << "No se encontro el miembro | " << name
          << " | en el arbol familiar. "
          << std::endl; // Solo desplegamos este mensaje en la llamada original
      member_found = true;
    }
    member_found = false; // Reiniciamos la bandera para futuras eliminaciones
    return tree;
  }
  is_root = false; // Indicamos que ya no estamos en la raiz

  if (tree->getName() == name) {
    std::cout << "Eliminando la raiz del arbol familiar " << name << "... "
              << std::endl;
    if (tree->getMother() != nullptr || tree->getFather() != nullptr) {
      std::cout << "Eliminando arbol completo... " << std::endl;
      FreeMemory(tree->getMother());
      FreeMemory(tree->getFather());
      delete tree;
      tree = nullptr;
    } else {
      delete tree;
      tree = nullptr;
    }
    is_root = true; // Reiniciamos la bandera para futuras eliminaciones
    return nullptr;
  }

  if (tree->getMother() != nullptr &&
      tree->getMother()->getName() ==
          name) { // Si el nodo a eliminar es un nodo mama
    Member *erase_mother = tree->getMother();
    std::cout << "Eliminando miembro: " << name << "... " << std::endl;
    if (erase_mother->getMother() !=
        nullptr) { // Si el nodo mama a eliminar tiene un nodo mama reasignamos
                   // ese nodo
      tree->setMother(
          erase_mother->getMother()); // Saltamos madre e eliminar, la nueva
                                      // "madre" sera la abuela
      FreeMemory(erase_mother->getFather());
      delete erase_mother;
    } else { // Si el nodo mama a eliminar no tiene un nodo mama, el nuevo nodo
             // mama apuntara a nulltpr
      tree->setMother(nullptr);
      FreeMemory(erase_mother->getFather()); // Liberamos en caso de no tener
                                             // mama pero si tener papa
      delete erase_mother;
    }
    std::cout << "Miembro eliminado exitosamente. " << std::endl;
    return tree;
  }

  if (tree->getFather() != nullptr &&
      tree->getFather()->getName() ==
          name) { // Si el nodo a eliminar es un nodo papa
    Member *erase_father = tree->getFather();
    std::cout << "Eliminando miembro: " << name << "... " << std::endl;
    if (erase_father->getFather() !=
        nullptr) { // Si el nodo papa a eliminar tiene un nodo papa reasignamos
                   // ese nodo
      tree->setFather(
          erase_father->getFather()); // Saltamos padre e eliminar, el nuevo
                                      // "padre" sera el abuelo
      FreeMemory(erase_father->getMother());
      delete erase_father;
    } else { // Si el nodo papa a eliminar no tiene un nodo papa, el nuevo nodo
             // papa apuntara a nulltpr
      tree->setFather(nullptr);
      FreeMemory(erase_father->getMother()); // Liberamos en caso de no tener
                                             // papa pero si tener mama
      delete erase_father;
    }
    std::cout << "Miembro eliminado exitosamente. " << std::endl;
    return tree;
  }

  // Buscamos de manera recursiva en los nodos mama/papa el nodo a eliminar
  tree->setMother(DeleteMember(tree->getMother(), name));
  tree->setFather(DeleteMember(tree->getFather(), name));

  is_root = true; // Reiniciamos la bandera para futuras eliminaciones
  return tree;    // Retornar el arbol sin modificar
}

// Funcion para encontrar un miembro dentro del arbol
bool FamilyTree::SearchMember(Member *tree, std::string name) {
  if (tree == nullptr)
    return false; // Si el arbol esta vacio retorna false

  if (tree->getName() == name) { // Si el miembro que buscamos esta en el
                                 // nodo actual retorna true
    return true;
  } else { // Buscamos recursivamente entre todos los nodos del arbol
    return SearchMember(tree->getMother(), name) ||
           SearchMember(tree->getFather(), name);
  }
}

// Funcion que genera el arbol familiar como una cadena string, usando
// std::ostringstream para el flujo de cadenas
std::string FamilyTree::GenerateTree(const Member *tree, int space,
                                     std::ostringstream &tree_as_string) {
  if (this->root == nullptr) {
    tree_as_string << "El arbol familiar esta vacio. No hay nada que mostrar."
                   << std::endl;
    return tree_as_string.str();
  }

  if (tree == nullptr) // Caso base: no hay mas nodos
    return tree_as_string.str();

  // Aumenta la distancia entre los niveles
  space += COUNT;

  // Recorremos los nodos mama para mostrarlos
  GenerateTree(tree->getMother(), space, tree_as_string);

  // Imprime el nodo actual despues del espaciado
  // count
  tree_as_string << std::endl;
  for (int i = COUNT; i < space; i++)
    tree_as_string << " ";
  tree_as_string << tree->getName() << std::endl;

  // Recorremos los nodos papa para mostrarlos
  GenerateTree(tree->getFather(), space, tree_as_string);
  return tree_as_string.str();
}

// Funcion que retorna el arbol como una string generado por GenerateTree()
std::string FamilyTree::PrintTree(const Member *tree) {
  std::ostringstream tree_as_string;
  std::ostringstream tree_aux;
  // Pasar tamaño del espaciado
  tree_as_string << GenerateTree(tree, 0, tree_aux);
  return tree_as_string.str();
}

// Funcion para mostrar las relaciones entre los miembros del arbol
void FamilyTree::ShowMemberRelationship(const Member *tree) {
  if (this->root == nullptr) { // Verificar si el árbol global está vacío
    std::cout
        << "\nEl arbol familiar esta vacio. No hay relaciones que mostrar."
        << std::endl;
    return;
  }
  if (tree == nullptr) { // Caso recursivo: no hay mas nodos
    return;
  }

  // Mostramos la relacion por cada nodo empezando por el actual
  std::cout << "Mi nombre es " << tree->getName();
  if (tree->getMother() != nullptr) {
    std::cout << ", mi madre es " << tree->getMother()->getName();
  }
  if (tree->getFather() != nullptr) {
    std::cout << ", mi padre es " << tree->getFather()->getName();
  }
  std::cout << "." << std::endl;

  // Recorremos el arbol de manera recursiva para establecer todas las
  // relaciones de la familia
  ShowMemberRelationship(tree->getMother());
  ShowMemberRelationship(tree->getFather());
}

// Funcion que genera la jerarquia preorden del arbol como una cadena string,
// tambien usa std::ostringstream
std::string FamilyTree::GeneratePreorder(const Member *tree,
                                         std::ostringstream &preorder_string) {
  if (tree != nullptr) {
    preorder_string << tree->getName() << std::endl;
    GeneratePreorder(tree->getMother(), preorder_string);
    GeneratePreorder(tree->getFather(), preorder_string);
  } else {
    preorder_string << "nullptr" << std::endl;
  }
  return preorder_string.str();
}

// Funcion que retorna la jerarquia preornden, se imprime dentro de un .txt (ver
// funcion exportar/importar)
std::string FamilyTree::PrintPreoder(const Member *tree) {
  std::ostringstream preorder_string, mother_tree, father_tree;
  preorder_string << tree->getName() << std::endl;
  preorder_string << GeneratePreorder(tree->getMother(), mother_tree);
  preorder_string << GeneratePreorder(tree->getFather(), father_tree);
  return preorder_string.str();
}

// Funcion para exportar el arbol hacia un archivo .txt
void FamilyTree::ExportTree(Member *tree, std::ofstream &file,
                            std::ofstream &file_aux) {
  if (tree ==
      nullptr) { // Si el arbol esta vacio mostramos nullptr porque el nodo
                 // esta vacio archivo_entrada << std::string(nivel * 2, ' ')
                 // << "Nodo vacio. " << std::endl;
    return;
  }
  if (!file) {
    std::cerr << "Error al abrir el archivo para exportar." << std::endl;
  }
  file_aux << PrintPreoder(
      tree);               // Pasamos la jerarquia (preorden) a un archivo .txt
  file << PrintTree(tree); // Pasamos la impresion del arbol a un archivo .txt
}

// Funcion para importar y reconstruir un arbol desde un archivo .txt (ve)
Member *FamilyTree::ImportTree(std::ifstream &input_file) {
  std::string name;

  // Leer el siguiente nombre desde el archivo
  if (!std::getline(input_file, name) || name == "nullptr") {
    return nullptr; // Si es "nullptr" o no hay mas lineas retorna nullptr
  }

  // Crear un nuevo nodo Miembro con el nombre leido
  Member *new_root = CreateMember(name);

  // Llamadas recursivas para los nodos madre y padre
  new_root->setMother(ImportTree(input_file));
  new_root->setFather(ImportTree(input_file));

  return new_root; // Retorna la raiz del subarbol construido
}

// Funcion auxiliar que es llamada por el destructor al finalizar la funcion
// main
void FamilyTree::FreeMemory(Member *tree) {
  if (tree == nullptr) { // si el arbol esta vacio no hay nada que liberar
    return;
  }
  // Hacemos uso de la recursividad para liberar todos los nodos del arbol
  FreeMemory(tree->getMother());
  tree->setMother(nullptr);
  FreeMemory(tree->getFather());
  tree->setFather(nullptr);
  delete tree;
}
FamilyTree::~FamilyTree() { FreeMemory(this->root); }

// Funcion para mostrar el menu con mejor estetica
void MostrarMenu() {

  // Titulo con formato
  std::cout << "\n";
  std::cout << CYAN
            << "=====================================================" << RESET
            << std::endl;
  std::cout << CYAN << "              *** GESTOR DE ARBOL FAMILIAR ***        "
            << RESET << std::endl;
  std::cout << CYAN
            << "=====================================================" << RESET
            << std::endl;
  std::cout << BLUE << BOLD << "Selecciona una opcion:" << RESET << std::endl;
  std::cout << std::endl;

  // Opciones del menu con formato
  std::cout << GREEN << "1. " << RESET << "Ingresar un miembro a la familia."
            << std::endl;
  std::cout << GREEN << "2. " << RESET << "Eliminar un miembro de la familia."
            << std::endl;
  std::cout << GREEN << "3. " << RESET
            << "Buscar un miembro dentro de la familia." << std::endl;
  std::cout << GREEN << "4. " << RESET << "Mostrar el arbol familiar completo."
            << std::endl;
  std::cout << GREEN << "5. " << RESET
            << "Mostrar las relaciones entre los miembros de la familia."
            << std::endl;
  std::cout << GREEN << "6. " << RESET << "Exportar el arbol familiar."
            << std::endl;
  std::cout << GREEN << "7. " << RESET << "Importar el arbol familiar."
            << std::endl;
  std::cout << GREEN << "8. " << RESET << "Salir." << std::endl;
  std::cout << std::endl;

  // Barra divisoria
  std::cout << CYAN
            << "=====================================================" << RESET
            << std::endl;

  // Solicitar la opcion
  std::cout << BLUE << "Ingrese su opcion: " << RESET;
}

// Funcion para usar pausa en los casos del menu
void Pause() {
  std::cout << "\n";
  system("pause");
}

//Funcion Principal Main
int main(int argc, char *argv[]){

    FamilyTree my_tree; // Arbol vacio
  std::ostringstream tree_impresion;
  int option = 0;
  std::string name, relationship;

  do {
    MostrarMenu();
    std::cin >> option;

    if (std::cin.fail()) { // Si ingresa una letra o un valor diferente
                           // entre 1-7, este lo ignora para evitar bucles
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << RED << "Tipo de dato no admitido. " << RESET << std::endl;
      Pause();
      continue;
    }

    switch (option) {
    case 1:
      std::cout << "Ingrese el nombre del nuevo miembro: " << std::endl;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::getline(std::cin, name);
      my_tree.setRoot(my_tree.InsertMember(my_tree.getRoot(), name));
      break;
    case 2:
      std::cout << "Ingrese el nombre del miembro a eliminar: " << std::endl;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::getline(std::cin, name);
      my_tree.setRoot(my_tree.DeleteMember(my_tree.getRoot(), name));
      Pause();
      break;
    case 3:
      std::cout << "Ingrese el miembro que desea buscar: " << std::endl;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::getline(std::cin, name);
      if (my_tree.SearchMember(my_tree.getRoot(), name)) {
        std::cout << GREEN << "Miembro encontrado! " << RESET << std::endl;
      } else {
        std::cout << RED << "No se encontro el miembro." << RESET << std::endl;
      }
      Pause();
      break;
    case 4:
      std::cout << CYAN
                << "\n******************* ARBOL FAMILIAR "
                   "*******************"
                << RESET << std::endl;
      std::cout << my_tree.PrintTree(my_tree.getRoot());
      std::cout << std::endl;
      Pause();
      break;
    case 5:
      my_tree.ShowMemberRelationship(my_tree.getRoot());
      std::cout << std::endl;
      Pause();
      break;
    case 6: {
      std::ofstream tree_file("arbol_familiar.txt", std::ios::trunc);
      std::ofstream preorder_file("preorden_familiar.txt", std::ios::trunc);
      my_tree.ExportTree(my_tree.getRoot(), tree_file, preorder_file);
      std::cout << GREEN
                << "Arbol exportado exitosamente a 'arbol_familiar.txt' "
                << RESET << std::endl;
      break;
    }
    case 7: {
      std::ifstream intput_file("preorden_familiar.txt");
      if (!intput_file) {
        std::cerr << RED
                  << "Error. No se pudo abrir el archivo para importarlo. "
                  << RESET << std::endl;
        break;
      } else {
        my_tree.FreeMemory(my_tree.getRoot());
      }

      my_tree.setRoot(my_tree.ImportTree(intput_file));
      std::cout << GREEN << "Arbol importado exitosamente!" << RESET
                << std::endl;
    } break;
    case 8:
      std::cout << YELLOW << "Saliendo del programa..." << RESET << std::endl;
      break;
    default:
      std::cout << RED << "Entrada invalida. Debe ser entre (1-8)." << RESET
                << std::endl;
      break;
    }

    std::cout << std::endl;
  } while (option != 8);

  return 0;
  
}
