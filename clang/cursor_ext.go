package clang

// #include "../lib/libclangExt.h"
import "C"

func (c Cursor) OperatorSpelling() string {
	o := cxstring{C.clang_ext_getOperatorSpelling(c.c)}
	defer o.Dispose()

	return o.String()
}

func (c Cursor) LiteralSpelling() string {
	o := cxstring{C.clang_ext_getLiteralSpelling(c.c)}
	defer o.Dispose()

	return o.String()
}
