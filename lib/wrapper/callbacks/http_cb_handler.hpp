#ifndef _HTTP_CB_HANDLER_
#define _HTTP_CB_HANDLER_

#include <napi.h>

constexpr int MAX_FUNCS_NUM = 20;
constexpr int MAX_FUNCS_POST = MAX_FUNCS_NUM;
constexpr int MAX_FUNCS_GET = MAX_FUNCS_NUM;

// HTTP_POST
typedef int (*HttpPostRefType)(const char *, ...);

HttpPostRefType returnHttpPostReference(Napi::Function fun);

#define MAKE_HTTP_POST_VARIABLE(n) \
    static Napi::FunctionReference httpPostFunRef##n;

// HTTP_GET
typedef void *(*HttpGetRefType)(const char *);

HttpGetRefType returnHttpGetReference(Napi::Function fun);

#define MAKE_HTTP_GET_VARIABLE(n) \
    static Napi::FunctionReference httpGetFunRef##n;

#endif