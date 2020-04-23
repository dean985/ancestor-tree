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



Person* printInorder( Person* node, string key) 
{ 
            return nullptr; 

  if (node == nullptr) 
        return nullptr; 
  
    /* first recur on left child */
    if(node->father != nullptr)
        printInorder(node->father,key); 
  
    /* then print the data of node */
    if(node->name == string(key))
        return node;
  
    /* now recur on right child */
    if(node->mother != nullptr)
        return printInorder(node->mother,key); 
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
  cout<<printInorder(this->root, relate)->name<<endl;
    return "";
    //return search(this->root, relate)->name;
}

string Tree::find(string family_relation )
{
    int height = 0;// the height of the realation acording to the root
    char gender = 'n';// n = nun, m = male, f = fmale
    
    if(family_relation == string("me"))
    {
        return this->root->name;

    }
    else if(family_relation == string("father"))
    {
        height = 1;
        gender = 'm';
    }
   else if(family_relation == string("mother"))
    {
        height = 1;
        gender = 'f';
    }
  else  if(family_relation == string("grandfather"))
    {
        height = 2;
        gender = 'm';
    }
    else  if(family_relation == string("grandmother"))
    {
        height = 2;
        gender = 'f';
    }
    else
    {
        int m = 0;
        string* t = parsing(family_relation, &m);
        if(t[0] != "great")
        {
             throw RuleException("not correct syntex");

        }
            
        for(int i = 0; i < m; i++)
        {
            if(t[i] != "grandmother" && t[i] != "grandfather")
            {
                if(t[i] != "great")
                {
                    throw RuleException("not correct syntex");
                }
            }
            
        }
        
        height = m;
        if(t[m-1] == "grandmother")
            gender='f';
        if(t[m-1] == "grandfather")
            gender='m';
      
    }
    
    return search(height, gender,this->root)->name;
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
