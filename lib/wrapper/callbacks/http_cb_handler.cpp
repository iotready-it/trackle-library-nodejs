#include <iostream>
#include <cstdint>

#include "trackle.h"
#include "protocol_defs.h"
#include "http_cb_handler.hpp"

// HTTP_POST
static int indexHttpPost = 0;
static std::array<const Napi::FunctionReference *, MAX_FUNCS_POST> httpPostRefFunctionList;

MAKE_HTTP_POST_VARIABLE(0)
MAKE_HTTP_POST_VARIABLE(1)
MAKE_HTTP_POST_VARIABLE(2)
MAKE_HTTP_POST_VARIABLE(3)
MAKE_HTTP_POST_VARIABLE(4)
MAKE_HTTP_POST_VARIABLE(5)
MAKE_HTTP_POST_VARIABLE(6)
MAKE_HTTP_POST_VARIABLE(7)
MAKE_HTTP_POST_VARIABLE(8)
MAKE_HTTP_POST_VARIABLE(9)
MAKE_HTTP_POST_VARIABLE(10)
MAKE_HTTP_POST_VARIABLE(11)
MAKE_HTTP_POST_VARIABLE(12)
MAKE_HTTP_POST_VARIABLE(13)
MAKE_HTTP_POST_VARIABLE(14)
MAKE_HTTP_POST_VARIABLE(15)
MAKE_HTTP_POST_VARIABLE(16)
MAKE_HTTP_POST_VARIABLE(17)
MAKE_HTTP_POST_VARIABLE(18)
MAKE_HTTP_POST_VARIABLE(19)

// FIXME: Sistemare il passaggio dei parametri variadici. Quali sono? Come mi arrivano? Come li passo?
#define MAKE_HTTP_POST_FUNCTION(n)                                                             \
    int httpPostFunctionCaller##n(const char *args, ...)                                       \
    {                                                                                          \
        Napi::Env env = httpPostRefFunctionList[n]->Env();                                     \
        Napi::Value result = httpPostRefFunctionList[n]->Call({Napi::String::New(env, args)}); \
        return result.ToNumber().Uint32Value();                                                \
    }

MAKE_HTTP_POST_FUNCTION(0)
MAKE_HTTP_POST_FUNCTION(1)
MAKE_HTTP_POST_FUNCTION(2)
MAKE_HTTP_POST_FUNCTION(3)
MAKE_HTTP_POST_FUNCTION(4)
MAKE_HTTP_POST_FUNCTION(5)
MAKE_HTTP_POST_FUNCTION(6)
MAKE_HTTP_POST_FUNCTION(7)
MAKE_HTTP_POST_FUNCTION(8)
MAKE_HTTP_POST_FUNCTION(9)
MAKE_HTTP_POST_FUNCTION(10)
MAKE_HTTP_POST_FUNCTION(11)
MAKE_HTTP_POST_FUNCTION(12)
MAKE_HTTP_POST_FUNCTION(13)
MAKE_HTTP_POST_FUNCTION(14)
MAKE_HTTP_POST_FUNCTION(15)
MAKE_HTTP_POST_FUNCTION(16)
MAKE_HTTP_POST_FUNCTION(17)
MAKE_HTTP_POST_FUNCTION(18)
MAKE_HTTP_POST_FUNCTION(19)

static std::array<HttpPostRefType, MAX_FUNCS_POST> httpPostRefList = {
    httpPostFunctionCaller0,
    httpPostFunctionCaller1,
    httpPostFunctionCaller2,
    httpPostFunctionCaller3,
    httpPostFunctionCaller4,
    httpPostFunctionCaller5,
    httpPostFunctionCaller6,
    httpPostFunctionCaller7,
    httpPostFunctionCaller8,
    httpPostFunctionCaller9,
    httpPostFunctionCaller10,
    httpPostFunctionCaller11,
    httpPostFunctionCaller12,
    httpPostFunctionCaller13,
    httpPostFunctionCaller14,
    httpPostFunctionCaller15,
    httpPostFunctionCaller16,
    httpPostFunctionCaller17,
    httpPostFunctionCaller18,
    httpPostFunctionCaller19};

