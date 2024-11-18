#ifndef RUBIK_CUBE_NANOKA_H
#define RUBIK_CUBE_NANOKA_H

#include <cube_array.hpp>
#include <rubik_cube_base.hpp>

// 魔方类
class Rubik_Cube
{
public:
    // 构造函数
    Rubik_Cube() : rubik_cube_num(NANOKA_CASE_NUM), rubik_layer_num(NANOKA_LAYER_NUM), rubik_storage(std::make_shared<Cube_Array>(NANOKA_CASE_NUM, NANOKA_LAYER_NUM)) {}
    Rubik_Cube(nanoka_num_t cube, nanoka_num_t layer) : rubik_cube_num(cube), rubik_layer_num(layer), rubik_storage(std::make_shared<Cube_Array>(cube, layer)) {}

    // 拷贝控制函数
    Rubik_Cube(Rubik_Cube &x) = default;
    Rubik_Cube(Rubik_Cube &&x) = default;
    // 析构函数
    ~Rubik_Cube() = default;
    // 拷贝控制运算符
    Rubik_Cube &operator=(Rubik_Cube &x) = default;
    Rubik_Cube &operator=(Rubik_Cube &&x) = default;

    // 检测魔方是否可用
    inline nanoka_status_t rubik_is_available(void)
    {
        // 检测魔方和内部存储的基本结构是否相同
        std::pair<nanoka_num_t, nanoka_num_t> storage_info = rubik_storage->cube_info();
        if (storage_info.first != rubik_cube_num || storage_info.second != rubik_layer_num)
        {
            std::cerr << "(Rubik_Cube::rubik_is_available) Infomation not valid." << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
            return NANOKA_ERROR;
        }

        // 检测魔方存储体是否符合正规魔方 (获取每个面的内容, 并且进行计数)
    }
    // 检测魔方是否是初始状态
    nanoka_status_t rubik_is_initial_state(void);
    // 魔方操作函数
    nanoka_status_t rubik_ctrl();

private:
    // 魔方阶数
    nanoka_num_t rubik_cube_num;
    // 魔方平面数
    nanoka_num_t rubik_layer_num;
    // 魔方内容存储体
    std::shared_ptr<Cube_Array> rubik_storage;
};

#endif
