/**
 * 
 *      class tree
 *          class Person
 *              type = {root, mother, father}
 * 
 */
#pragma once
#include <string>
using namespace std;

namespace family{
    
    class Person{
        private:
            string name;
            Person* father;
            Person* mother;
        public:
            Person(string _name, Person* pa, Person* ma){
                name = _name;
                father = pa;
                mother = ma;
            }

    };

    class Tree{
        Person* root;

        public:
            Tree(){
                root = nullptr;
            }
            Tree(string child){
                Person* p  = new Person(child, nullptr, nullptr);
                root = p;
            }
                    

            Tree& addFather(string child, string father);       // function return reference the new tree
            Tree& addMother(string child, string mother);       // function return reference the new tree
            string relation(string family_memeber_name);
            string find(string family_relation );
            void display();
            void remove(string name);

            
    };

}
