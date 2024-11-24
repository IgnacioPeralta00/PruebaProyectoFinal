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