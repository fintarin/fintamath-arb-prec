#include "fintamath/expressions/unary/DerivativeExpression.hpp"

#include "fintamath/exceptions/InvalidInputUnaryOpearatorException.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/IUnaryExpression.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/calculus/Derivative.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

const Derivative DER;

DerivativeExpression::DerivativeExpression(const IMathObject &obj) : IUnaryExpression(obj) {
}

DerivativeExpression::DerivativeExpression(MathObjectPtr &&obj) : IUnaryExpression(std::move(obj)) {
}

const IFunction *DerivativeExpression::getFunction() const {
  return &DER;
}

MathObjectPtr DerivativeExpression::toMinimalObject() const {
  // TODO: remove this and use general toString() from UnaryExpression
  return simplify(true);
}

MathObjectPtr DerivativeExpression::simplify(bool isPrecise) const {
  MathObjectPtr value;

  if (const auto *expr = cast<IExpression>(info.get())) {
    value = expr->simplify(isPrecise);
  } else {
    value = info->toMinimalObject();
  }

  if (is<IExpression>(value)) {
    // TODO: implement derivative of expression
    return std::make_unique<DerivativeExpression>(std::move(value));
  }
  if (is<INumber>(value) || is<IConstant>(value)) {
    return ZERO.clone();
  }
  if (is<Variable>(value)) {
    return ONE.clone();
  }

  return clone();
}

// void DerivativeExpression::validate() const {
//   if (const auto *childExpr = cast<IExpression>(info.get())) {
//     childExpr->validate();
//   }

//   this->validateArgs(*getFunction(), {*info});
// }

void DerivativeExpression::compress() {
  if (auto *childExpr = cast<Expression>(info.get())) {
    info = std::move(childExpr->getInfo());
  }
}

}
