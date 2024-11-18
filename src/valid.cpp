// 验证工具包头文件
#include <valid.hpp>

#define VALID_MODE 1
#define COMMON_MODE 0

// layer_array 联合编译控制宏定义
#define VALID_LAYER_ARRAY_FULL_DEBUG 0
#define VALID_LAYER_ARRAY_STORAGE_STATUS 0
#define VALID_LAYER_ARRAY_SPIN_STATUS 0
#define VALID_LAYER_ARRAY_SPIN_SET_STATUS 0

// cube_array 联合编译控制宏定义
#define VALID_CUBE_ARRAY_FULL_DEBUG 0
#define VALID_CUBE_ARRAY_STORAGE_STATUS 0
#define VALID_CUBE_ARRAY_STORAGE_MODE COMMON_MODE

#define VALID_CUBE_ARRAY_SPIN_STATUS 0
#define VALID_CUBE_ARRAY_SPIN_YAW_STATUS 0
#define VALID_CUBE_ARRAY_SPIN_ROLL_STATUS 0
#define VALID_CUBE_ARRAY_SPIN_PITCH_STATUS 1

#define VALID_CUBE_ARRAY_STATISTIC_STATUS 1

// rubik_cube 联合编译控制宏定义
#define VALID_RUBIK_CUBE_FULL_DEBUG 0
#define VALID_RUBIK_CUBE_DONE_STATUS 1

// rubik_cube 验证区块函数
void valid_rubik_cube(void){
    std::cout << "valid_rubik_cube 测试函数开始运行!" << std::endl;
    // 开始验证存储体结构
    auto x = std::make_shared<Rubik_Cube>(NANOKA_CASE_NUM, NANOKA_LAYER_NUM);

    std::map<nanoka_num_t, const char *> pr = {
        {NANOKA_SUCCESS, "NANOKA_SUCCESS"}, {NANOKA_ERROR, "NANOKA_ERROR"}};

#if VALID_RUBIK_CUBE_DONE_STATUS || VALID_RUBIK_CUBE_FULL_DEBUG
    nanoka_status_t stt = x->rubik_done();
    std::cout << "查询魔方状态: " << pr[stt] << std::endl;
    x->rubik_check("Left");

    for (nanoka_num_t i = 0; i < 4;++i){
        x->rubik_ctrl(NANOKA_MOVE_YAW, MOVE_POS_90);
        stt = x->rubik_done();
        std::cout << "查询魔方状态: " << pr[stt] << std::endl;
        x->rubik_check("Left");
    }
#endif
}

// 初始化模式选择函数
void _valid_cube_array_reset(std::shared_ptr<Cube_Array> x, nanoka_num_t mode)
{
    if (mode == COMMON_MODE)
        x->cube_reset();
    else if (mode == VALID_MODE)
        x->cube_valid(1);
    else
        throw std::runtime_error("_valid_cube_array_reset param 'mode' is invalid");
}

// cube_array 验证区块函数
void valid_cube_array(void)
{
    std::cout << "valid_cube_array 测试函数开始运行!" << std::endl;
    // 开始验证存储体结构
    auto x = std::make_shared<Cube_Array>(NANOKA_CASE_NUM, NANOKA_LAYER_NUM);
    _valid_cube_array_reset(x, VALID_CUBE_ARRAY_STORAGE_MODE);
    x->cube_print();

#if VALID_CUBE_ARRAY_STATISTIC_STATUS || VALID_CUBE_ARRAY_FULL_DEBUG
    nanoka_statistic_t count = x->cube_count();

    std::cout << "统计后的面数为: " << count.first << std::endl;
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

    std::cout << "开始测试快捷运算函数 nanoka_equal(nanoka_num_t)" << std::endl;
    nanoka_status_t ret = nanoka_equal(m_keys, 0, NANOKA_ANY);
    std::cout << "nanoka_equal(m_keys, 0, NANOKA_ANY) => " << pr[ret] << std::endl;
    
    ret = nanoka_equal(m_keys, 0, NANOKA_ALL);
    std::cout << "nanoka_equal(m_keys, 0, NANOKA_ALL) => " << pr[ret] << std::endl;
    
    ret = nanoka_equal(m_keys, 1, NANOKA_ANY);
    std::cout << "nanoka_equal(m_keys, 1, NANOKA_ANY) => " << pr[ret] << std::endl;
    
    ret = nanoka_equal(m_keys, 1, NANOKA_ALL);
    std::cout << "nanoka_equal(m_keys, 1, NANOKA_ALL) => " << pr[ret] << std::endl;
    
    ret = nanoka_equal(m_values, 4, NANOKA_ANY);
    std::cout << "nanoka_equal(m_values, 4, NANOKA_ANY) => " << pr[ret] << std::endl;
    
    ret = nanoka_equal(m_values, 4, NANOKA_ALL);
    std::cout << "nanoka_equal(m_values, 4, NANOKA_ANY) => " << pr[ret] << std::endl;

    std::cout << "开始测试快捷运算函数 nanoka_equal(nanoka_num_t)" << std::endl;
    // 直接读取 Top 面
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
#endif

#if VALID_CUBE_ARRAY_SPIN_STATUS || VALID_CUBE_ARRAY_FULL_DEBUG
#if VALID_CUBE_ARRAY_SPIN_YAW_STATUS
    // Z 轴旋转
    _valid_cube_array_reset(x, VALID_CUBE_ARRAY_STORAGE_MODE);
    std::cout << "\n对顶面顺时针旋转 90 度" << std::endl;
    x->cube_move(NANOKA_MOVE_YAW, MOVE_POS_90);
    x->cube_print();

    _valid_cube_array_reset(x, VALID_CUBE_ARRAY_STORAGE_MODE);
    std::cout << "\n对顶面旋转 180 度" << std::endl;
    x->cube_move(NANOKA_MOVE_YAW, MOVE_180);
    x->cube_print();

    _valid_cube_array_reset(x, VALID_CUBE_ARRAY_STORAGE_MODE);
    std::cout << "\n对顶面逆时针旋转 90 度" << std::endl;
    x->cube_move(NANOKA_MOVE_YAW, MOVE_NEG_90);
    x->cube_print();
#endif

#if VALID_CUBE_ARRAY_SPIN_ROLL_STATUS
    // Y 轴旋转
    _valid_cube_array_reset(x, VALID_CUBE_ARRAY_STORAGE_MODE);
    std::cout << "\n对前面顺时针旋转 90 度" << std::endl;
    x->cube_move(NANOKA_MOVE_ROLL, MOVE_POS_90);
    x->cube_print();

    _valid_cube_array_reset(x, VALID_CUBE_ARRAY_STORAGE_MODE);
    std::cout << "\n对前面旋转 180 度" << std::endl;
    x->cube_move(NANOKA_MOVE_ROLL, MOVE_180);
    x->cube_print();

    _valid_cube_array_reset(x, VALID_CUBE_ARRAY_STORAGE_MODE);
    std::cout << "\n对前面逆时针旋转 90 度" << std::endl;
    x->cube_move(NANOKA_MOVE_ROLL, MOVE_NEG_90);
    x->cube_print();
#endif

#if VALID_CUBE_ARRAY_SPIN_PITCH_STATUS
    // X 轴旋转
    _valid_cube_array_reset(x, VALID_CUBE_ARRAY_STORAGE_MODE);
    std::cout << "\n对左面顺时针旋转 90 度" << std::endl;
    x->cube_move(NANOKA_MOVE_PITCH, MOVE_POS_90);
    x->cube_print();

    _valid_cube_array_reset(x, VALID_CUBE_ARRAY_STORAGE_MODE);
    std::cout << "\n对左面旋转 180 度" << std::endl;
    x->cube_move(NANOKA_MOVE_PITCH, MOVE_180);
    x->cube_print();

    _valid_cube_array_reset(x, VALID_CUBE_ARRAY_STORAGE_MODE);
    std::cout << "\n对左面逆时针旋转 90 度" << std::endl;
    x->cube_move(NANOKA_MOVE_PITCH, MOVE_NEG_90);
    x->cube_print();
#endif

#endif
}

