#ifndef VALID_HEADER_NANOKA_H
#define VALID_HEADER_NANOKA_H

#include <cube_algorithm.hpp>
#include <cube_array.hpp>
#include <layer_array.hpp>
#include <rubik_cube.hpp>
#include <rubik_cube_base.hpp>

void valid_layer_array(void);
void _valid_cube_array_reset(std::shared_ptr<Cube_Array> x, nanoka_num_t mode);
void valid_cube_array(void);
void valid_rubik_cube(void);
void valid_cube_algo(void);

#endif
