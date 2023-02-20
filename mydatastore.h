#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include "product.h"
#include "user.h"
#include <string>
#include <vector>
#include <map>
#include <set>

#include <list>


class MyDataStore : public DataStore {
public:
    MyDataStore();

    virtual ~MyDataStore();

    //add product
    virtual void addProduct(Product* p);

    //add user
    virtual void addUser(User* s);

    //search for the product that has the keyword
    //also apply add and or search
   
    virtual std::vector<Product*> search(std::vector<std::string>& words, int type);
   
     //Remake the data file using current product and user
    
    virtual void dump(std::ostream& file);

    bool addcart(std::string users, Product*);


    void productTocart(std::string user, Product* product, std::string& s);


    bool buy_c(std::string users);

    void viewCart(std::string users, bool& invalid);

   
private:
        //set for products
   std::set<Product*> 
        products;
    //map to pair up the products with keywords      
    std::map<std::string, std::set<Product*>>
            keywordmap;  
        //username and user map
    std::map<std::string, User*> 
        userm;
    //set for users
    std::set<User*> 
        users;

    //user and carts
   
    std::map<User*, std::list<Product*>> 
        carts;

    
};

#endif