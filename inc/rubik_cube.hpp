#ifndef RUBIK_CUBE_NANOKA_H
#define RUBIK_CUBE_NANOKA_H

#include <rubik_cube_base.hpp>

// ħ����
class Rubik_Cube
{
public:
    // ���캯��
    Rubik_Cube() : cube_num(2), layer_num(6) {}
    Rubik_Cube(int cube) : cube_num(cube), layer_num(6) {}
    Rubik_Cube(int cube, int layer) : cube_num(cube), layer_num(layer) {}

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
    int cube_num;
    // ħ��ƽ����
    int layer_num;
    // ħ�����ݴ洢��
    std::vector<int> cube_storage;
};

#endif
