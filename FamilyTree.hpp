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
            int gender; // man =0; woman = 1;
            Person* father;
            Person* mother;

            Person(string _name){
                name = _name;
                father = nullptr;
                mother = nullptr;
            }
            ~Person(){
                delete father;
                delete mother;
            }

    };

    class Tree{
        public:
        Person* root;

        Tree(string child){
            root = new Person(child);
        }

        ~Tree(){
            delete root;
        }
        
        Tree& addFather(string child, string father);
        Tree& addMother(string child, string mother);

        Person *getPerson(string wanted, Person *start);

        string relation(string family_memeber_name);
        int relationDegree(Person *current, string relate, int t);

        string find(string family_relation );
        void display();
        void remove(string name);
        void remove(Person *toDelete);

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
