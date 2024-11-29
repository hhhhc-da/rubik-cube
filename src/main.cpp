#include <valid.hpp>

// 各种调试宏定义
#define FULL_DEBUG_MODE 0
#define VALID_LAYER_ARRAY_CONFIG 0
#define VALID_CUBE_ARRAY_CONFIG 0
#define VALID_RUBIK_CUBE_CONFIG 0
#define VALID_CUBE_ALGO_CONFIG 0

int main(void)
{
    std::cout << "Hello rubik cube!\nAuthor: Nanoka." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

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

    std::shared_ptr<Algo_BFS> x = std::make_shared<Algo_BFS>();

    std::cout << "随机将魔方打乱 5 次" << std::endl;
    nanoka_num_t result = x->nanoka_compute_bfs(5);
    std::cout << "这个魔方的最短旋转次数为 " << result << " 次" << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    // 使用时间: 1.275s
    std::cout << "使用时间: " << std::fixed << std::setprecision(3) << duration.count() << "s" << std::endl;

    system("pause");
    return 0;
}
