#ifndef Q3_H
#define Q3_H
#include <iostream>
#include <regex>
#include <queue>
#include <fstream>
#include <istream>
using std::string;
namespace q3 {
static size_t time_conversion(const std::string &duration) {
  std::string pattern = "(\\d+)h(\\d*)m*";
  std::regex reg(pattern);
  std::smatch result;
  size_t cost = 0;
  if (std::regex_match(duration, result, reg)) {
    cost = std::stoi(result[1]) * 60;
    if (result[2] != "") {
      cost += std::stoi(result[2]);
    }
  }
  return cost;
}
std::vector<std::string> split(const std::string &connection_times) {
  std::vector<std::string> res;
  std::string s = "";
  for (char ch : connection_times) {
    if (ch != ',') {
      s.push_back(ch);
    } else {
      res.push_back(s);
      s = "";
    }
  }
  res.push_back(s);
  return res;
}
struct Flight {
  std::string flight_number;
  size_t duration;
  size_t connections;
  size_t connection_times = 0;
  size_t price;
  size_t score;
  Flight(std::string &item) {
    std::string
        pattern = R"(\d- flight_number:(.+) - duration:(.+) - connections:(\d+) - connection_times:(.+) - price:(\d+))";
    std::regex reg(pattern);
    std::smatch result;
    if (std::regex_search(item, result, reg)) {
      flight_number = result[1];
      duration = time_conversion(result[2]);
      connections = std::stoi(result[3]);
      std::vector<string> vecs = split(result[4]);
      for (auto &v : vecs) {
        connection_times += time_conversion(v);
      }
      price = std::stoi(result[5]);
    }
    score = duration + connection_times + 3 * price;
  }
  bool operator<(const Flight &other) const {
    return this->score >= other.score;
  }
};
std::priority_queue<Flight> gather_flights(std::string filename) {
  std::priority_queue<Flight> pq{};
  filename = "../resources/" + filename;
  std::ifstream fs(filename, ios::in);
  if (fs) {
    string line;
    while (getline(fs, line)) {
      pq.emplace(line);
    }
  }
  return pq;
}
}
#endif //Q3_H