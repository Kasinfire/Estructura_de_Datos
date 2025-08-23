#include "date.hpp"

using namespace std;

bool Date::itIsAValidDate(int y, int m, int d) {
  if (y < 1 || m < 1 || m > 12 || d < 1)
    return false;

  int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  if (m == 2 && ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))) {
    return d <= 29;
  }
  return d <= daysInMonth[m - 1];
}

Date::Date() : year(2025), month(8), day(20) {}

Date::Date(int y, int m, int d) : year(y), month(m), day(d) {
  if (!itIsAValidDate(y, m, d))
    throw invalid_argument("Fecha invalida");
}

Date::Date(const Date& d) : year(d.year), month(d.month), day(d.day) {}

int Date::getYear() const {
  return year;
}
int Date::getMonth() const {
  return month;
}
int Date::getDay() const {
  return day;
}

std::string Date::toString() const {
  string sDay = (day < 10 ? "0" : "") + to_string(day);
  string sMonth = (month < 10 ? "0" : "") + to_string(month);
  return sDay + "/" + sMonth + "/" + to_string(year);
}

void Date::setYear(const int& y) {
  if (!itIsAValidDate(y, month, day)) {
    throw invalid_argument("Anio invalido");
  }
  year = y;
}

void Date::setMonth(const int& m) {
  if (!itIsAValidDate(year, m, day)) {
    throw invalid_argument("Mes invalido");
  }
  month = m;
}

void Date::setDay(const int& d) {
  if (!itIsAValidDate(year, month, d)) {
    throw invalid_argument("Dia invalido");
  }
  day = d;
}

Date& Date::operator=(const Date& d) {
  if (this != &d) {
    year = d.year;
    month = d.month;
    day = d.day;
  }
  return *this;
}
