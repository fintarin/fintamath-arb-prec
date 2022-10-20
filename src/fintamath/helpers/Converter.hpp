#pragma once

#include <memory>

namespace fintamath {
  class IMathObject;
  using MathObjectPtr = std::unique_ptr<IMathObject>;
}

namespace fintamath::help {
  MathObjectPtr convertMathObject(const IMathObject &value, const IMathObject &type);
}