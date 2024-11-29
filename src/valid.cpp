// ��֤���߰�ͷ�ļ�
#include <valid.hpp>

#define VALID_MODE 1
#define COMMON_MODE 0

// layer_array ���ϱ�����ƺ궨��
#define VALID_LAYER_ARRAY_FULL_DEBUG 0
#define VALID_LAYER_ARRAY_STORAGE_STATUS 0
#define VALID_LAYER_ARRAY_SPIN_STATUS 0

// cube_array ���ϱ�����ƺ궨��
#define VALID_CUBE_ARRAY_FULL_DEBUG 0
#define VALID_CUBE_ARRAY_STORAGE_STATUS 0
#define VALID_CUBE_ARRAY_STORAGE_MODE VALID_MODE

#define VALID_CUBE_ARRAY_SPIN_STATUS 0
#define VALID_CUBE_ARRAY_SPIN_YAW_STATUS 0
#define VALID_CUBE_ARRAY_SPIN_ROLL_STATUS 0
#define VALID_CUBE_ARRAY_SPIN_PITCH_STATUS 0
#define VALID_CUBE_ARRAY_SPIN_YAW_2_STATUS 1
#define VALID_CUBE_ARRAY_SPIN_ROLL_2_STATUS 1
#define VALID_CUBE_ARRAY_SPIN_PITCH_2_STATUS 1

#define VALID_CUBE_ARRAY_STATISTIC_STATUS 0

// rubik_cube ���ϱ�����ƺ궨��
#define VALID_RUBIK_CUBE_FULL_DEBUG 0
#define VALID_RUBIK_CUBE_DONE_STATUS 0
#define VALID_RUBIK_CUBE_RANDOM_STATUS 0

// cube_algorithm ���ϱ�����ƺ궨��
#define VALID_CUBE_ALGO_FULL_DEBUG 0
#define VALID_CUBE_ALGO_IN_STATUS 0
#define VALID_CUBE_ALGO_EXPAND_STATUS 0

// cube_algorithm ��֤���麯��
void valid_cube_algo(void)
{
    std::cout << "valid_cube_algo ���Ժ�����ʼ����!" << std::endl;

#if VALID_CUBE_ALGO_IN_STATUS || VALID_CUBE_ALGO_FULL_DEBUG
    nanoka_map_t source = {
        {0, {{1, 2, 3}, {2, 3, 4}}}, {1, {{1, 2, 3}, {7, 3, 6}}}};
    std::vector<nanoka_storage_t> tv = {1, 2, 3};
    std::cout << ((nanoka_in(source, tv) == NANOKA_SUCCESS) ? "NANOKA_SUCCESS" : "NANOKA_ERROR") << std::endl;

    tv = {7, 3, 6};
    std::cout << ((nanoka_in(source, tv) == NANOKA_SUCCESS) ? "NANOKA_SUCCESS" : "NANOKA_ERROR") << std::endl;

    tv = {1, 2, 3, 4};
    std::cout << ((nanoka_in(source, tv) == NANOKA_SUCCESS) ? "NANOKA_SUCCESS" : "NANOKA_ERROR") << std::endl;
#endif

#if VALID_CUBE_ALGO_EXPAND_STATUS || VALID_CUBE_ALGO_FULL_DEBUG
    std::shared_ptr<Algo_BFS> x = std::make_shared<Algo_BFS>();

    nanoka_num_t result = x->nanoka_compute_bfs();
    std::cout << "���ħ���������ת����Ϊ " << result << " ��" << std::endl;
#endif
}

