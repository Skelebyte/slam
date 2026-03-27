#ifndef SLAM_COMMON_HPP
#define SLAM_COMMON_HPP

// #include "../../third_party/HandmadeMath.h"
#include "../third_party/glad/gl.h"
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace slam {
typedef int32_t i32;
typedef uint32_t u32;
typedef int64_t i64;
typedef uint64_t u64;
typedef int8_t i8;
typedef uint8_t u8;
typedef int16_t i16;
typedef uint16_t u16;
typedef float f32;
typedef double f64;
typedef unsigned char uchar;
typedef std::string str;

// T &
template <typename T> using Ref = T &;
// const T &
template <typename T> using CRef = const T &;
// T *
template <typename T> using Ptr = T *;
template <typename T> using UPtr = std::unique_ptr<T>;
template <typename T> using SPtr = std::shared_ptr<T>;

str ToStr(int value);
str ToStr(double value);
str ToStr(float value);
str ToStr(char value);
str ToStr(char *value);

struct Destroyable {
  virtual void Destroy() { destroyed = true; };
  bool IsDestroyed() const { return destroyed; }

private:
  bool destroyed = false;
};

template <typename T> struct Singleton {
  // Singleton(const Singleton &) = delete;

  static T &Get() {
    static T instance;
    return instance;
  }
  bool IsInitialized() const { return initialized; }

protected:
  bool initialized = false;
};

struct ID {
  u32 GetID() { return id; }

protected:
  u32 *GetID_Ptr() { return &id; }
  void SetID(u32 newID) { id = newID; }

private:
  u32 id;
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