#ifndef RUBIK_CUBE_NANOKA_BASE_H
#define RUBIK_CUBE_NANOKA_BASE_H

#include <iostream>
#include <vector>

#include <map>
#include <memory>
#include <set>
#include <utility>

#include <cstdlib>

#include <fstream>
#include <sstream>

#include <algorithm>
#include <numeric>

#include <exception>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cmath>

#include <random>
#include <unistd.h>

/* 这里使用的是二阶魔方，首先魔方有每面四个格子
 * 同时，魔方是正规的正方体，所以我们默认使用六个面
 * 在表示数据的时候，我们的四个数据采用以下方式进行
 * | 1 2 | (顺时针描述我们的四个数据)
 * | 4 3 | (二阶魔方限定，三阶麻烦一点)
 * 这样表示数据时，我们可以轻松地实现魔方的旋转操作
 * 同时，我们使用一维数组进行存储，这样能有效减少误操作可能性
 * 我们使用动态定长的循环结构来表示数据
 */

//////////////////////////////////////////////////////////////////////
// 二阶魔方
#define NANOKA_CASE_NUM     2
// 普通的正方体魔方面数
#define NANOKA_LAYER_NUM    6
// 计数基准类型
typedef int nanoka_num_t;
// 存储基准类型
typedef uint8_t nanoka_storage_t;

//////////////////////////////////////////////////////////////////////
// 返回状态码重定义
typedef int nanoka_status_t;

#define NANOKA_SUCCESS      0
#define NANOKA_ERROR        1

//////////////////////////////////////////////////////////////////////
// 操作方式重定义
typedef int nanoka_move_t;
typedef int nanoka_move_enum_t;

// 水平偏转
#define NANOKA_MOVE_YAW     0
// 前后翻滚
#define NANOKA_MOVE_ROLL    1
// 左右横滚
#define NANOKA_MOVE_PITCH   2

// 操作数枚举类型
#define MOVE_POS_90         0
#define MOVE_POS_180        1
#define MOVE_NEG_180        1
#define MOVE_NEG_90         2

//////////////////////////////////////////////////////////////////////

#endif
