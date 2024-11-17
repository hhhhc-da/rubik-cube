// 验证工具包头文件
#include <valid.hpp>

#define STORAGE_STATUS      0
#define SPIN_STATUS         1

// layer_array 验证区块函数
void valid_layer_array(void)
{
    std::cout << "valid_layer_array 测试函数开始运行!" << std::endl;
    // 开始验证存储体结构
    auto x = std::make_shared<Layer_Array>(NANOKA_CASE_NUM * NANOKA_CASE_NUM);

    std::map<nanoka_num_t, const char *> pr = {
        {0, "<1,2>"}, {1, "<2,4>"}, {2, "<4,3>"}, {3, "<3,1>"}};

#if STORAGE_STATUS

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
        std::vector<nanoka_num_t> vec = {2, 4};
        x->alter(i, vec);
        x->print_storage();
        x->full(1);
    }
#endif

#if SPIN_STATUS
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
}