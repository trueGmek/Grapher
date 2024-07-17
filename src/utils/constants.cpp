#pragma once
#include <string>
namespace constants {

class shader {
public:
  //
  inline static const std::string MVP{"MVP"};
  //
  inline static const std::string time{"uTime"};
  inline static const std::string frequency{"uFrequency"};
  inline static const std::string speed{"uSpeed"};
  inline static const std::string amplitude{"uAmplitude"};
  inline static const std::string color{"uColor"};

  shader() = delete;
};

} // namespace constants
