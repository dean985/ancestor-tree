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

    CHECK_NOTHROW(tree.find("me")); 
    CHECK(tree.find("me") == string("yosef"));
    CHECK(tree.find("father") == string("avi"));
    CHECK(tree.find("mother") == string("rivka"));
    CHECK(tree.find("grandfather") == string("moshe") || tree.find("grandfather") == string("israel") );
    CHECK(tree.find("grandmother") == string("mira") || tree.find("grandmother") == string("rina"));
    
    tree.addFather("israel","Elon");
    CHECK(tree.find("great-grandfather") == string("Elon"));
    
    tree.addFather("moshe","Sami");
    CHECK(tree.find("great-grandfather") == string("Sami"));
    
    tree.addFather("mira","dan");
    tree.addFather("rina","haim");
    
    string great_grandfather;
    CHECK_NOTHROW(great_grandfather = T.find("great-great-grandfather")); 
    
    CHECK( great_grandfather == string("sami")||great_grandfather == string("dan")||great_grandfather == string("Elon")
    ||great_grandfather == string("haim"));
    

    CHECK_THROWS_AS(tree.find("sister") , RuleException);
    CHECK_THROWS_AS(tree.find(""), RuleException);
    CHECK_THROWS_AS(tree.find("grandma") , RuleException);
    CHECK_THROWS_AS(tree.find("grandpa") , RuleException);
    CHECK_THROWS_AS(tree.find("cousin") , RuleException);
    CHECK_THROWS_AS(tree.find("aunt") , RuleException);
    CHECK_THROWS_AS(tree.find("uncle") , RuleException);
    CHECK_THROWS_AS(tree.find("grand-grandfather") , RuleException);
    CHECK_THROWS_AS(tree.find("grand-grandmother") , RuleException);
    CHECK_THROWS_AS(tree.find(" "), RuleException);
}

TEST_CASE("Test for relation function")
{
    Tree tree = getTree();
    CHECK(tree.relation("yoni") == string("unrelated"));
    CHECK(tree.relation("avI") == string("unrelated"));
    CHECK(tree.relation("yosef") == string("me"));
    CHECK(tree.relation("avi") == string("father"));
    CHECK(tree.relation("rivka") == string("mother"));
    
    CHECK(tree.relation("moshe") == string("grandfather"));
    CHECK(tree.relation("mira") == string("grandmother"));
    CHECK(tree.relation("israel") == string("grandfather"));
    CHECK(tree.relation("rina") == string("grandmother"));
    CHECK(tree.relation("rinah") == string("unrelated"));
    
    ////////////////////////////////////////////////
    
    tree.addFather("moshe","Elon");
    CHECK(tree.relation("Elon") == string("great-grandfather"));
    
    tree.addFather("israel","Elon");
    CHECK(tree.relation("Elon") == string("great-grandfather"));
    
    tree.addFather("mira","zack");
    tree.addFather("zack","Elon");
    CHECK(tree.relation("Elon") == string("great-grandfather"));
    
    tree.addMother("mira","zack");// PAY ATTANTION now we have mother "zack" and father "zack"
    CHECK(tree.relation("zack") == string("great-grandfather"));
    CHECK(tree.relation("Zack") == string("unrelated"));
    
    tree.addFather("moshe","Lital");
    CHECK(tree.relation("Lital") == string("great-grandmother"));
    
    CHECK(tree.relation(" ") == string("unrelated"));
    CHECK(tree.relation("") == string("unrelated"));
    
    Tree T ("Ronny");
    T.addFather("Ronny", "Dan").addMother("Ronny", "Rivka");

    CHECK(T.relation("Ronny") == string("me"));
    CHECK(T.relation("Dan") == string("father"));
    CHECK(T.relation("Rivka") == string("mother"));
    CHECK(T.relation("Rina") == string("unrelated"));
    CHECK(T.relation("Noa") == string("unrelated"));
    T.addMother("Rivka", "Arbel").addMother("Arbel", "Rita").addFather("Dan", "Ronen").addFather("Ronen", "Almog");
    CHECK(T.relation("Arbel") == string("grandmother"));
    CHECK(T.relation("Rita") == string("great-grandmother"));
    CHECK(T.relation("Ronen") == string("grandfather"));
    CHECK(T.relation("Almog") == string("great-grandfather"));


    

    
}


TEST_CASE("Test for addFather function"){
    
}
TEST_CASE("Test for addMother function"){
    
}

