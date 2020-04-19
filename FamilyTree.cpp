#include "FamilyTree.hpp"
using namespace family;
//TODO start with father -> root -> mother
/**
 * This method receives two arguments - 
 *      name of the person wanted
 *      the person in the tree to start search from
 * It returns the node of that person, going by father-root-mother -> Left-Root-Right
 */
Person* Tree::getPerson(string wanted, Person* start){
    if (start == nullptr){
        return nullptr;
    }
    if (start->father->name == wanted){
        return start->father;
    }else if (start->name == wanted){
        return start;
    }else if(start->mother->name == wanted){
        return start->mother;
    }
    Person* f_side = getPerson(wanted, start->father);
    Person* m_side = getPerson(wanted, start->mother);

    if (f_side)
        return f_side;
    if (m_side)
        return m_side;

    return nullptr;
}



Tree& Tree::addFather(string child, string father){
    Person *Pchild = getPerson(child, this->root);
    if (Pchild){
        if (Pchild->father){
            Pchild->father = new Person(father);
        }else{
            throw RuleException("Already has a father!");
        }
    }else{
        throw RuleException("Child wasn't found!");
    }
    return *this;
}



 Tree& Tree::addMother(string child, string mother){
     Person *Pchild = getPerson(child, this->root);
     if (Pchild){
        if (Pchild->mother){
            Pchild->mother = new Person(mother);
        }else{
            throw RuleException("Already has a mother!");
        }
     }else{
        throw RuleException("Child wasn't found!");
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

//Removes by string name
void Tree::remove(string toDelete){
    if (this->root->name == toDelete){
        throw RuleException("Cann't delete root of the tree!");
    }
    Person *startDelete = getPerson(toDelete, this->root);
    if (startDelete){
        remove(startDelete);
    }else{
        throw RuleException("The person to be deleted wasn't found!");
    }
}

//Removes by Person
void Tree::remove(Person* toDelete){
    if(!(toDelete->father) && !(toDelete->mother)){
        //It's an orphan
        delete (toDelete);
    }

    if(!(toDelete->father)){
        //if he has a father
        remove(toDelete->father);
    }

    if(!(toDelete->mother)){
        //if he has a mother
        remove(toDelete->mother);
    }

    delete (toDelete);
}