HttpPostRefType returnHttpPostReference(Napi::Function fun)
{
    if (indexHttpPost >= 0 && indexHttpPost < static_cast<int>(httpPostRefFunctionList.size()))
    {
        switch (indexHttpPost)
        {
        case 0:
            httpPostFunRef0 = Napi::Persistent(fun);
            httpPostFunRef0.SuppressDestruct();
            httpPostRefFunctionList[0] = &httpPostFunRef0;
            break;
        case 1:
            httpPostFunRef1 = Napi::Persistent(fun);
            httpPostFunRef1.SuppressDestruct();
            httpPostRefFunctionList[1] = &httpPostFunRef1;
            break;
        case 2:
            httpPostFunRef2 = Napi::Persistent(fun);
            httpPostFunRef2.SuppressDestruct();
            httpPostRefFunctionList[2] = &httpPostFunRef2;
            break;
        case 3:
            httpPostFunRef3 = Napi::Persistent(fun);
            httpPostFunRef3.SuppressDestruct();
            httpPostRefFunctionList[3] = &httpPostFunRef3;
            break;
        case 4:
            httpPostFunRef4 = Napi::Persistent(fun);
            httpPostFunRef4.SuppressDestruct();
            httpPostRefFunctionList[4] = &httpPostFunRef4;
            break;
        case 5:
            httpPostFunRef5 = Napi::Persistent(fun);
            httpPostFunRef5.SuppressDestruct();
            httpPostRefFunctionList[5] = &httpPostFunRef5;
            break;
        case 6:
            httpPostFunRef6 = Napi::Persistent(fun);
            httpPostFunRef6.SuppressDestruct();
            httpPostRefFunctionList[6] = &httpPostFunRef6;
            break;
        case 7:
            httpPostFunRef7 = Napi::Persistent(fun);
            httpPostFunRef7.SuppressDestruct();
            httpPostRefFunctionList[7] = &httpPostFunRef7;
            break;
        case 8:
            httpPostFunRef8 = Napi::Persistent(fun);
            httpPostFunRef8.SuppressDestruct();
            httpPostRefFunctionList[8] = &httpPostFunRef8;
            break;
        case 9:
            httpPostFunRef9 = Napi::Persistent(fun);
            httpPostFunRef9.SuppressDestruct();
            httpPostRefFunctionList[9] = &httpPostFunRef9;
            break;
        case 10:
            httpPostFunRef10 = Napi::Persistent(fun);
            httpPostFunRef10.SuppressDestruct();
            httpPostRefFunctionList[10] = &httpPostFunRef10;
            break;
        case 11:
            httpPostFunRef11 = Napi::Persistent(fun);
            httpPostFunRef11.SuppressDestruct();
            httpPostRefFunctionList[11] = &httpPostFunRef11;
            break;
        case 12:
            httpPostFunRef12 = Napi::Persistent(fun);
            httpPostFunRef12.SuppressDestruct();
            httpPostRefFunctionList[12] = &httpPostFunRef12;
            break;
        case 13:
            httpPostFunRef13 = Napi::Persistent(fun);
            httpPostFunRef13.SuppressDestruct();
            httpPostRefFunctionList[13] = &httpPostFunRef13;
            break;
        case 14:
            httpPostFunRef14 = Napi::Persistent(fun);
            httpPostFunRef14.SuppressDestruct();
            httpPostRefFunctionList[14] = &httpPostFunRef14;
            break;
        case 15:
            httpPostFunRef15 = Napi::Persistent(fun);
            httpPostFunRef15.SuppressDestruct();
            httpPostRefFunctionList[15] = &httpPostFunRef15;
            break;
        case 16:
            httpPostFunRef0 = Napi::Persistent(fun);
            httpPostFunRef0.SuppressDestruct();
            httpPostRefFunctionList[16] = &httpPostFunRef16;
            break;
        case 17:
            httpPostFunRef17 = Napi::Persistent(fun);
            httpPostFunRef17.SuppressDestruct();
            httpPostRefFunctionList[17] = &httpPostFunRef17;
            break;
        case 18:
            httpPostFunRef18 = Napi::Persistent(fun);
            httpPostFunRef18.SuppressDestruct();
            httpPostRefFunctionList[18] = &httpPostFunRef18;
            break;
        case 19:
            httpPostFunRef19 = Napi::Persistent(fun);
            httpPostFunRef19.SuppressDestruct();
            httpPostRefFunctionList[19] = &httpPostFunRef19;
            break;
        default:
            break;
        }
        const HttpPostRefType func = httpPostRefList[indexHttpPost];
        indexHttpPost++;
        return func;
    }

    return nullptr;
}

// HTTP_GET
static int indexHttpGet = 0;
static constexpr int MAX_BUFF_RESULT_LENGTH = 1024;
static std::array<const Napi::FunctionReference *, MAX_FUNCS_GET> httpGetRefFunctionList;