// rubik_cube ��֤���麯��
void valid_rubik_cube(void)
{
    std::cout << "valid_rubik_cube ���Ժ�����ʼ����!" << std::endl;
    // ��ʼ��֤�洢��ṹ
    auto x = std::make_shared<Rubik_Cube>(NANOKA_CASE_NUM, NANOKA_LAYER_NUM);

    std::map<nanoka_num_t, const char *> pr = {
        {NANOKA_SUCCESS, "NANOKA_SUCCESS"}, {NANOKA_ERROR, "NANOKA_ERROR"}};

#if VALID_RUBIK_CUBE_DONE_STATUS || VALID_RUBIK_CUBE_FULL_DEBUG
    nanoka_status_t stt = x->rubik_done();
    std::cout << "��ѯħ��״̬: " << pr[stt] << std::endl;
    x->rubik_check("Left");

    for (nanoka_num_t i = 0; i < 4; ++i)
    {
        x->rubik_ctrl(NANOKA_MOVE_YAW, MOVE_POS_90);
        stt = x->rubik_done();
        std::cout << "��ѯħ��״̬: " << pr[stt] << std::endl;
        x->rubik_check("Left");
    }
#endif

#if VALID_RUBIK_CUBE_RANDOM_STATUS || VALID_RUBIK_CUBE_FULL_DEBUG
    x->rubik_random_state_generator(100);
#endif
}

// ��ʼ��ģʽѡ����
void _valid_cube_array_reset(std::shared_ptr<Cube_Array> x, nanoka_num_t mode)
{
    if (mode == COMMON_MODE)
        x->cube_reset();
    else if (mode == VALID_MODE)
        x->cube_valid(1);
    else
        throw std::runtime_error("_valid_cube_array_reset param 'mode' is invalid");
}

