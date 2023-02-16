#ifndef BOOK_H
#define BOOK_H
#include "product.h"

class Book : public Product {

public:
	Book(const std::string category, const std::string name, double price, int qty,const std::string isbn, const std::string author);
	
	virtual ~Book();

	virtual std::set<std::string> keywords() const;

//returns a string 
	virtual std::string display() const;

//output product
	virtual void dump(std::ostream& os) const;

	virtual bool isMatch(std::vector<std::string>& searchTerms) const;

  std::string getIsbn() const;

	std::string getAuthor() const;


private:

	std::string isbn_;
	std::string author_;

};
#endif