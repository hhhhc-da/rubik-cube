#ifndef CUBE_ALGORITHM_NANOKA_H
#define CUBE_ALGORITHM_NANOKA_H

#include <rubik_cube.hpp>
#include <rubik_cube_base.hpp>

// �������ǵ���ת�������ƣ����������ڵ������޵Ľǵ��ǲ�����
class Algo_BFS
{
public:
    Algo_BFS() : order_rc(std::make_shared<Rubik_Cube>(NANOKA_CASE_NUM, NANOKA_LAYER_NUM)), reverse_rc(std::make_shared<Rubik_Cube>(NANOKA_CASE_NUM, NANOKA_LAYER_NUM)), num_pack({0, 0}) {}

    Algo_BFS(Algo_BFS &) = default;
    Algo_BFS(Algo_BFS &&) = default;
    ~Algo_BFS() = default;
    Algo_BFS &operator=(Algo_BFS &) = default;
    Algo_BFS &operator=(Algo_BFS &&) = default;

    // ����ħ�����ϵ�֮��
    nanoka_num_t nanoka_compute_bfs(void);
    // ħ����ʼ�����ʼ��״̬����
    nanoka_status_t nanoka_random_state(nanoka_num_t depth);

private:
    // ����ħ���洢��
    std::shared_ptr<Rubik_Cube> order_rc, reverse_rc;
    // ����ħ����״̬�洢
    std::map<nanoka_num_t, std::vector<nanoka_storage_t>> order_map, reverse_map;
    // ����ħ���Ĳ�����ʶ
    std::vector<nanoka_num_t> num_pack;
};

#endif
