#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include "product.h"
#include "user.h"
#include <string>
#include <vector>
#include <map>
#include <set>


class MyDataStore : public DataStore {
public:
    MyDataStore();

    virtual ~MyDataStore();

    //add product
    void addProduct(Product* p);

    //add user
    void addUser(User* s);

    //search for the product that has the keyword
    //also apply add and or search
   
    std::vector<Product*> search(std::vector<std::string>& word, int s);

   
     //Remake the data file using current product and user
    
    void dump(std::ostream& file);

    void productTocart(std::string user, Product* product, std::string& s);

    void buy_cart(std::string user, std::string& s);

    std::vector<Product*> viewcart(std::string user, std::string& s);

private:
    std::map<std::string, std::vector<Product*>*>
            carts;  
    std::map<std::string, std::set<Product*>*>
            keywordmap;  
    std::map<std::string, User*> users;  

    std::vector<Product*>
            products;  
};

#endif