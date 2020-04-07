#include "FamilyTree.hpp"
using namespace family;

Tree& Tree::addFather(string child, string father){
    return *this;
} 
 Tree& Tree::addMother(string child, string mother){
     return *this;
 }
string Tree::relation(string family_memeber_name){
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