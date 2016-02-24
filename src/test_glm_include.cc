#include <iostream>

#include <glm/glm.hpp>

int main() {
  std::cout << "Hello!" << std::endl;

  glm::vec3 position = glm::vec3(1.0, 2.0, 3.0);
  std::cout << position.x << " " << position.y << " " << position.z
            << std::endl;
}
