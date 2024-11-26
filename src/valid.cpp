// ��֤���߰�ͷ�ļ�
#include <valid.hpp>

#define VALID_LAYER_ARRAY_STORAGE_STATUS 0
#define VALID_LAYER_ARRAY_SPIN_STATUS 0
#define VALID_LAYER_ARRAY_SPIN_SET_STATUS 1

// layer_array ��֤���麯��
void valid_layer_array(void)
{
    std::cout << "valid_layer_array ���Ժ�����ʼ����!" << std::endl;
    // ��ʼ��֤�洢��ṹ
    auto x = std::make_shared<Layer_Array>(NANOKA_CASE_NUM * NANOKA_CASE_NUM);

    std::map<nanoka_num_t, const char *> pr = {
        {0, "<1,2>"}, {1, "<2,4>"}, {2, "<4,3>"}, {3, "<3,1>"}};

#if VALID_LAYER_ARRAY_STORAGE_STATUS
    x->valid(1);
    x->print_storage();

    // ���Ի�ȡԪ�� API
    std::vector<nanoka_storage_t> sto = x->get_storage();
    std::cout << "Ԫ�ر���: [";
    for (auto s : sto)
    {
        std::cout << " " << static_cast<nanoka_num_t>(s) << std::flush;
    }
    std::cout << " ]" << std::endl;

    x->full(1);
    x->print_storage();

    // ��ʼ��֤�洢�� API
    for (nanoka_num_t i = 0; i < NANOKA_CASE_NUM * NANOKA_CASE_NUM; ++i)
    {
        std::cout << "��ʼ�޸�λ��: " << pr[i] << ", �޸�Ϊ <2,3>" << std::endl;
        x->alter(i, 2, 3);
        x->print_storage();
        x->full(1);

        std::cout << "��ʼ�޸�λ��: " << pr[i] << ", �޸�Ϊ <5,5>" << std::endl;
        x->alter(i, 5);
        x->print_storage();
        x->full(1);

        std::cout << "��ʼ�޸�λ��: " << pr[i] << ", �޸�Ϊ <2,4>" << std::endl;
        std::vector<nanoka_num_t> vec = {2, 4};
        x->alter(i, vec);
        x->print_storage();
        x->full(1);
    }
#endif

#if VALID_LAYER_ARRAY_SPIN_STATUS
    // ��ʼ������ת API
    x->valid(1);
    x->print_storage();

    for (nanoka_num_t i = 0; i < 4; ++i)
    {
        std::cout << "˳ʱ����ת90��" << std::endl;
        x->route_90(false);
        x->print_storage();
    }
    for (nanoka_num_t i = 0; i < 4; ++i)
    {
        std::cout << "��ʱ����ת90��" << std::endl;
        x->route_90(true);
        x->print_storage();
    }
#endif

#if VALID_LAYER_ARRAY_SPIN_SET_STATUS
    // ��ʼ���ϼ��� API
    x->valid(1);
    x->print_storage();

    nanoka_case_t cases = x->get_all_route_case();
    for (std::vector<nanoka_storage_t> case_m : cases)
    {
        std::cout << "���ϱ���: [";
        for (auto s : case_m)
        {
            std::cout << " " << static_cast<nanoka_num_t>(s) << std::flush;
        }
        std::cout << " ]" << std::endl;
    }
#endif
}