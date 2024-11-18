#include <cube_array.hpp>

// 魔方初始化函数
nanoka_status_t Cube_Array::cube_init(void)
{
    try
    {
        // 个数校验
        if (cube_storage.size() != layer_num)
            throw std::runtime_error("cube_storage.size() != layer_num");

        // 将每个平面的所有内容都覆盖
        for (nanoka_num_t i = 0; i < layer_num; ++i)
        {
            nanoka_status_t ret = cube_full(i, i + 1);

            if (ret != NANOKA_SUCCESS)
                throw std::runtime_error("cube_full failed.");
        }
        return NANOKA_SUCCESS;
    }
    catch (std::runtime_error e)
    {
        std::cerr << "(Cube_Array::cube_init) Runtime_error: " << e.what() << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    catch (...)
    {
        std::cerr << "(Cube_Array::cube_init) Unknown_error: Process crushed." << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    return NANOKA_ERROR;
}

nanoka_status_t Cube_Array::cube_reset(void)
{
    // 重新初始化以实现复位 (幸亏用了智能指针)
    cube_init();
}

// 魔方填充函数 (使用 nanoka_num_t 类型数据表示颜色)
nanoka_status_t Cube_Array::cube_full(nanoka_num_t layer, nanoka_num_t color)
{
    try
    {
        nanoka_status_t ret = cube_storage.at(layer)->full(color);

        if (ret != NANOKA_SUCCESS)
            throw std::runtime_error("cube_storage.at(layer)->full(color) failed.");
        return NANOKA_SUCCESS;
    }
    catch (std::runtime_error e)
    {
        std::cerr << "(Cube_Array::cube_full) Runtime_error: " << e.what() << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    catch (...)
    {
        std::cerr << "(Cube_Array::cube_full) Unknown_error: Process crushed." << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    return NANOKA_ERROR;
}

// 魔方验证函数
nanoka_status_t Cube_Array::cube_valid(nanoka_num_t start_color)
{
    try
    {
        // 个数校验
        if (cube_storage.size() != layer_num)
            throw std::runtime_error("cube_storage.size() != layer_num");

        // 将每个平面的所有内容都覆盖
        for (nanoka_num_t i = 0; i < layer_num; ++i)
        {
            nanoka_status_t ret = cube_storage.at(i)->valid(start_color + i);

            if (ret != NANOKA_SUCCESS)
                throw std::runtime_error("cube_storage.at(layer)->full(color) failed.");
        }
        return NANOKA_SUCCESS;
    }
    catch (std::runtime_error e)
    {
        std::cerr << "(Cube_Array::cube_valid) Runtime_error: " << e.what() << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    catch (...)
    {
        std::cerr << "(Cube_Array::cube_valid) Unknown_error: Process crushed." << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    return NANOKA_ERROR;
}

// 魔方格式化输出函数
nanoka_status_t Cube_Array::cube_print(void)
{
    try
    {
        // 个数校验
        if (cube_storage.size() != layer_num)
            throw std::runtime_error("cube_storage.size() != layer_num");

        std::map<nanoka_num_t, const char *> pr = {
            {0, "Top"}, {1, "Left"}, {2, "Front"}, {3, "Right"}, {4, "Back"}, {5, "Bottom"}};

        // 将每个平面的所有内容都覆盖
        for (nanoka_num_t i = 0; i < layer_num; ++i)
        {
            std::cout << "输出面为: [ " << pr[i] << " ]" << std::endl;
            cube_storage.at(i)->print_storage();
        }
        return NANOKA_SUCCESS;
    }
    catch (std::runtime_error e)
    {
        std::cerr << "(Cube_Array::cube_print) Runtime_error: " << e.what() << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    catch (...)
    {
        std::cerr << "(Cube_Array::cube_print) Unknown_error: Process crushed." << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    return NANOKA_ERROR;
}

// 魔方旋转函数
nanoka_status_t Cube_Array::cube_move(nanoka_move_t move_type, nanoka_move_enum_t move_step)
{
    // 映射表
    std::map<std::string, nanoka_num_t> desc = {
        {"Top", 0}, {"Left", 1}, {"Front", 2}, {"Right", 3}, {"Back", 4}, {"Bottom", 5}};

    try
    {
        // 偏航角
        if (move_type == NANOKA_MOVE_YAW)
        {
            // 存储缓冲区
            std::vector<std::vector<nanoka_storage_t>> buffer;
            std::vector<std::string> half_buffer = {"Left", "Front", "Right", "Back"};

            for (nanoka_num_t i = 0; i < half_buffer.size(); ++i)
            {
                buffer.push_back(cube_storage.at(desc[half_buffer.at(i)])->read(0));
                if (buffer[buffer.size() - 1].size() == 0)
                    throw std::runtime_error("read data is empty.");
            }

            // 断言检测
            if (buffer.empty())
                throw std::runtime_error("read buffer is empty.");
            if (buffer.size() != half_buffer.size())
                throw std::runtime_error("buffer.size() != half_buffer.size().");

            // bias 初始值为 0 表示状态不变, 状态应该改变
            nanoka_num_t bias = 0;

            // 顺时针旋转 90 度
            if (move_step == MOVE_POS_90)
            {
                cube_storage.at(desc["Top"])->route_90(false);
                bias = 1;
            }
            // 旋转 180 度
            else if (move_step == MOVE_180)
            {
                // 旋转两次
                for (nanoka_num_t i = 0; i < 2; ++i)
                    cube_storage.at(desc["Top"])->route_90(false);
                bias = 2;
            }
            // 逆时针旋转 90 度
            else if (move_step == MOVE_NEG_90)
            {
                cube_storage.at(desc["Top"])->route_90(true);
                bias = 3;
            }
            else
                throw std::runtime_error("nanoka_move_enum_t move_step invalid.");

            // 顺时针旋转，应该把 Front 面的内容转移到 Left 面中, 也就是对向左移动一组元素
            for (nanoka_num_t i = 0; i < half_buffer.size(); ++i)
                cube_storage.at(desc[half_buffer.at(i)])->alter(0, buffer[(i + bias) % buffer.size()]);
        }
        // 横滚角
        else if (move_type == NANOKA_MOVE_ROLL)
        { // 存储缓冲区
            std::vector<std::vector<nanoka_storage_t>> buffer;
            // std::vector<std::pair<std::string, nanoka_num_t>> half_buffer = {{"Bottom",0}, {"Left",1}, {"Top",2}, {"Right":3}};
            std::vector<std::string> half_buffer = {"Bottom", "Left", "Top", "Right"};

            for (nanoka_num_t i = 0; i < half_buffer.size(); ++i)
            {
                // 这个函数不要乱改, 这个是计算过的结果
                buffer.push_back(cube_storage.at(desc[half_buffer.at(i)])->read(i));
                if (buffer[buffer.size() - 1].size() == 0)
                    throw std::runtime_error("read data is empty.");
            }

            // 断言检测
            if (buffer.empty())
                throw std::runtime_error("read buffer is empty.");
            if (buffer.size() != half_buffer.size())
                throw std::runtime_error("buffer.size() != half_buffer.size().");

            // bias 初始值为 0 表示状态不变, 状态应该改变
            nanoka_num_t bias = 0;

            // 顺时针旋转 90 度
            if (move_step == MOVE_POS_90)
            {
                cube_storage.at(desc["Front"])->route_90(false);
                bias = 1;
            }
            // 旋转 180 度
            else if (move_step == MOVE_180)
            {
                // 旋转两次
                for (nanoka_num_t i = 0; i < 2; ++i)
                    cube_storage.at(desc["Front"])->route_90(false);
                bias = 2;
            }
            // 逆时针旋转 90 度
            else if (move_step == MOVE_NEG_90)
            {
                cube_storage.at(desc["Front"])->route_90(true);
                bias = 3;
            }
            else
                throw std::runtime_error("nanoka_move_enum_t move_step invalid.");

            // 顺时针旋转，应该把 Front 面的内容转移到 Left 面中, 也就是对向左移动一组元素
            for (nanoka_num_t i = 0; i < half_buffer.size(); ++i)
            {
                nanoka_num_t p = (i + buffer.size() - bias) % buffer.size();
                cube_storage.at(desc[half_buffer.at(i)])->alter(i, buffer[p]);
            }
        }
        // 俯仰角
        else if (move_type == NANOKA_MOVE_PITCH)
        {
            // 存储缓冲区
            std::vector<std::vector<nanoka_storage_t>> buffer;
            std::vector<std::pair<std::string, nanoka_num_t>> half_buffer = {
                {"Bottom", 3}, {"Back", 1}, {"Top", 3}, {"Front", 3}};

            for (nanoka_num_t i = 0; i < half_buffer.size(); ++i)
            {
                buffer.push_back(cube_storage.at(desc[half_buffer.at(i).first])->read(half_buffer.at(i).second));
                if (buffer[buffer.size() - 1].size() == 0)
                    throw std::runtime_error("read data is empty.");
            }

            // 断言检测
            if (buffer.empty())
                throw std::runtime_error("read buffer is empty.");
            if (buffer.size() != half_buffer.size())
                throw std::runtime_error("buffer.size() != half_buffer.size().");

            // bias 初始值为 0 表示状态不变, 状态应该改变
            nanoka_num_t bias = 0;

            // 顺时针旋转 90 度
            if (move_step == MOVE_POS_90)
            {
                cube_storage.at(desc["Left"])->route_90(false);
                bias = 1;
            }
            // 旋转 180 度
            else if (move_step == MOVE_180)
            {
                // 旋转两次
                for (nanoka_num_t i = 0; i < 2; ++i)
                    cube_storage.at(desc["Left"])->route_90(false);
                bias = 2;
            }
            // 逆时针旋转 90 度
            else if (move_step == MOVE_NEG_90)
            {
                cube_storage.at(desc["Left"])->route_90(true);
                bias = 3;
            }
            else
                throw std::runtime_error("nanoka_move_enum_t move_step invalid.");

            // 顺时针旋转，应该把 Front 面的内容转移到 Left 面中, 也就是对向左移动一组元素
            for (nanoka_num_t i = 0; i < half_buffer.size(); ++i)
            {
                nanoka_num_t p = (i + buffer.size() - bias) % buffer.size();
                cube_storage.at(desc[half_buffer.at(i).first])->alter(half_buffer.at(i).second, buffer[p]);
            }
        }
        else
            throw std::runtime_error("nanoka_move_t move_type invalid.");

        return NANOKA_SUCCESS;
    }
    catch (std::runtime_error e)
    {
        std::cerr << "(Cube_Array::cube_print) Runtime_error: " << e.what() << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    catch (...)
    {
        std::cerr << "(Cube_Array::cube_print) Unknown_error: Process crushed." << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    return NANOKA_ERROR;
}

// 魔方表面个数统计函数
nanoka_statistic_t Cube_Array::cube_count(void)
{
    // 我们最后的缓存结果值
    std::map<nanoka_num_t, nanoka_num_t> map_buffer;
    // 用来缓存已经记录进去的数据
    std::vector<nanoka_num_t> index_buffer;

    try
    {
        // 统计不同的情况, 首先要检测主键是否在 Map 内
        for (nanoka_num_t i = 0; i < layer_num; ++i)
        {
            std::vector<nanoka_storage_t> buf = cube_storage.at(i)->get_storage();
            for (auto unit : buf)
            {
                nanoka_num_t color = static_cast<nanoka_num_t>(unit);
                // 如果在里面没有找到相关内容, 那么我们就插入新数据
                if (std::find_if(index_buffer.begin(), index_buffer.end(), [&](nanoka_num_t x)
                                 { return x == color; }) == index_buffer.end())
                    map_buffer[color] = 1;
                else
                    map_buffer[color] += 1;
            }
        }

        // 最终要检验我们的个数是否相符
        if (map_buffer.size() != index_buffer.size() || index_buffer.size() != layer_num)
            throw std::runtime_error("map_buffer.size() != index_buffer.size() or index_buffer.size() != layer_num");
    }
    catch (std::runtime_error e)
    {
        index_buffer.clear();
        std::cerr << "(Cube_Array::cube_count) Runtime_error: " << e.what() << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    catch (...)
    {
        index_buffer.clear();
        std::cerr << "(Cube_Array::cube_count) Unknown_error: Process crushed." << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }

    return {index_buffer.size(), map_buffer};
}

// 默认构造函数
Cube_Array::Cube_Array() : cube_num(NANOKA_CASE_NUM), layer_num(NANOKA_LAYER_NUM)
{
    // 拷贝指针头
    for (nanoka_num_t i = 0; i < NANOKA_LAYER_NUM; ++i)
        cube_storage.push_back(std::make_shared<Layer_Array>(NANOKA_CASE_NUM * NANOKA_CASE_NUM));
    cube_init();
}

// 单一传值构造函数
Cube_Array::Cube_Array(nanoka_num_t cube) : cube_num(cube), layer_num(6)
{
    for (nanoka_num_t i = 0; i < NANOKA_LAYER_NUM; ++i)
        cube_storage.push_back(std::make_shared<Layer_Array>(cube * cube));
    cube_init();
}

// 全部传值构造函数
Cube_Array::Cube_Array(nanoka_num_t cube, nanoka_num_t layer) : cube_num(cube), layer_num(layer)
{
    for (nanoka_num_t i = 0; i < layer; ++i)
        cube_storage.push_back(std::make_shared<Layer_Array>(cube * cube));
    cube_init();
}