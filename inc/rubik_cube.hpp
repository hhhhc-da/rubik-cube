#ifndef RUBIK_CUBE_NANOKA_H
#define RUBIK_CUBE_NANOKA_H

#include <cube_array.hpp>
#include <rubik_cube_base.hpp>

// 魔方类
class Rubik_Cube
{
public:
    // 构造函数
    Rubik_Cube() : rubik_cube_num(NANOKA_CASE_NUM), rubik_layer_num(NANOKA_LAYER_NUM), rubik_storage(std::make_shared<Cube_Array>(NANOKA_CASE_NUM, NANOKA_LAYER_NUM)), gen(rd()), dis(0, 2) {}
    Rubik_Cube(nanoka_num_t cube, nanoka_num_t layer) : rubik_cube_num(cube), rubik_layer_num(layer), rubik_storage(std::make_shared<Cube_Array>(cube, layer)), gen(rd()), dis(0, 2) {}

    // 拷贝控制函数
    Rubik_Cube(Rubik_Cube &x) = default;
    Rubik_Cube(Rubik_Cube &&x) = default;
    // 析构函数
    ~Rubik_Cube() = default;
    // 拷贝控制运算符
    Rubik_Cube &operator=(Rubik_Cube &x) = default;
    Rubik_Cube &operator=(Rubik_Cube &&x) = default;

    // 检测魔方是否可用
    nanoka_status_t rubik_is_available(void);
    // 检测魔方是否是初始状态
    nanoka_status_t rubik_done(void);
    /* 魔方操作函数
     *
     * nanoka_move_t 类型成员:
     * NANOKA_MOVE_YAW      : 调整魔方偏航角
     * NANOKA_MOVE_ROLL     : 调整魔方横滚角
     * NANOKA_MOVE_PITCH    : 调整魔方翻转角
     *
     * nanoka_move_enum_t 类型成员:
     * MOVE_POS_90          : 顺时针旋转 90 度
     * MOVE_POS_180         : 顺时针旋转 180 度
     * MOVE_180             : 旋转 180 度
     * MOVE_NEG_180         : 逆时针旋转 180 度
     * MOVE_NEG_90          : 逆时针旋转 90 度
     */
    nanoka_status_t rubik_ctrl(nanoka_move_t move_type, nanoka_move_enum_t move_step);
    // 魔方快速查看某个面函数
    void rubik_check(std::string position);
    // 魔方随机旋转函数
    nanoka_status_t rubik_random_state_generator(nanoka_num_t depth);

    // 魔方查看所有面函数
    nanoka_status_t rubik_print(void)
    {
        rubik_storage->cube_print();
    }
    // 魔方复原函数
    nanoka_status_t rubik_reset(void)
    {
        return rubik_storage->cube_reset();
    }
    // 魔方随机数生成函数
    nanoka_num_t rubik_random_generator(void)
    {
        return dis(gen);
    }

private:
    // 魔方阶数
    nanoka_num_t rubik_cube_num;
    // 魔方平面数
    nanoka_num_t rubik_layer_num;
    // 魔方内容存储体
    std::shared_ptr<Cube_Array> rubik_storage;
    // 随机数内容
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<nanoka_num_t> dis;
};

#endif
