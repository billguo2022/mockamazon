#include "mydatastore.h"
#include "util.h"

MyDataStore::MyDataStore() {

}

MyDataStore::~MyDataStore() {
//deallocate keyword map, carts
	
    std::set<Product*>::iterator it1;
	
    for (it1 = products.begin(); it1 != products.end(); ++it1) {
			delete (*it1);
	}
	std::set<User*>::iterator it2;
	
    for (it2= users.begin(); it2 != users.end(); ++it2) {
			delete (*it2);
	}
}

void MyDataStore::addProduct(Product* p) {
	// insert a profuct
	products.insert(p);

	// add to the the keyword set
	std::set<std::string> keywords = p->keywords();

	for (std::set<std::string>::iterator it = keywords.begin(); it != keywords.end(); ++it) {
		
        std::map<std::string, std::set<Product*>>::iterator it2;
            
        std::string key = convToLower(*it);

            it2 = keywordmap.find(key);
            if (it2 != keywordmap.end()) {
			    it2->second.insert(p);
            }  
        	if (it2 == keywordmap.end()) {
            	std::set<Product*> nproduct;
			    
                nproduct.insert(p);
			    
                keywordmap[key] = nproduct;
        	}
        	
    	}
	}


void MyDataStore::addUser(User* t) {
    // adds user 
    if (userm.find(t->getName()) == userm.end()) {
				users.insert(t);
        userm[convToLower(t->getName())] = t;
	}
    
	else{
        return;
    }

}


//search for porduct that matches the keywords
//s represent and search or or search

std::vector<Product*> MyDataStore::search(std::vector<std::string>& word, int s) {
	
	std::vector<Product*> r;
	
    if (s != 0 && s != 1) {
		return r;
	}

	std::set<Product*> products;
	for (unsigned int i = 0; i < word.size(); i++) {
		//a set to store the matches
        std::set<Product*> m;
		// searches for the key keywordmap, and assigns the resulting iterator to it
		std::map<std::string, std::set<Product*>>::iterator it;

        it = keywordmap.find(word[i]);

		if (it != keywordmap.end()){
			m = (it->second);
		}
		// if and
		if (s == 0) { 
			if (i == 0) {
				products = m;
			} else {
                //if its and do the intersection
				products= setIntersection(products, m);
			}
		
        } 
        //if or
        if (s== 1){ 
            //if it's or do the union
			products= setUnion(products, m);
		}
	}


	for(std::set<Product*>::iterator it = products.begin(); it != products.end(); ++it) {
		
        r.push_back(*it);
	}
	return r;
}

void MyDataStore::dump(std::ostream& file) {
   
    file << "<products>\n";
    
	// dump all products
	std::set<Product*>::iterator it;

    for (it = products.begin(); it != products.end(); ++it) {
        
        (*it)->dump(file);
    }

   	file << "</products>\n";
	file << "<users>\n";

    //dump all users
	std::set<User*>::iterator  it1;
    for (it1 = users.begin(); it1 != users.end(); ++it1) {
        
		(*it1)->dump(file);
    }
    file << "</users>"<<std::endl;
          
}


bool MyDataStore::addcart(std::string user, Product* p)  {

	
	std::map<std::string, User*>::iterator it1 = userm.find(user);
	
    //std::set<Product*>::iterator it2 = products.find(p);
	
    //if the user and product are not found
    if (it1 == userm.end()) {
		return false;
	}
    // if (it2 == products.end()){

    //     return false;
    // }
    // //pointer point to user

	User* s = it1->second;

	std::map<User*, std::list<Product*>>::iterator it3 ;
  it3 = carts.find(s);

	if (it3!= carts.end()) {
		it3->second.push_back(p);
	} else{
		std::list<Product*> cart1;
		cart1.push_back(p);
		carts[s] = cart1;
	}
	return true;
}








void MyDataStore::viewCart(std::string user, bool& invalid) {
   
   std::list<Product*> c1;

	// find the user
	std::map<std::string, User*>::iterator it1;
  // for (it1=userm.begin(); it1!=userm.end();++it1){
	// 	std::cout<<it1->first<<std::endl;
	// }
  it1 = userm.find(user);
	
  if (it1 == userm.end()) {
			invalid = true;
			std::cout << "Invalid username" << std::endl;
			return;
		}
	User* s= it1->second;
	
	//std::cout<<"USer: " << s->getName()<<std::endl;
    //find the cart 

	std::map<User*, std::list<Product*>>::iterator it2 = carts.find(s);
    
    //if it's found
	if (it2 != carts.end()) {
		c1 = (it2->second);
		int counter=1;
		for(std::list<Product*>::iterator it3= c1.begin(); it3!=c1.end();++it3){
			std::cout<<"Item "<<counter<<std::endl;
			std::cout<<(*it3)->displayString()<<std::endl;
			std::cout<<std::endl;
			counter++;
			
		}
		
	} else {
		std::cout <<"NOT FOUND" << std::endl;
		return;
	}
	
}



bool MyDataStore::buy_c(std::string s) {
	
	std::map<std::string, User*>::iterator it1 = userm.find(s);
	
    //if the user doesn't exist
  if (it1 == userm.end()) {
		return false;
	}
    //if not have a pointer point to it
	User* t = it1->second;

	
	std::map<User*, std::list<Product*>>::iterator it2;

    it2 = carts.find(t);

    //if the cart is empty just return
	if (it2 == carts.end()) {
		return true;
	}
    //if the cart is not empty
  else{
      std::list<Product*> ucart = it2->second;
			std::cout<<"SIZE:"<<ucart.size()<<std::endl;
      std::list<Product*>::iterator it3;
      std::list<Product*> incart;

      for (it3 = ucart.begin(); it3 != ucart.end(); ++it3) {
          //std::cout << (*it3) << std::endl;
					int m= (*it3)->getQty();
					double k = t->getBalance();
					double z = (*it3)->getPrice();

          if(m>0 && (k> z)){
              (*it3)->subtractQty(1);
              t->deductAmount((*it3)->getPrice());
              //incart.push_back(*it3);


          } else {
						incart.push_back(*it3);
					
					}
            //remove things just bought
	     
      }
			if(incart.size()>0){
					carts[t]=incart;
			}else{
				carts.erase(t);
			}

			 return true;

    }
		
}
	
	
	