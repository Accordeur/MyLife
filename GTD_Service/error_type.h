//
// Created by Zelonge on 2021/4/11.
//

#ifndef MYLIFE_ERROR_TYPE_H
#define MYLIFE_ERROR_TYPE_H
#include <cstdint>
enum GTD_RESULT : int32_t {
    GTD_OK = 0,
    GTD_PARA_INVALID,
    GTD_ID_HAS_EXIST,
    GTD_UNKNOWN
};
#endif //MYLIFE_ERROR_TYPE_H
