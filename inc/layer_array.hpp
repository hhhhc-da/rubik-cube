#ifndef LAYER_ARRAY_NANOKA_H
#define LAYER_ARRAY_NANOKA_H

#include <rubik_cube_base.hpp>

class Layer_Array
{
public:
    Layer_Array();
    Layer_Array(nanoka_num_t len);
    Layer_Array(nanoka_num_t len, std::vector<nanoka_storage_t> data);
    Layer_Array(nanoka_num_t len, std::vector<nanoka_storage_t>& data);
    Layer_Array(nanoka_num_t len, std::vector<nanoka_storage_t>&& data);

    // 旋转九十度函数 (默认顺时针, 开启 reverse 可以逆时针旋转 90 度)
    nanoka_status_t route_90(bool reverse);
    // 获取当前的面结果 (不允许外部修改)
    std::vector<nanoka_storage_t> get_storage(void) const;
    // 获取所有旋转后的情况结果
    std::set<std::vector<nanoka_storage_t>> get_all_route_case(void);
    // 修改两个区块
    nanoka_status_t 

private:
    nanoka_num_t data_len;
    std::vector<nanoka_storage_t> storage;
};

#endif
