#include <gtest/gtest.h>

#include "fintamath/core/IArithmetic.hpp"

#include "fintamath/exceptions/InvalidInputBinaryOpearatorException.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

namespace {

class TestArithmetic : public IArithmeticCRTP<TestArithmetic> {
protected:
  TestArithmetic &add(const TestArithmetic & /* rhs */) override {
    return *this;
  }

  TestArithmetic &substract(const TestArithmetic & /* rhs */) override {
    return *this;
  }

  TestArithmetic &multiply(const TestArithmetic & /* rhs */) override {
    return *this;
  }

  TestArithmetic &divide(const TestArithmetic & /* rhs */) override {
    return *this;
  }

  TestArithmetic &negate() override {
    return *this;
  }
};

}

TEST(ArithmeticTests, addTest) {
  ArithmeticPtr m1 = std::make_unique<Integer>(1);
  ArithmeticPtr m2 = std::make_unique<Rational>(2);
  ArithmeticPtr m3 = std::make_unique<Rational>(1, 2);

  EXPECT_EQ((*m1 + *m1)->toString(), "2");
  EXPECT_EQ((*m2 + *m2)->toString(), "4");
  EXPECT_EQ((*m1 + *m2)->toString(), "3");
  EXPECT_EQ((*m2 + *m1)->toString(), "3");

  EXPECT_EQ((*m1 + *m3)->toString(), "3/2");
  EXPECT_EQ((*m2 + *m3)->toString(), "5/2");
  EXPECT_EQ((*m3 + *m1)->toString(), "3/2");
  EXPECT_EQ((*m3 + *m2)->toString(), "5/2");
  EXPECT_EQ((*m3 + *m3)->toString(), "1");

  EXPECT_TRUE((*m1 + *m1)->instanceof<Integer>());
  EXPECT_TRUE((*m2 + *m2)->instanceof<Integer>());
  EXPECT_TRUE((*m1 + *m2)->instanceof<Integer>());
  EXPECT_TRUE((*m2 + *m1)->instanceof<Integer>());

  EXPECT_TRUE((*m1 + *m3)->instanceof<Rational>());
  EXPECT_TRUE((*m2 + *m3)->instanceof<Rational>());
  EXPECT_TRUE((*m3 + *m1)->instanceof<Rational>());
  EXPECT_TRUE((*m3 + *m2)->instanceof<Rational>());
  EXPECT_TRUE((*m3 + *m3)->instanceof<Integer>());

  EXPECT_THROW(*m1 + TestArithmetic(), InvalidInputBinaryOpearatorException);
  EXPECT_THROW(TestArithmetic() + *m1, InvalidInputBinaryOpearatorException);

  Integer a;
  EXPECT_EQ((a += 3).toString(), "3");
  EXPECT_EQ((Rational() + 1).toString(), "1");
  EXPECT_EQ((-1 + Rational()).toString(), "-1");
}

TEST(ArithmeticTests, subTest) {
  ArithmeticPtr m1 = std::make_unique<Integer>(1);
  ArithmeticPtr m2 = std::make_unique<Rational>(2);
  ArithmeticPtr m3 = std::make_unique<Rational>(1, 2);

  EXPECT_EQ((*m1 - *m1)->toString(), "0");
  EXPECT_EQ((*m2 - *m2)->toString(), "0");
  EXPECT_EQ((*m1 - *m2)->toString(), "-1");
  EXPECT_EQ((*m2 - *m1)->toString(), "1");

  EXPECT_EQ((*m1 - *m3)->toString(), "1/2");
  EXPECT_EQ((*m2 - *m3)->toString(), "3/2");
  EXPECT_EQ((*m3 - *m1)->toString(), "-1/2");
  EXPECT_EQ((*m3 - *m2)->toString(), "-3/2");
  EXPECT_EQ((*m3 - *m3)->toString(), "0");

  EXPECT_TRUE((*m1 - *m1)->instanceof<Integer>());
  EXPECT_TRUE((*m2 - *m2)->instanceof<Integer>());
  EXPECT_TRUE((*m1 - *m2)->instanceof<Integer>());
  EXPECT_TRUE((*m2 - *m1)->instanceof<Integer>());

  EXPECT_TRUE((*m1 - *m3)->instanceof<Rational>());
  EXPECT_TRUE((*m2 - *m3)->instanceof<Rational>());
  EXPECT_TRUE((*m3 - *m1)->instanceof<Rational>());
  EXPECT_TRUE((*m3 - *m2)->instanceof<Rational>());
  EXPECT_TRUE((*m3 - *m3)->instanceof<Integer>());

  EXPECT_THROW(*m1 - TestArithmetic(), InvalidInputBinaryOpearatorException);
  EXPECT_THROW(TestArithmetic() - *m1, InvalidInputBinaryOpearatorException);

  Integer a;
  EXPECT_EQ((a -= 3).toString(), "-3");
  EXPECT_EQ((Integer() - 1).toString(), "-1");
  EXPECT_EQ((-1 - Integer()).toString(), "-1");
}

