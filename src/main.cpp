#include <valid.hpp>

// 各种调试宏定义
#define FULL_DEBUG_MODE NANOKA_MODE

#if NANOKA_MODE
// 调试宏定义
#define VALID_LAYER_ARRAY_CONFIG 0
#define VALID_CUBE_ARRAY_CONFIG 0
#define VALID_RUBIK_CUBE_CONFIG 0
#define VALID_CUBE_ALGO_CONFIG 0
#endif

int main(void)
{
    std::cout << "Hello rubik cube!\nAuthor: Nanoka." << std::endl;
#if !NANOKA_MODE
    auto start = std::chrono::high_resolution_clock::now();
#endif

#if NANOKA_MODE
    // 调试用代码
#if VALID_LAYER_ARRAY_CONFIG || FULL_DEBUG_MODE
    valid_layer_array();
#endif

#if VALID_CUBE_ARRAY_CONFIG || FULL_DEBUG_MODE
    valid_cube_array();
#endif

#if VALID_RUBIK_CUBE_CONFIG || FULL_DEBUG_MODE
    valid_rubik_cube();
#endif

#if VALID_CUBE_ALGO_CONFIG || FULL_DEBUG_MODE
    valid_cube_algo();
#endif

#endif

#if !NANOKA_MODE
    // 正式工程代码
    std::shared_ptr<Algo_BFS> x = std::make_shared<Algo_BFS>();

    std::cout << "随机将魔方打乱 7 次" << std::endl;
    nanoka_num_t result = x->nanoka_compute_bfs(7);
    std::cout << "这个魔方的最短旋转次数为 " << result << " 次" << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    // 使用时间: 1.275s
    std::cout << "使用时间: " << std::fixed << std::setprecision(3) << duration.count() << "s" << std::endl;
#endif

    system("pause");
    return 0;
}
