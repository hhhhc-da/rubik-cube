#include <valid.hpp>

// ���ֵ��Ժ궨��
#define FULL_DEBUG_MODE 0
#define VALID_RUBIK_CUBE_BASE_CONFIG 0
#define VALID_LAYER_ARRAY_CONFIG 0
#define VALID_CUBE_ARRAY_CONFIG 0
#define VALID_RUBIK_CUBE_CONFIG 0
#define VALID_CUBE_ALGO_CONFIG 0

int main(void)
{
    std::cout << "Hello rubik cube!\nAuthor: Nanoka." << std::endl;

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

    std::cout << "�����ħ������ 6 ��" << std::endl;
    nanoka_num_t result = x->nanoka_compute_bfs();
    std::cout << "���ħ���������ת����Ϊ " << result << " ��" << std::endl;

    // system("pause");
    return 0;
}
