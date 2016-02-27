#include <iostream>

#include <gli/gli.hpp>

int main() {
  std::cout << "Hello!" << std::endl;

  gli::texture texture;

  std::cout << "Empty? " << texture.empty() << std::endl;
}
