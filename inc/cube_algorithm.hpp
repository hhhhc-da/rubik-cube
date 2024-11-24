#ifndef CUBE_ALGORITHM_NANOKA_H
#define CUBE_ALGORITHM_NANOKA_H

#include <rubik_cube.hpp>
#include <rubik_cube_base.hpp>

// 由于我们的旋转函数限制，所以我们在第六卦限的角点是不动的
class Algo_BFS
{
public:
    Algo_BFS() : rc(std::make_shared<Rubik_Cube>(NANOKA_CASE_NUM, NANOKA_LAYER_NUM)), num_pack({0, 0}) {}

    Algo_BFS(Algo_BFS &) = default;
    Algo_BFS(Algo_BFS &&) = default;
    ~Algo_BFS() = default;
    Algo_BFS &operator=(Algo_BFS &) = default;
    Algo_BFS &operator=(Algo_BFS &&) = default;

    // 计算魔方的上帝之数
    nanoka_num_t nanoka_compute_bfs(void);
    // 魔方开始随机初始化状态函数
    nanoka_status_t nanoka_random_state(nanoka_num_t depth);
    /* BFS 中选择插入的标识有
     * NANOKA_ORDER 0
     * NANOKA_REVERSE 1
     * 本函数用于更新状态表内的数据
     */
    nanoka_status_t nanoka_expand_map(nanoka_num_t direction);
    // 魔方新边界比较函数, 只需要对新的边界进行比较
    nanoka_status_t nanoka_compare_map(void);

private:
    // 魔方运算缓冲区
    std::shared_ptr<Rubik_Cube> rc;
    // 两个魔方的状态存储
    nanoka_map_t order_map, reverse_map;
    // 两个魔方的层数标识 (快速访问用)
    std::vector<nanoka_num_t> num_pack;
};

#endif
