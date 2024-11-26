#ifndef CUBE_ARRAY_NANOKA_H
#define CUBE_ARRAY_NANOKA_H

#include <layer_array.hpp>
#include <rubik_cube_base.hpp>

class Cube_Array
{
public:
    // �������ƺ���
    Cube_Array();
    Cube_Array(nanoka_num_t cube);
    Cube_Array(nanoka_num_t cube, nanoka_num_t layer);
    ~Cube_Array() = default;

    // ħ����ת����
    nanoka_status_t cube_move(nanoka_move_t move_type, nanoka_move_enum_t move_step);
    // ħ����ʼ������
    nanoka_status_t cube_init(nanoka_num_t data_len, nanoka_num_t layer_num);
    // ħ����亯�� (ʹ�� int �������ݱ�ʾ��ɫ)
    nanoka_status_t cube_full(nanoka_num_t layer, nanoka_num_t color);

private:
    // ħ������
    int cube_num;
    // ħ��ƽ����
    int layer_num;
    // ħ�����ݴ洢�� (ʹ�� vector ������ݽṹ�������ָ��)
    std::vector<std::shared_ptr<Layer_Array>> cube_storage;
};

#endif
