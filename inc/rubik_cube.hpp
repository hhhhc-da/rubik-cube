#ifndef RUBIK_CUBE_NANOKA_H
#define RUBIK_CUBE_NANOKA_H

#include <rubik_cube_base.hpp>

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

    

private:
    // 魔方阶数
    int cube_num;
    // 魔方平面数
    int layer_num;
    // 魔方内容存储体
    std::vector<int> cube_storage;
};

#endif
