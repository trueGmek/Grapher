#include <string>
// TODO: TO ITS OWN PACKAGE IN CMAKE
namespace constants {

class shader {
public:
  inline static const std::string time{"uTime"};
  inline static const std::string color{"uColor"};
  inline static const std::string MVP{"MVP"};

  shader() = delete;
};

} // namespace constants
