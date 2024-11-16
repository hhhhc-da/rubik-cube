#ifndef CUBE_ARRAY_NANOKA_H
#define CUBE_ARRAY_NANOKA_H

#include <layer_array.hpp>
#include <rubik_cube_base.hpp>

class Cube_Array
{
public:
    // 拷贝控制函数
    Cube_Array();
    Cube_Array(nanoka_num_t cube);
    Cube_Array(nanoka_num_t cube, nanoka_num_t layer);
    ~Cube_Array() = default;

    // 魔方旋转函数
    nanoka_status_t cube_move(nanoka_move_t move_type, nanoka_move_enum_t move_step);
    // 魔方初始化函数
    nanoka_status_t cube_init(void);
    // 魔方填充函数 (使用 int 类型数据表示颜色)
    nanoka_status_t cube_full(nanoka_num_t layer, nanoka_num_t color);

private:
    // 魔方阶数
    int cube_num;
    // 魔方平面数
    int layer_num;
    // 魔方内容存储体 (使用 vector 存放数据结构体的智能指针) - 长度为 cube_num^2
    std::vector<std::shared_ptr<Layer_Array>> cube_storage;
};

#endif
