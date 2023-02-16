#ifndef CLOTHING_H
#define CLOTHING_H
#include "product.h"

class Clothing : public Product {

public:
	Clothing(const std::string category, const std::string name, double price, int qty, 
		const std::string size, const std::string brand);
	
	virtual ~Clothing();

	//keyword function
	virtual std::set<std::string> keywords() const;
	
	//display string function
	virtual std::string displayString() const;
	
	//dump output function
	virtual void dump(std::ostream& os) const;

//return size
	std::string getSize() const;
	
	//return brand
	std::string getBrand() const;

private:

	std::string size_;
	std::string brand_;
};
#endif