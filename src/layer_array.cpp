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

// ��ת��ʮ�Ⱥ��� (Ĭ��˳ʱ��, ���� reverse ������ʱ����ת 90 ��)
nanoka_status_t Layer_Array::route_90(bool reverse)
{
}

// ��ȡ��ǰ������ (�������ⲿ�޸�)
std::vector<nanoka_storage_t> Layer_Array::get_storage(void) const
{
}

// ��ȡ������ת���������
std::set<std::vector<nanoka_storage_t>> Layer_Array::get_all_route_case(void)
{
}

// �޸���������(0,1,2,3 �ֱ��ʾ�޸� <1,2>,<2,3>,<3,4>,<4,1>)
nanoka_status_t Layer_Array::alter(nanoka_num_t pos, nanoka_num_t data1, nanoka_num_t data2)
{
}

nanoka_status_t Layer_Array::alter(nanoka_num_t pos, std::vector<nanoka_num_t> data)
{
}

nanoka_status_t Layer_Array::alter(nanoka_num_t pos, std::pair<nanoka_num_t, nanoka_num_t> data)
{
}