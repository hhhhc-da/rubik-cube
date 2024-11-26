#ifndef CUBE_ALGORITHM_NANOKA_H
#define CUBE_ALGORITHM_NANOKA_H

#include <rubik_cube.hpp>
#include <rubik_cube_base.hpp>

// �������ǵ���ת�������ƣ����������ڵ������޵Ľǵ��ǲ�����
class Algo_BFS
{
public:
    Algo_BFS() : rc(std::make_shared<Rubik_Cube>(NANOKA_CASE_NUM, NANOKA_LAYER_NUM)), num_pack({0, 0}) {}

    Algo_BFS(Algo_BFS &) = default;
    Algo_BFS(Algo_BFS &&) = default;
    ~Algo_BFS() = default;
    Algo_BFS &operator=(Algo_BFS &) = default;
    Algo_BFS &operator=(Algo_BFS &&) = default;

    // ����ħ�����ϵ�֮��
    nanoka_num_t nanoka_compute_bfs(void);
    // ħ����ʼ�����ʼ��״̬����
    nanoka_status_t nanoka_random_state(nanoka_num_t depth);
    /* BFS ��ѡ�����ı�ʶ��
     * NANOKA_ORDER 0
     * NANOKA_REVERSE 1
     * ���������ڸ���״̬���ڵ�����
     */
    nanoka_status_t nanoka_expand_map(nanoka_num_t direction);
    // ħ���±߽�ȽϺ���, ֻ��Ҫ���µı߽���бȽ�
    nanoka_status_t nanoka_compare_map(void);

private:
    // ħ�����㻺����
    std::shared_ptr<Rubik_Cube> rc;
    // ����ħ����״̬�洢
    nanoka_map_t order_map, reverse_map;
    // ����ħ���Ĳ�����ʶ (���ٷ�����)
    std::vector<nanoka_num_t> num_pack;
};

#endif
