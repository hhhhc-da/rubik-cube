#ifndef LAYER_ARRAY_NANOKA_H
#define LAYER_ARRAY_NANOKA_H

#include <rubik_cube_base.hpp>

// 魔方一个面的数据存储体
class Layer_Array
{
public:
    // 多种构造函数
    Layer_Array() : data_len(NANOKA_CASE_NUM * NANOKA_CASE_NUM)
    {
        for (nanoka_num_t i = 0; i < NANOKA_CASE_NUM * NANOKA_CASE_NUM; ++i)
            storage.emplace_back(0);
    }
    Layer_Array(nanoka_num_t len) : data_len(len)
    {
        for (nanoka_num_t i = 0; i < len; ++i)
            storage.emplace_back(0);
    }
    Layer_Array(nanoka_num_t len, std::vector<nanoka_storage_t> data) : data_len(len), storage(data) {}
    Layer_Array(nanoka_num_t len, std::vector<nanoka_storage_t> &data) : data_len(len), storage(data) {}
    Layer_Array(nanoka_num_t len, std::vector<nanoka_storage_t> &&data) : data_len(len), storage(data) {}
    // 默认构造和析构函数
    Layer_Array(Layer_Array &) = default;
    Layer_Array(Layer_Array &&) = default;
    Layer_Array &operator=(Layer_Array &) = default;
    Layer_Array &operator=(Layer_Array &&) = default;
    ~Layer_Array() = default;
    // 快速写入
    Layer_Array &operator=(std::vector<nanoka_storage_t> data);

    // 旋转九十度函数 (默认顺时针, 开启 reverse 可以逆时针旋转 90 度)
    nanoka_status_t route_90(bool reverse);
    // 获取当前的面结果 (不允许外部修改)
    std::vector<nanoka_storage_t> get_storage(void) const;
    // 格式化输出
    void print_storage(void) const;
    // 读取我感兴趣的部分
    std::vector<nanoka_storage_t> read(nanoka_num_t pos);
    // 修改两个区块(0,1,2,3 分别表示修改 <1,2>,<2,3>,<3,4>,<4,1>)
    nanoka_status_t alter(nanoka_num_t pos, std::vector<nanoka_storage_t> data);
    // 填充四个区块
    nanoka_status_t full(nanoka_num_t color);
    // 二阶魔方测试旋转用顺序填充区块函数
    nanoka_status_t valid(nanoka_num_t start_color);

private:
    nanoka_num_t data_len;
    // 存储体变为 9 个的
    std::vector<nanoka_storage_t> storage;
};

#endif
