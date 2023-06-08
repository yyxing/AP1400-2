#include <string>
#include <vector>
#include <iostream>
#include "cappuccino.h"
#include "sub_ingredients.h"

Cappuccino::~Cappuccino() {
  for (const auto &i : side_items) {
    std::cout << "delete " << i->get_name() << std::endl;
    delete i;
  }
  side_items.clear();
}
Cappuccino::Cappuccino() {
  this->ingredients.push_back(new Espresso(2));
  this->ingredients.push_back(new Milk(2));
  this->ingredients.push_back(new MilkFoam(1));
  this->name = "Cappuccino";
}
Cappuccino::Cappuccino(const Cappuccino &cap) {

}
void Cappuccino::operator=(const Cappuccino &cap) {

}
std::string Cappuccino::get_name() {
  return this->name;
}
double Cappuccino::price() {
  return 0;
}
void Cappuccino::add_side_item(Ingredient *side) {
  this->side_items.push_back(side);
}
std::vector<Ingredient *> &Cappuccino::get_side_items() {
  return this->side_items;
}
