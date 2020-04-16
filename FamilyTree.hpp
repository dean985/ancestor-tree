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
        public:
            string name;
            Person* father;
            Person* mother;

            Person(string _name, Person* pa, Person* ma){
                name = _name;
                father = pa;
                mother = ma;
            }
            Person(string _name){
                name = _name;
                father = nullptr;
                mother = nullptr;
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
                    

            Tree& addFather(string child, string father);
            Tree& addFather(string child, string father, Person* start);

            Tree& addMother(string child, string mother);
            Tree& addMother(string child, string mother, Person* start);
       
            
            string relation(string family_memeber_name);
            string find(string family_relation );
            void display();
            void remove(string name);

    };


    struct RuleException : public exception 
    {
       string err;
       RuleException(string e) : err(e) {}
       ~RuleException() throw () {}
       const char * what () const throw () 
       {
          return err.c_str();
       }
    };

}
