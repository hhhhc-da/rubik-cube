#ifndef RUBIK_CUBE_NANOKA_H
#define RUBIK_CUBE_NANOKA_H

#include "rubik_cube_base.hpp"

// ������ʽ�ض���
typedef int nanoka_move_t;
// ˮƽƫת
#define NANOKA_MOVE_YAW     0 
// ǰ�󷭹�
#define NANOKA_MOVE_ROLL    1
// ���Һ��
#define NANOKA_MOVE_PITCH   2
// ������ö������
typedef enum
{
    MOVE_POS_90 = 0,
    MOVE_POS_180,
    MOVE_NEG_180,
    MOVE_NEG_90
}
nanoka_move_enum_t;

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

    // ħ����ת����
    nanoka_status cube_move(nanoka_move_t move_type, nanoka_move_enum_t move_step);

private:
    // ħ������
    int cube_num;
    // ħ��ƽ����
    int layer_num;
    // ħ�����ݴ洢��
    std::vector<int> cube_storage;
};

#endif
