#pragma once

#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"

namespace fintamath {

class LogExpression : public IBinaryExpressionCRTP<LogExpression> {
public:
  explicit LogExpression(ArgumentPtr inLhsChild, ArgumentPtr inRhsChild);

  std::string toString() const override;

  std::shared_ptr<IFunction> getOutputFunction() const override;

  static MathObjectType getTypeStatic() {
    return MathObjectType::LogExpression;
  }

protected:
  ArgumentPtr preciseSimplify() const override;

  SimplifyFunctionVector getFunctionsForPreSimplify() const override;

  SimplifyFunctionVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr callFunctionSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr constSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr equalSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr powSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);
};

}