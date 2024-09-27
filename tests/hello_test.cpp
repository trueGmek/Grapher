#include <gtest/gtest.h>
#include "parser.h"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Arrange
  // Act
  // Assert
  EXPECT_TRUE(true);
}
TEST(Parser, TestMethodWorks) {
  // Arrange
  const Parser parser{};
  const int arg = 2;

  // Act
  int result = parser.TestMethod(arg);

  // Assert
  EXPECT_EQ(result, arg);
}

TEST(Parser, TestMethod_2_NE_3) {
  // Arrange
  const Parser parser{};
  const int arg = 2;

  // Act
  int result = parser.TestMethod(arg);

  // Assert
  EXPECT_NE(result, 3);
}
