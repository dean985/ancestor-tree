#include "FamilyTree.hpp"
#include <iostream>
using namespace family;

using namespace std;



////////////////////////////////////////////////////////////
/////////////// assistent functions ///////////////////////
//////////////////////////////////////////////////////////

/**
 * This method receives two arguments - 
 *      name of the person wanted
 *      the person in the tree to start search from
 * It returns the node of that person, going by father-root-mother -> Left-Root-Right
 */
Person* Tree::getPerson(string wanted, Person* start){
   if ((start->name) == wanted){
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

//Removes by Person
void Tree::remove(Person* toDelete){
    if (toDelete != nullptr){
        delete (toDelete->father);
        toDelete->father = nullptr;
        delete (toDelete->mother);
        toDelete->mother = nullptr;
        delete (toDelete);
    }
}

string* parsing(string text, int* spaces){
        int t = 0;
        // Searching for spaces - in order to understand
        // how many words are there
        for(int i =0 ; i<text.length(); i++){
            if (text[i] == '-') t++;
        }
        *spaces = t+1;
        //Array of words
        string* str = new string[*spaces];
        int letters = 0;
        int wordlength = 0;

        for (int i = 0; i <text.length(); i++){
            //if it is a space
            if (text[i] != '-') letters++;
            // else , it is a letter.
            else {
                str[wordlength] = text.substr(i-letters, letters);
                letters = 0;
                wordlength++;
            }
            //If reached to the end of the string
            if (i == text.length()-1){
                str[wordlength] = text.substr(i+1-letters, letters+1);
                wordlength++;
            }
        }
        return str;
    }


/////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////



Tree& Tree::addFather(string child, string father){

    Person *Pchild = getPerson(child, this->root);
    if (Pchild){

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
     if (Pchild){
        if (Pchild->mother == nullptr){
            Pchild->mother = new Person(mother);
            Pchild->mother->gender = 1;
            return *this;                               
        }else{
            throw RuleException("Already has a mother!");
        }
     }else{
        throw RuleException("Child wasn't found!");
    }
     return *this;
 }

string Find(Person* root,string name) {

    if(root == NULL){
        return "x";
    }

    if((int)name.find('-') == -1){

        if((int)name.find("father") != -1 && root->father){
            return root->father->name;
        }
        if((int)name.find("mother") != -1 && root->mother){
            return root->mother->name;
        }
        else
            return "nullll";
    }

    int index = name.find('-');
    index++;
    int len = name.length();

    if(Find(root->father,name.substr(index,len)) != "nullll"){
        return Find(root->father,name.substr(index,len));
    } else if(Find(root->mother,name.substr(index,len)) != "nullll" ){
        return Find(root->mother,name.substr(index,len));
    }

    return "nullll";
}

string Tree::find(string family_relation )
{

      if (family_relation == "me")
          return this->root->name;
      else if (this->root->father && family_relation == "father"){
          return this->root->father->name;
      }
      else if(this->root->mother && family_relation == "mother"){
          return this->root->mother->name;
      }
      else if (!this->root->father && family_relation == "father"){
          throw RuleException(family_relation + " isn't there");
      }
      else if (!this->root->mother && family_relation =="mother"){          
          throw RuleException(family_relation + " isn't there");
      }

      string f_side, m_side;
      if (this->root->father){
          f_side = Find(this->root->father, family_relation);
          if (f_side != "nullll")
              return f_side;
      }
      if (this->root->mother){
          m_side = Find(this->root->mother, family_relation);
        if (m_side != "nullll"){
            return m_side;
        }
      }
      throw RuleException("Couldn't find it in the tree");
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

        return ans;
    }

    return "PROBLEM ";
}


void Tree::display(){
    printTree(0, root);
    return;
}

Person* getChild(Person* root, Person* parent){
    if (root->father && root->father->name == parent->name){
        return root;
    }
    else if (root->mother && root->mother->name == parent->name ){
        return root;
    }

    try{
        Person* f_side = getChild(root->father, parent);
        if (f_side)
            return f_side;
    }catch(...){

    }
    try{
        Person* m_side = getChild(root->mother, parent);
        if (m_side)
            return m_side;
    }catch(...){

    }
    return nullptr;
}

//Removes by string nameq
void Tree::remove(string toDelete){
    if (this->root->name == toDelete){
        throw RuleException("Can't delete root of the tree!");
    }
    Person *startDelete = getPerson(toDelete, this->root);
    Person *current = this->root;
    Person *child = getChild(current, startDelete);
    int gender = startDelete->gender;
    if (startDelete){
        remove(startDelete);
        switch (gender){
            case 0:
                child->father = nullptr;
                break;
            case 1:
                child->mother = nullptr;
                break;
        }
    }else{
        throw RuleException("The person to be deleted wasn't found!");
    }
}


