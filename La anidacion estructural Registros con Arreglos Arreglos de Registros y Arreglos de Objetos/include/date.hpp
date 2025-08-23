#ifndef DATE_HPP__
#define DATE_HPP__

#include <stdexcept>
#include <string>

class Date {
 private:
  int year;
  int month;  // aquí estan los tres atributos
  int day;

  bool itIsAValidDate(int y, int m, int d);

 public:
  Date();
  Date(int y, int m, int d);
  Date(const Date&);

  int getYear() const;
  int getMonth() const;
  int getDay() const;

  std::string toString() const;

  void setYear(const int&);
  void setMonth(const int&);
  void setDay(const int&);

  Date& operator=(const Date&);
};

#endif  // DATE_HPP__