#include "productservice.h"
#include "gtest/gtest.h"

TEST(ProductServiceTest, AddProduct) {
	UnitSize unit(100, "g");
	Product product(1, "Test", "Case", unit);
	// TODO: we should mock product!!!
	ProductService::addProduct(product);
}

TEST(ProductServiceTest, AddProductDuplicated) {
	UnitSize unit(100, "g");
	Product product(2, "Test", "Case", unit);
	ProductService::addProduct(product);
	
	ASSERT_THROW(ProductService::addProduct(product), int);
}
			
TEST(ProductServiceTest, ExistsProductNonExisting) {
	ASSERT_FALSE(ProductService::existsProduct(0));
}

TEST(ProductServiceTest, ExistsProductExisting) {
	UnitSize unit(100, "g");
	Product product(4, "Test", "Case", unit);
	ProductService::addProduct(product);
	
	ASSERT_TRUE(ProductService::existsProduct(4));
}

TEST(ProductServiceTest, GetProductNonExisting) {
	ASSERT_THROW(ProductService::getProduct(0), int);
}

TEST(ProductServiceTest, GetProductExisting) {
	UnitSize unit(100, "g");
	Product product(5, "Test", "Case", unit);
	ProductService::addProduct(product);
	
	const Product foundProduct = ProductService::getProduct(5);
	ASSERT_EQ(product.getBarcode(), foundProduct.getBarcode());
	ASSERT_EQ(product.getBrand(), foundProduct.getBrand());
	ASSERT_EQ(product.getName(), foundProduct.getName());
}
