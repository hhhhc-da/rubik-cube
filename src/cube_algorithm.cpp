#include <cube_algorithm.hpp>

nanoka_num_t Algo_BFS::nanoka_compute_bfs(nanoka_num_t depth)
{
#if NANOKA_MODE
    try
    {
#endif
        // �������Ȼ�ȡ���ǵĳ�ʼ״̬
        nanoka_status_t ret = nanoka_random_state(depth);
#if NANOKA_MODE
        if (ret == NANOKA_ERROR)
            throw std::runtime_error("nanoka_random_state failed.");
#endif
        std::map<nanoka_num_t, nanoka_num_t> dir = {
            {0, NANOKA_ORDER}, {1, NANOKA_REVERSE}};

        // ��ʱ�жϱ���
        nanoka_num_t time_out = 100;
        // �������Ǽ��һ���Ƿ�һ��ʼ���ǶԵ�
        while (--time_out)
        {
            std::cout << "ʣ�����: " + std::to_string(time_out) << std::endl;
            // ���ȼ��һ���ǲ��Ǻ��Լ���ͬ
            if (nanoka_equal(order_map[0].at(0), reverse_map[0].at(0)) == NANOKA_SUCCESS)
            {
                std::cout << "ħ�����������״̬" << std::endl;
                return 0;
            }

            for (nanoka_num_t i = 0; i < dir.size(); ++i)
            {
                std::cout << "������Ϣ: order �� " << num_pack.at(0) << ", reverse �� " << num_pack.at(1) << std::endl;

                // ��ʼά�����ǵ�״̬��, ÿ��ά����Ҫ�����ж����
                ret = nanoka_expand_map(dir[i]);
                if (ret == NANOKA_ERROR)
                {
                    // throw std::runtime_error(std::string("nanoka_expand_map (") + ((i == 0) ? "NANOKA_ORDER" : "NANOKA_REVERSE") + std::string(") failed."));
                    std::cout << "����������Ľڵ�" << std::endl;
                    return num_pack.at(0) + num_pack.at(1) + 1;
                }
            }
        }
#if NANOKA_MODE
    }
    catch (std::runtime_error e)
    {
        std::cerr << "(Algo_BFS::nanoka_compute_bfs) Runtime_error: " << e.what() << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    catch (...)
    {
        std::cerr << "(Algo_BFS::nanoka_compute_bfs) Unknown_error: Process crushed." << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
#endif
    return static_cast<nanoka_num_t>(NANOKA_FAILURE);
}

/* BFS ��ѡ�����ı�ʶ��
 * NANOKA_ORDER 0
 * NANOKA_REVERSE 1
 * ���������ڸ���״̬���ڵ�����
 */
nanoka_status_t Algo_BFS::nanoka_expand_map(nanoka_num_t direction)
{
#if NANOKA_MODE
    try
    {
        if (num_pack.size() != 2)
            throw std::runtime_error("num_pack.size() != 2 (size() = " + std::to_string(num_pack.size()) + ")");
#endif
        // ��ϵӳ���
        std::map<nanoka_num_t, nanoka_num_t> ir = {{0, NANOKA_MOVE_YAW}, {1, NANOKA_MOVE_ROLL}, {2, NANOKA_MOVE_PITCH}, {3, NANOKA_MOVE_YAW_2}, {4, NANOKA_MOVE_ROLL_2}, {5, NANOKA_MOVE_PITCH_2}},
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
                        {
                            storage.push_back(buffer);

                            if (nanoka_in(reverse_map[num_pack.at(1)], buffer) == NANOKA_SUCCESS)
                            {
                                std::cout << "���һ�������: " << storage.size() << std::endl;
                                return NANOKA_ERROR;
                            }
                        }
                    }
                }
            }

            num_pack.at(0) += 1;
            order_map[num_pack.at(0)] = storage;
            std::cout << "���������������: [" + std::to_string(storage.size()) + "]" << std::endl;
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
                        {
                            storage.push_back(buffer);

                            if (nanoka_in(order_map[num_pack.at(0)], buffer) == NANOKA_SUCCESS)
                            {
                                std::cout << "���һ�������: " << storage.size() << std::endl;
                                return NANOKA_ERROR;
                            }
                        }
                    }
                }
            }

            num_pack.at(1) += 1;
            reverse_map[num_pack.at(1)] = storage;
            std::cout << "���������������: [" + std::to_string(storage.size()) + "]" << std::endl;
        }
        else
            throw std::runtime_error("nanoka_random_state failed.");

        return NANOKA_SUCCESS;
#if NANOKA_MODE
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
#endif
}

// ħ���±߽�ȽϺ���, ֻ��Ҫ���µı߽���бȽ�
nanoka_status_t Algo_BFS::nanoka_compare_map(void)
{
#if NANOKA_MODE
    try
    {
#endif
        // ����ֱ���ó������ǵ����µ�һ�� MAP ����
        std::vector<std::vector<nanoka_storage_t>> _order = order_map[num_pack.at(0)];
        std::vector<std::vector<nanoka_storage_t>> _reverse = reverse_map[num_pack.at(1)];
#if NANOKA_MODE
        if (_order.size() == 0 || _reverse.size() == 0)
            throw std::runtime_error("_order.size() = " + std::to_string(_order.size()) + ", _reverse.size() = " + std::to_string(_reverse.size()) + ".");
#endif
        for (auto &elem : _order)
        {
            for (auto &elem2 : _reverse)
            {
                if (nanoka_equal(elem, elem2) == NANOKA_SUCCESS)
                    return NANOKA_SUCCESS;
            }
        }
        return NANOKA_ERROR;
#if NANOKA_MODE
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
#endif
}

nanoka_status_t Algo_BFS::nanoka_random_state(nanoka_num_t depth)
{
#if NANOKA_MODE
    try
    {
#endif
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
#if NANOKA_MODE
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
#endif
}