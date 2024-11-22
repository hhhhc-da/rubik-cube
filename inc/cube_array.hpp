#ifndef CUBE_ARRAY_NANOKA_H
#define CUBE_ARRAY_NANOKA_H

#include <layer_array.hpp>
#include <rubik_cube_base.hpp>

// 魔方数据结构存储体
class Cube_Array
{
public:
    // 拷贝控制函数
    Cube_Array();
    Cube_Array(nanoka_num_t cube);
    Cube_Array(nanoka_num_t cube, nanoka_num_t layer);
    ~Cube_Array() = default;

    // 魔方初始化函数
    nanoka_status_t cube_init(void);
    // 魔方恢复初始化
    nanoka_status_t cube_reset(void);
    // 魔方填充函数 (使用 int 类型数据表示颜色)
    nanoka_status_t cube_full(nanoka_num_t layer, nanoka_num_t color);
    // 魔方格式化输出函数
    nanoka_status_t cube_print(void);
    // 魔方旋转函数
    nanoka_status_t cube_move(nanoka_move_t move_type, nanoka_move_enum_t move_step);
    // 魔方验证函数
    nanoka_status_t cube_valid(nanoka_num_t start_color);
    // 魔方基本内容获取函数
    inline std::pair<nanoka_num_t, nanoka_num_t> cube_info(void) const
    {
        return {cube_num, layer_num};
    }
    // 魔方表面个数统计函数
    nanoka_statistic_t cube_count(void);
    // 魔方内容读取函数
    std::vector<nanoka_storage_t> cube_read(nanoka_num_t pos)
    {
        return cube_storage.at(pos)->get_storage();
    }
    // 魔方内容写入函数
    nanoka_status_t cube_write(nanoka_num_t pos, std::vector<nanoka_storage_t> data);
    // 魔方存储体获取函数
    std::vector<nanoka_storage_t> cube_read_all(void);
    // 魔方存储体写入函数
    nanoka_status_t cube_write_all(std::vector<nanoka_storage_t> x);
    // 魔方单面输出函数
    void cube_print_pos(nanoka_num_t pos)
    {
        cube_storage.at(pos)->print_storage();
    }

private:
    // 魔方阶数
    nanoka_num_t cube_num;
    // 魔方平面数
    nanoka_num_t layer_num;
    // 魔方内容存储体 (使用 vector 存放数据结构体的智能指针) - 长度为 cube_num^2
    std::vector<std::shared_ptr<Layer_Array>> cube_storage;
};

#endif
