#include <rubik_cube.hpp>

// ħ�������ת����
nanoka_status_t Rubik_Cube::rubik_random_state_generator(nanoka_num_t depth)
{
    // ����������ħ����λ
    rubik_reset();

    // �������������
    std::vector<nanoka_num_t> random_cache;
    std::map<nanoka_num_t, const char *> action = {
        {0, "YAW"}, {1, "ROLL"}, {2, "PITCH"}};
    std::map<nanoka_num_t, const char *> op = {
        {0, "+90"}, {1, "180"}, {2, "-90"}};

    try
    {
        for (nanoka_num_t j = 0; j < depth; ++j)
        {
            for (nanoka_num_t i = 0; i < 2; ++i)
            {
                random_cache.push_back(rubik_random_generator());
            }

            std::cout << "��" << j + 1 << "����תħ�� ( " << action[random_cache.at(0)]
                      << " " << op[random_cache.at(1)] << " )" << std::endl;
            rubik_ctrl(random_cache.at(0), random_cache.at(1));

            // ������ʱ����
            random_cache.clear();
        }

        rubik_print();
        return NANOKA_SUCCESS;
    }
    catch (std::runtime_error e)
    {
        std::cerr << "(Rubik_Cube::rubik_check) Runtime_error: " << e.what() << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    catch (...)
    {
        std::cerr << "(Rubik_Cube::rubik_check) Unknown_error: Process crushed." << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    return NANOKA_ERROR;
}

// ħ�����ٲ鿴ĳ���溯��
void Rubik_Cube::rubik_check(std::string position)
{
    try
    {
        std::map<std::string, nanoka_num_t> f = {
            {"Top", 0}, {"Left", 1}, {"Front", 2}, {"Right", 3}, {"Back", 4}, {"Bottom", 5}};
        std::vector<std::string> s = {"Top", "Left", "Front", "Right", "Back", "Bottom"};

        if (std::find_if(s.begin(), s.end(), [&](std::string x)
                         { return x == position; }) == s.end())
            throw std::runtime_error("Key is invalid.");

        rubik_storage->cube_print_pos(f[position]);
    }
    catch (std::runtime_error e)
    {
        std::cerr << "(Rubik_Cube::rubik_check) Runtime_error: " << e.what() << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    catch (...)
    {
        std::cerr << "(Rubik_Cube::rubik_check) Unknown_error: Process crushed." << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
}

// ���ħ���Ƿ����
nanoka_status_t Rubik_Cube::rubik_is_available(void)
{
    // ���ħ�����ڲ��洢�Ļ����ṹ�Ƿ���ͬ
    std::pair<nanoka_num_t, nanoka_num_t> storage_info = rubik_storage->cube_info();
    if (storage_info.first != rubik_cube_num || storage_info.second != rubik_layer_num)
    {
        std::cerr << "(Rubik_Cube::rubik_is_available) Infomation not valid." << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
        return NANOKA_ERROR;
    }

    // ���ħ���洢���Ƿ��������ħ�� (��ȡÿ���������, ���ҽ��м���)
    nanoka_statistic_t count = rubik_storage->cube_count();
    std::vector<nanoka_num_t> m_values = nanoka_get_values(count.second);

    nanoka_status_t value_flag = nanoka_equal(m_values, rubik_cube_num * rubik_cube_num, NANOKA_ALL);

    if (count.second.size() != rubik_layer_num)
    {
        std::cerr << "(Rubik_Cube::rubik_is_available) Storage not valid." << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
        return NANOKA_ERROR;
    }
    return NANOKA_SUCCESS;
}

// ���ħ���Ƿ��ǳ�ʼ״̬
nanoka_status_t Rubik_Cube::rubik_done(void)
{
    try
    {
        nanoka_status_t avail = rubik_is_available();
        if (avail == NANOKA_ERROR)
            throw std::runtime_error("rubik cube is not available.");
        // ħ���������ͨ����ֻ��Ҫ����ĸ����Ƿ���ɫ��ͬ����
        for (nanoka_num_t i = 0; i < rubik_layer_num; ++i)
        {
            std::vector<nanoka_storage_t> buffer2 = rubik_storage->cube_read(i);
            nanoka_status_t ret = nanoka_equal(buffer2, buffer2.at(0), NANOKA_ALL);
            if (ret == NANOKA_ERROR)
                return NANOKA_ERROR;
        }
        return NANOKA_SUCCESS;
    }
    catch (std::runtime_error e)
    {
        std::cerr << "(Rubik_Cube::rubik_done) Runtime_error: " << e.what() << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    catch (...)
    {
        std::cerr << "(Rubik_Cube::rubik_done) Unknown_error: Process crushed." << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    return NANOKA_ERROR;
}

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
nanoka_status_t Rubik_Cube::rubik_ctrl(nanoka_move_t move_type, nanoka_move_enum_t move_step)
{
    return rubik_storage->cube_move(move_type, move_step);
}