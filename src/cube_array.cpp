#include <cube_array.hpp>

// ħ����ת����
nanoka_status Cube_Array::cube_move(nanoka_move_t move_type, nanoka_move_enum_t move_step){
    switch(move_type){
        case NANOKA_MOVE_YAW:
            break;
        case NANOKA_MOVE_ROLL:
            break;
        case NANOKA_MOVE_PITCH:
            break;
        default:
            throw std::runtime_error("nanoka_move_t move_type invalid.");
    }
}

// Ĭ�Ϲ��캯��
Cube_Array::Cube_Array(): cube_num(2), layer_num(6) 
{
    cube_storage = new uint8_t[24];
}

// ��һ��ֵ���캯��
Cube_Array::Cube_Array(int cube) : cube_num(cube), layer_num(6)
{
    cube_storage = new uint8_t[cube*cube*6];
}

// ȫ����ֵ���캯��
Cube_Array::Cube_Array(int cube, int layer) : cube_num(cube), layer_num(layer)
{
    cube_storage = new uint8_t[cube*cube*layer];
}

// �������������ڴ�
Cube_Array::~Cube_Array()
{
    delete[] cube_storage;
}