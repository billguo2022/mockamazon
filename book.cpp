#include <sstream>
#include "book.h"
#include "util.h"

//constructor implementation
Book::Book(const std::string category,const std::string name, double price, int qty, const std::string isbn, const std::string author) : 

	Product(category, name, price, qty) {
		isbn_ = isbn;
		author_ = author;		
}

//destructor implementation
Book::~Book() {
}

//return isbn
std::string Book::getIsbn() const {
	return isbn_;
}

//return author
std::string Book::getAuthor() const {
	return author_;
}

//get keywords of author, name of the book and isbn
std::set<std::string> Book::keywords() const {
	
	std::set<std::string> authorKeywords = parseStringToWords(author_);
	
	std::set<std::string> nameKeywords = parseStringToWords(name_);
	
	std::set<std::string> keywords = setUnion(authorKeywords, nameKeywords);
	
	keywords.insert(isbn_);
	return keywords;
}

//display the book as a string
std::string Book::display() const {
	 return (name_ + "\n" + "author: " + author_ + " isbn: " + isbn_ + "\n" + price_ + " "+ qty_ + " left.");
}

//dump output stream from requirements
void Book::dump(std::ostream& os) const {
   
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n"<< isbn_ << "\n" << author_ << std::endl;

}

//similar to the one in product.cpp
bool Book::isMatch(std::vector<std::string>& searchTerms) const { 
	
	return false; 
	
}