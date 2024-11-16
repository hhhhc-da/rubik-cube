#include <layer_array.hpp>

Layer_Array::Layer_Array() : data_len(NANOKA_CASE_NUM * NANOKA_CASE_NUM)
{
}

Layer_Array::Layer_Array(nanoka_num_t len)
{
}

Layer_Array::Layer_Array(nanoka_num_t len, std::vector<nanoka_storage_t> data)
{
}

Layer_Array::Layer_Array(nanoka_num_t len, std::vector<nanoka_storage_t> &data)
{
}

Layer_Array::Layer_Array(nanoka_num_t len, std::vector<nanoka_storage_t> &&data)
{
}

// 旋转九十度函数 (默认顺时针, 开启 reverse 可以逆时针旋转 90 度)
nanoka_status_t Layer_Array::route_90(bool reverse)
{
}

// 获取当前的面结果 (不允许外部修改)
std::vector<nanoka_storage_t> Layer_Array::get_storage(void) const
{
}

// 获取所有旋转后的情况结果
std::set<std::vector<nanoka_storage_t>> Layer_Array::get_all_route_case(void)
{
}

// 修改两个区块(0,1,2,3 分别表示修改 <1,2>,<2,3>,<3,4>,<4,1>)
nanoka_status_t Layer_Array::alter(nanoka_num_t pos, nanoka_num_t data1, nanoka_num_t data2)
{
}

nanoka_status_t Layer_Array::alter(nanoka_num_t pos, std::vector<nanoka_num_t> data)
{
}

nanoka_status_t Layer_Array::alter(nanoka_num_t pos, std::pair<nanoka_num_t, nanoka_num_t> data)
{
}