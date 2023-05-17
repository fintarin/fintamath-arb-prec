#pragma once

#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"

namespace fintamath {

class NotExpression : public IUnaryExpressionCRTP<NotExpression> {
public:
  explicit NotExpression(const ArgumentPtr &inChild);

  static MathObjectType getTypeStatic() {
    return MathObjectType::NotExpression;
  }

protected:
  SimplifyFunctionsVector getFunctionsForSimplify() const override;

  SimplifyFunctionsVector getFunctionsForPreSimplify() const override;

  SimplifyFunctionsVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr callNotFunction(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr simplifyLogicNegatable(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr simplifyNestedNot(const IFunction &func, const ArgumentPtr &rhs);
};

}