// layer_array 验证区块函数
void valid_layer_array(void)
{
    std::cout << "valid_layer_array 测试函数开始运行!" << std::endl;
    auto x = std::make_shared<Layer_Array>(NANOKA_CASE_NUM * NANOKA_CASE_NUM);

    std::map<nanoka_num_t, const char *> pr = {
        {0, "<1,2>"}, {1, "<2,4>"}, {2, "<4,3>"}, {3, "<3,1>"}};

#if VALID_LAYER_ARRAY_STORAGE_STATUS || VALID_LAYER_ARRAY_FULL_DEBUG
    x->valid(1);
    x->print_storage();

    // 测试获取元素 API
    std::vector<nanoka_storage_t> sto = x->get_storage();
    std::cout << "元素遍历0: [";
    for (auto s : sto)
    {
        std::cout << " " << static_cast<nanoka_num_t>(s) << std::flush;
    }
    std::cout << " ]" << std::endl;

    for (nanoka_num_t i = 0; i < 4; ++i)
    {
        auto storage_pos = x->read(i);

        std::cout << "查询遍历" << i + 1 << ": [";
        for (auto s : storage_pos)
        {
            std::cout << " " << static_cast<nanoka_num_t>(s) << std::flush;
        }
        std::cout << " ]" << std::endl;
    }

    x->full(1);
    x->print_storage();

    // 开始验证存储体 API
    for (nanoka_num_t i = 0; i < NANOKA_CASE_NUM * NANOKA_CASE_NUM; ++i)
    {
        std::cout << "开始修改位置: " << pr[i] << ", 修改为 <2,3>" << std::endl;
        x->alter(i, 2, 3);
        x->print_storage();
        x->full(1);

        std::cout << "开始修改位置: " << pr[i] << ", 修改为 <5,5>" << std::endl;
        x->alter(i, 5);
        x->print_storage();
        x->full(1);

        std::cout << "开始修改位置: " << pr[i] << ", 修改为 <2,4>" << std::endl;
        std::vector<nanoka_storage_t> vec = {2, 4};
        x->alter(i, vec);
        x->print_storage();
        x->full(1);
    }
#endif

#if VALID_LAYER_ARRAY_SPIN_STATUS || VALID_LAYER_ARRAY_FULL_DEBUG
    // 开始测试旋转 API
    x->valid(1);
    x->print_storage();

    for (nanoka_num_t i = 0; i < 4; ++i)
    {
        std::cout << "顺时针旋转90度" << std::endl;
        x->route_90(false);
        x->print_storage();
    }
    for (nanoka_num_t i = 0; i < 4; ++i)
    {
        std::cout << "逆时针旋转90度" << std::endl;
        x->route_90(true);
        x->print_storage();
    }
#endif

#if VALID_LAYER_ARRAY_SPIN_SET_STATUS || VALID_LAYER_ARRAY_FULL_DEBUG
    // 开始集合计算 API
    x->valid(1);
    x->print_storage();

    nanoka_case_t cases = x->get_all_route_case();
    for (std::vector<nanoka_storage_t> case_m : cases)
    {
        std::cout << "集合遍历: [";
        for (auto s : case_m)
        {
            std::cout << " " << static_cast<nanoka_num_t>(s) << std::flush;
        }
        std::cout << " ]" << std::endl;
    }
#endif
}