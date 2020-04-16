#include "doctest.h"
#include "FamilyTree.hpp"
#include <string>
using namespace std;
using namespace family;

/**
 *                                        yosef
 *                  avi                                            rivka
 *        mira             moshe                        israel              rina
 * 
 * 
 */

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
    CHECK(((tree.find("grandfather") == string("moshe")) || (tree.find("grandfather") == string("israel") )));
    CHECK(((tree.find("grandmother") == string("mira")) || (tree.find("grandmother") == string("rina"))));
    
    tree.addFather("israel","Elon");
    CHECK(tree.find("great-grandfather") == string("Elon"));
    
    tree.addFather("moshe","Sami");
    CHECK(tree.find("great-grandfather") == string("Sami"));
    
    tree.addFather("mira","dan");
    tree.addFather("rina","haim");
    
    string great_grandfather;
    CHECK_NOTHROW(great_grandfather = tree.find("great-great-grandfather")); 
    
    CHECK(( (great_grandfather == string("sami"))||(great_grandfather == string("dan"))||(great_grandfather == string("Elon"))
   ||(great_grandfather == string("haim"))));
    

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
    Tree tree = getTree();
    // Basics tests
    CHECK_NOTHROW(tree.addFather("moshe", "natan"));
    CHECK_NOTHROW(tree.addFather("natan", "natan"));

    //Trying to overwrite an existing father
    CHECK_THROWS_AS(tree.addFather("yosef", "bar"), RuleException);
    CHECK_THROWS_AS(tree.addFather("avi", "shlomi"), RuleException);

    //Trying non existing family members
    CHECK_THROWS_AS(tree.addFather("abcd", "yosef"), RuleException);
    CHECK_THROWS_AS(tree.addFather("1234", "elad"), RuleException);

    //Adding an empty name
    CHECK_NOTHROW(tree.addFather("mira", ""));
    CHECK(tree.relation("great-grandfather") == string(""));
    tree.remove("mira");
    tree.addMother("avi", "mira");

    //A space as a name for a person
    CHECK_NOTHROW(tree.addFather("mira", " "));
    CHECK(tree.relation("great-grandfather") == string(" "));
    tree.remove(" ");

    //Checking addFather worked, creating a new tree of only fathers
    Tree t("jack");
    t.addFather("jack", "shalom")
        .addFather("shalom", "tzadok")
        .addFather("tzadok", "moshe");
    CHECK(tree.relation("shalom") == string("father"));
    CHECK(tree.find("father") == string("shalom"));
    CHECK(tree.relation("tzadok") == string("grandfather"));
    CHECK(tree.find("grandfather") == string("tzadok"));
    //Removing tzadok and his father moshe from tree
    t.remove("tzadok");
    CHECK_NOTHROW(tree.addFather("shalom", "iftah"));

    //Adding persons wih indetical name, but with different  
    //position in the family tree
    /**               INIT              FIRST CHECK         SECOND CHECK
     *                jack                jack                  jack
     *          shalom          ->     shalom       ->       shalom
     *      iftah                   iftah                 iftah
     *                            iftah                 iftah
     *                                                iftah
     *                         
     */
    t.addFather("iftah", "iftah")
        .addFather("iftah", "iftah");
    CHECK(t.find("great-grandfather") == string("iftah"));
    CHECK(t.find("great-great-grandfather") == string("iftah"));

    delete &t;
    delete &tree;
}
TEST_CASE("Test for addMother function"){
    Tree t("yoni");
    CHECK_NOTHROW(t.addMother("yoni", "haya"));
    CHECK_NOTHROW(t.addMother("haya", "rahel"));
    CHECK_NOTHROW(t.addMother("rahel", "gila"));

    CHECK(t.find("mother") == string("haya"));
    CHECK(t.find("grandmother") == string("rahel"));
    CHECK(t.find("great-grandmother") == string("gila"));
    //Mother already exists
    CHECK_THROWS(t.addMother("yoni", "haya")); 
    CHECK_THROWS(t.addMother("haya", "rina")); 
    //Child doesn't exists
    CHECK_THROWS(t.addMother("daniel", "abcd"));

    //Adding an empty name
    CHECK_NOTHROW(t.addMother("gila", ""));
    CHECK(t.relation("great-great-grandmother") == string(""));

    //A space as a name for a person
    CHECK_NOTHROW(t.addMother("", " "));

    delete &t;
}
TEST_CASE("Test for remove function"){
    Tree t = getTree();
    //Removing root
    CHECK_THROWS(t.remove("yosef"));
    //Removing a person hat doesn't exists
    CHECK_THROWS(t.relation("aaaaa"));
    //Removing a sub-family
    CHECK_NOTHROW(t.remove("rivka"));
    CHECK_NOTHROW(t.addMother("yosef","rahel"));
    CHECK(t.relation("israel") == string("unrelated"));
    CHECK(t.relation("rina") == string("unrelated"));
    CHECK(t.relation("rivka") == string("unrelated"));

    //Removing already removed persons
    CHECK_THROWS(t.remove("israel"));
    CHECK_THROWS(t.remove("rina"));
    CHECK_THROWS(t.remove("rivka"));

    //Removing a different sub-family
    CHECK_NOTHROW(t.remove("avi"));
    CHECK(t.relation("avi") == string("unrelated"));
    CHECK(t.relation("mira") == string("unrelated"));
    CHECK(t.relation("moshe") == string("unrelated"));
    CHECK_NOTHROW(t.addFather("yosef", "eli"));

    //Another sub-family
    t.addFather("eli", "avraham")
     .addMother("eli", "sara")
     .addFather("avraham", "shulman")
     .addMother("avraham", "shula");
    CHECK_NOTHROW(t.remove("eli"));
    CHECK(t.relation("eli") == string("unrelated"));
    CHECK(t.relation("avraham") == string("unrelated"));
    CHECK(t.relation("sara") == string("unrelated"));
    CHECK(t.relation("shulman") == string("unrelated"));
    CHECK(t.relation("shula") == string("unrelated"));

    delete &t;
}

