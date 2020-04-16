#include "doctest.h"
#include "FamilyTree.hpp"
#include <string>
using namespace std;
using namespace family;



Tree getTree(){
    Tree t("yosef");
    t.addFather("yosef", "avi");
    t.addMother("yosef", "rivka");
    t.addFather("avi", "moshe");
    t.addMother("avi", "mira");
    t.addFather("rivka", "israel");
    t.addMother("rivka", "rina");
    return t;
}

 

TEST_CASE("Test for find function"){
    Tree tree = getTree();

    CHECK_THROWS_AS(tree.find("great-grandfather") , RuleException);
    CHECK_THROWS_AS(tree.find("great-grandmother") , RuleException);
    CHECK_THROWS_AS(tree.find(" "), RuleException);
    CHECK_THROWS_AS(tree.find("Father"), RuleException);
    
}
TEST_CASE("Test for relation function"){
    Tree tree = getTree();
    CHECK(tree.relation("yoni") == string("unrelated"));
    CHECK(tree.relation("avI") == string("unrelated"));
}

TEST_CASE("Test for addFather function"){
    
}
TEST_CASE("Test for addMother function"){
    
}

