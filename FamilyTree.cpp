#include "FamilyTree.hpp"
#include <iostream>
using namespace family;
using namespace std;
/**
 * This method receives two arguments - 
 *      name of the person wanted
 *      the person in the tree to start search from
 * It returns the node of that person, going by father-root-mother -> Left-Root-Right
 */
Person* Tree::getPerson(string wanted, Person* start){
   if ((start->name).compare(wanted) == 0){
       return start;
   }
    if (start->father != nullptr) {
        Person *ans = getPerson(wanted, start->father);
        if (ans != nullptr){
            return ans;
        }
    }
    if (start->mother != nullptr){
        Person *ans = getPerson(wanted, start->mother);
        if (ans != nullptr){
            return ans;
        }
    }
    return nullptr;
}



Tree& Tree::addFather(string child, string father){
    Person *Pchild = getPerson(child, this->root);
    if (Pchild != nullptr){
        if (Pchild->father == nullptr){
            Pchild->father = new Person(father);
            return *this;                              
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
     if (Pchild != nullptr){
        if (Pchild->mother == nullptr){
            Pchild->mother = new Person(mother);
            return *this;                               
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