MAKE_HTTP_GET_VARIABLE(0)
MAKE_HTTP_GET_VARIABLE(1)
MAKE_HTTP_GET_VARIABLE(2)
MAKE_HTTP_GET_VARIABLE(3)
MAKE_HTTP_GET_VARIABLE(4)
MAKE_HTTP_GET_VARIABLE(5)
MAKE_HTTP_GET_VARIABLE(6)
MAKE_HTTP_GET_VARIABLE(7)
MAKE_HTTP_GET_VARIABLE(8)
MAKE_HTTP_GET_VARIABLE(9)
MAKE_HTTP_GET_VARIABLE(10)
MAKE_HTTP_GET_VARIABLE(11)
MAKE_HTTP_GET_VARIABLE(12)
MAKE_HTTP_GET_VARIABLE(13)
MAKE_HTTP_GET_VARIABLE(14)
MAKE_HTTP_GET_VARIABLE(15)
MAKE_HTTP_GET_VARIABLE(16)
MAKE_HTTP_GET_VARIABLE(17)
MAKE_HTTP_GET_VARIABLE(18)
MAKE_HTTP_GET_VARIABLE(19)

#define MAKE_HTTP_GET_FUNCTION(n)                                                                                     \
    void *httpGetFunctionCaller##n(const char *args)                                                                  \
    {                                                                                                                 \
        Napi::Env env = httpGetRefFunctionList[n]->Env();                                                             \
        Napi::Value response = httpGetRefFunctionList[n]->Call({Napi::String::New(env, args)});                       \
        if (response.IsBoolean())                                                                                     \
        {                                                                                                             \
            return reinterpret_cast<void *>(static_cast<uintptr_t>(static_cast<bool>(response.ToBoolean().Value()))); \
        }                                                                                                             \
                                                                                                                      \
        if (response.IsNumber())                                                                                      \
        {                                                                                                             \
            double value = response.ToNumber().DoubleValue();                                                         \
            if (value == static_cast<int>(value))                                                                     \
            {                                                                                                         \
                return reinterpret_cast<void *>(static_cast<uintptr_t>(static_cast<int>(value)));                     \
            }                                                                                                         \
            else if (value == static_cast<long>(value))                                                               \
            {                                                                                                         \
                return reinterpret_cast<void *>(static_cast<uintptr_t>(static_cast<long>(value)));                    \
            }                                                                                                         \
            else                                                                                                      \
            {                                                                                                         \
                return reinterpret_cast<void *>(static_cast<uintptr_t>(value));                                       \
            }                                                                                                         \
        }                                                                                                             \
                                                                                                                      \
        if (response.IsString())                                                                                      \
        {                                                                                                             \
            Napi::String str = response.As<Napi::String>();                                                           \
            if (str.Utf8Value().size() + 1 <= MAX_BUFF_RESULT_LENGTH)                                                 \
            {                                                                                                         \
                char *result = new char[str.Utf8Value().size() + 1];                                                  \
                strncpy(result, str.Utf8Value().c_str(), str.Utf8Value().size());                                     \
                result[str.Utf8Value().size()] = '\0';                                                                \
                return result;                                                                                        \
            }                                                                                                         \
            char *result = new char[1];                                                                               \
            result[0] = '\0';                                                                                         \
            return result;                                                                                            \
        }                                                                                                             \
        return nullptr;                                                                                               \
    }

MAKE_HTTP_GET_FUNCTION(0)
MAKE_HTTP_GET_FUNCTION(1)
MAKE_HTTP_GET_FUNCTION(2)
MAKE_HTTP_GET_FUNCTION(3)
MAKE_HTTP_GET_FUNCTION(4)
MAKE_HTTP_GET_FUNCTION(5)
MAKE_HTTP_GET_FUNCTION(6)
MAKE_HTTP_GET_FUNCTION(7)
MAKE_HTTP_GET_FUNCTION(8)
MAKE_HTTP_GET_FUNCTION(9)
MAKE_HTTP_GET_FUNCTION(10)
MAKE_HTTP_GET_FUNCTION(11)
MAKE_HTTP_GET_FUNCTION(12)
MAKE_HTTP_GET_FUNCTION(13)
MAKE_HTTP_GET_FUNCTION(14)
MAKE_HTTP_GET_FUNCTION(15)
MAKE_HTTP_GET_FUNCTION(16)
MAKE_HTTP_GET_FUNCTION(17)
MAKE_HTTP_GET_FUNCTION(18)
MAKE_HTTP_GET_FUNCTION(19)

static std::array<HttpGetRefType, MAX_FUNCS_GET> httpGetRefList = {
    httpGetFunctionCaller0,
    httpGetFunctionCaller1,
    httpGetFunctionCaller2,
    httpGetFunctionCaller3,
    httpGetFunctionCaller4,
    httpGetFunctionCaller5,
    httpGetFunctionCaller6,
    httpGetFunctionCaller7,
    httpGetFunctionCaller8,
    httpGetFunctionCaller9,
    httpGetFunctionCaller10,
    httpGetFunctionCaller11,
    httpGetFunctionCaller12,
    httpGetFunctionCaller13,
    httpGetFunctionCaller14,
    httpGetFunctionCaller15,
    httpGetFunctionCaller16,
    httpGetFunctionCaller17,
    httpGetFunctionCaller18,
    httpGetFunctionCaller19};

