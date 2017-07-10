
#include "libclangExt.h"

#include "clang/AST/Stmt.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ExprCXX.h"
#include "llvm/ADT/SmallString.h"

// The following namespace contains duplicated methods in the standard libclang
// that we need but are not exposed.
// -----------------------------------------------------------------------------

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

// Extension starts here
// -----------------------------------------------------------------------------

CXString clang_ext_getOperatorSpelling(CXCursor cursor)
{
  // Unary operator
  if (cursor.kind == CXCursor_UnaryOperator) {
    clang::UnaryOperator *op = (clang::UnaryOperator *) clang::getCursorExpr(cursor);
    return clang::cxstring::createDup(clang::UnaryOperator::getOpcodeStr(op->getOpcode()));
  }

  // Binary operator
  if (cursor.kind == CXCursor_BinaryOperator) {
    clang::BinaryOperator *op = (clang::BinaryOperator *) clang::getCursorExpr(cursor);
    return clang::cxstring::createDup(clang::BinaryOperator::getOpcodeStr(op->getOpcode()));
  }

  return clang::cxstring::createEmpty();
}

CXString clang_ext_getLiteralSpelling(CXCursor cursor)
{
  // Integer literal
  if (cursor.kind == CXCursor_IntegerLiteral) {
    clang::IntegerLiteral *lit = (clang::IntegerLiteral *) clang::getCursorExpr(cursor);
    return clang::cxstring::createDup(lit->getValue().toString(10, true));
  }

  // Floating literal
  if (cursor.kind == CXCursor_FloatingLiteral) {
    clang::FloatingLiteral *lit = (clang::FloatingLiteral *) clang::getCursorExpr(cursor);
    llvm::SmallString<64> str;
    lit->getValue().toString(str);
    return clang::cxstring::createDup(str.c_str());
  }
}

