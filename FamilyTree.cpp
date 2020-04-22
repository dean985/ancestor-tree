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
            Pchild->father->gender = 0;
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
            Pchild->gender = 1;
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
    Person *currentP = getPerson(relate, root);
    if (!currentP)
        return "unrelated";
    int degree = relationDegree(root, relate, 0);
    if (degree == 1)
        return "me";
    else if (degree == 2){
        if (currentP->gender == 0){
            return "father";
        }
        else{
            return "mother";
        }
    }
    else if (degree == 3){
        if (currentP->gender == 0){
            return "grandfather";
        }else{
            return "grandmother";
        }
    }
    else {
        string ans = "";
        for (int i = 3; i < degree; i++)
            ans = "great-" + ans;         
        if (currentP->gender == 0)
            ans += "grandfather";
        else
            ans += "grandmother";

        return ans + "  " + relate;
    }

    return "PROBLEM ";
}
int Tree::relationDegree(Person* current, string relate, int t){
    if (current == nullptr)
        return (-1) * t;
    if(current->name == relate)
        return 1;
    else{
        int fathers = 1 + relationDegree(current->father, relate, t + 1);
        int mothers = 1 + relationDegree(current->mother, relate, t + 1);
        if (fathers > 0)
            return fathers;
        else
            return mothers;
    }
}
string Tree::find(string family_relation ){
    return " ";
}

void printTree(int s, Person* root){
    if(root){
        s += 6;
        printTree(s, root->father);
        std::cout << endl;
        for (int i = 6; i < s; i++){
            std::cout << " ";
        }
        std::cout << root->name << std::endl;
        printTree(s, root->mother);
    }
}
void Tree::display(){
    printTree(0, root);
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