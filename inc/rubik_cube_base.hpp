#ifndef RUBIK_CUBE_NANOKA_BASE_H
#define RUBIK_CUBE_NANOKA_BASE_H

#include <iostream>
#include <vector>

#include <iterator>
#include <map>
#include <memory>
#include <set>
#include <utility>

#include <cstdlib>

#include <fstream>
#include <sstream>

#include <algorithm>
#include <numeric>

#include <exception>

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>

#include <random>
#include <unistd.h>

/* ����ʹ�õ��Ƕ���ħ��������ħ����ÿ���ĸ�����
 * ͬʱ��ħ��������������壬��������Ĭ��ʹ��������
 * �ڱ�ʾ���ݵ�ʱ�����ǵ��ĸ����ݲ������·�ʽ����
 * | 1 2 | (˳ʱ���������ǵ��ĸ�����)
 * | 4 3 | (����ħ���޶��������鷳һ��)
 * ������ʾ����ʱ�����ǿ������ɵ�ʵ��ħ������ת����
 * ͬʱ������ʹ��һά������д洢����������Ч���������������
 * ����ʹ�ö�̬������ѭ���ṹ����ʾ����
 */

//////////////////////////////////////////////////////////////////////
// ����ħ��
#define NANOKA_CASE_NUM 2
// ��ͨ��������ħ������
#define NANOKA_LAYER_NUM 6
// ������׼����
typedef int nanoka_num_t;
// �洢��׼����
typedef uint8_t nanoka_storage_t;
// �����׼����
typedef std::set<std::vector<nanoka_storage_t>> nanoka_case_t;
// ͳ�ƻ�׼����
typedef std::pair<nanoka_num_t, std::map<nanoka_num_t, nanoka_num_t>> nanoka_statistic_t;

//////////////////////////////////////////////////////////////////////
// ����״̬���ض���
typedef int nanoka_status_t;

#define NANOKA_SUCCESS 0
#define NANOKA_ERROR 1

//////////////////////////////////////////////////////////////////////
// ������ʽ�ض���
typedef int nanoka_move_t;
typedef int nanoka_move_enum_t;

// ˮƽƫת
#define NANOKA_MOVE_YAW 0
// ���Һ��
#define NANOKA_MOVE_ROLL 1
// ǰ�󷭹�
#define NANOKA_MOVE_PITCH 2

// ������ö������
#define MOVE_POS_90 0
#define MOVE_POS_180 1
#define MOVE_NEG_180 1
#define MOVE_180 1
#define MOVE_NEG_90 2

//////////////////////////////////////////////////////////////////////

// ��ȡ Map ������
std::vector<nanoka_num_t> nanoka_get_keys(std::map<nanoka_num_t, nanoka_num_t> &m);
// ��ȡ Map ��ֵ
std::vector<nanoka_num_t> nanoka_get_values(std::map<nanoka_num_t, nanoka_num_t> &m);

#define NANOKA_ANY 0
#define NANOKA_ALL 1

// ��ݱȽϺ���
nanoka_status_t nanoka_equal(std::vector<nanoka_num_t> data, nanoka_num_t value, nanoka_status_t mode);
nanoka_status_t nanoka_equal(std::vector<nanoka_storage_t> data, nanoka_num_t value, nanoka_status_t mode);
nanoka_status_t nanoka_equal(std::vector<nanoka_storage_t> data, std::vector<nanoka_storage_t> data2);

#endif
