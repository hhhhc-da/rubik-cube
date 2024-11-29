#include <valid.hpp>

// ���ֵ��Ժ궨��
#define FULL_DEBUG_MODE NANOKA_MODE

#if NANOKA_MODE
// ���Ժ궨��
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
    // �����ô���
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
    // ��ʽ���̴���
    std::shared_ptr<Algo_BFS> x = std::make_shared<Algo_BFS>();

    std::cout << "�����ħ������ 7 ��" << std::endl;
    nanoka_num_t result = x->nanoka_compute_bfs(7);
    std::cout << "���ħ���������ת����Ϊ " << result << " ��" << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    // ʹ��ʱ��: 1.275s
    std::cout << "ʹ��ʱ��: " << std::fixed << std::setprecision(3) << duration.count() << "s" << std::endl;
#endif

    system("pause");
    return 0;
}
