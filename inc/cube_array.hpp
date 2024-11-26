#ifndef CUBE_ARRAY_NANOKA_H
#define CUBE_ARRAY_NANOKA_H

#include <layer_array.hpp>
#include <rubik_cube_base.hpp>

// ħ�����ݽṹ�洢��
class Cube_Array
{
public:
    // �������ƺ���
    Cube_Array();
    Cube_Array(nanoka_num_t cube);
    Cube_Array(nanoka_num_t cube, nanoka_num_t layer);
    ~Cube_Array() = default;

    // ħ����ʼ������
    nanoka_status_t cube_init(void);
    // ħ���ָ���ʼ��
    nanoka_status_t cube_reset(void);
    // ħ����亯�� (ʹ�� int �������ݱ�ʾ��ɫ)
    nanoka_status_t cube_full(nanoka_num_t layer, nanoka_num_t color);
    // ħ����ʽ���������
    nanoka_status_t cube_print(void);
    // ħ����ת����
    nanoka_status_t cube_move(nanoka_move_t move_type, nanoka_move_enum_t move_step);
    // ħ����֤����
    nanoka_status_t cube_valid(nanoka_num_t start_color);
    // ħ���������ݻ�ȡ����
    inline std::pair<nanoka_num_t, nanoka_num_t> cube_info(void) const
    {
        return {cube_num, layer_num};
    }
    // ħ���������ͳ�ƺ���
    nanoka_statistic_t cube_count(void);
    // ħ�����ݶ�ȡ����
    std::vector<nanoka_storage_t> cube_read(nanoka_num_t pos)
    {
        return cube_storage.at(pos)->get_storage();
    }
    // ħ������д�뺯��
    nanoka_status_t cube_write(nanoka_num_t pos, std::vector<nanoka_storage_t> data);
    // ħ���洢���ȡ����
    std::vector<nanoka_storage_t> cube_read_all(void);
    // ħ���洢��д�뺯��
    nanoka_status_t cube_write_all(std::vector<nanoka_storage_t> x);
    // ħ�������������
    void cube_print_pos(nanoka_num_t pos)
    {
        cube_storage.at(pos)->print_storage();
    }

private:
    // ħ������
    nanoka_num_t cube_num;
    // ħ��ƽ����
    nanoka_num_t layer_num;
    // ħ�����ݴ洢�� (ʹ�� vector ������ݽṹ�������ָ��) - ����Ϊ cube_num^2
    std::vector<std::shared_ptr<Layer_Array>> cube_storage;
};

#endif
