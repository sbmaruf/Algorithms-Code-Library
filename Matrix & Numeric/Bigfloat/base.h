#pragma once

#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include <vector>
#include <map>
#include <stdexcept>
#include <string>
#include <sstream>

#ifdef _MSC_VER
# define INLINE __forceinline
  typedef  unsigned __int64 u8;
  typedef  unsigned __int32 u4;
  typedef  unsigned __int16 u2;
  typedef  unsigned __int8  u1;
  typedef  __int64 s8;
  typedef  __int32 s4;
  typedef  __int16 s2;
  typedef  __int8  s1;
#else
# include <stdint.h>
# define INLINE inline
  typedef  uint64_t  u8;
  typedef  uint32_t  u4;
  typedef  uint16_t  u2;
  typedef  uint8_t   u1;
  typedef  int64_t  s8;
  typedef  int32_t  s4;
  typedef  int16_t  s2;
  typedef  int8_t   s1;
#endif

class CosmosException : public std::exception
{
public:
    CosmosException(const char* m) : _msg(m) {}
    CosmosException(const std::string& m) : _msg(m) {}
    virtual ~CosmosException() throw() {}
    virtual const char* what() const throw()
    {
        return _msg.c_str();
    }
protected:
    std::string _msg;
};

#define ASSERT(condition, ...) do { \
  if (!(condition)) Assert(__LINE__, __FILE__, #condition, ##__VA_ARGS__); \
 } while(0)

#define ASSERTFG(f,g) do { \
  double fr = (f); double gr = (g); double diff = (fr-gr); \
  if (diff > 1.0e-10 || diff < -1.0e-10) \
  Assert(__LINE__, __FILE__, #f "," #g, "%f, %f, %f", fr, gr, diff); \
 } while(0)

static void Assert(
    int line,
    const char* filename,
    const char* condition)
{
	static const int bufSize = 4000;
    char y[bufSize];
    sprintf(y, "line=[%d], file=[%s], condition=[%s]",
            line, filename, condition);
    throw CosmosException(y);
}

static void Assert(
    int line,
    const char* filename,
    const char* condition,
    const char* fmt,
    ...)
{
	static const int bufSize = 4000;
    char x[bufSize];
    char y[bufSize];
    va_list args;
    va_start(args, fmt);
    vsprintf(x, fmt, args);
    va_end(args);
    sprintf(y, "line=[%d], file=[%s], condition=[%s], %s",
            line, filename, condition, x);
    throw CosmosException(y);
}

