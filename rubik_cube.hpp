#ifndef RUBIK_CUBE_NANOKA_H
#define RUBIK_CUBE_NANOKA_H

#include "rubik_cube_base.hpp"

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

// 魔方类
class Rubik_Cube
{
public:
    // 构造函数
    Rubik_Cube() : cube_num(2), layer_num(6) {}
    Rubik_Cube(int cube) : cube_num(cube), layer_num(6) {}
    Rubik_Cube(int cube, int layer) : cube_num(cube), layer_num(layer) {}

    Rubik_Cube(Rubik_Cube& x) {
        cube_num = x.cube_num;
        layer_num = x.layer_num;
        cube_storage = x.cube_storage;
    }
    Rubik_Cube(Rubik_Cube&& x) {
        cube_num = x.cube_num;
        layer_num = x.layer_num;
        cube_storage = x.cube_storage;
    }

    // 析构函数
    ~Rubik_Cube() = default;
    // 拷贝控制运算符
    Rubik_Cube &operator=(Rubik_Cube &x) = default;
    Rubik_Cube &operator=(Rubik_Cube &&x) = default;

    // 魔方旋转函数
    nanoka_status cube_move(nanoka_move_t move_type, nanoka_move_enum_t move_step);

private:
    // 魔方阶数
    int cube_num;
    // 魔方平面数
    int layer_num;
    // 魔方内容存储体
    std::vector<int> cube_storage;
};

#endif
