#ifndef RUBIK_CUBE_NANOKA_H
#define RUBIK_CUBE_NANOKA_H

#include <cube_array.hpp>
#include <rubik_cube_base.hpp>

// ħ����
class Rubik_Cube
{
public:
    // ���캯��
    Rubik_Cube() : rubik_cube_num(NANOKA_CASE_NUM), rubik_layer_num(NANOKA_LAYER_NUM), rubik_storage(std::make_shared<Cube_Array>(NANOKA_CASE_NUM, NANOKA_LAYER_NUM)), gen(rd()), dis(0, 2) {}
    Rubik_Cube(nanoka_num_t cube, nanoka_num_t layer) : rubik_cube_num(cube), rubik_layer_num(layer), rubik_storage(std::make_shared<Cube_Array>(cube, layer)), gen(rd()), dis(0, 2) {}

    // �������ƺ���
    Rubik_Cube(Rubik_Cube &x) = default;
    Rubik_Cube(Rubik_Cube &&x) = default;
    // ��������
    ~Rubik_Cube() = default;
    // �������������
    Rubik_Cube &operator=(Rubik_Cube &x) = default;
    Rubik_Cube &operator=(Rubik_Cube &&x) = default;

    // ���ħ���Ƿ����
    nanoka_status_t rubik_is_available(void);
    // ���ħ���Ƿ��ǳ�ʼ״̬
    nanoka_status_t rubik_done(void);
    /* ħ����������
     *
     * nanoka_move_t ���ͳ�Ա:
     * NANOKA_MOVE_YAW      : ����ħ��ƫ����
     * NANOKA_MOVE_ROLL     : ����ħ�������
     * NANOKA_MOVE_PITCH    : ����ħ����ת��
     *
     * nanoka_move_enum_t ���ͳ�Ա:
     * MOVE_POS_90          : ˳ʱ����ת 90 ��
     * MOVE_POS_180         : ˳ʱ����ת 180 ��
     * MOVE_180             : ��ת 180 ��
     * MOVE_NEG_180         : ��ʱ����ת 180 ��
     * MOVE_NEG_90          : ��ʱ����ת 90 ��
     */
    nanoka_status_t rubik_ctrl(nanoka_move_t move_type, nanoka_move_enum_t move_step);
    // ħ�����ٲ鿴ĳ���溯��
    void rubik_check(std::string position);
    // ħ�������ת����
    nanoka_status_t rubik_random_state_generator(nanoka_num_t depth);

    // ħ���鿴�����溯��
    nanoka_status_t rubik_print(void)
    {
        rubik_storage->cube_print();
    }
    // ħ����ԭ����
    nanoka_status_t rubik_reset(void)
    {
        return rubik_storage->cube_reset();
    }
    // ħ����������ɺ���
    nanoka_num_t rubik_random_generator(void)
    {
        return dis(gen);
    }

private:
    // ħ������
    nanoka_num_t rubik_cube_num;
    // ħ��ƽ����
    nanoka_num_t rubik_layer_num;
    // ħ�����ݴ洢��
    std::shared_ptr<Cube_Array> rubik_storage;
    // ���������
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<nanoka_num_t> dis;
};

#endif
