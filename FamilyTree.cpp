#include "FamilyTree.hpp"
using namespace family;
//TODO start with father -> root -> mother

Tree& Tree::addFather(string child, string father){
    // Tree::addFather(child, father, this->root);
    return *this;
}

Tree& Tree::addFather(string child, string father, Person* start){
    if (start != nullptr){
        if (start->name == child){
            if (start->father != nullptr){
                throw RuleException(child + "- already has a father");
            }
            Person* p = new Person(father);
            start->father = p;
            return *this;
        }
        this->addFather(child, father, start->father);
        this->addFather(child, father, start->mother);
    }
    return *this;
} 


 Tree& Tree::addMother(string child, string mother){
    // Tree::addMother(child, mother, this->root); 
    return *this;
 }
Tree& Tree::addMother(string child, string mother, Person* start){
    if (start != nullptr){
        if(start->name == child){
            if (start->mother != nullptr){
                throw RuleException(child + "- already has a mother");
            }
            Person* p = new Person(mother);
            start->mother = p;
            return *this;
        }
        this->addMother(child, mother, start->father);
        this->addMother(child, mother, start->mother);
    }
    return *this;
}



string Tree::relation(string relate){
    return " ";
}
string Tree::find(string family_relation ){
    return " ";
}
void Tree::display(){
    return;
}
void Tree::remove(string name){
    return;
}