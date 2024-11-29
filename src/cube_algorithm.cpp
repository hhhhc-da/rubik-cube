#include <cube_algorithm.hpp>

nanoka_num_t Algo_BFS::nanoka_compute_bfs(nanoka_num_t depth)
{
#if NANOKA_MODE
    try
    {
#endif
        // 我们首先获取我们的初始状态
        nanoka_status_t ret = nanoka_random_state(depth);
#if NANOKA_MODE
        if (ret == NANOKA_ERROR)
            throw std::runtime_error("nanoka_random_state failed.");
#endif
        std::map<nanoka_num_t, nanoka_num_t> dir = {
            {0, NANOKA_ORDER}, {1, NANOKA_REVERSE}};

        // 超时判断变量
        nanoka_num_t time_out = 100;
        // 首先我们检查一下是否一开始就是对的
        while (--time_out)
        {
            std::cout << "剩余次数: " + std::to_string(time_out) << std::endl;
            // 首先检测一下是不是和自己相同
            if (nanoka_equal(order_map[0].at(0), reverse_map[0].at(0)) == NANOKA_SUCCESS)
            {
                std::cout << "魔方本就是完好状态" << std::endl;
                return 0;
            }

            for (nanoka_num_t i = 0; i < dir.size(); ++i)
            {
                std::cout << "层数信息: order 层 " << num_pack.at(0) << ", reverse 层 " << num_pack.at(1) << std::endl;

                // 开始维护我们的状态表, 每次维护后都要重新判断相等
                ret = nanoka_expand_map(dir[i]);
                if (ret == NANOKA_ERROR)
                {
                    // throw std::runtime_error(std::string("nanoka_expand_map (") + ((i == 0) ? "NANOKA_ORDER" : "NANOKA_REVERSE") + std::string(") failed."));
                    std::cout << "发现了最近的节点" << std::endl;
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

/* BFS 中选择插入的标识有
 * NANOKA_ORDER 0
 * NANOKA_REVERSE 1
 * 本函数用于更新状态表内的数据
 */
nanoka_status_t Algo_BFS::nanoka_expand_map(nanoka_num_t direction)
{
#if NANOKA_MODE
    try
    {
        if (num_pack.size() != 2)
            throw std::runtime_error("num_pack.size() != 2 (size() = " + std::to_string(num_pack.size()) + ")");
#endif
        // 关系映射表
        std::map<nanoka_num_t, nanoka_num_t> ir = {{0, NANOKA_MOVE_YAW}, {1, NANOKA_MOVE_ROLL}, {2, NANOKA_MOVE_PITCH}, {3, NANOKA_MOVE_YAW_2}, {4, NANOKA_MOVE_ROLL_2}, {5, NANOKA_MOVE_PITCH_2}},
                                             op = {{0, MOVE_POS_90}, {1, MOVE_180}, {2, MOVE_NEG_90}};

        // 判断是增长哪个方向
        if (direction == NANOKA_ORDER) // 正向增长
        {
            std::cout << "开始正向增长, 开始读取 order_map[" + std::to_string(num_pack.at(0)) + "]" << std::endl;
            std::vector<std::vector<nanoka_storage_t>> &base = order_map[num_pack.at(0)];
            std::vector<std::vector<nanoka_storage_t>> storage;

            for (auto &elem : base)
            {
                for (nanoka_num_t i = 0; i < ir.size(); ++i)
                {
                    for (nanoka_num_t j = 0; j < op.size(); ++j)
                    {
                        // 首先恢复魔方状态
                        rc->rubik_write_all(elem);
                        // 然后对魔方进行操作
                        rc->rubik_ctrl(i, j);
                        // 将最新的数据拿出来判断重复
                        std::vector<nanoka_storage_t> buffer = rc->rubik_read_all();
                        // 如果没有重复, 那么我们将他添加到新一个表中
                        if (nanoka_in(order_map, buffer) != NANOKA_SUCCESS)
                        {
                            storage.push_back(buffer);

                            if (nanoka_in(reverse_map[num_pack.at(1)], buffer) == NANOKA_SUCCESS)
                            {
                                std::cout << "最后一层遍历到: " << storage.size() << std::endl;
                                return NANOKA_ERROR;
                            }
                        }
                    }
                }
            }

            num_pack.at(0) += 1;
            order_map[num_pack.at(0)] = storage;
            std::cout << "正向增长插入个数: [" + std::to_string(storage.size()) + "]" << std::endl;
        }
        else if (direction == NANOKA_REVERSE) // 反向增长
        {
            std::cout << "开始反向增长, 开始读取 reverse_map[" + std::to_string(num_pack.at(1)) + "]" << std::endl;
            std::vector<std::vector<nanoka_storage_t>> &base = reverse_map[num_pack.at(1)];
            std::vector<std::vector<nanoka_storage_t>> storage;

            for (auto &elem : base)
            {
                for (nanoka_num_t i = 0; i < ir.size(); ++i)
                {
                    for (nanoka_num_t j = 0; j < op.size(); ++j)
                    {
                        // 首先恢复魔方状态
                        rc->rubik_write_all(elem);
                        // 然后对魔方进行操作
                        rc->rubik_ctrl(i, j);
                        // 将最新的数据拿出来判断重复
                        std::vector<nanoka_storage_t> buffer = rc->rubik_read_all();
                        // 如果没有重复, 那么我们将他添加到新一个表中
                        if (nanoka_in(reverse_map, buffer) != NANOKA_SUCCESS)
                        {
                            storage.push_back(buffer);

                            if (nanoka_in(order_map[num_pack.at(0)], buffer) == NANOKA_SUCCESS)
                            {
                                std::cout << "最后一层遍历到: " << storage.size() << std::endl;
                                return NANOKA_ERROR;
                            }
                        }
                    }
                }
            }

            num_pack.at(1) += 1;
            reverse_map[num_pack.at(1)] = storage;
            std::cout << "反向增长插入个数: [" + std::to_string(storage.size()) + "]" << std::endl;
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

// 魔方新边界比较函数, 只需要对新的边界进行比较
nanoka_status_t Algo_BFS::nanoka_compare_map(void)
{
#if NANOKA_MODE
    try
    {
#endif
        // 我们直接拿出来我们的最新的一层 MAP 即可
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
        // 先把主状态存入状态表, 然后将随机状态存入状态表
        nanoka_status_t ret = rc->rubik_reset();
        if (ret == NANOKA_ERROR)
            throw std::runtime_error("rc->rubik_reset failed.");

        std::vector<std::vector<nanoka_storage_t>> o;
        o.push_back(rc->rubik_read_all()); // 担心出问题所以浅拷贝一份
        order_map[0] = o;

        ret = rc->rubik_random_state_generator(depth);
        if (ret == NANOKA_ERROR)
            throw std::runtime_error("rc->rubik_random_state_generator failed.");

        std::vector<std::vector<nanoka_storage_t>> r;
        r.push_back(rc->rubik_read_all()); // 担心出问题所以浅拷贝一份
        reverse_map[0] = r;

        // 清空计数器
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