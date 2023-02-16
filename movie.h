#ifndef MOVIE_H
#define MOVIE_H
#include "product.h"

class Movie : 

public Product {

public:
//constructor
	Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating);
	//destructor
	virtual ~Movie();
  //dump function
	virtual void dump(std::ostream& os) const;
 //keyword function
	virtual std::set<std::string> keywords() const;
//display words function
	virtual std::string display() const;

//return rating
	std::string getRating() const;
	//return genre
	std::string getGenre() const;
	
	virtual bool isMatch(std::vector<std::string>& searchTerms) const;
	
private:

	std::string genre_;
	std::string rating_;
};

#endif