﻿
#pragma once

//
// 基本的な定義
//


#if defined (_MSC_VER)

// TIPS:std::min std::maxを使うために定義しておく
#define NOMINMAX

// Eigenの16バイトアライメントは無効
#define EIGEN_DONT_ALIGN

// VS2012では可変引数テンプレートが使えない苦肉の策
#undef _VARIADIC_MAX
#define _VARIADIC_MAX (10)

// いくつかの余計な警告を表示しないようにする
#pragma warning (disable:4244)
#pragma warning (disable:4800)
#pragma warning (disable:4996)

#endif


// TIPS:std::cout をReleaseビルドで排除する
#ifdef DEBUG
#define DOUT std::cout
#else
#define DOUT 0 && std::cout
#endif

// TIPS:プリプロセッサを文字列として定義する
#define PREPRO_TO_STR(value) PREPRO_STR(value)
#define PREPRO_STR(value)    #value

typedef unsigned char  u_char;
typedef unsigned int   u_int;
typedef unsigned long  u_long;


#if (TARGET_OS_IPHONE)

// リリース時 NSLog 一網打尽マクロ
#ifdef DEBUG
#define NSLOG(...) NSLog(__VA_ARGS__)
#else
#define NSLOG(...) 
#endif

#endif
