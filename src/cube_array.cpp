#include <cube_array.hpp>

// ħ����ʼ������
nanoka_status_t Cube_Array::cube_init(void)
{
    try
    {
        // ����У��
        if (cube_storage.size() != layer_num)
            throw std::runtime_error("cube_storage.size() != layer_num");

        // ��ÿ��ƽ����������ݶ�����
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
    // ���³�ʼ����ʵ�ָ�λ (�ҿ���������ָ��)
    cube_init();
}

// ħ����亯�� (ʹ�� nanoka_num_t �������ݱ�ʾ��ɫ)
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

// ħ����֤����
nanoka_status_t Cube_Array::cube_valid(nanoka_num_t start_color)
{
    try
    {
        // ����У��
        if (cube_storage.size() != layer_num)
            throw std::runtime_error("cube_storage.size() != layer_num");

        // ��ÿ��ƽ����������ݶ�����
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

// ħ����ʽ���������
nanoka_status_t Cube_Array::cube_print(void)
{
    try
    {
        // ����У��
        if (cube_storage.size() != layer_num)
            throw std::runtime_error("cube_storage.size() != layer_num");

        std::map<nanoka_num_t, const char *> pr = {
            {0, "Top"}, {1, "Left"}, {2, "Front"}, {3, "Right"}, {4, "Back"}, {5, "Bottom"}};

        // ��ÿ��ƽ����������ݶ�����
        for (nanoka_num_t i = 0; i < layer_num; ++i)
        {
            std::cout << "�����Ϊ: [ " << pr[i] << " ]" << std::endl;
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

// ħ����ת����
nanoka_status_t Cube_Array::cube_move(nanoka_move_t move_type, nanoka_move_enum_t move_step)
{
    // ӳ���
    std::map<std::string, nanoka_num_t> desc = {
        {"Top", 0}, {"Left", 1}, {"Front", 2}, {"Right", 3}, {"Back", 4}, {"Bottom", 5}};

    try
    {
        // ƫ����
        if (move_type == NANOKA_MOVE_YAW)
        {
            // �洢������
            std::vector<std::vector<nanoka_storage_t>> buffer;
            std::vector<std::string> half_buffer = {"Left", "Front", "Right", "Back"};

            for (nanoka_num_t i = 0; i < half_buffer.size(); ++i)
            {
                buffer.push_back(cube_storage.at(desc[half_buffer.at(i)])->read(0));
                if (buffer[buffer.size() - 1].size() == 0)
                    throw std::runtime_error("read data is empty.");
            }

            // ���Լ��
            if (buffer.empty())
                throw std::runtime_error("read buffer is empty.");
            if (buffer.size() != half_buffer.size())
                throw std::runtime_error("buffer.size() != half_buffer.size().");

            // bias ��ʼֵΪ 0 ��ʾ״̬����, ״̬Ӧ�øı�
            nanoka_num_t bias = 0;

            // ˳ʱ����ת 90 ��
            if (move_step == MOVE_POS_90)
            {
                cube_storage.at(desc["Top"])->route_90(false);
                bias = 1;
            }
            // ��ת 180 ��
            else if (move_step == MOVE_180)
            {
                // ��ת����
                for (nanoka_num_t i = 0; i < 2; ++i)
                    cube_storage.at(desc["Top"])->route_90(false);
                bias = 2;
            }
            // ��ʱ����ת 90 ��
            else if (move_step == MOVE_NEG_90)
            {
                cube_storage.at(desc["Top"])->route_90(true);
                bias = 3;
            }
            else
                throw std::runtime_error("nanoka_move_enum_t move_step invalid.");

            // ˳ʱ����ת��Ӧ�ð� Front �������ת�Ƶ� Left ����, Ҳ���Ƕ������ƶ�һ��Ԫ��
            for (nanoka_num_t i = 0; i < half_buffer.size(); ++i)
                cube_storage.at(desc[half_buffer.at(i)])->alter(0, buffer[(i + bias) % buffer.size()]);
        }
        // �����
        else if (move_type == NANOKA_MOVE_ROLL)
        { // �洢������
            std::vector<std::vector<nanoka_storage_t>> buffer;
            // std::vector<std::pair<std::string, nanoka_num_t>> half_buffer = {{"Bottom",0}, {"Left",1}, {"Top",2}, {"Right":3}};
            std::vector<std::string> half_buffer = {"Bottom", "Left", "Top", "Right"};

            for (nanoka_num_t i = 0; i < half_buffer.size(); ++i)
            {
                // ���������Ҫ�Ҹ�, ����Ǽ�����Ľ��
                buffer.push_back(cube_storage.at(desc[half_buffer.at(i)])->read(i));
                if (buffer[buffer.size() - 1].size() == 0)
                    throw std::runtime_error("read data is empty.");
            }

            // ���Լ��
            if (buffer.empty())
                throw std::runtime_error("read buffer is empty.");
            if (buffer.size() != half_buffer.size())
                throw std::runtime_error("buffer.size() != half_buffer.size().");

            // bias ��ʼֵΪ 0 ��ʾ״̬����, ״̬Ӧ�øı�
            nanoka_num_t bias = 0;

            // ˳ʱ����ת 90 ��
            if (move_step == MOVE_POS_90)
            {
                cube_storage.at(desc["Front"])->route_90(false);
                bias = 1;
            }
            // ��ת 180 ��
            else if (move_step == MOVE_180)
            {
                // ��ת����
                for (nanoka_num_t i = 0; i < 2; ++i)
                    cube_storage.at(desc["Front"])->route_90(false);
                bias = 2;
            }
            // ��ʱ����ת 90 ��
            else if (move_step == MOVE_NEG_90)
            {
                cube_storage.at(desc["Front"])->route_90(true);
                bias = 3;
            }
            else
                throw std::runtime_error("nanoka_move_enum_t move_step invalid.");

            // ˳ʱ����ת��Ӧ�ð� Front �������ת�Ƶ� Left ����, Ҳ���Ƕ������ƶ�һ��Ԫ��
            for (nanoka_num_t i = 0; i < half_buffer.size(); ++i)
            {
                nanoka_num_t p = (i + buffer.size() - bias) % buffer.size();
                cube_storage.at(desc[half_buffer.at(i)])->alter(i, buffer[p]);
            }
        }
        // ������
        else if (move_type == NANOKA_MOVE_PITCH)
        {
            // �洢������
            std::vector<std::vector<nanoka_storage_t>> buffer;
            std::vector<std::pair<std::string, nanoka_num_t>> half_buffer = {
                {"Bottom", 3}, {"Back", 1}, {"Top", 3}, {"Front", 3}};

            for (nanoka_num_t i = 0; i < half_buffer.size(); ++i)
            {
                buffer.push_back(cube_storage.at(desc[half_buffer.at(i).first])->read(half_buffer.at(i).second));
                if (buffer[buffer.size() - 1].size() == 0)
                    throw std::runtime_error("read data is empty.");
            }

            // ���Լ��
            if (buffer.empty())
                throw std::runtime_error("read buffer is empty.");
            if (buffer.size() != half_buffer.size())
                throw std::runtime_error("buffer.size() != half_buffer.size().");

            // bias ��ʼֵΪ 0 ��ʾ״̬����, ״̬Ӧ�øı�
            nanoka_num_t bias = 0;

            // ˳ʱ����ת 90 ��
            if (move_step == MOVE_POS_90)
            {
                cube_storage.at(desc["Left"])->route_90(false);
                bias = 1;
            }
            // ��ת 180 ��
            else if (move_step == MOVE_180)
            {
                // ��ת����
                for (nanoka_num_t i = 0; i < 2; ++i)
                    cube_storage.at(desc["Left"])->route_90(false);
                bias = 2;
            }
            // ��ʱ����ת 90 ��
            else if (move_step == MOVE_NEG_90)
            {
                cube_storage.at(desc["Left"])->route_90(true);
                bias = 3;
            }
            else
                throw std::runtime_error("nanoka_move_enum_t move_step invalid.");

            // ˳ʱ����ת��Ӧ�ð� Front �������ת�Ƶ� Left ����, Ҳ���Ƕ������ƶ�һ��Ԫ��
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

// ħ���������ͳ�ƺ���
nanoka_statistic_t Cube_Array::cube_count(void)
{
    // �������Ļ�����ֵ
    std::map<nanoka_num_t, nanoka_num_t> map_buffer;
    // ���������Ѿ���¼��ȥ������
    std::vector<nanoka_num_t> index_buffer;

    try
    {
        // ͳ�Ʋ�ͬ�����, ����Ҫ��������Ƿ��� Map ��
        for (nanoka_num_t i = 0; i < layer_num; ++i)
        {
            std::vector<nanoka_storage_t> buf = cube_storage.at(i)->get_storage();
            for (auto unit : buf)
            {
                nanoka_num_t color = static_cast<nanoka_num_t>(unit);
                // ���������û���ҵ��������, ��ô���ǾͲ���������
                if (std::find_if(index_buffer.begin(), index_buffer.end(), [&](nanoka_num_t x)
                                 { return x == color; }) == index_buffer.end())
                    map_buffer[color] = 1;
                else
                    map_buffer[color] += 1;
            }
        }

        // ����Ҫ�������ǵĸ����Ƿ����
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

// Ĭ�Ϲ��캯��
Cube_Array::Cube_Array() : cube_num(NANOKA_CASE_NUM), layer_num(NANOKA_LAYER_NUM)
{
    // ����ָ��ͷ
    for (nanoka_num_t i = 0; i < NANOKA_LAYER_NUM; ++i)
        cube_storage.push_back(std::make_shared<Layer_Array>(NANOKA_CASE_NUM * NANOKA_CASE_NUM));
    cube_init();
}

// ��һ��ֵ���캯��
Cube_Array::Cube_Array(nanoka_num_t cube) : cube_num(cube), layer_num(6)
{
    for (nanoka_num_t i = 0; i < NANOKA_LAYER_NUM; ++i)
        cube_storage.push_back(std::make_shared<Layer_Array>(cube * cube));
    cube_init();
}

// ȫ����ֵ���캯��
Cube_Array::Cube_Array(nanoka_num_t cube, nanoka_num_t layer) : cube_num(cube), layer_num(layer)
{
    for (nanoka_num_t i = 0; i < layer; ++i)
        cube_storage.push_back(std::make_shared<Layer_Array>(cube * cube));
    cube_init();
}