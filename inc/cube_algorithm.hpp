#ifndef CUBE_ALGORITHM_NANOKA_H
#define CUBE_ALGORITHM_NANOKA_H

#include <rubik_cube.hpp>
#include <rubik_cube_base.hpp>

// 由于我们的旋转函数限制，所以我们在第六卦限的角点是不动的
class Algo_BFS
{
public:
    Algo_BFS() : order_rc(std::make_shared<Rubik_Cube>(NANOKA_CASE_NUM, NANOKA_LAYER_NUM)), reverse_rc(std::make_shared<Rubik_Cube>(NANOKA_CASE_NUM, NANOKA_LAYER_NUM)), num_pack({0, 0}) {}

    Algo_BFS(Algo_BFS &) = default;
    Algo_BFS(Algo_BFS &&) = default;
    ~Algo_BFS() = default;
    Algo_BFS &operator=(Algo_BFS &) = default;
    Algo_BFS &operator=(Algo_BFS &&) = default;

    // 计算魔方的上帝之数
    nanoka_num_t nanoka_compute_bfs(void);
    // 魔方开始随机初始化状态函数
    nanoka_status_t nanoka_random_state(nanoka_num_t depth);

private:
    // 两个魔方存储体
    std::shared_ptr<Rubik_Cube> order_rc, reverse_rc;
    // 两个魔方的状态存储
    std::map<nanoka_num_t, std::vector<nanoka_storage_t>> order_map, reverse_map;
    // 两个魔方的层数标识
    std::vector<nanoka_num_t> num_pack;
};

#endif
