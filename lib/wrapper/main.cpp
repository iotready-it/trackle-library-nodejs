#include "./proxy/trackle_proxy.hpp"

Napi::Object init(Napi::Env env, Napi::Object exports)
{
    // Getters
    exports.Set(
        "getMaxDeviceIdLength",
        Napi::Function::New(env, getMaxDeviceIdLength));
    exports.Set(
        "getMaxDevicePrivateKeyLength",
        Napi::Function::New(env, getMaxDevicePrivateKeyLength));

    // Init Settings
    exports.Set(
        "setLogCallback",
        Napi::Function::New(env, setLogCallback));
    exports.Set(
        "setLogLevel",
        Napi::Function::New(env, setLogLevel));
    exports.Set(
        "setEnabled",
        Napi::Function::New(env, setEnabled));
    exports.Set(
        "setFirmwareVersion",
        Napi::Function::New(env, setFirmwareVersion));
    exports.Set(
        "setProductId",
        Napi::Function::New(env, setProductId));
    exports.Set(
        "setOtaMethod",
        Napi::Function::New(env, setOtaMethod));
    exports.Set(
        "setConnectionType",
        Napi::Function::New(env, setConnectionType));

    // Set
    exports.Set(
        "setMillis",
        Napi::Function::New(env, setMillis));
    exports.Set(
        "setDeviceId",
        Napi::Function::New(env, setDeviceId));
    exports.Set(
        "setKeys",
        Napi::Function::New(env, setKeys));
    exports.Set(
        "setSendCallback",
        Napi::Function::New(env, setSendCallback));
    exports.Set(
        "setReceiveCallback",
        Napi::Function::New(env, setReceiveCallback));
    exports.Set(
        "setConnectCallback",
        Napi::Function::New(env, setConnectCallback));
    exports.Set(
        "setDisconnectCallback",
        Napi::Function::New(env, setDisconnectCallback));
    exports.Set(
        "setSystemTimeCallback",
        Napi::Function::New(env, setSystemTimeCallback));
    exports.Set(
        "setSystemRebootCallback",
        Napi::Function::New(env, setSystemRebootCallback));
    exports.Set(
        "setPublishHealthCheckInterval",
        Napi::Function::New(env, setPublishHealthCheckInterval));
    exports.Set(
        "setCompletedPublishCallback",
        Napi::Function::New(env, setCompletedPublishCallback));

    // Actions
    exports.Set(
        "connect",
        Napi::Function::New(env, connect));
    exports.Set(
        "disconnect",
        Napi::Function::New(env, disconnect));
    exports.Set(
        "loop",
        Napi::Function::New(env, loop));

    // Post and Get
    exports.Set(
        "post",
        Napi::Function::New(env, post));
    exports.Set(
        "get",
        Napi::Function::New(env, get));
    exports.Set(
        "publish",
        Napi::Function::New(env, publish));

    // added
    exports.Set(
        "setUpdateStateCallback",
        Napi::Function::New(env, setUpdateStateCallback));
    exports.Set(
        "syncState",
        Napi::Function::New(env, syncState));
    exports.Set(
        "setOverrideConnection",
        Napi::Function::New(env, setOverrideConnection));
    exports.Set(
        "setConnectionStatusCallback",
        Napi::Function::New(env, setConnectionStatusCallback));
    return exports;
}

NODE_API_MODULE(trackle_wrapper, init);