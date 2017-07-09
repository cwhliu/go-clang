package clang

// #include "../lib/libclangExt.h"
import "C"

func (c Cursor) OperatorSpelling() string {
	o := cxstring{C.clang_ext_getOperatorSpelling(c.c)}
	defer o.Dispose()

	return o.String()
}
