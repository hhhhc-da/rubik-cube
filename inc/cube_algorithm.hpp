#ifndef CUBE_BUFFER_NANOKA_H
#define CUBE_BUFFER_NANOKA_H

#include <rubik_cube.hpp>
#include <rubik_cube_base.hpp>

// �������ǵ���ת�������ƣ����������ڵ������޵Ľǵ��ǲ�����
class Algo_BFS
{
public:
    Algo_BFS() : order_rc(std::make_shared<Rubik_Cube>(NANOKA_CASE_NUM, NANOKA_LAYER_NUM);), reverse_rc(std::make_shared<Rubik_Cube>(NANOKA_CASE_NUM, NANOKA_LAYER_NUM);) {}
    
    Algo_BFS(Algo_BFS &) = default;
    Algo_BFS(Algo_BFS &&) = default;
    ~Algo_BFS() = default;
    Algo_BFS &operator=(Algo_BFS &) = default;
    Algo_BFS &operator=(Algo_BFS &&) = default;

    nanoka_num_t nanoka_compute_bfs(void);

private:
    // ����ħ���洢��
    std::shared_ptr<Rubik_Cube> order_rc, reverse_rc;
    // ����ħ����״̬�洢
    std::map<nanoka_num_t, std::vector<nanoka_storage_t>> order_map, reverse_map;
};

#endif
