#include "espresso_based.h"
#include <iostream>
EspressoBased::~EspressoBased() {
  for (const auto &i : ingredients) {
    std::cout << "delete " << (*i).get_name() << " " << i->get_name() << std::endl;
    delete i;
  }
  ingredients.clear();
}
