#pragma once

#define WINDOWS
#ifdef WINDOWS
#define __import __declspec(dllimport)
#define __export __declspec(dllexport)

#ifdef ENGINE_IMPORT
#define API __declspec(dllimport)
#else
#define API __declspec(dllexport)
#endif
#else
#define __import extern "C"
#define __export __attribute__((visibility("default")))
#define API __attribute__((visibility("default")))
#endif

