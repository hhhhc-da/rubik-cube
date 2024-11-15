#include "rubik_cube.hpp"

nanoka_status Rubik_Cube::cube_move(nanoka_move_t move_type, nanoka_move_enum_t move_step){
    switch(move_type){
        case NANOKA_MOVE_YAW:
            break;
        case NANOKA_MOVE_ROLL:
            break;
        case NANOKA_MOVE_PITCH:
            break;
        default:
            throw std::runtime_error("nanoka_move_t move_type invalid.");
    }
}