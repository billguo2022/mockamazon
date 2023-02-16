#include "mydatastore.h"
#include "util.h"

MyDataStore::MyDataStore() {

}

MyDataStore::~MyDataStore() {
//deallocate keyword map, users, products,carts
	std::map<std::string, std::vector<Product*>*>::iterator it1;
	std::map<std::string, User*>::iterator it2;
	std::vector<Product*>::iterator it3;
	std::map<std::string, std::set<Product*>*>::iterator it4;

	for (it1 = carts.begin(); it1 != carts.end(); ++it1) {
		delete it1->second;
	}
	for (it2 = users.begin(); it2 != users.end(); ++it2) {
		delete it2->second;
	}
	 for (it3 = products.begin(); it3 != products.end(); ++it3) {
        delete *it3;
    }
		for (it4 = keywordmap.begin();it4 != keywordmap.end(); ++it4) {
       
	    delete it4->second;
    }
}

void MyDataStore::addProduct(Product* p) {
	// insert a profuct
	products.push_back(p);

	// add to the the keyword set
	std::set<std::string> keywords = p->keywords();
	std::set<std::string>::iterator it;


		
		std::string key = convToLower(*it);
		
		for (std::set<std::string>::iterator it = keywords.begin(); it != keywords.end(); ++it) {
			std::string key = convToLower(*it);
        	if (keywordmap.find(key) == keywordmap.end()) {
            	keywordmap[key] = new std::set<Product*>;
        	}
        	keywordmap[key]->insert(p);
    	}
	}


void MyDataStore::addUser(User* t) {
    // adds user to the map


    users[t->getName()] = t;
    // create a crat for the user
    carts[t->getName()] = new std::vector<Product*>;
}


//search for porduct that matches the keywords
//s represent and search or or search

std::vector<Product*> MyDataStore::search(std::vector<std::string>& word, int s) {
    std::set<Product*> set;
  
	if (s == 1) {
		//union all the related products 
      std::vector<std::string>::iterator it ;
        for (it = word.begin(); it != word.end(); ++it) {
           
		    if (keywordmap.find(*it) != keywordmap.end()) {  // if keyword can be found
                
				set = setUnion(set, *keywordmap[*it]);
            }
        }
	}
   if(s==0){
        // set set equal to the first term
        std::vector<std::string>::iterator it ;
		for (it = word.begin(); it != word.end(); ++it) {
       		
			 if (keywordmap.find(*it) != keywordmap.end()) {
            	set = *keywordmap[*it];
       		 }
        // iterates through keyword adn keeping the current products
		std::vector<std::string>::iterator it1;
        for ( it1= word.begin(); it1 != word.end(); ++it1) {
           
		    if (keywordmap.find(*it1) != keywordmap.end()) {  //if keyword can be found
                set = setIntersection(set, *keywordmap[*it1]);
            } else {
                set.clear();  
            }
        }
    }
   }
    // now that we have the set, turn it into a vector
    std::vector<Product*> hit;
	
	std::set<Product*>::iterator it2;
    
	for (it2 = set.begin(); it2 != set.end(); ++it2) {
        hit.push_back(*it2);
    }
    return hit;
}

void MyDataStore::dump(std::ostream& file) {
   
    file << "<products>\n";
    
	// dump all products
	std::vector<Product*>::iterator it;

    for (it = products.begin(); it != products.end(); ++it) {
        (*it)->dump(file);
    }

   	file << "</products>\n";
	file << "<users>\n";

    //dump all users
	std::map<std::string, User*>::iterator it1;
    for (it1 = users.begin(); it1 != users.end(); ++it1) {
        
		(it1->second)->dump(file);
    }
    file << "</users>"<<std::endl;
          
}


void MyDataStore::productTocart(std::string user, Product* product, std::string& s) {
//check if there is a cart
    if (carts.find(user) != carts.end()) {
        
		//put the product into cart

        // add the product to the bvack
        carts[user]->push_back(product);
	}
     if (carts.find(user) == carts.end()) {
        // if the user is not valid
        s = "Invalid";
    }
}

std::vector<Product*> MyDataStore::viewcart(std::string user, std::string& s) {
    std::vector<Product*> cart;

    if (carts.find(user) != carts.end()) {
        cart = *carts[user];
    } 
	if (carts.find(user) == carts.end()) {
        s = "Invalid";
    }

    return cart;
}


void MyDataStore::buy_cart(std::string user, std::string& s) {
    
    if (carts.find(user) != carts.end()) {
		std::vector<Product*>::iterator it;
	   
		 for (it = carts[user]->begin(); it != carts[user]->end(); ++it) {
           
		    if (users[user]->getBalance() >= (*it)->getPrice() && (*it)->getQty() > 0) {
				//if the user has enough money, subtract the money from user's current total, adn subtract the qty of product
                
                users[user]->deductAmount((*it)->getPrice());
                
				(*it)->subtractQty(1);
				//since erase will make it euqal to the next item, we don't want to skip, so minus it by 1
                
                carts[user]->erase(it);
                --it;
            }
        }
    } 
	if (carts.find(user) == carts.end()) {
        
        s = "Invalid ";
    }
}