#include <cube_algorithm.hpp>

nanoka_num_t Algo_BFS::nanoka_compute_bfs(void)
{
    try
    {
        // �������Ȼ�ȡ���ǵĳ�ʼ״̬
        nanoka_status_t ret = nanoka_random_state(6);
        if (ret == NANOKA_ERROR)
            throw std::runtime_error("nanoka_random_state failed.");

        std::map<nanoka_num_t, nanoka_num_t> dir = {
            {0, NANOKA_ORDER}, {1, NANOKA_REVERSE}};

        // ��ʱ�жϱ���
        nanoka_num_t time_out = 20;
        // �������Ǽ��һ���Ƿ�һ��ʼ���ǶԵ�
        while (--time_out)
        {
            std::cout << "��ʼ���ħ��״̬ (ʣ�����: " + std::to_string(time_out) + ")" << std::endl;
            for (nanoka_num_t i = 0; i < dir.size(); ++i)
            {
                std::cout << "������Ϣ: order �� " << num_pack.at(0) << ", reverse �� " << num_pack.at(1) << std::endl;
                ret = nanoka_compare_map();
                // ����������·��, ������ֱ���˳�
                if (ret == NANOKA_SUCCESS)
                {
                    std::cout << "�����������·��" << std::endl;
                    return num_pack.at(0) + num_pack.at(1);
                }

                // ��ʼά�����ǵ�״̬��, ÿ��ά����Ҫ�����ж����
                ret = nanoka_expand_map(dir[i]);
                if (ret == NANOKA_ERROR)
                    throw std::runtime_error(std::string("nanoka_expand_map (") + ((i == 0) ? "NANOKA_ORDER" : "NANOKA_REVERSE") + std::string(") failed."));
            }
        }
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

/* BFS ��ѡ�����ı�ʶ��
 * NANOKA_ORDER 0
 * NANOKA_REVERSE 1
 * ���������ڸ���״̬���ڵ�����
 */
nanoka_status_t Algo_BFS::nanoka_expand_map(nanoka_num_t direction)
{
    try
    {
        if (num_pack.size() != 2)
            throw std::runtime_error("num_pack.size() != 2 (size() = " + std::to_string(num_pack.size()) + ")");

        // ��ϵӳ���
        std::map<nanoka_num_t, nanoka_num_t> ir = {{0, NANOKA_MOVE_YAW}, {1, NANOKA_MOVE_ROLL}, {2, NANOKA_MOVE_PITCH}},
                                             op = {{0, MOVE_POS_90}, {1, MOVE_180}, {2, MOVE_NEG_90}};

        // �ж��������ĸ�����
        if (direction == NANOKA_ORDER) // ��������
        {
            std::cout << "��ʼ��������, ��ʼ��ȡ order_map[" + std::to_string(num_pack.at(0)) + "]" << std::endl;
            std::vector<std::vector<nanoka_storage_t>> &base = order_map[num_pack.at(0)];
            std::vector<std::vector<nanoka_storage_t>> storage;

            for (auto &elem : base)
            {
                for (nanoka_num_t i = 0; i < ir.size(); ++i)
                {
                    for (nanoka_num_t j = 0; j < op.size(); ++j)
                    {
                        // ���Ȼָ�ħ��״̬
                        rc->rubik_write_all(elem);
                        // Ȼ���ħ�����в���
                        rc->rubik_ctrl(i, j);
                        // �����µ������ó����ж��ظ�
                        std::vector<nanoka_storage_t> buffer = rc->rubik_read_all();
                        // ���û���ظ�, ��ô���ǽ�����ӵ���һ������
                        if (nanoka_in(order_map, buffer) != NANOKA_SUCCESS)
                            storage.push_back(buffer);
                    }
                }
            }

            num_pack.at(0) += 1;
            order_map[num_pack.at(0)] = storage;
        }
        else if (direction == NANOKA_REVERSE) // ��������
        {
            std::cout << "��ʼ��������, ��ʼ��ȡ reverse_map[" + std::to_string(num_pack.at(1)) + "]" << std::endl;
            std::vector<std::vector<nanoka_storage_t>> &base = reverse_map[num_pack.at(1)];
            std::vector<std::vector<nanoka_storage_t>> storage;

            for (auto &elem : base)
            {
                for (nanoka_num_t i = 0; i < ir.size(); ++i)
                {
                    for (nanoka_num_t j = 0; j < op.size(); ++j)
                    {
                        // ���Ȼָ�ħ��״̬
                        rc->rubik_write_all(elem);
                        // Ȼ���ħ�����в���
                        rc->rubik_ctrl(i, j);
                        // �����µ������ó����ж��ظ�
                        std::vector<nanoka_storage_t> buffer = rc->rubik_read_all();
                        // ���û���ظ�, ��ô���ǽ�����ӵ���һ������
                        if (nanoka_in(reverse_map, buffer) != NANOKA_SUCCESS)
                            storage.push_back(buffer);
                    }
                }
            }

            num_pack.at(1) += 1;
            reverse_map[num_pack.at(1)] = storage;
        }
        else
            throw std::runtime_error("nanoka_random_state failed.");

        return NANOKA_SUCCESS;
    }
    catch (std::runtime_error e)
    {
        std::cerr << "(Algo_BFS::nanoka_expand_map) Runtime_error: " << e.what() << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    catch (...)
    {
        std::cerr << "(Algo_BFS::nanoka_expand_map) Unknown_error: Process crushed." << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    return NANOKA_ERROR;
}

// ħ���±߽�ȽϺ���, ֻ��Ҫ���µı߽���бȽ�
nanoka_status_t Algo_BFS::nanoka_compare_map(void)
{
    try
    {
        // ����ֱ���ó������ǵ����µ�һ�� MAP ����
        std::vector<std::vector<nanoka_storage_t>> _order = order_map[num_pack.at(0)];
        std::vector<std::vector<nanoka_storage_t>> _reverse = reverse_map[num_pack.at(1)];

        if (_order.size() == 0 || _reverse.size() == 0)
            throw std::runtime_error("_order.size() = " + std::to_string(_order.size()) + ", _reverse.size() = " + std::to_string(_reverse.size()) + ".");

        for (auto &elem : _order)
        {
            for (auto &elem2 : _reverse)
            {
                // std::cout << "��ʼ�Ƚ�:\n[ " << std::flush;
                // for (auto &x : elem)
                //     std::cout << static_cast<nanoka_num_t>(x) << " ";
                // std::cout << "]" << std::endl;
                // std::cout << "[ " << std::flush;
                // for (auto &x : elem2)
                //     std::cout << static_cast<nanoka_num_t>(x) << " ";
                // std::cout << "]" << std::endl;

                if (nanoka_equal(elem, elem2) == NANOKA_SUCCESS)
                    return NANOKA_SUCCESS;
            }
        }
        return NANOKA_ERROR;
    }
    catch (std::runtime_error e)
    {
        std::cerr << "(Algo_BFS::nanoka_compare_map) Runtime_error: " << e.what() << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    catch (...)
    {
        std::cerr << "(Algo_BFS::nanoka_compare_map) Unknown_error: Process crushed." << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    return NANOKA_ERROR;
}

nanoka_status_t Algo_BFS::nanoka_random_state(nanoka_num_t depth)
{
    try
    {
        // �Ȱ���״̬����״̬��, Ȼ�����״̬����״̬��
        nanoka_status_t ret = rc->rubik_reset();
        if (ret == NANOKA_ERROR)
            throw std::runtime_error("rc->rubik_reset failed.");

        std::vector<std::vector<nanoka_storage_t>> o;
        o.push_back(rc->rubik_read_all()); // ���ĳ���������ǳ����һ��
        order_map[0] = o;

        ret = rc->rubik_random_state_generator(depth);
        if (ret == NANOKA_ERROR)
            throw std::runtime_error("rc->rubik_random_state_generator failed.");

        std::vector<std::vector<nanoka_storage_t>> r;
        r.push_back(rc->rubik_read_all()); // ���ĳ���������ǳ����һ��
        reverse_map[0] = r;

        // ��ռ�����
        num_pack = {0, 0};

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