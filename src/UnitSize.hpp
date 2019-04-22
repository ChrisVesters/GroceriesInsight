#ifndef UNITSIZE_HPP
#define UNITSIZE_HPP

#include <string>

class UnitSize {
public:
	UnitSize(long quantity, std::string unit);

	long getQuantity() const;
	std::string getUnit() const;
	
	friend std::string to_string(const UnitSize& self);
private:
	long quantity;
	std::string unit;
};

#endif // UNITSIZE_HPP