// cube_array ��֤���麯��
void valid_cube_array(void)
{
    std::cout << "valid_cube_array ���Ժ�����ʼ����!" << std::endl;
    // ��ʼ��֤�洢��ṹ
    auto x = std::make_shared<Cube_Array>(NANOKA_CASE_NUM, NANOKA_LAYER_NUM);
    _valid_cube_array_reset(x, VALID_CUBE_ARRAY_STORAGE_MODE);
    x->cube_print();

#if VALID_CUBE_ARRAY_STATISTIC_STATUS || VALID_CUBE_ARRAY_FULL_DEBUG
    nanoka_statistic_t count = x->cube_count();

    std::cout << "ͳ�ƺ������Ϊ: " << count.first << std::endl;
    std::vector<nanoka_num_t> m_keys = nanoka_get_keys(count.second);

    std::cout << "Keys: [ " << std::flush;
    for (auto &x : m_keys)
    {
        std::cout << x << " ";
    }
    std::cout << "]" << std::endl;

    std::vector<nanoka_num_t> m_values = nanoka_get_values(count.second);

    std::cout << "Values: [ " << std::flush;
    for (auto &x : m_values)
    {
        std::cout << x << " ";
    }
    std::cout << "]" << std::endl;

    std::map<nanoka_status_t, const char *> pr = {
        {NANOKA_SUCCESS, "NANOKA_SUCCESS"}, {NANOKA_ERROR, "NANOKA_ERROR"}};

    std::cout << "��ʼ���Կ�����㺯�� nanoka_equal(nanoka_num_t)" << std::endl;
    nanoka_status_t ret = nanoka_equal(m_keys, 0, NANOKA_ANY);
    std::cout << "nanoka_equal(m_keys, 0, NANOKA_ANY) => " << pr[ret] << std::endl;

    ret = nanoka_equal(m_keys, 0, NANOKA_ALL);
    std::cout << "nanoka_equal(m_keys, 0, NANOKA_ALL) => " << pr[ret] << std::endl;

    ret = nanoka_equal(m_keys, 1, NANOKA_ANY);
    std::cout << "nanoka_equal(m_keys, 1, NANOKA_ANY) => " << pr[ret] << std::endl;

    ret = nanoka_equal(m_keys, 1, NANOKA_ALL);
    std::cout << "nanoka_equal(m_keys, 1, NANOKA_ALL) => " << pr[ret] << std::endl;

    ret = nanoka_equal(m_values, 9, NANOKA_ANY);
    std::cout << "nanoka_equal(m_values, 9, NANOKA_ANY) => " << pr[ret] << std::endl;

    ret = nanoka_equal(m_values, 9, NANOKA_ALL);
    std::cout << "nanoka_equal(m_values, 9, NANOKA_ANY) => " << pr[ret] << std::endl;

    std::cout << "��ʼ���Կ�����㺯�� nanoka_equal(nanoka_num_t)" << std::endl;
    // ֱ�Ӷ�ȡ Top ��
    std::vector<nanoka_storage_t> buffer2 = x->cube_read(0);

    ret = nanoka_equal(buffer2, buffer2.at(0), NANOKA_ALL);
    x->cube_print_pos(0);
    std::cout << "nanoka_equal(buffer2, buffer2.at(0), NANOKA_ALL) => " << pr[ret] << std::endl;

    x->cube_valid(1);
    buffer2 = x->cube_read(0);
    ret = nanoka_equal(buffer2, buffer2.at(0), NANOKA_ALL);
    x->cube_print_pos(0);
    std::cout << "nanoka_equal(buffer2, buffer2.at(0), NANOKA_ALL) => " << pr[ret] << std::endl;

#endif

#if VALID_CUBE_ARRAY_STORAGE_STATUS || VALID_CUBE_ARRAY_FULL_DEBUG
    std::vector<nanoka_num_t> vec = {2, 8, 3, 5, 4, 7};

    for (nanoka_num_t i = 0; i < vec.size(); ++i)
    {
        x->cube_full(i, vec.at(i));
    }
    x->cube_print();

    _valid_cube_array_reset(x, VALID_CUBE_ARRAY_STORAGE_MODE);
    std::vector<nanoka_storage_t> all_storage = x->cube_read_all();

    std::cout << "�ܹ��洢ռ��: " << all_storage.size() << " * " << sizeof(nanoka_storage_t) << " Byte" << std::endl;

    std::cout << "�洢��: [ " << std::flush;
    for (nanoka_storage_t &elem : all_storage)
        std::cout << static_cast<nanoka_num_t>(elem) << " ";
    std::cout << "]" << std::endl;

    std::vector<nanoka_storage_t> wbuf;
    for (nanoka_num_t i = 0; i < NANOKA_CASE_NUM * NANOKA_CASE_NUM * NANOKA_LAYER_NUM; ++i)
        wbuf.emplace_back(i % 8 + 1);

    x->cube_write_all(wbuf);
    all_storage = x->cube_read_all();

    std::cout << "�޸ĺ�洢��: [ " << std::flush;
    for (nanoka_storage_t &elem : all_storage)
        std::cout << static_cast<nanoka_num_t>(elem) << " ";
    std::cout << "]" << std::endl;

#endif

#if VALID_CUBE_ARRAY_SPIN_STATUS || VALID_CUBE_ARRAY_FULL_DEBUG

    _valid_cube_array_reset(x, VALID_CUBE_ARRAY_STORAGE_MODE);
    std::cout << "\nħ��ԭʼ״̬" << std::endl;
    x->cube_print();

#if VALID_CUBE_ARRAY_SPIN_YAW_STATUS || VALID_CUBE_ARRAY_FULL_DEBUG
    // Z ����ת
    _valid_cube_array_reset(x, VALID_CUBE_ARRAY_STORAGE_MODE);
    std::cout << "\n�Զ���˳ʱ����ת 90 ��" << std::endl;
    x->cube_move(NANOKA_MOVE_YAW, MOVE_POS_90);
    x->cube_print();

    _valid_cube_array_reset(x, VALID_CUBE_ARRAY_STORAGE_MODE);
    std::cout << "\n�Զ�����ת 180 ��" << std::endl;
    x->cube_move(NANOKA_MOVE_YAW, MOVE_180);
    x->cube_print();

    _valid_cube_array_reset(x, VALID_CUBE_ARRAY_STORAGE_MODE);
    std::cout << "\n�Զ�����ʱ����ת 90 ��" << std::endl;
    x->cube_move(NANOKA_MOVE_YAW, MOVE_NEG_90);
    x->cube_print();
#endif

#if VALID_CUBE_ARRAY_SPIN_ROLL_STATUS || VALID_CUBE_ARRAY_FULL_DEBUG
    // Y ����ת
    _valid_cube_array_reset(x, VALID_CUBE_ARRAY_STORAGE_MODE);
    std::cout << "\n��ǰ��˳ʱ����ת 90 ��" << std::endl;
    x->cube_move(NANOKA_MOVE_ROLL, MOVE_POS_90);
    x->cube_print();

    _valid_cube_array_reset(x, VALID_CUBE_ARRAY_STORAGE_MODE);
    std::cout << "\n��ǰ����ת 180 ��" << std::endl;
    x->cube_move(NANOKA_MOVE_ROLL, MOVE_180);
    x->cube_print();

    _valid_cube_array_reset(x, VALID_CUBE_ARRAY_STORAGE_MODE);
    std::cout << "\n��ǰ����ʱ����ת 90 ��" << std::endl;
    x->cube_move(NANOKA_MOVE_ROLL, MOVE_NEG_90);
    x->cube_print();
#endif

#if VALID_CUBE_ARRAY_SPIN_PITCH_STATUS || VALID_CUBE_ARRAY_FULL_DEBUG
    // X ����ת
    _valid_cube_array_reset(x, VALID_CUBE_ARRAY_STORAGE_MODE);
    std::cout << "\n������˳ʱ����ת 90 ��" << std::endl;
    x->cube_move(NANOKA_MOVE_PITCH, MOVE_POS_90);
    x->cube_print();

    _valid_cube_array_reset(x, VALID_CUBE_ARRAY_STORAGE_MODE);
    std::cout << "\n��������ת 180 ��" << std::endl;
    x->cube_move(NANOKA_MOVE_PITCH, MOVE_180);
    x->cube_print();

    _valid_cube_array_reset(x, VALID_CUBE_ARRAY_STORAGE_MODE);
    std::cout << "\n��������ʱ����ת 90 ��" << std::endl;
    x->cube_move(NANOKA_MOVE_PITCH, MOVE_NEG_90);
    x->cube_print();
#endif

#if VALID_CUBE_ARRAY_SPIN_YAW_2_STATUS || VALID_CUBE_ARRAY_FULL_DEBUG
    // Z ����ת2
    _valid_cube_array_reset(x, VALID_CUBE_ARRAY_STORAGE_MODE);
    std::cout << "\n�Զ���(�ڲ�)˳ʱ����ת 90 ��" << std::endl;
    x->cube_move(NANOKA_MOVE_YAW_2, MOVE_POS_90);
    x->cube_print();

    _valid_cube_array_reset(x, VALID_CUBE_ARRAY_STORAGE_MODE);
    std::cout << "\n�Զ���(�ڲ�)��ת 180 ��" << std::endl;
    x->cube_move(NANOKA_MOVE_YAW_2, MOVE_180);
    x->cube_print();

    _valid_cube_array_reset(x, VALID_CUBE_ARRAY_STORAGE_MODE);
    std::cout << "\n�Զ���(�ڲ�)��ʱ����ת 90 ��" << std::endl;
    x->cube_move(NANOKA_MOVE_YAW_2, MOVE_NEG_90);
    x->cube_print();
#endif

#if VALID_CUBE_ARRAY_SPIN_ROLL_2_STATUS || VALID_CUBE_ARRAY_FULL_DEBUG
    // Y ����ת
    _valid_cube_array_reset(x, VALID_CUBE_ARRAY_STORAGE_MODE);
    std::cout << "\n��ǰ��(�ڲ�)˳ʱ����ת 90 ��" << std::endl;
    x->cube_move(NANOKA_MOVE_ROLL_2, MOVE_POS_90);
    x->cube_print();

    _valid_cube_array_reset(x, VALID_CUBE_ARRAY_STORAGE_MODE);
    std::cout << "\n��ǰ��(�ڲ�)��ת 180 ��" << std::endl;
    x->cube_move(NANOKA_MOVE_ROLL_2, MOVE_180);
    x->cube_print();

    _valid_cube_array_reset(x, VALID_CUBE_ARRAY_STORAGE_MODE);
    std::cout << "\n��ǰ��(�ڲ�)��ʱ����ת 90 ��" << std::endl;
    x->cube_move(NANOKA_MOVE_ROLL_2, MOVE_NEG_90);
    x->cube_print();
#endif

#if VALID_CUBE_ARRAY_SPIN_PITCH_2_STATUS || VALID_CUBE_ARRAY_FULL_DEBUG
    // X ����ת
    _valid_cube_array_reset(x, VALID_CUBE_ARRAY_STORAGE_MODE);
    std::cout << "\n������(�ڲ�)˳ʱ����ת 90 ��" << std::endl;
    x->cube_move(NANOKA_MOVE_PITCH_2, MOVE_POS_90);
    x->cube_print();

    _valid_cube_array_reset(x, VALID_CUBE_ARRAY_STORAGE_MODE);
    std::cout << "\n������(�ڲ�)��ת 180 ��" << std::endl;
    x->cube_move(NANOKA_MOVE_PITCH_2, MOVE_180);
    x->cube_print();

    _valid_cube_array_reset(x, VALID_CUBE_ARRAY_STORAGE_MODE);
    std::cout << "\n������(�ڲ�)��ʱ����ת 90 ��" << std::endl;
    x->cube_move(NANOKA_MOVE_PITCH_2, MOVE_NEG_90);
    x->cube_print();
#endif

#endif
}

