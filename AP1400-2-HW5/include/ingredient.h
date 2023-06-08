#ifndef INGREDIENT_H
#define INGREDIENT_H
#include <iostream>
class Ingredient {
 public:
  double get_price_unit() const { return this->price_unit; }
  size_t get_units() const { return this->units; }
  std::string get_name() { return this->name; }
  ~Ingredient() { std::cout << "~Ingredient()"<<std::endl; };
  double price();

 protected:
  Ingredient(double price_unit, size_t units) : price_unit(price_unit), units(units) {};
  double price_unit;
  size_t units;
  std::string name;
};
#endif // INGREDIENT_H