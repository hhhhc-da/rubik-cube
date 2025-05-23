#ifndef RUBIK_CUBE_NANOKA_BASE_H
#define RUBIK_CUBE_NANOKA_BASE_H

#include <iostream>
#include <vector>

#include <iterator>
#include <map>
#include <memory>
#include <set>
#include <utility>
#include <tuple>

#include <cstdlib>

#include <fstream>
#include <sstream>

#include <algorithm>
#include <numeric>

#include <exception>

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>

#include <random>
#include <unistd.h>

#include <chrono>
#include <iomanip>

/* 这里使用的是二阶魔方，首先魔方有每面四个格子
 * 同时，魔方是正规的正方体，所以我们默认使用六个面
 * 在表示数据的时候，我们的四个数据采用以下方式进行
 * | 1 2 | (顺时针描述我们的四个数据)
 * | 4 3 | (二阶魔方限定，三阶麻烦一点)
 * 这样表示数据时，我们可以轻松地实现魔方的旋转操作
 * 同时，我们使用一维数组进行存储，这样能有效减少误操作可能性
 * 我们使用动态定长的循环结构来表示数据
 * 三阶魔方采用以下的存储方式 (9 号元素放在其他 vector 内)
 * | 1 2 3 |
 * | 8 9 4 |
 * | 7 6 5 |
 * 这样可以实现比较快的旋转
 */

//////////////////////////////////////////////////////////////////////
// 三阶魔方
#define NANOKA_CASE_NUM 3
// 普通的正方体魔方面数
#define NANOKA_LAYER_NUM 6
// 计数基准类型
typedef int nanoka_num_t;
// 存储基准类型
typedef uint8_t nanoka_storage_t;
// 情况基准类型
typedef std::set<std::vector<nanoka_storage_t>> nanoka_case_t;
// 统计基准类型
typedef std::pair<nanoka_num_t, std::map<nanoka_num_t, nanoka_num_t>> nanoka_statistic_t;
// 存储数据结构
typedef std::map<nanoka_num_t, std::vector<std::vector<nanoka_storage_t>>> nanoka_map_t;

//////////////////////////////////////////////////////////////////////
// 返回状态码重定义
typedef int nanoka_status_t;

#define NANOKA_SUCCESS 0
#define NANOKA_ERROR 1
#define NANOKA_FAILURE -1

//////////////////////////////////////////////////////////////////////
// 操作方式重定义
typedef int nanoka_move_t;
typedef int nanoka_move_enum_t;

#define NANOKA_OP_BIAS 3

// 水平偏转
#define NANOKA_MOVE_YAW 0
#define NANOKA_MOVE_YAW_2 NANOKA_MOVE_YAW + NANOKA_OP_BIAS
// 左右横滚
#define NANOKA_MOVE_ROLL 1
#define NANOKA_MOVE_ROLL_2 NANOKA_MOVE_ROLL + NANOKA_OP_BIAS
// 前后翻滚
#define NANOKA_MOVE_PITCH 2
#define NANOKA_MOVE_PITCH_2 NANOKA_MOVE_PITCH + NANOKA_OP_BIAS

// 操作数枚举类型
#define MOVE_POS_90 0
#define MOVE_POS_180 1
#define MOVE_NEG_180 1
#define MOVE_180 1
#define MOVE_NEG_90 2

//////////////////////////////////////////////////////////////////////

// BFS 中选择插入的标识
#define NANOKA_ORDER 0
#define NANOKA_REVERSE 1

// 随机数链接
extern std::random_device rd;
extern std::mt19937 gen;
extern std::uniform_int_distribution<nanoka_num_t> dis;

// 获取 Map 的主键
std::vector<nanoka_num_t> nanoka_get_keys(std::map<nanoka_num_t, nanoka_num_t> &m);
// 获取 Map 的值
std::vector<nanoka_num_t> nanoka_get_values(std::map<nanoka_num_t, nanoka_num_t> &m);

#define NANOKA_ANY 0
#define NANOKA_ALL 1

// 快捷比较函数
nanoka_status_t nanoka_equal(std::vector<nanoka_num_t> &data, nanoka_num_t value, nanoka_status_t mode);
nanoka_status_t nanoka_equal(std::vector<nanoka_storage_t> &data, nanoka_num_t value, nanoka_status_t mode);
nanoka_status_t nanoka_equal(std::vector<nanoka_storage_t> &data, std::vector<nanoka_storage_t> &data2);

// 检索函数
nanoka_status_t nanoka_in(nanoka_map_t &data_map, std::vector<nanoka_storage_t> &data);
nanoka_status_t nanoka_in(std::vector<std::vector<nanoka_storage_t>> &data_set, std::vector<nanoka_storage_t> &data);

#define NANOKA_DEVELOP_MODE 1
#define NANOKA_DEPLOY_MODE 0

#define NANOKA_MODE NANOKA_DEPLOY_MODE

#endif
