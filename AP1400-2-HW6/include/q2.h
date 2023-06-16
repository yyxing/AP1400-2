#ifndef Q2_H
#define Q2_H
#include <string>
#include <iostream>
#include <istream>
#include <fstream>

using std::ios;
namespace q2 {
  struct Patient {
    std::string name;
    size_t age;
    size_t smokes;
    size_t area_q;
    size_t alkhol;
    size_t score;
  };
void trim(std::string &s)
{
  int index = 0;
  if(!s.empty())
  {
    while( (index = s.find(' ',index)) != std::string::npos)
    {
      s.erase(index,1);
    }
  }
}
std::vector<q2::Patient> read_file(std::string filename) {
  filename = "../resources/" + filename;
  std::ifstream ifstream(filename, ios::in);
  std::vector<Patient> patients;
  if (ifstream) {
    Patient patient;
    std::string line;
    std::getline(ifstream, line);
    std::getline(ifstream, line);
    while (std::getline(ifstream, line)) {
      std::vector<std::string> words;
      std::istringstream sin(line);
      std::string field;
      while (std::getline(sin, field,',')) {
        trim(field);
        words.push_back(field);
      }
      patient.name = words[0] + " " + words[1];
      patient.age = std::stoi(words[2]);
      patient.smokes = std::stoi(words[3]);
      patient.area_q = std::stoi(words[4]);
      patient.alkhol = std::stoi(words[5]);
      patient.score = 3*patient.age + 5*patient.smokes + 2*patient.area_q + 4*patient.alkhol;
      patients.push_back(patient);
      words.clear();
    }
  }
  ifstream.close();
  return patients;
}

void sort(std::vector<q2::Patient>& patients) {
  std::sort(patients.begin(), patients.end(), [](Patient p1, Patient p2) {
    return p1.score >= p2.score;
  });
}
}

#endif //Q2_H