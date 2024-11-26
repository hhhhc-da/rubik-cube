#ifndef RUBIK_CUBE_NANOKA_H
#define RUBIK_CUBE_NANOKA_H

#include <cube_array.hpp>
#include <rubik_cube_base.hpp>

// ħ����
class Rubik_Cube
{
public:
    // ���캯��
    Rubik_Cube() : rubik_cube_num(NANOKA_CASE_NUM), rubik_layer_num(NANOKA_LAYER_NUM), rubik_storage(std::make_shared<Cube_Array>(NANOKA_CASE_NUM, NANOKA_LAYER_NUM)) {}
    Rubik_Cube(nanoka_num_t cube, nanoka_num_t layer) : rubik_cube_num(cube), rubik_layer_num(layer), rubik_storage(std::make_shared<Cube_Array>(cube, layer)) {}

    // �������ƺ���
    Rubik_Cube(Rubik_Cube &x) = default;
    Rubik_Cube(Rubik_Cube &&x) = default;
    // ��������
    ~Rubik_Cube() = default;
    // �������������
    Rubik_Cube &operator=(Rubik_Cube &x) = default;
    Rubik_Cube &operator=(Rubik_Cube &&x) = default;

    // ���ħ���Ƿ����
    inline nanoka_status_t rubik_is_available(void)
    {
        // ���ħ�����ڲ��洢�Ļ����ṹ�Ƿ���ͬ
        std::pair<nanoka_num_t, nanoka_num_t> storage_info = rubik_storage->cube_info();
        if (storage_info.first != rubik_cube_num || storage_info.second != rubik_layer_num)
        {
            std::cerr << "(Rubik_Cube::rubik_is_available) Infomation not valid." << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
            return NANOKA_ERROR;
        }

        // ���ħ���洢���Ƿ��������ħ�� (��ȡÿ���������, ���ҽ��м���)
    }
    // ���ħ���Ƿ��ǳ�ʼ״̬
    nanoka_status_t rubik_is_initial_state(void);
    // ħ����������
    nanoka_status_t rubik_ctrl();

private:
    // ħ������
    nanoka_num_t rubik_cube_num;
    // ħ��ƽ����
    nanoka_num_t rubik_layer_num;
    // ħ�����ݴ洢��
    std::shared_ptr<Cube_Array> rubik_storage;
};

#endif
