#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"

using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);


int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;



    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
	    /* Add support for other commands here */
			
            else if (cmd == "ADD") {
                
                string user;
                int r;
                
                bool notvalid = false;
                
                //if input username and r 
                if (ss >> user)  {
                    if(ss>>r){

                        
                        if(r>=1 && r<=(int)hits.size()){
                            user = convToLower(user);
                        //call the add cart function to add
                            notvalid = !ds.addcart(user,hits[r-1]);
                         }
                        else{
                             notvalid = true;

                        }

                    }
                }
                else{
                    //if not the command then not valid
                    notvalid = true;
                }
                if(notvalid==true){

                    cout<<"invalid request"<<endl;
                }
            }  
              //to see someone's cart  
            else if (cmd == "VIEWCART") {
                //std::cout <<"HERE"<<std::endl;
								string user;
                //only see it if the user's valid
                user = convToLower(user);
                bool notvalid = false;
                if (ss >> user) { 
                    user = convToLower(user);
										//std::cout<<user<<std::endl;
                    //make a new product pointer
                    //std::list<Product*> p;

                    //call the viewcart function
                   	ds.viewCart(user, notvalid);
                // if the user's not valid, return false
                } else {
                    notvalid = true;
                    cout << "Invalid username" << endl;
                }

           } 
					 else if ( cmd == "BUYCART") { 
            //let a user checkout
                string user;
                bool notvalid = false;
                if (ss >> user) {

                    user= convToLower(user);
                    //call the buy funciton to buy cart or checkout
                    notvalid= !ds.buy_c(user);
                } else {
                    notvalid = true;
                }
                if (notvalid == true) {
                    cout << "Invalid username" << endl;
                }
            }
            
            
            else {
                cout << "Unknown command" << endl;
            }



            
        }

    
		}
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
