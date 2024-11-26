// ��֤���߰�ͷ�ļ�
#include <valid.hpp>

// layer_array ���ϱ�����ƺ궨��
#define VALID_LAYER_ARRAY_FULL_DEBUG 0
#define VALID_LAYER_ARRAY_STORAGE_STATUS 0
#define VALID_LAYER_ARRAY_SPIN_STATUS 0
#define VALID_LAYER_ARRAY_SPIN_SET_STATUS 0

// cube_array ���ϱ�����ƺ궨��
#define VALID_CUBE_ARRAY_FULL_DEBUG 0
#define VALID_CUBE_ARRAY_STORAGE_STATUS 0
#define VALID_MODE 1
#define COMMON_MODE 0
#define VALID_CUBE_ARRAY_STORAGE_MODE COMMON_MODE

#define VALID_CUBE_ARRAY_SPIN_STATUS 1
#define VALID_CUBE_ARRAY_SPIN_YAW_STATUS 0
#define VALID_CUBE_ARRAY_SPIN_ROLL_STATUS 0
#define VALID_CUBE_ARRAY_SPIN_PITCH_STATUS 1

// rubik_cube_base ���ϱ�����ƺ궨��
#define VALID_RUBIK_CUBE_BASE_FULL_DEBUG 0
#define VALID_RUBIK_CUBE_BASE_MAP_FUNC_STATUS 1

// rubik_cube ���ϱ�����ƺ궨��
#define VALID_RUBIK_CUBE_FULL_DEBUG 0

// // rubik_cube ��֤���麯��
// void valid_rubik_cube(void){
//     std::cout << "valid_rubik_cube ���Ժ�����ʼ����!" << std::endl;
//     // ��ʼ��֤�洢��ṹ
//     // auto x = std::make_shared<Layer_Array>(NANOKA_CASE_NUM * NANOKA_CASE_NUM);
// }

// cube_array_base ��֤���麯��
void valid_cube_array_base(void)
{
    std::map<nanoka_num_t, nanoka_num_t> m = {
        {1, 67}, {2, 45}, {4, 21}, {3, 98}};

    std::vector<nanoka_num_t> m_keys = nanoka_get_keys(m);

    std::cout << "Keys: [ " << std::flush;
    for (auto &x : m_keys)
    {
        std::cout << x << " ";
    }
    std::cout << "]" << std::endl;

    std::vector<nanoka_num_t> m_values = nanoka_get_values(m);

    std::cout << "Values: [ " << std::flush;
    for (auto &x : m_values)
    {
        std::cout << x << " ";
    }
    std::cout << "]" << std::endl;
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

#if VALID_CUBE_ARRAY_STORAGE_STATUS || VALID_CUBE_ARRAY_FULL_DEBUG
    std::vector<nanoka_num_t> vec = {2, 8, 3, 5, 4, 7};

    for (nanoka_num_t i = 0; i < vec.size(); ++i)
    {
        x->cube_full(i, vec.at(i));
    }
    x->cube_print();
#endif

#if VALID_CUBE_ARRAY_SPIN_STATUS || VALID_CUBE_ARRAY_FULL_DEBUG
#if VALID_CUBE_ARRAY_SPIN_YAW_STATUS
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

#if VALID_CUBE_ARRAY_SPIN_ROLL_STATUS
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

#if VALID_CUBE_ARRAY_SPIN_PITCH_STATUS
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

#endif
}

// layer_array ��֤���麯��
void valid_layer_array(void)
{
    std::cout << "valid_layer_array ���Ժ�����ʼ����!" << std::endl;
    auto x = std::make_shared<Layer_Array>(NANOKA_CASE_NUM * NANOKA_CASE_NUM);

    std::map<nanoka_num_t, const char *> pr = {
        {0, "<1,2>"}, {1, "<2,4>"}, {2, "<4,3>"}, {3, "<3,1>"}};

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

    for (nanoka_num_t i = 0; i < 4; ++i)
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
    for (nanoka_num_t i = 0; i < NANOKA_CASE_NUM * NANOKA_CASE_NUM; ++i)
    {
        std::cout << "��ʼ�޸�λ��: " << pr[i] << ", �޸�Ϊ <2,3>" << std::endl;
        x->alter(i, 2, 3);
        x->print_storage();
        x->full(1);

        std::cout << "��ʼ�޸�λ��: " << pr[i] << ", �޸�Ϊ <5,5>" << std::endl;
        x->alter(i, 5);
        x->print_storage();
        x->full(1);

        std::cout << "��ʼ�޸�λ��: " << pr[i] << ", �޸�Ϊ <2,4>" << std::endl;
        std::vector<nanoka_storage_t> vec = {2, 4};
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

#if VALID_LAYER_ARRAY_SPIN_SET_STATUS || VALID_LAYER_ARRAY_FULL_DEBUG
    // ��ʼ���ϼ��� API
    x->valid(1);
    x->print_storage();

    nanoka_case_t cases = x->get_all_route_case();
    for (std::vector<nanoka_storage_t> case_m : cases)
    {
        std::cout << "���ϱ���: [";
        for (auto s : case_m)
        {
            std::cout << " " << static_cast<nanoka_num_t>(s) << std::flush;
        }
        std::cout << " ]" << std::endl;
    }
#endif
}