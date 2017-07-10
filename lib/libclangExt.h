
#ifndef LIBCLANG_EXT_H
#define LIBCLANG_EXT_H

#include "clang-c/Index.h"
#include "clang-c/CXString.h"

#ifdef __cplusplus
extern "C" {
#endif

// String representation of operators (unary, binary)
CXString clang_ext_getOperatorSpelling(CXCursor cursor);

// String representation of literals (integer, floating)
CXString clang_ext_getLiteralSpelling(CXCursor cursor);

#ifdef __cplusplus
}
#endif

#endif // LIBCLANG_EXT_H

