#include "FamilyTree.hpp"
#include <iostream>
using namespace family;





////////////////////////////////////////////////////////////
/////////////// assistent functions ///////////////////////
//////////////////////////////////////////////////////////

Person* search(int height,char gender,Person* root)
{
    if(height == 0)
        return root;
    if(gender == 'm')
        {
            return search(height - 1, gender,root->father);
        }
    if(gender == 'f')
        {
            return search(height - 1, gender,root->mother);
        }
        return NULL;
}

Person* search(Person* root, string key) 
{ 
    if (root == nullptr || root->name == key) 
       return root; 
     
    // Key is greater than root's key 
        return search(root->father, key); 
  
    // Key is smaller than root's key 
        return search(root->mother, key); 
} 


Person* Tree::getPerson(string wanted, Person* start){
   
   if(start->name == wanted || (start->father == nullptr && start->mother== nullptr))
        return start;
        
    Person* ans = nullptr;
    
    if(start->father != nullptr)
        ans = getPerson(wanted,start->father);
        
    if(ans == nullptr && start->mother != nullptr)
        ans = getPerson(wanted, start->mother);
        
    return ans;
   
}



/////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////



Tree& Tree::addFather(string child, string father){
    
    Person *Pchild = getPerson(father, this->root);


    if (Pchild){
        if (Pchild->father == nullptr){
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
        if (Pchild->mother == nullptr){
            Pchild->mother = new Person(mother);
        }else{
            throw RuleException("Already has a mother!");
        }
     }else{
        throw RuleException("Child wasn't found!");
    }
     return *this;
 }

string Tree::relation(string relate)
{
    return "";
    //return search(this->root, relate)->name;
}

string Tree::find(string family_relation )
{
    return " ";
    
    
    // int height = 0;// the height of the realation acording to the root
    // char gender = 'n';// n = nun, m = male, f = fmale
    
    // if(family_relation == string("me"))
    // {
    //     return this->root->name;

    // }
    // if(family_relation == string("father"))
    // {
    //     height = 1;
    //     gender = 'm';
    // }
    // if(family_relation == string("mother"))
    // {
    //     height = 1;
    //     gender = 'f';
    // }
    //     if(family_relation == string("grandfather"))
    // {
    //     height = 2;
    //     gender = 'm';
    // }
    //     if(family_relation == string("grandmother"))
    // {
    //     height = 2;
    //     gender = 'f';
    // }
    // else
    // {
    //     //////////// enter the abillity to breake the great-grandfather
    // }
    
    // return search(height, gender,this->root)->name;
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
