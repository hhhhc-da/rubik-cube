#ifndef LAYER_ARRAY_NANOKA_H
#define LAYER_ARRAY_NANOKA_H

#include <rubik_cube_base.hpp>

// ħ��һ��������ݴ洢��
class Layer_Array
{
public:
    // ���ֹ��캯��
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
    // Ĭ�Ϲ������������
    Layer_Array(Layer_Array &) = default;
    Layer_Array(Layer_Array &&) = default;
    Layer_Array &operator=(Layer_Array &) = default;
    Layer_Array &operator=(Layer_Array &&) = default;
    ~Layer_Array() = default;
    // ����д��
    Layer_Array &operator=(std::vector<nanoka_storage_t> data);

    // ��ת��ʮ�Ⱥ��� (Ĭ��˳ʱ��, ���� reverse ������ʱ����ת 90 ��)
    nanoka_status_t route_90(bool reverse);
    // ��ȡ��ǰ������ (�������ⲿ�޸�)
    std::vector<nanoka_storage_t> get_storage(void) const;
    // ��ʽ�����
    void print_storage(void) const;
    // ��ȡ�Ҹ���Ȥ�Ĳ���
    std::vector<nanoka_storage_t> read(nanoka_num_t pos);
    // �޸���������(0,1,2,3 �ֱ��ʾ�޸� <1,2>,<2,3>,<3,4>,<4,1>)
    nanoka_status_t alter(nanoka_num_t pos, std::vector<nanoka_storage_t> data);
    // ����ĸ�����
    nanoka_status_t full(nanoka_num_t color);
    // ����ħ��������ת��˳��������麯��
    nanoka_status_t valid(nanoka_num_t start_color);

private:
    nanoka_num_t data_len;
    // �洢���Ϊ 9 ����
    std::vector<nanoka_storage_t> storage;
};

#endif
