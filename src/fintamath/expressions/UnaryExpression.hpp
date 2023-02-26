#pragma once

#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

template <typename Derived>
class UnaryExpressionCRTP : public IExpressionCRTP<Derived> {
public:
  UnaryExpressionCRTP() = default;

  UnaryExpressionCRTP(const UnaryExpressionCRTP &rhs) : info(rhs.info->clone()) {
  }

  UnaryExpressionCRTP(UnaryExpressionCRTP &&rhs) noexcept = default;

  UnaryExpressionCRTP &operator=(const UnaryExpressionCRTP &rhs) {
    if (&rhs != this) {
      if (rhs.info) {
        info = rhs.info;
      } else {
        info = nullptr;
      }
    }
    return *this;
  }

  UnaryExpressionCRTP &operator=(UnaryExpressionCRTP &&rhs) noexcept = default;

  void setPrecision(uint8_t precision) final {
    if (is<IExpression>(info)) {
      auto expr = cast<IExpression>(std::move(info));
      expr->setPrecision(precision);
      info = std::move(expr);
      return;
    }

    if (const auto *constant = cast<IConstant>(info.get())) {
      info = (*constant)();
    }

    if (is<INumber>(info)) {
      info = convert<Real>(*info).precise(precision).clone();
    }
  }

protected:
  MathObjectPtr info;
};

}