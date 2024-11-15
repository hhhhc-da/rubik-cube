#ifndef RUBIK_CUBE_NANOKA_BASE_H
#define RUBIK_CUBE_NANOKA_BASE_H

#include <iostream>
#include <vector>

#include <map>
#include <memory>
#include <set>

#include <cstdlib>

#include <fstream>
#include <sstream>

#include <algorithm>
#include <numeric>

#include <exception>

#include <cstddef>
#include <cstdint>

#include <unistd.h>
#include <random>

#define NANOKA_CASE_NUM 2

// 返回状态码重定义
typedef int nanoka_status;

#define NANOKA_SUCCESS 0
#define NANOKA_ERROR 1

// 操作方式重定义
typedef int nanoka_move_t;
// 水平偏转
#define NANOKA_MOVE_YAW     0 
// 前后翻滚
#define NANOKA_MOVE_ROLL    1
// 左右横滚
#define NANOKA_MOVE_PITCH   2
// 操作数枚举类型
typedef enum
{
    MOVE_POS_90 = 0,
    MOVE_POS_180,
    MOVE_NEG_180,
    MOVE_NEG_90
}
nanoka_move_enum_t;

#endif