// layer_array ��֤���麯��
void valid_layer_array(void)
{
    std::cout << "valid_layer_array ���Ժ�����ʼ����!" << std::endl;
    auto x = std::make_shared<Layer_Array>(NANOKA_CASE_NUM * NANOKA_CASE_NUM);

    std::map<nanoka_num_t, const char *> pr = {
        {0, "<1,2,3>"}, {1, "<3,4,5>"}, {2, "<5,6,7>"}, {3, "<7,8,1>"}, {4, "<8,9,4>"}, {5, "<2,9,6>"}};

#if VALID_LAYER_ARRAY_STORAGE_STATUS || VALID_LAYER_ARRAY_FULL_DEBUG
    x->valid(1);
    x->print_storage();

    // ���Ի�ȡԪ�� API
    std::vector<nanoka_storage_t> sto = x->get_storage();
    std::cout << "Ԫ�ر���0: [";
    for (auto s : sto)
    {
        std::cout << " " << static_cast<nanoka_num_t>(s) << std::flush;
    }
    std::cout << " ]" << std::endl;

    for (nanoka_num_t i = 0; i < 6; ++i)
    {
        auto storage_pos = x->read(i);

        std::cout << "��ѯ����" << i + 1 << ": [";
        for (auto s : storage_pos)
        {
            std::cout << " " << static_cast<nanoka_num_t>(s) << std::flush;
        }
        std::cout << " ]" << std::endl;
    }

    x->full(1);
    x->print_storage();

    // ��ʼ��֤�洢�� API
    for (nanoka_num_t i = 0; i < pr.size(); ++i)
    {
        std::cout << "��ʼ�޸�λ��: " << pr[i] << ", �޸�Ϊ <2,4,7>" << std::endl;
        std::vector<nanoka_storage_t> vec = {2, 4, 7};
        x->alter(i, vec);
        x->print_storage();
        x->full(1);
    }
#endif

#if VALID_LAYER_ARRAY_SPIN_STATUS || VALID_LAYER_ARRAY_FULL_DEBUG
    // ��ʼ������ת API
    x->valid(1);
    x->print_storage();

    for (nanoka_num_t i = 0; i < 4; ++i)
    {
        std::cout << "˳ʱ����ת90��" << std::endl;
        x->route_90(false);
        x->print_storage();
    }
    for (nanoka_num_t i = 0; i < 4; ++i)
    {
        std::cout << "��ʱ����ת90��" << std::endl;
        x->route_90(true);
        x->print_storage();
    }
#endif
}