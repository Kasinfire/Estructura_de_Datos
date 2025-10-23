#ifndef __EXCEPTION_HPP__
#define __EXCEPTION_HPP__

#include <string>

class Exception : public std::exception {
 private:
  std::string msg;

 public:
  Exception() noexcept : msg("Error indefinido") {}
  Exception(const Exception& e) noexcept : msg(e.msg) {}
  Exception(const std::string& ms) : msg(ms) {}

  Exception& operator=(const Exception& e) noexcept {
    msg = e.msg;
    return *this;
  }

  virtual ~Exception() {};
  virtual const char* what() const noexcept { return msg.c_str(); }
};

#endif  // __EXCEPTION_HPP__