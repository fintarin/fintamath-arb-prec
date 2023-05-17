#pragma once

#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"

namespace fintamath {

class OrExpression : public IPolynomExpressionCRTP<OrExpression> {
public:
  explicit OrExpression(const ArgumentsPtrVector &inChildren);

  // TODO!!! reimplement
  // ArgumentPtr logicNegate() const override;

  static MathObjectType getTypeStatic() {
    return MathObjectType::OrExpression;
  }

protected:
  std::string operatorChildToString(const ArgumentPtr &inChild, const ArgumentPtr &prevChild) const override;

  ArgumentPtr postSimplify() const override;

  SimplifyFunctionsVector getFunctionsForSimplify() const override;

  SimplifyFunctionsVector getFunctionsForPostSimplify() const override;

  bool isComparableOrderInversed() const override;

private:
  static ArgumentPtr simplifyBooleans(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr simplifyEqual(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr simplifyNot(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr simplifyAnd(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr simplifyAbsorption(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);
};

}