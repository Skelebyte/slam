#ifndef SLAM_COMMON_HPP
#define SLAM_COMMON_HPP

#include <iostream>
#include <string>
#include <vector>

namespace slam {
typedef unsigned int sUint;
typedef unsigned char sUchar;
typedef std::string sString;

struct Destroyable {
  virtual void Destroy() { destroyed = true; };
  bool IsDestroyed() const { return destroyed; }

private:
  bool destroyed = false;
};

template <typename T> struct Singleton {
  static T &Get() {
    static T instance;
    return instance;
  }
  bool IsInitialized() const { return initialized; }

protected:
  bool initialized = false;
};

struct ID {
  sUint GetID() { return id; }

protected:
  sUint *GetID_Ptr() { return &id; }
  void SetID(sUint newID) { id = newID; }

private:
  sUint id;
};

/**
 * @brief Checks if is destroyed, and returns a value.
 *
 */
#define IS_DESTROYED(retValue)                                                 \
  do {                                                                         \
    if (IsDestroyed())                                                         \
      return retValue;                                                         \
  } while (0)

#define DESTROY_BASE Destroyable::Destroy()

#define DESTROY()                                                              \
  do {                                                                         \
    IS_DESTROYED();                                                            \
    DESTROY_BASE;                                                              \
  } while (0)

#ifndef LOG_MACRO
#define LOG_MACRO
/**
 * @brief Wrapper for `std::cout`. Appends the file and function at the end.
 *
 * Example:
 * `LOG("My name is " << name << " and I am " << age <<".");`
 *
 * Output:
 * `[LOG] My name is John Doe and I am 26. (file: src/main.cpp, function:
 * main)`
 */
#define LOG(value)                                                             \
  std::cout << "[LOG] " << value << " (file: " << __FILE__                     \
            << ", function: " << __FUNCTION__ << ")\n"

#endif

/**
 * @brief Wrapper for `std::cout`. Prints value and appends `\n` at the end.
 *
 * Example:
 * `PRINT("My name is " << name << " and I am " << age <<".");`
 *
 * Output:
 * `My name is John Doe and I am 26.`
 */
#define PRINT(value) std::cout << value << "\n"

} // namespace slam

#endif