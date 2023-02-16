#include "mydatastore.h"
#include "util.h"

MyDataStore::MyDataStore() {

}

MyDataStore::~MyDataStore() {

	std::map<std::string, std::set<Product*> *>::iterator it1;
	std::map<User*, std::list<Product*>*>::it2;
	std::vector<Product*>::iterator it3;
	std::map<std::string, std::set<Product*>*>::iterator it4;

	for (it1 = search_.begin(); it1 != search_.end(); ++it1) {
		delete it1->second;
	}
	for (it2 = cart_.begin(); itCart != cart_.end(); ++it2) {
		delete it2->second;
	}
	 for (it3 = products_.begin(); it != products_.end(); ++it) {
        delete *it;
    }
		for (it4 = keywordMappings_.begin();
         it != keywordMappings_.end();
         ++it) {
        delete it->second;
    }