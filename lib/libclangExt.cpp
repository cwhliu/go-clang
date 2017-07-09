
#include "libclangExt.h"

#include "clang/AST/Stmt.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ExprCXX.h"

namespace clang {
  enum CXStringFlag {
    CXS_Unmanaged,
    CXS_Malloc,
    CXS_StringBuf
  };

  const clang::Stmt *getCursorStmt(CXCursor cursor) {
    if (cursor.kind == CXCursor_ObjCSuperClassRef ||
        cursor.kind == CXCursor_ObjCProtocolRef ||
        cursor.kind == CXCursor_ObjCClassRef) {
      return nullptr;
    }

    return static_cast<const clang::Stmt *>(cursor.data[1]);
  };

  const clang::Expr *getCursorExpr(CXCursor cursor) {
    return clang::dyn_cast_or_null<clang::Expr>(getCursorStmt(cursor));
  };

  namespace cxstring {
    CXString createEmpty() {
      CXString str;
      str.data = "";
      str.private_flags = CXS_Unmanaged;
      return str;
    }

    CXString createDup(StringRef string) {
      CXString result;
      char *spelling = static_cast<char *>(malloc(string.size() + 1));
      memmove(spelling, string.data(), string.size());
      spelling[string.size()] = 0;
      result.data = spelling;
      result.private_flags = (unsigned) CXS_Malloc;
      return result;
    }
  };
}

CXString clang_ext_getOperatorSpelling(CXCursor cursor)
{
  if (cursor.kind == CXCursor_BinaryOperator) {
    clang::BinaryOperator *op = (clang::BinaryOperator *) clang::getCursorExpr(cursor);
    return clang::cxstring::createDup(clang::BinaryOperator::getOpcodeStr(op->getOpcode()));
  }

  return clang::cxstring::createEmpty();
}

