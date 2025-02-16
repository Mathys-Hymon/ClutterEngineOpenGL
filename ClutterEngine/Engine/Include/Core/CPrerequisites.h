#pragma once
#include <Core/CLog/CLog.h>
#include <Core/Maths/Vectors/Vector2.h>
#include <filesystem>
#include <stdlib.h>
#include <stdexcept>
#include <map>
#include <memory>
#include <string>
#include <typeinfo>

inline const char* ContentPath(const wchar_t* path)
{
	thread_local static std::string strPath;
	strPath = (std::filesystem::path(L"Content/") / path).string();

	return strPath.c_str();
}

inline const char* ContentPath(const char* path)
{
	thread_local static std::string strPath;
	strPath = (std::filesystem::path(L"Content/") / path).string();

	return strPath.c_str();
}

inline const char* EnginePath(const char* path)
{
	thread_local static std::string strPath;
	strPath = (std::filesystem::path("Content/Engine/") / path).string();

	return strPath.c_str();
}

inline const char* EnginePath(const wchar_t* path)
{
	thread_local static std::string strPath;
	strPath = (std::filesystem::path(L"Content/Engine/") / path).string();

	return strPath.c_str();
}


// COMMON DATA TYPES

// float type
using f32 = float;          // 32-bit float
using f64 = double;         // 64-bit float

// int type
using i8 = std::int8_t;    // 8-bit signed integer
using i16 = std::int16_t;   // 16-bit signed integer
using i32 = std::int32_t;   // 32-bit signed integer
using i64 = std::int64_t;   // 64-bit signed integer

// Unsigned int type
using u8 = std::uint8_t;   // 8-bit unsigned integer
using u16 = std::uint16_t;  // 16-bit unsigned integer
using u32 = std::uint32_t;  // 32-bit unsigned integer
using u64 = std::uint64_t;  // 64-bit unsigned integer
