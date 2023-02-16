#include <sstream>
#include "clothing.h"
#include "util.h"

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand) :
	Product(category, name, price, qty)
{
	size_ = size;
	brand_ = brand;
}

Clothing::~Clothing() {}

//brand and name keywords
std::set<std::string> Clothing::keywords() const {

	std::set<std::string> keybrand = parseStringToWords(brand_);
	std::set<std::string> keyname = parseStringToWords(name_);
	return setUnion(keybrand, keyname);

}


std::string Clothing::getSize() const {return size_;}

std::string Clothing::getBrand() const {return brand_;}

//display the string
std::string Clothing::displayString() const {
    
    return (name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" +std::to_string(price_)+ " "+ std::to_string(qty_) + " left.");
}

//dump output
void Clothing::dump(std::ostream& os) const {
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n"<<size_ << "\n" << brand_ << std::endl;
}