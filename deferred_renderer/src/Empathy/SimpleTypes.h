#pragma once
#include <stdint.h>
#include <string>

#include <glm/glm.hpp>

// Signed
typedef signed __int8 i8;
typedef signed __int16 i16;
typedef signed __int32 i32;
typedef signed __int64 i64;

constexpr i8    i8_MAX =  INT8_MAX;
constexpr i16   i16_MAX = INT16_MAX;
constexpr i32   i32_MAX = INT32_MAX;
constexpr i64   i64_MAX = INT64_MAX;

typedef float	f32;
typedef double	f64;

// Unsigned
typedef unsigned __int8     u8;
typedef unsigned __int16    u16;
typedef unsigned __int32    u32;
typedef unsigned __int64    u64;

constexpr u8    U8_MAX = UINT8_MAX;
constexpr u16   U16_MAX = UINT16_MAX;
constexpr u32   U32_MAX = UINT32_MAX;
constexpr u64   U64_MAX = UINT64_MAX;

// GLM Math
typedef glm::vec2  vec2;
typedef glm::vec3  vec3;
typedef glm::vec4  vec4;
typedef glm::ivec2 ivec2;
typedef glm::ivec3 ivec3;
typedef glm::ivec4 ivec4;

#ifndef NULL
#define NULL 0
#endif

#define ARRAY_COUNT(x) (sizeof(x) / sizeof(x[0]))