#pragma once

#include <memory>
#include <vector>

#include "fintamath/MathObject.hpp"

namespace fintamath {
  class Expression : public MathObject {
  public:
    struct Elem {
      std::shared_ptr<MathObject> info;
      std::shared_ptr<Elem> left;
      std::shared_ptr<Elem> right;

      std::shared_ptr<Elem> clone();
      bool equals(const std::shared_ptr<Elem> &rhs) const;
      std::string toString() const;
    };

    Expression() = default;
    explicit Expression(const std::string &strExpr);

    std::string toString() const override;

    std::string solve();

    std::unique_ptr<MathObject> clone() const override;

    bool equals(const MathObject &rhs) const override;

  private:
    std::shared_ptr<Elem> root;

    void makeExpression(const std::vector<std::string> &tokensVect);
  };
}