HttpGetRefType returnHttpGetReference(Napi::Function fun)
{
    if (indexHttpGet >= 0 && indexHttpGet < static_cast<int>(httpGetRefFunctionList.size()))
    {
        switch (indexHttpGet)
        {
        case 0:
            httpGetFunRef0 = Napi::Persistent(fun);
            httpGetFunRef0.SuppressDestruct();
            httpGetRefFunctionList[0] = &httpGetFunRef0;
            break;
        case 1:
            httpGetFunRef1 = Napi::Persistent(fun);
            httpGetFunRef1.SuppressDestruct();
            httpGetRefFunctionList[1] = &httpGetFunRef1;
            break;
        case 2:
            httpGetFunRef2 = Napi::Persistent(fun);
            httpGetFunRef2.SuppressDestruct();
            httpGetRefFunctionList[2] = &httpGetFunRef2;
            break;
        case 3:
            httpGetFunRef3 = Napi::Persistent(fun);
            httpGetFunRef3.SuppressDestruct();
            httpGetRefFunctionList[3] = &httpGetFunRef3;
            break;
        case 4:
            httpGetFunRef4 = Napi::Persistent(fun);
            httpGetFunRef4.SuppressDestruct();
            httpGetRefFunctionList[4] = &httpGetFunRef4;
            break;
        case 5:
            httpGetFunRef5 = Napi::Persistent(fun);
            httpGetFunRef5.SuppressDestruct();
            httpGetRefFunctionList[5] = &httpGetFunRef5;
            break;
        case 6:
            httpGetFunRef6 = Napi::Persistent(fun);
            httpGetFunRef6.SuppressDestruct();
            httpGetRefFunctionList[6] = &httpGetFunRef6;
            break;
        case 7:
            httpGetFunRef7 = Napi::Persistent(fun);
            httpGetFunRef7.SuppressDestruct();
            httpGetRefFunctionList[7] = &httpGetFunRef7;
            break;
        case 8:
            httpGetFunRef8 = Napi::Persistent(fun);
            httpGetFunRef8.SuppressDestruct();
            httpGetRefFunctionList[8] = &httpGetFunRef8;
            break;
        case 9:
            httpGetFunRef9 = Napi::Persistent(fun);
            httpGetFunRef9.SuppressDestruct();
            httpGetRefFunctionList[9] = &httpGetFunRef9;
            break;
        case 10:
            httpGetFunRef10 = Napi::Persistent(fun);
            httpGetFunRef10.SuppressDestruct();
            httpGetRefFunctionList[10] = &httpGetFunRef10;
            break;
        case 11:
            httpGetFunRef11 = Napi::Persistent(fun);
            httpGetFunRef11.SuppressDestruct();
            httpGetRefFunctionList[11] = &httpGetFunRef11;
            break;
        case 12:
            httpGetFunRef12 = Napi::Persistent(fun);
            httpGetFunRef12.SuppressDestruct();
            httpGetRefFunctionList[12] = &httpGetFunRef12;
            break;
        case 13:
            httpGetFunRef13 = Napi::Persistent(fun);
            httpGetFunRef13.SuppressDestruct();
            httpGetRefFunctionList[13] = &httpGetFunRef13;
            break;
        case 14:
            httpGetFunRef14 = Napi::Persistent(fun);
            httpGetFunRef14.SuppressDestruct();
            httpGetRefFunctionList[14] = &httpGetFunRef14;
            break;
        case 15:
            httpGetFunRef15 = Napi::Persistent(fun);
            httpGetFunRef15.SuppressDestruct();
            httpGetRefFunctionList[15] = &httpGetFunRef15;
            break;
        case 16:
            httpGetFunRef0 = Napi::Persistent(fun);
            httpGetFunRef0.SuppressDestruct();
            httpGetRefFunctionList[16] = &httpGetFunRef16;
            break;
        case 17:
            httpGetFunRef17 = Napi::Persistent(fun);
            httpGetFunRef17.SuppressDestruct();
            httpGetRefFunctionList[17] = &httpGetFunRef17;
            break;
        case 18:
            httpGetFunRef18 = Napi::Persistent(fun);
            httpGetFunRef18.SuppressDestruct();
            httpGetRefFunctionList[18] = &httpGetFunRef18;
            break;
        case 19:
            httpGetFunRef19 = Napi::Persistent(fun);
            httpGetFunRef19.SuppressDestruct();
            httpGetRefFunctionList[19] = &httpGetFunRef19;
            break;
        default:
            break;
        }
        const HttpGetRefType func = httpGetRefList[indexHttpGet];
        indexHttpGet++;
        return func;
    }

    return nullptr;
}