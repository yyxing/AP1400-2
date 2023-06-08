#ifndef ESPRESSO_BASED_H
#define ESPRESSO_BASED_H

#include <string>
#include <vector>
#include "ingredient.h"
class EspressoBased
{
 public:
  virtual std::string get_name() = 0;
  virtual double price() = 0;

  void brew();
  std::vector<Ingredient*>& get_ingredients() {return this->ingredients;}

  ~EspressoBased();

 protected:
  EspressoBased() = default;
  EspressoBased(const EspressoBased& esp);
  void operator=(const EspressoBased& esp);

  // 基础配料
  std::vector<Ingredient*> ingredients;
  std::string name;

};

#endif // ESPRESSO_BASED_H