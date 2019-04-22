#include "UnitSize.hpp"

UnitSize::UnitSize(long quantity, std::string unit) : quantity{quantity}, unit{unit} {
}

long UnitSize::getQuantity() const {
	return quantity;
}

std::string UnitSize::getUnit() const {
	return unit;
}
	
std::string to_string(const UnitSize& self) {
    return std::to_string(self.quantity) + self.unit;
 }
