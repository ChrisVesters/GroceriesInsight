#include "productservice.h"
#include "gtest/gtest.h"

class ProductServiceTest : public ::testing::Test {
	
};

TEST(ProductServiceTest, AddProduct) {
	Product product(1, "Test", "Case");
	// TODO: we should mock product!!!
	ProductService::addProduct(product);
}

TEST(ProductServiceTest, AddProductDuplicated) {
	Product product(2, "Test", "Case");
	ProductService::addProduct(product);
	
	ASSERT_THROW(ProductService::addProduct(product), int);
}
			
TEST(ProductServiceTest, ExistsProductNonExisting) {
	ASSERT_FALSE(ProductService::existsProduct(0));
}

TEST(ProductServiceTest, ExistsProductExisting) {
	Product product(4, "Test", "Case");
	ProductService::addProduct(product);
	
	ASSERT_TRUE(ProductService::existsProduct(4));
}

TEST(ProductServiceTest, GetProductNonExisting) {
	ASSERT_THROW(ProductService::getProduct(0), int);
}

TEST(ProductServiceTest, GetProductExisting) {
	Product product(5, "Test", "Case");
	ProductService::addProduct(product);
	
	const Product foundProduct = ProductService::getProduct(5);
	ASSERT_EQ(product.getBarcode(), foundProduct.getBarcode());
	ASSERT_EQ(product.getBrand(), foundProduct.getBrand());
	ASSERT_EQ(product.getName(), foundProduct.getName());
}