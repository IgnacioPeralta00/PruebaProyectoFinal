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
  bool SearchMember(Member *, std::string);
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

