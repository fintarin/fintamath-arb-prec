#include "fintamath/expressions/DerivativeExpression.hpp"

#include "fintamath/exceptions/InvalidInputUnaryOpearatorException.hpp"
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

DerivativeExpression::DerivativeExpression(const DerivativeExpression &rhs) : info(rhs.info->clone()) {
}

DerivativeExpression &DerivativeExpression::operator=(const DerivativeExpression &rhs) {
  if (this != &rhs) {
    info = rhs.info->clone();
  }

  return *this;
}

DerivativeExpression::DerivativeExpression(const IMathObject &obj) {
  info = obj.simplify();
}

DerivativeExpression::DerivativeExpression(MathObjectPtr &&obj) : info(std::move(obj)) {
}

std::string DerivativeExpression::toString() const {
  return "(" + info->toString() + ")'";
}

const IFunction *DerivativeExpression::getFunction() const {
  return &DER;
}

void DerivativeExpression::setPrecision(uint8_t precision) {
  if (auto *expr = cast<IExpression>(info.get())) {
    expr->setPrecision(precision);
  }
}

MathObjectPtr DerivativeExpression::simplify() const {
  return simplify(true);
}

MathObjectPtr DerivativeExpression::simplify(bool isPrecise) const {
  MathObjectPtr value;

  if (const auto *expr = cast<IExpression>(info.get())) {
    value = expr->simplify(isPrecise);
  } else {
    value = info->simplify();
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

}
