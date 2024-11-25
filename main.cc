// Declaracion de librerias
#include <iostream>

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


