#include <cube_algorithm.hpp>

nanoka_num_t Algo_BFS::nanoka_compute_bfs(void)
{
    try
    {
        // �������Ȼ�ȡ���ǵĳ�ʼ״̬
        nanoka_random_state(5);

        // ��ʼά�����ǵ�״̬��
        
    }
    catch (std::runtime_error e)
    {
        std::cerr << "(Algo_BFS::nanoka_compute_bfs) Runtime_error: " << e.what() << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    catch (...)
    {
        std::cerr << "(Algo_BFS::nanoka_compute_bfs) Unknown_error: Process crushed." << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    return static_cast<nanoka_num_t>(NANOKA_FAILURE);
}

nanoka_status_t Algo_BFS::nanoka_random_state(nanoka_num_t depth)
{
    try
    {
        // ��һ�����������ʼ��������һ��������ͨ��ʼ��
        nanoka_status_t ret = reverse_rc->rubik_random_state_generator(depth);
        if (ret == NANOKA_ERROR)
            throw std::runtime_error("(Algo_BFS::nanoka_random_state) reverse_rc->rubik_random_state_generator failed.");

        ret = order_rc->rubik_reset();
        if (ret == NANOKA_ERROR)
            throw std::runtime_error("(Algo_BFS::nanoka_random_state) order_rc->rubik_reset failed.");

        num_pack.clear();
        for (nanoka_num_t i; i < 2; ++i)
            num_pack.emplace_back(0);

        return NANOKA_SUCCESS;
    }
    catch (std::runtime_error e)
    {
        std::cerr << "(Algo_BFS::nanoka_random_state) Runtime_error: " << e.what() << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    catch (...)
    {
        std::cerr << "(Algo_BFS::nanoka_random_state) Unknown_error: Process crushed." << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    return NANOKA_ERROR;
}