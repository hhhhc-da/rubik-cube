#ifndef RUBIK_CUBE_NANOKA_BASE_H
#define RUBIK_CUBE_NANOKA_BASE_H

#include <iostream>
#include <vector>

#include <map>
#include <memory>
#include <set>

#include <cstdlib>

#include <fstream>
#include <sstream>

#include <algorithm>
#include <numeric>

#include <exception>

#include <cstddef>
#include <cstdint>

#include <unistd.h>
#include <random>

#define NANOKA_CASE_NUM 2

// ����״̬���ض���
typedef int nanoka_status;

#define NANOKA_SUCCESS 0
#define NANOKA_ERROR 1

// ������ʽ�ض���
typedef int nanoka_move_t;
// ˮƽƫת
#define NANOKA_MOVE_YAW     0 
// ǰ�󷭹�
#define NANOKA_MOVE_ROLL    1
// ���Һ��
#define NANOKA_MOVE_PITCH   2
// ������ö������
typedef enum
{
    MOVE_POS_90 = 0,
    MOVE_POS_180,
    MOVE_NEG_180,
    MOVE_NEG_90
}
nanoka_move_enum_t;

#endif
