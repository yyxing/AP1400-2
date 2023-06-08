#ifndef CAPPUCCINO
#define CAPPUCCINO
#include <string>
#include <vector>
#include "ingredient.h"
#include "espresso_based.h"
class Cappuccino : public EspressoBased
{
 public:
  Cappuccino();
  Cappuccino(const Cappuccino& cap);
  ~Cappuccino();
  void operator=(const Cappuccino& cap);

  virtual std::string get_name();
  virtual double price();

  void add_side_item(Ingredient* side);
  std::vector<Ingredient*>& get_side_items();

 private:
  // 用户新加
  std::vector<Ingredient*> side_items;

};

#endif // CAPPUCCINO