TEST(ArithmeticTests, mulTest) {
  ArithmeticPtr m1 = std::make_unique<Integer>(1);
  ArithmeticPtr m2 = std::make_unique<Rational>(2);
  ArithmeticPtr m3 = std::make_unique<Rational>(1, 2);

  EXPECT_EQ((*m1 * *m1)->toString(), "1");
  EXPECT_EQ((*m2 * *m2)->toString(), "4");
  EXPECT_EQ((*m1 * *m2)->toString(), "2");
  EXPECT_EQ((*m2 * *m1)->toString(), "2");

  EXPECT_EQ((*m1 * *m3)->toString(), "1/2");
  EXPECT_EQ((*m2 * *m3)->toString(), "1");
  EXPECT_EQ((*m3 * *m1)->toString(), "1/2");
  EXPECT_EQ((*m3 * *m2)->toString(), "1");
  EXPECT_EQ((*m3 * *m3)->toString(), "1/4");

  EXPECT_TRUE((*m1 * *m1)->instanceof<Integer>());
  EXPECT_TRUE((*m2 * *m2)->instanceof<Integer>());
  EXPECT_TRUE((*m1 * *m2)->instanceof<Integer>());
  EXPECT_TRUE((*m2 * *m1)->instanceof<Integer>());

  EXPECT_TRUE((*m1 * *m3)->instanceof<Rational>());
  EXPECT_TRUE((*m2 * *m3)->instanceof<Integer>());
  EXPECT_TRUE((*m3 * *m1)->instanceof<Rational>());
  EXPECT_TRUE((*m3 * *m2)->instanceof<Integer>());
  EXPECT_TRUE((*m3 * *m3)->instanceof<Rational>());

  EXPECT_THROW(*m1 * TestArithmetic(), InvalidInputBinaryOpearatorException);
  EXPECT_THROW(TestArithmetic() * *m1, InvalidInputBinaryOpearatorException);

  Integer a = 2;
  EXPECT_EQ((a *= 3).toString(), "6");
  EXPECT_EQ((Integer(2) * 2).toString(), "4");
  EXPECT_EQ((-2 * Integer(2)).toString(), "-4");
}

TEST(ArithmeticTests, divTest) {
  ArithmeticPtr m1 = std::make_unique<Integer>(1);
  ArithmeticPtr m2 = std::make_unique<Rational>(2);
  ArithmeticPtr m3 = std::make_unique<Rational>(1, 2);

  EXPECT_EQ((*m1 / *m1)->toString(), "1");
  EXPECT_EQ((*m2 / *m2)->toString(), "1");
  EXPECT_EQ((*m1 / *m2)->toString(), "1/2");
  EXPECT_EQ((*m2 / *m1)->toString(), "2");

  EXPECT_EQ((*m1 / *m3)->toString(), "2");
  EXPECT_EQ((*m2 / *m3)->toString(), "4");
  EXPECT_EQ((*m3 / *m1)->toString(), "1/2");
  EXPECT_EQ((*m3 / *m2)->toString(), "1/4");
  EXPECT_EQ((*m3 / *m3)->toString(), "1");

  EXPECT_TRUE((*m1 / *m1)->instanceof<Integer>());
  EXPECT_TRUE((*m2 / *m2)->instanceof<Integer>());
  EXPECT_TRUE((*m1 / *m2)->instanceof<Rational>());
  EXPECT_TRUE((*m2 / *m1)->instanceof<Integer>());

  EXPECT_TRUE((*m1 / *m3)->instanceof<Integer>());
  EXPECT_TRUE((*m2 / *m3)->instanceof<Integer>());
  EXPECT_TRUE((*m3 / *m1)->instanceof<Rational>());
  EXPECT_TRUE((*m3 / *m2)->instanceof<Rational>());
  EXPECT_TRUE((*m3 / *m3)->instanceof<Integer>());

  EXPECT_THROW(*m1 / TestArithmetic(), InvalidInputBinaryOpearatorException);
  EXPECT_THROW(TestArithmetic() / *m1, InvalidInputBinaryOpearatorException);

  Integer a = 4;
  EXPECT_EQ((a /= 2).toString(), "2");
  EXPECT_EQ((Integer(4) / 2).toString(), "2");
  EXPECT_EQ((-2 / Integer(2)).toString(), "-1");
}

TEST(ArithmeticTests, convertTest) {
  ArithmeticPtr m1 = std::make_unique<Integer>(1);
  EXPECT_EQ((+*m1)->toString(), "1");

  EXPECT_EQ((+Integer(1)).toString(), "1");
}

TEST(ArithmeticTests, negateTest) {
  ArithmeticPtr m1 = std::make_unique<Integer>(1);
  EXPECT_EQ((-*m1)->toString(), "-1");

  EXPECT_EQ((-Integer(1)).toString(), "-1");
}
