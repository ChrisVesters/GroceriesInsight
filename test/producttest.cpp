#include "product.h"
#include "gtest/gtest.h"

TEST(ProductTest, Constructor) {
	Product testProduct(123, "Test", "Case");
}

TEST(ProductTest, ConstructorNullBrand) {
	ASSERT_THROW(Product testProduct(123, NULL, "Case"), std::logic_error);
}

TEST(ProductTest, ConstructorEmptyBrand) {
	ASSERT_DEATH(Product testProduct(123, "", "Case"), "!brand.empty()");
}

TEST(ProductTest, ConstructorNullName) {
	ASSERT_THROW(Product testProduct(123, "Test", NULL), std::logic_error);
}

TEST(ProductTest, ConstructorEmptyName) {
	ASSERT_DEATH(Product testProduct(123, "Test", ""), "!name.empty()");
}

TEST(ProductTest, GetBarcode) {
	Product testProduct(123, "Test", "Case");
	ASSERT_EQ(123, testProduct.getBarcode());
}

TEST(ProductTest, GetBrand) {
	Product testProduct(123, "Test", "Case");
	ASSERT_EQ("Test", testProduct.getBrand());
}

TEST(ProductTest, GetName) {
	Product testProduct(123, "Test", "Case");
	ASSERT_EQ("Case", testProduct.getName());
}
