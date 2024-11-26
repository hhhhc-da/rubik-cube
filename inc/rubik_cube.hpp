#ifndef RUBIK_CUBE_NANOKA_H
#define RUBIK_CUBE_NANOKA_H

#include <rubik_cube_base.hpp>

// ħ����
class Rubik_Cube
{
public:
    // ���캯��
    Rubik_Cube(Rubik_Cube& x) {
        cube_num = x.cube_num;
        layer_num = x.layer_num;
        cube_storage = x.cube_storage;
    }
    Rubik_Cube(Rubik_Cube&& x) {
        cube_num = x.cube_num;
        layer_num = x.layer_num;
        cube_storage = x.cube_storage;
    }

    // ��������
    ~Rubik_Cube() = default;
    // �������������
    Rubik_Cube &operator=(Rubik_Cube &x) = default;
    Rubik_Cube &operator=(Rubik_Cube &&x) = default;

    

private:
    // ħ������
    nanoka_num_t cube_num;
    // ħ��ƽ����
    nanoka_num_t layer_num;
    // ħ�����ݴ洢��
    std::vector<nanoka_num_t> cube_storage;
};

#endif
