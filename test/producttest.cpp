#include "product.h"
#include "gtest/gtest.h"

TEST(ProductTest, Constructor) {
	UnitSize unit(100, "g");
	Product testProduct(123, "Test", "Case", unit);
}

TEST(ProductTest, ConstructorNullBrand) {
	UnitSize unit(100, "g");
	ASSERT_THROW(Product testProduct(123, nullptr, "Case", unit), std::logic_error);
}

TEST(ProductTest, ConstructorEmptyBrand) {
	UnitSize unit(100, "g");
	ASSERT_DEATH(Product testProduct(123, "", "Case", unit), "!brand.empty()");
}

TEST(ProductTest, ConstructorNullName) {
	UnitSize unit(100, "g");
	ASSERT_THROW(Product testProduct(123, "Test", nullptr, unit), std::logic_error);
}

TEST(ProductTest, ConstructorEmptyName) {
	UnitSize unit(100, "g");
	ASSERT_DEATH(Product testProduct(123, "Test", "", unit), "!name.empty()");
}

TEST(ProductTest, GetBarcode) {
	UnitSize unit(100, "g");
	Product testProduct(123, "Test", "Case", unit);
	ASSERT_EQ(123, testProduct.getBarcode());
}

TEST(ProductTest, GetBrand) {
	UnitSize unit(100, "g");
	Product testProduct(123, "Test", "Case", unit);
	ASSERT_EQ("Test", testProduct.getBrand());
}

TEST(ProductTest, GetName) {
	UnitSize unit(100, "g");
	Product testProduct(123, "Test", "Case", unit);
	ASSERT_EQ("Case", testProduct.getName());
}

TEST(ProductTest, getUnitSize) {
	UnitSize unit(100, "g");
	Product testProduct(123, "Test", "Case", unit);
	ASSERT_EQ(100, testProduct.getUnitSize().getQuantity());
	ASSERT_EQ("g", testProduct.getUnitSize().getUnit());
}
