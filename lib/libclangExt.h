
#ifndef LIBCLANG_EXT_H
#define LIBCLANG_EXT_H

#include "clang-c/Index.h"
#include "clang-c/CXString.h"

#ifdef __cplusplus
extern "C" {
#endif

CXString clang_ext_getOperatorSpelling(CXCursor cursor);

#ifdef __cplusplus
}
#endif

#endif // LIBCLANG_EXT_H

