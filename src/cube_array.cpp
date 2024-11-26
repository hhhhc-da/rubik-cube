#include <cube_array.hpp>

// ħ����ʼ������
nanoka_status_t Cube_Array::cube_init(nanoka_num_t data_len, nanoka_num_t layer_num)
{
    try
    {
        // ����У��
        if (cube_storage.size() != layer_num)
            throw std::runtime_error("cube_storage.size() != layer_num");

        // ��ÿ��ƽ����������ݶ�����
        for (int i = 0; i < NANOKA_LAYER_NUM; ++i)
        {
            nanoka_status_t ret = cube_full(i, i);

            if (ret != NANOKA_SUCCESS)
                throw std::runtime_error("cube_full failed.");
        }
        return NANOKA_SUCCESS;
    }
    catch (std::runtime_error e)
    {
        std::cerr << "(Cube_Array::cube_init) Runtime_error: " << e.what()  << " File " << __FILE__ << ", line " << __LINE__  << "." << std::endl;
    }
    catch (...)
    {
        std::cerr << "(Cube_Array::cube_init) Unknown_error: Process crushed." << " File " << __FILE__ << ", line " << __LINE__  << "." << std::endl;
    }
    return NANOKA_ERROR;
}

// ħ����亯�� (ʹ�� int �������ݱ�ʾ��ɫ)
nanoka_status_t Cube_Array::cube_full(nanoka_num_t layer, nanoka_num_t color)
{
    try
    {
        nanoka_status_t ret = cube_storage.at(layer)->full(color);

        if (ret != NANOKA_SUCCESS)
            throw std::runtime_error("cube_storage.at(layer)->full(color) failed.");
    }
    catch (std::runtime_error e)
    {
        std::cerr << "(Cube_Array::cube_full) Runtime_error: " << e.what() << " File " << __FILE__ << ", line " << __LINE__  << "." << std::endl;
    }
    catch (...)
    {
        std::cerr << "(Cube_Array::cube_full) Unknown_error: Process crushed." << " File " << __FILE__ << ", line " << __LINE__  << "." << std::endl;
    }
    return NANOKA_ERROR;
}

// ħ����ת����
nanoka_status_t Cube_Array::cube_move(nanoka_move_t move_type, nanoka_move_enum_t move_step)
{
    // switch (move_type)
    // {
    // case NANOKA_MOVE_YAW:
    //     break;
    // case NANOKA_MOVE_ROLL:
    //     break;
    // case NANOKA_MOVE_PITCH:
    //     break;
    // default:
    //     throw std::runtime_error("nanoka_move_t move_type invalid.");
    // }
}

// Ĭ�Ϲ��캯��
Cube_Array::Cube_Array() : cube_num(NANOKA_CASE_NUM), layer_num(NANOKA_LAYER_NUM)
{
    // ����ָ��ͷ
    for (nanoka_num_t i = 0; i < NANOKA_LAYER_NUM; ++i)
        cube_storage.push_back(std::make_shared<Layer_Array>(NANOKA_CASE_NUM * NANOKA_CASE_NUM));
}

// ��һ��ֵ���캯��
Cube_Array::Cube_Array(nanoka_num_t cube) : cube_num(cube), layer_num(6)
{
    for (nanoka_num_t i = 0; i < NANOKA_LAYER_NUM; ++i)
        cube_storage.push_back(std::make_shared<Layer_Array>(cube * cube));
}

// ȫ����ֵ���캯��
Cube_Array::Cube_Array(nanoka_num_t cube, nanoka_num_t layer) : cube_num(cube), layer_num(layer)
{
    for (nanoka_num_t i = 0; i < layer; ++i)
        cube_storage.push_back(std::make_shared<Layer_Array>(cube * cube));
}