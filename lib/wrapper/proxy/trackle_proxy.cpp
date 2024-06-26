#include <trackle.h>
#include "logging.h"
#include "trackle_proxy.hpp"

#include "../callbacks/default_callbacks.hpp"
#include "../utils/utils.hpp"
#define POST_NUMBER 20
#define GET_NUMBER 20
using namespace std;

// Global variables
static Trackle trackleLibraryInstance;

/*
 **************************
 *  getMaxDeviceIdLength  *
 **************************
 */
Napi::Number getMaxDeviceIdLength(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    return Napi::Number::New(env, DEVICE_ID_LENGTH);
}

/*
 **********************************
 *  getMaxDevicePrivateKeyLength  *
 **********************************
 */
Napi::Number getMaxDevicePrivateKeyLength(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    return Napi::Number::New(env, PRIVATE_KEY_LENGTH);
}

/*
 ********************
 *  setLogCallback  *
 ********************
 */
// FIXME: attribute e reserved per ora non restituiti
void logCallbackCaller(const char *msg, int level, const char *category, void *attribute, void *reserved)
{
    auto iterator = systemCallbacksMap.find(LOG_REF_CB);

    if (iterator != systemCallbacksMap.end())
    {
        Napi::Env env = iterator->second.Env();

        iterator->second.Call({
            Napi::String::New(env, msg),
            Napi::Number::New(env, level),
            Napi::String::New(env, category ? category : ""),
        });
    }
    else
    {
        LOG(ERROR, "logCallbackCaller: Callback \"%s\" not found in map!", LOG_REF_CB.c_str());
    }

    return;
}
void setLogCallback(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    if (info.Length() != 1 && !info[0].IsFunction())
    {
        Napi::TypeError::New(env, "setLogCallback: expects a callback arg!").ThrowAsJavaScriptException();
        return;
    }

    Napi::FunctionReference refCb = Napi::Persistent(info[0].As<Napi::Function>());
    refCb.SuppressDestruct();

    // Create a pair of <string,reference> to call in postFunctionCaller
    systemCallbacksMap.emplace(std::make_pair<std::string, Napi::FunctionReference>(std::string(LOG_REF_CB), std::move(refCb)));

    trackleLibraryInstance.setLogCallback(logCallbackCaller);
}

/*
 **********************************
 *  setLogLevel  *
 **********************************
 */
void setLogLevel(const Napi::CallbackInfo &info)
{
    // LOG(TRACE, "Called setLogLevel");

    int logLevel = info[0].As<Napi::Number>().Uint32Value();
    Log_Level logLevelEnum = (Log_Level)logLevel;

    trackleLibraryInstance.setLogLevel(logLevelEnum);

    // LOG(TRACE, "setlogLevel was correctly done");
    return;
}

/*
 ****************
 *  setEnabled  *
 ****************
 */
void setEnabled(const Napi::CallbackInfo &info)
{
    // LOG(TRACE, "Called setEnabled");

    Napi::Env env = info.Env();

    if (!info.Length() != 0 && info[0].IsBoolean())
    {
        Napi::TypeError::New(env, "trackleSetEnabled: expects a Boolean arg!").ThrowAsJavaScriptException();
        return;
    }

    bool enabled = info[0].As<Napi::Boolean>();

    trackleLibraryInstance.setEnabled(enabled);

    // LOG(TRACE, "setEnabled was correctly done");

    return;
}

/*
 ************************
 *  setFirmwareVersion  *
 ************************
 */
void setFirmwareVersion(const Napi::CallbackInfo &info)
{
    // LOG(TRACE, "Called setFirmwareVersion");

    Napi::Env env = info.Env();

    if (!info.Length() != 0 && info[0].IsNumber())
    {
        Napi::TypeError::New(env, "setFirmwareVersion: expects a Number arg!").ThrowAsJavaScriptException();
        return;
    }

    int version = info[0].As<Napi::Number>().Uint32Value();

    trackleLibraryInstance.setFirmwareVersion(version);

    // LOG(TRACE, "setFirmwareVersion was correctly done");

    return;
}

/*
 ************************
 *  setProductId  *
 ************************
 */
void setProductId(const Napi::CallbackInfo &info)
{
    // LOG(TRACE, "Called setFirmwareVersion");

    Napi::Env env = info.Env();

    if (!info.Length() != 0 && info[0].IsNumber())
    {
        Napi::TypeError::New(env, "setProductId: expects a Number arg!").ThrowAsJavaScriptException();
        return;
    }

    int version = info[0].As<Napi::Number>().Uint32Value();

    trackleLibraryInstance.setProductId(version);

    // LOG(TRACE, "setFirmwareVersion was correctly done");

    return;
}

/*
 ******************
 *  setOtaMethod  *
 ******************
 */
void setOtaMethod(const Napi::CallbackInfo &info)
{
    // LOG(TRACE, "Called setOtaMethod");

    Napi::Env env = info.Env();

    if (!info.Length() != 0 && info[0].IsNumber())
    {
        Napi::TypeError::New(env, "setOtaMethod: expects a Number arg!").ThrowAsJavaScriptException();
        return;
    }

    int otaMethod = info[0].As<Napi::Number>().Uint32Value();
    Ota_Method otaMethodEnum = (Ota_Method)otaMethod;

    trackleLibraryInstance.setOtaMethod(otaMethodEnum);

    // LOG(TRACE, "setOtaMethod was correctly done");

    return;
}

/*
 ***********************
 *  setConnectionType  *
 ***********************
 */
void setConnectionType(const Napi::CallbackInfo &info)
{
    LOG(TRACE, "Called setConnectionType");

    Napi::Env env = info.Env();

    if (!info.Length() != 0 && info[0].IsNumber())
    {
        Napi::TypeError::New(env, "setConnectionType: expects a Number arg!").ThrowAsJavaScriptException();
        return;
    }

    int connType = info[0].As<Napi::Number>().Uint32Value();
    Connection_Type connTypeEnum = (Connection_Type)connType;

    trackleLibraryInstance.setConnectionType(connTypeEnum);

    // LOG(TRACE, "setConnectionType was correctly done");

    return;
}

/*
 ***************
 *  setMillis  *
 ***************
 */
system_tick_t millisCallbackCaller()
{
    // LOG(TRACE, "Called millisCallbackCaller");

    auto iterator = systemCallbacksMap.find(MILLIS_REF_CB);
    Napi::Value result;

    if (iterator != systemCallbacksMap.end())
    {
        result = iterator->second.Call({});
    }
    else
    {
        LOG(ERROR, "millisCallbackCaller: Callback \"%s\" not found in map!", MILLIS_REF_CB.c_str());
    }

    return result
               ? static_cast<system_tick_t>(result.ToNumber().Uint32Value())
               : -1;
}
void setMillis(const Napi::CallbackInfo &info)
{
    // LOG(TRACE, "Called setMillis");

    Napi::Env env = info.Env();

    if (info.Length() != 1)
    {
        Napi::Error::New(env, "setMillis: expects exactly one argument as callback!").ThrowAsJavaScriptException();
        return;
    }

    if (!info[0].IsFunction())
    {
        Napi::Error::New(env, "setMillis: expect a callback function!").ThrowAsJavaScriptException();
        return;
    }

    Napi::FunctionReference refLogCb = Napi::Persistent(info[0].As<Napi::Function>());
    refLogCb.SuppressDestruct();

    // Create a pair of <string,reference> to call in postFunctionCaller
    systemCallbacksMap.emplace(std::make_pair<std::string, Napi::FunctionReference>(std::string(MILLIS_REF_CB), std::move(refLogCb)));

    trackleLibraryInstance.setMillis(millisCallbackCaller);

    LOG(TRACE, "setMillis was correctly done");
}

/*
 *****************
 *  setDeviceId  *
 *****************
 */
void setDeviceId(const Napi::CallbackInfo &info)
{
    LOG(TRACE, "Called setDeviceId");

    Napi::Env env = info.Env();

    if (info.Length() != 1 || !info[0].IsString())
    {
        Napi::TypeError::New(env, "setDeviceId: expects a String").ThrowAsJavaScriptException();
        return;
    }

    std::string str = info[0].As<Napi::String>().Utf8Value();

    if (str.length() != DEVICE_ID_LENGTH * 2)
    {
        Napi::TypeError::New(env, "setDeviceId: string length should be " + std::to_string(DEVICE_ID_LENGTH * 2) + " (in hex)").ThrowAsJavaScriptException();
        return;
    }

    std::vector<uint8_t> buffer;
    for (size_t i = 0; i < str.length(); i += 2)
    {
        std::string byteString = str.substr(i, 2);
        buffer.push_back(static_cast<uint8_t>(std::stoi(byteString, nullptr, 16)));
    }

    // Crea un nuovo Uint8Array utilizzando il buffer creato
    Napi::Uint8Array uint8Array = Napi::Uint8Array::New(env, buffer.size());
    std::memcpy(uint8Array.Data(), buffer.data(), buffer.size());

    trackleLibraryInstance.setDeviceId(uint8Array.Data());

    // LOG(TRACE, "Set deviceId was correctly done");

    return;
}

/*
 *************
 *  setKeys  *
 *************
 */
void setKeys(const Napi::CallbackInfo &info)
{
    // LOG(TRACE, "Called setKeys");

    Napi::Env env = info.Env();

    if ((info.Length() != 1))
    {
        Napi::TypeError::New(env, "setKeys: expects an Array of lenght " + std::to_string(PRIVATE_KEY_LENGTH)).ThrowAsJavaScriptException();
        return;
    }

    if (!info[0].IsBuffer())
    {
        Napi::TypeError::New(env, "setKeys: expects an ArrayBuffer!").ThrowAsJavaScriptException();
        return;
    }

    Napi::Uint8Array buffer = info[0].As<Napi::Uint8Array>();
    uint8_t *devicePrivateKey = buffer.Data();

    trackleLibraryInstance.setKeys(devicePrivateKey);

    // LOG(TRACE, "Set keys was correctly done");

    return;
}

/*
 *********************
 *  setSendCallback  *
 *********************
 */
// FIXME: controllare che tmp sia restituito corretto (fatto di test)
int sendCallbackCaller(const unsigned char *buf, uint32_t buflen, void *tmp)
{
    LOG(TRACE, "Called sendCallbackCaller");

    auto iterator = systemCallbacksMap.find(SEND_REF_CB);
    Napi::Value result;

    if (iterator != systemCallbacksMap.end())
    {
        Napi::Env env = iterator->second.Env();

        result = iterator->second.Call({Napi::Buffer<unsigned char>::New(env, const_cast<unsigned char *>(buf), buflen),
                                        Napi::Number::New(env, buflen),
                                        Napi::External<void>::New(env, tmp)});
    }
    else
    {
        LOG(ERROR, "sendCallbackCaller: Callback \"%s\" not found in map!", SEND_REF_CB.c_str());
    }

    return result
               ? result.ToNumber().Uint32Value()
               : -1;
}
void setSendCallback(const Napi::CallbackInfo &info)
{
    LOG(TRACE, "Called setSendCallback");

    Napi::Env env = info.Env();

    if (info.Length() > 1)
    {
        Napi::Error::New(env, "setSendCallback: expects exactly one argument as callback or nothing to use default one!").ThrowAsJavaScriptException();
        return;
    }

    if (info.Length() == 0)
    {
        LOG(WARN, "Setting default callback: default_send_udp_cb");
        trackleLibraryInstance.setSendCallback(default_send_udp_cb);
    }
    else
    {
        if (!info[0].IsFunction())
        {
            Napi::Error::New(env, "setSendCallback: expect a callback function!").ThrowAsJavaScriptException();
            return;
        }

        Napi::FunctionReference refCb = Napi::Persistent(info[0].As<Napi::Function>());
        refCb.SuppressDestruct();

        // Create a pair of <string,reference> to call in sendCallbackCaller
        systemCallbacksMap.emplace(std::make_pair<std::string, Napi::FunctionReference>(std::string(SEND_REF_CB), std::move(refCb)));

        trackleLibraryInstance.setSendCallback(sendCallbackCaller);
    }

    LOG(TRACE, "Set sendCb was correctly done");

    return;
}

/*
 ************************
 *  setReceiveCallback  *
 ************************
 */
// FIXME: controllare che tmp sia restituito corretto (fatto di test)
int rcvCallbackCaller(unsigned char *buf, uint32_t buflen, void *tmp)
{
    LOG(ERROR, "Called rcvCallbackCaller %d", buflen);

    auto iterator = systemCallbacksMap.find(RECEIVE_REF_CB);
    Napi::Value result;

    if (iterator != systemCallbacksMap.end())
    {
        Napi::Env env = iterator->second.Env();

        result = iterator->second.Call({Napi::Buffer<unsigned char>::New(env, static_cast<unsigned char *>(buf), buflen),
                                        Napi::Number::New(env, buflen),
                                        Napi::External<void>::New(env, tmp)});
    }
    else
    {
        LOG(ERROR, "rcvCallbackCaller: Callback \"%s\" not found in map!", RECEIVE_REF_CB.c_str());
    }

    return result
               ? result.ToNumber().Uint32Value()
               : -1;
}
void setReceiveCallback(const Napi::CallbackInfo &info)
{
    LOG(TRACE, "Called setReceiveCallback");

    Napi::Env env = info.Env();

    if (info.Length() > 1)
    {
        Napi::Error::New(env, "setReceiveCallback: expects exactly one argument as callback or nothing to use default one!").ThrowAsJavaScriptException();
        return;
    }

    if (info.Length() == 0)
    {
        LOG(WARN, "Setting default callback: default_receive_udp_cb");
        trackleLibraryInstance.setReceiveCallback(default_receive_udp_cb);
    }
    else
    {
        if (!info[0].IsFunction())
        {
            Napi::Error::New(env, "setReceiveCallback: expect a callback function!").ThrowAsJavaScriptException();
            return;
        }

        Napi::FunctionReference refCb = Napi::Persistent(info[0].As<Napi::Function>());
        refCb.SuppressDestruct();

        // Create a pair of <string,reference> to call in sendCallbackCaller
        systemCallbacksMap.emplace(std::make_pair<std::string, Napi::FunctionReference>(std::string(RECEIVE_REF_CB), std::move(refCb)));

        trackleLibraryInstance.setReceiveCallback(rcvCallbackCaller);
    }

    LOG(TRACE, "Set receiveCb was correctly done");

    return;
}

/*
 ************************
 *  setConnectCallback  *
 ************************
 */
int connectCallbackCaller(const char *address, int port)
{
    LOG(TRACE, "Called connectCallbackCaller");

    auto iterator = systemCallbacksMap.find(CONNECT_REF_CB);
    Napi::Value result;

    if (iterator != systemCallbacksMap.end())
    {
        Napi::Env env = iterator->second.Env();

        result = iterator->second.Call({Napi::String::New(env, address), Napi::Number::New(env, port)});
    }
    else
    {
        LOG(ERROR, "connectCallbackCaller: Callback \"%s\" not found in map!", CONNECT_REF_CB.c_str());
    }

    return result
               ? result.ToNumber().Uint32Value()
               : -1;
}
void setConnectCallback(const Napi::CallbackInfo &info)
{
    LOG(TRACE, "Called setConnectCallback");

    Napi::Env env = info.Env();

    if (info.Length() > 1)
    {
        Napi::Error::New(env, "setConnectCallback: expects exactly one argument as callback or nothing to use default one!").ThrowAsJavaScriptException();
        return;
    }

    if (info.Length() == 0)
    {
        LOG(WARN, "Setting default callback: default_connect_udp_cb");
        trackleLibraryInstance.setConnectCallback(default_connect_udp_cb);
    }
    else
    {
        if (!info[0].IsFunction())
        {
            Napi::Error::New(env, "setConnectCallback: expect a callback function!").ThrowAsJavaScriptException();
            return;
        }

        Napi::FunctionReference refCb = Napi::Persistent(info[0].As<Napi::Function>());
        refCb.SuppressDestruct();

        // Create a pair of <string,reference> to call in sendCallbackCaller
        systemCallbacksMap.emplace(std::make_pair<std::string, Napi::FunctionReference>(std::string(CONNECT_REF_CB), std::move(refCb)));

        trackleLibraryInstance.setConnectCallback(connectCallbackCaller);
    }

    LOG(TRACE, "setConnectCb was correctly done");

    return;
}
/*
 ************************
 *  setOverrideConnection  *
 ************************
 */
void setOverrideConnection(const Napi::CallbackInfo &info)
{
    LOG(TRACE, "Called setConnectCallback");

    Napi::Env env = info.Env();

    if (info.Length() != 2)
    {
        Napi::Error::New(env, "setOverrideConnection: expects exactly 2 arguments!").ThrowAsJavaScriptException();
        return;
    }

    if (!info[0].IsString())
    {
        Napi::Error::New(env, "setOverrideConnection: expect ip address to be a string!").ThrowAsJavaScriptException();
        return;
    }

    if (!info[1].IsNumber())
    {
        Napi::Error::New(env, "setOverrideConnection: expect port to be a number!").ThrowAsJavaScriptException();
        return;
    }

    // Ottieni l'indirizzo IP dalla prima stringa e il numero di porta dall'argomento numerico
    std::string ipadress = info[0].As<Napi::String>().Utf8Value();
    int port = info[1].As<Napi::Number>().Int32Value();

    // Effettua la chiamata alla tua funzione di libreria C++
    Callbacks_setConnectionOverride(true, const_cast<char *>(ipadress.c_str()), port);

    LOG(TRACE, "setConnectCb was correctly done");

    return;
}

/*
 ***************************
 *  setDisconnectCallback  *
 ***************************
 */
int disconnectCallbackCaller()
{
    LOG(TRACE, "Called disconnectCallbackCaller");

    auto iterator = systemCallbacksMap.find(DISCONNECT_REF_CB);
    Napi::Value result;

    if (iterator != systemCallbacksMap.end())
    {
        result = iterator->second.Call({});
    }
    else
    {
        LOG(ERROR, "disconnectCallbackCaller: Callback \"%s\" not found in map!", DISCONNECT_REF_CB.c_str());
    }

    return result
               ? result.ToNumber().Uint32Value()
               : -1;
}
void setDisconnectCallback(const Napi::CallbackInfo &info)
{
    LOG(TRACE, "Called setDisconnectCallback");

    Napi::Env env = info.Env();

    if (info.Length() > 1)
    {
        Napi::Error::New(env, "setDisconnectCallback: expects exactly one argument as callback or nothing to use default one!").ThrowAsJavaScriptException();
        return;
    }

    if (info.Length() == 0)
    {
        LOG(WARN, "Setting default callback: default_disconnect_udp_cb");
        trackleLibraryInstance.setDisconnectCallback(default_disconnect_udp_cb);
    }
    else
    {

        if (!info[0].IsFunction())
        {
            Napi::Error::New(env, "setDisconnectCallback: expect a callback function!").ThrowAsJavaScriptException();
            return;
        }

        Napi::FunctionReference refCb = Napi::Persistent(info[0].As<Napi::Function>());
        refCb.SuppressDestruct();

        // Create a pair of <string,reference> to call in sendCallbackCaller
        systemCallbacksMap.emplace(std::make_pair<std::string, Napi::FunctionReference>(std::string(DISCONNECT_REF_CB), std::move(refCb)));

        trackleLibraryInstance.setDisconnectCallback(disconnectCallbackCaller);
    }

    LOG(TRACE, "setDisconnectCb was correctly done");

    return;
}

/*
 ***************************
 *  setSystemTimeCallback  *
 ***************************
 */
// FIXME: controllare che data sia restituito corretto (fatto di test)
void systemTimeCallbackCaller(time_t time, unsigned int param, void *data)
{
    LOG(TRACE, "Called systemTimeCallbackCaller");

    auto iterator = systemCallbacksMap.find(SYSTEM_TIME_REF_CB);

    if (iterator != systemCallbacksMap.end())
    {
        Napi::Env env = iterator->second.Env();

        // Creation of an external object for the void* param to pass to the call
        // The napi_create_external contain the original pointer to the void* function
        napi_value external;
        napi_create_external(env, data, nullptr, nullptr, &external);

        iterator->second.Call({Napi::Number::New(env, time),
                               Napi::Number::New(env, param),
                               Napi::External<void>::New(env, external)});
    }
    else
    {
        LOG(ERROR, "systemTimeCallbackCaller: Callback \"%s\" not found in map!", SYSTEM_TIME_REF_CB.c_str());
    }

    return;
}
void setSystemTimeCallback(const Napi::CallbackInfo &info)
{
    LOG(TRACE, "Called setSystemTimeCallback");

    Napi::Env env = info.Env();

    if (info.Length() != 1)
    {
        Napi::Error::New(env, "setSystemTimeCallback: expects exactly one argument as callback!").ThrowAsJavaScriptException();
        return;
    }

    if (!info[0].IsFunction())
    {
        Napi::Error::New(env, "setSystemTimeCallback: expect a callback function!").ThrowAsJavaScriptException();
        return;
    }

    Napi::FunctionReference refCb = Napi::Persistent(info[0].As<Napi::Function>());
    refCb.SuppressDestruct();

    // Create a pair of <string,reference> to call in sendCallbackCaller
    systemCallbacksMap.emplace(std::make_pair<std::string, Napi::FunctionReference>(std::string(SYSTEM_TIME_REF_CB), std::move(refCb)));

    trackleLibraryInstance.setSystemTimeCallback(systemTimeCallbackCaller);

    LOG(TRACE, "setSystemTimeCb was correctly done");

    return;
}

/*
 *****************************
 *  setSystemRebootCallback  *
 *****************************
 */
void systemRebootCallbackCaller(const char *data)
{
    LOG(TRACE, "Called systemRebootCallbackCaller");

    auto iterator = systemCallbacksMap.find(SYS_REBOOT_REF_CB);

    if (iterator != systemCallbacksMap.end())
    {
        Napi::Env env = iterator->second.Env();

        iterator->second.Call({Napi::String::New(env, data)});
    }
    else
    {
        LOG(ERROR, "systemRebootCallbackCaller: Callback \"%s\" not found in map.", SYS_REBOOT_REF_CB.c_str());
    }

    return;
}
void setSystemRebootCallback(const Napi::CallbackInfo &info)
{
    LOG(TRACE, "Called setSystemRebootCallback");

    Napi::Env env = info.Env();

    if (info.Length() != 1)
    {
        Napi::Error::New(env, "setSystemRebootCallback: expects exactly one argument as callback!").ThrowAsJavaScriptException();
        return;
    }

    if (!info[0].IsFunction())
    {
        Napi::Error::New(env, "setSystemRebootCallback: expect a callback function!").ThrowAsJavaScriptException();
        return;
    }

    Napi::FunctionReference refCb = Napi::Persistent(info[0].As<Napi::Function>());
    refCb.SuppressDestruct();

    // Create a pair of <string,reference> to call in setSleepCallback
    systemCallbacksMap.emplace(std::make_pair<std::string, Napi::FunctionReference>(std::string(SYS_REBOOT_REF_CB), std::move(refCb)));

    trackleLibraryInstance.setSystemRebootCallback(systemRebootCallbackCaller);

    LOG(TRACE, "setSystemRebootCb was correctly done");

    return;
}

/*
 ***********************************
 *  setPublishHealthCheckInterval  *
 ***********************************
 */
void setPublishHealthCheckInterval(const Napi::CallbackInfo &info)
{
    LOG(TRACE, "Called setPublishHealthCheckInterval");

    Napi::Env env = info.Env();

    if (!info.Length() != 0 && info[0].IsNumber())
    {
        Napi::TypeError::New(env, "setPublishHealthCheckInterval: expects a Number arg!").ThrowAsJavaScriptException();
        return;
    }

    uint32_t interval = info[0].As<Napi::Number>().Uint32Value();

    trackleLibraryInstance.setPublishHealthCheckInterval(interval);

    LOG(TRACE, "setPublishHealthCheckInterval was correctly done");

    return;
}

/*
 *********************************
 *  setCompletedPublishCallback  *
 *********************************
 */
// FIXME: controllare che data sia restituito corretti, reserved non viene restituito
// TODO: controllare che data abbia un valore in memoria attualmente mi risulta null
void completedPublishCallback(int error, const void *data, void *callbackData, void *reserved)
{
    LOG(TRACE, "Called completedPublishCallback");

    auto iterator = systemCallbacksMap.find(COMPLETE_PUBLISH_REF_CB);

    if (iterator != systemCallbacksMap.end())
    {
        Napi::Env env = iterator->second.Env();

        uint32_t *cbPtr = (uint32_t *)callbackData;
        // const char *strData = static_cast<const char *>(data);
        // LOG(INFO, "Data pointed by data: %s", strData);
        long value = reinterpret_cast<long>(cbPtr);

        iterator->second.Call({Napi::Number::New(env, error), Napi::Number::New(env, value)});
    }
    else
    {
        LOG(ERROR, "completedPublishCallback: Callback \"%s\" not found in map.", COMPLETE_PUBLISH_REF_CB.c_str());
    }

    return;
}

void setCompletedPublishCallback(const Napi::CallbackInfo &info)
{
    LOG(TRACE, "Called setCompletedPublishCallback");

    Napi::Env env = info.Env();

    if (info.Length() != 1)
    {
        Napi::Error::New(env, "setCompletedPublishCallback: expects exactly one argument as callback!").ThrowAsJavaScriptException();
        return;
    }

    if (!info[0].IsFunction())
    {
        Napi::Error::New(env, "setCompletedPublishCallback: expect a callback function!").ThrowAsJavaScriptException();
        return;
    }

    Napi::FunctionReference refCb = Napi::Persistent(info[0].As<Napi::Function>());
    refCb.SuppressDestruct();

    // Create a pair of <string,reference> to call in setSleepCallback
    systemCallbacksMap.emplace(std::make_pair<std::string, Napi::FunctionReference>(std::string(COMPLETE_PUBLISH_REF_CB), std::move(refCb)));

    trackleLibraryInstance.setCompletedPublishCallback(completedPublishCallback);

    LOG(TRACE, "setCompletedPublishCb was correctly done");

    return;
}

/*
 *************
 *  connect  *
 *************
 */
Napi::Number connect(const Napi::CallbackInfo &info)
{
    LOG(TRACE, "Called connect");

    Napi::Env env = info.Env();

    if (info.Length() != 0)
    {
        Napi::Error::New(env, "connect: expects no argument!").ThrowAsJavaScriptException();
        return Napi::Number::New(env, -1);
    }

    LOG(TRACE, "Connecting...");

    int result = trackleLibraryInstance.connect();

    return Napi::Number::New(env, result);
}

/*
 ****************
 *  disconnect  *
 ****************
 */
void disconnect(const Napi::CallbackInfo &info)
{
    LOG(TRACE, "Called disconnect");

    Napi::Env env = info.Env();

    if (info.Length() != 0)
    {
        Napi::Error::New(env, "disconnect: expects no argument!").ThrowAsJavaScriptException();
        return;
    }

    LOG(INFO, "Disconnecting...");

    trackleLibraryInstance.disconnect();

    return;
}

/*
 **********
 *  loop  *
 **********
 */
void loop(const Napi::CallbackInfo &info)
{
    trackleLibraryInstance.loop();

    return;
}

/*
 **********
 *  POST  *
 **********
 */

int defaultPost(const char *args, bool isOwner, const char *funKey)
{
    std::string name = std::string("POST_") + std::string(funKey);
    auto iterator = postCallbacksMap.find(name);

    if (iterator != postCallbacksMap.end())
    {
        Napi::Env env = iterator->second.Env();

        Napi::Value result = iterator->second.Call({Napi::String::New(env, args)});
        return result
                   ? result.ToNumber().Int32Value()
                   : -4;
    }
    else
    {
        LOG(ERROR, "completedPublishCallback: Callback \"%s\" not found in map.", COMPLETE_PUBLISH_REF_CB.c_str());

        return -3;
    }
}

Napi::Boolean post(const Napi::CallbackInfo &info)
{
    LOG(TRACE, "Called postFunction");

    Napi::Env env = info.Env();

    if (info.Length() != 3)
    {
        Napi::Error::New(env, "postFunction: expects 3 arguments!").ThrowAsJavaScriptException();
        return Napi::Boolean::New(env, false);
    }

    if (!info[0].IsString())
    {
        Napi::Error::New(env, "postFunction: expects first argument to be a string!").ThrowAsJavaScriptException();
        return Napi::Boolean::New(env, false);
    }

    if (!info[1].IsFunction())
    {
        Napi::Error::New(env, "postFunction: expects second argument to be a function!").ThrowAsJavaScriptException();
        return Napi::Boolean::New(env, false);
    }

    if (!info[2].IsNumber())
    {
        Napi::Error::New(env, "postFunction: expects third argument to be a number!").ThrowAsJavaScriptException();
        return Napi::Boolean::New(env, false);
    }

    // Arg1
    // Napi::String s = info[0].As<Napi::String>();
    std::string s = info[0].ToString().Utf8Value();
    const char *postFunName = s.c_str();
    std::string name = "POST_" + s;
    // Arg2
    Napi::FunctionReference refCb = Napi::Persistent(info[1].As<Napi::Function>());
    refCb.SuppressDestruct();

    // Arg3
    int postFunPermission = info[2].As<Napi::Number>().Uint32Value();
    Function_PermissionDef postFunPermissionEnum = (Function_PermissionDef)postFunPermission;

    bool result = false;
    // TODO: Domandare se  la funReference ritorna sempre e solo string o anche i variadici
    // LOG(INFO, "postFunction %s", postFunName);
    result = trackleLibraryInstance.post(postFunName, defaultPost, postFunPermissionEnum);
    if (result == true)
    {
        postCallbacksMap.emplace(std::make_pair<std::string, Napi::FunctionReference>(std::string(name), std::move(refCb)));
        LOG(TRACE, "postFunction was correctly done");
        return Napi::Boolean::New(env, result);
    }
    else
    {
        LOG(TRACE, "postFunction wasn't correctly done");
        return Napi::Boolean::New(env, result);
    }
}

/*
 **********
 *  GET  *
 **********
 */

// typedef void *(*user_variable_pointer_t)(const char *paramString, const char* varKey);

bool defaultBool(const char *paramString, const char *varKey)
{
    std::string name = std::string("GET_") + std::string(varKey);
    auto iterator = getCallbacksMap.find(name);

    if (iterator != getCallbacksMap.end())
    {
        Napi::Env env = iterator->second.Env();

        Napi::Value result = iterator->second.Call({Napi::String::New(env, paramString)});

        return result.ToBoolean().Value();
    }
    else
    {
        LOG(ERROR, "completedPublishCallback: Callback \"%s\" not found in map.", COMPLETE_PUBLISH_REF_CB.c_str());

        return false;
    }
}

int defaultInt(const char *paramString, const char *varKey)
{
    std::string name = std::string("GET_") + std::string(varKey);
    auto iterator = getCallbacksMap.find(name);

    if (iterator != getCallbacksMap.end())
    {
        Napi::Env env = iterator->second.Env();

        Napi::Value result = iterator->second.Call({Napi::String::New(env, paramString)});

        return result.IsNumber() ? result.ToNumber().Int32Value() : -4;
    }
    else
    {
        LOG(ERROR, "completedPublishCallback: Callback \"%s\" not found in map.", COMPLETE_PUBLISH_REF_CB.c_str());

        return -3;
    }
}

double defaultDouble(const char *paramString, const char *varKey)
{
    std::string name = std::string("GET_") + std::string(varKey);
    auto iterator = getCallbacksMap.find(name);

    if (iterator != getCallbacksMap.end())
    {
        Napi::Env env = iterator->second.Env();

        Napi::Value result = iterator->second.Call({Napi::String::New(env, paramString)});
        return result.IsNumber() ? result.ToNumber().DoubleValue() : -4;
    }
    else
    {
        LOG(ERROR, "completedPublishCallback: Callback \"%s\" not found in map.", COMPLETE_PUBLISH_REF_CB.c_str());

        return -3;
    }
}

static char jsonResponse[1024];
void *defaultJson(const char *paramString, const char *varKey)
{
    std::string name = std::string("GET_") + std::string(varKey);
    auto iterator = getCallbacksMap.find(name);

    if (iterator != getCallbacksMap.end())
    {
        Napi::Env env = iterator->second.Env();

        Napi::Value result = iterator->second.Call({Napi::String::New(env, paramString)});

        std::string str = result.ToString().Utf8Value();

        return strdup(str.c_str());
    }
    else
    {
        LOG(ERROR, "completedPublishCallback: Callback \"%s\" not found in map.", COMPLETE_PUBLISH_REF_CB.c_str());

        return strdup("");
    }
}
const char *defaultChar(const char *paramString, const char *varKey)
{
    std::string name = std::string("GET_") + std::string(varKey);
    auto iterator = getCallbacksMap.find(name);

    if (iterator != getCallbacksMap.end())
    {
        Napi::Env env = iterator->second.Env();

        Napi::Value result = iterator->second.Call({Napi::String::New(env, paramString)});

        std::string str = result.ToString().Utf8Value();

        return strdup(str.c_str());
    }
    else
    {
        LOG(ERROR, "completedPublishCallback: Callback \"%s\" not found in map.", COMPLETE_PUBLISH_REF_CB.c_str());

        return strdup("");
    }
}

Napi::Boolean get(const Napi::CallbackInfo &info)
{
    LOG(TRACE, "Called getFunction");

    Napi::Env env = info.Env();

    if (info.Length() != 3)
    {
        Napi::Error::New(env, "getFunction: expects 3 arguments!").ThrowAsJavaScriptException();
        return Napi::Boolean::New(env, false);
    }

    if (!info[0].IsString())
    {
        Napi::Error::New(env, "getFunction: expects first argument to be a string!").ThrowAsJavaScriptException();
        return Napi::Boolean::New(env, false);
    }

    if (!info[1].IsFunction())
    {
        Napi::Error::New(env, "getFunction: expects second argument to be a function!").ThrowAsJavaScriptException();
        return Napi::Boolean::New(env, false);
    }

    if (!info[2].IsNumber())
    {
        Napi::Error::New(env, "getFunction: expects third argument to be a number!").ThrowAsJavaScriptException();
        return Napi::Boolean::New(env, false);
    }

    // Arg1
    std::string s = info[0].ToString().Utf8Value();
    const char *getFunName = s.c_str();
    std::string name = "GET_" + s;

    // Arg2
    Napi::FunctionReference refCb = Napi::Persistent(info[1].As<Napi::Function>());
    refCb.SuppressDestruct();

    // Arg3
    int returnType = info[2].As<Napi::Number>().Uint32Value();
    Data_TypeDef returnTypeEnum = (Data_TypeDef)returnType;
    bool result = false;

    if (returnTypeEnum == VAR_BOOLEAN)
    {
        result = trackleLibraryInstance.get(getFunName, defaultBool);
    }
    else if (returnTypeEnum == VAR_INT)
    {
        result = trackleLibraryInstance.get(getFunName, defaultInt);
    }
    else if (returnTypeEnum == VAR_CHAR || returnTypeEnum == VAR_STRING)
    {
        result = trackleLibraryInstance.get(getFunName, defaultChar);
    }
    else if (returnTypeEnum == VAR_JSON)
    {
        result = trackleLibraryInstance.get(getFunName, defaultJson, VAR_JSON);
    }
    else if (returnTypeEnum == VAR_DOUBLE)
    {
        result = trackleLibraryInstance.get(getFunName, defaultDouble);
    }

    if (result == true)
    {
        getCallbacksMap.emplace(std::make_pair<std::string, Napi::FunctionReference>(std::string(name), std::move(refCb)));
        LOG(TRACE, "getFunction was correctly done");
        return Napi::Boolean::New(env, result);
    }
    else
    {
        LOG(INFO, "getFunction wasn't correctly done");
        return Napi::Boolean::New(env, result);
    }

    LOG(TRACE, "getFunction was correctly done");

    return Napi::Boolean::New(env, result);
}

/*
 *************
 *  publish  *
 *************
 */
Napi::Boolean publish(const Napi::CallbackInfo &info)
{
    LOG(TRACE, "Called publish");

    Napi::Env env = info.Env();

    if (info.Length() < 2 || info.Length() > 6)
    {
        Napi::Error::New(env, "publish: expects from 2 to 6 arguments!").ThrowAsJavaScriptException();
        return Napi::Boolean::New(env, false);
    }

    if (!info[0].IsString())
    {
        Napi::Error::New(env, "publish: expects first argument to be a string!").ThrowAsJavaScriptException();
        return Napi::Boolean::New(env, false);
    }
    if (!info[1].IsString())
    {
        Napi::Error::New(env, "publish: expects second argument to be a string!").ThrowAsJavaScriptException();
        return Napi::Boolean::New(env, false);
    }
    if (!info[2].IsUndefined() && !info[2].IsNumber())
    {
        Napi::Error::New(env, "publish: expects third argument to be a number!").ThrowAsJavaScriptException();
        return Napi::Boolean::New(env, false);
    }
    if (!info[3].IsUndefined() && !info[3].IsString())
    {
        Napi::Error::New(env, "publish: expects fourth argument to be a string!").ThrowAsJavaScriptException();
        return Napi::Boolean::New(env, false);
    }
    if (!info[4].IsUndefined() && !info[4].IsNumber())
    {
        Napi::Error::New(env, "publish: expects fifth argument to be a number!").ThrowAsJavaScriptException();
        return Napi::Boolean::New(env, false);
    }
    if (!info[5].IsUndefined() && !info[5].IsNumber())
    {
        Napi::Error::New(env, "publish: expects sixth argument to be a number!").ThrowAsJavaScriptException();
        return Napi::Boolean::New(env, false);
    }

    // Arg1
    Napi::String eventName = info[0].As<Napi::String>();
    // Arg2
    Napi::String data = info[1].As<Napi::String>();
    // Arg3
    Napi::Number ttl = Napi::Number::New(env, DEFAULT_TTL);
    // Arg4
    Event_Type eventTypeEnum = PUBLIC;
    // Arg5
    Event_Flags eventFlagEnum = WITH_ACK;
    // Arg6
    Napi::Number msg_key = Napi::Number::New(env, 0);

    if (!info[2].IsUndefined())
    {
        ttl = info[2].As<Napi::Number>();
    }

    if (!info[3].IsUndefined())
    {

        char eventType = info[3].As<Napi::String>().Utf8Value()[0];
        eventTypeEnum = (Event_Type)eventType;
        }

    if (!info[4].IsUndefined())
    {
        int eventFlagEnum = info[4].As<Napi::Number>();
    }

    if (!info[5].IsUndefined())
    {
        msg_key = info[5].As<Napi::Number>();
    }

    bool result = trackleLibraryInstance.publish(eventName ? eventName.Utf8Value().c_str() : "",
                                                 data ? data.Utf8Value().c_str() : "",
                                                 ttl.Int32Value(),
                                                 eventTypeEnum,
                                                 eventFlagEnum,
                                                 msg_key.Uint32Value());

    LOG(TRACE, "publish was correctly done");

    return Napi::Boolean::New(env, result);
}
/*
 *********************************
 *  setUpdateStateCallback  *
 *********************************
 */
// codici per int  1: succes -1: error -2: un-auth (not the owner is making the call)
int UpdateStateCallback(const char *function_key, const char *arg, ...)
{
    LOG(TRACE, "Called UpdateStateCallback");

    auto iterator = systemCallbacksMap.find(UPDATE_STATE_REF_CB);
    Napi::Value result;
    if (iterator != systemCallbacksMap.end())
    {
        Napi::Env env = iterator->second.Env();
        // const char *strData = static_cast<const char *>(data);
        // LOG(INFO, "Data pointed by data: %s", strData);

        result = iterator->second.Call({Napi::String::New(env, function_key), Napi::String::New(env, arg)});
    }
    else
    {

        LOG(ERROR, "UDATE_STATE_REF_CB: Callback \"%s\" not found in map.", UPDATE_STATE_REF_CB.c_str());
        return -1;
    }

    return result
               ? result.ToNumber().Uint32Value()
               : -1;
}

void setUpdateStateCallback(const Napi::CallbackInfo &info)
{
    LOG(TRACE, "Called setUpdateStateCallback");

    Napi::Env env = info.Env();

    if (info.Length() != 1)
    {
        Napi::Error::New(env, "setUpdateStateCallback: expects exactly one argument as callback!").ThrowAsJavaScriptException();
        return;
    }

    if (!info[0].IsFunction())
    {
        Napi::Error::New(env, "setUpdateStateCallback: expect a callback function!").ThrowAsJavaScriptException();
        return;
    }

    Napi::FunctionReference refCb = Napi::Persistent(info[0].As<Napi::Function>());
    refCb.SuppressDestruct();

    // Create a pair of <string,reference> to call in setSleepCallback
    systemCallbacksMap.emplace(std::make_pair<std::string, Napi::FunctionReference>(std::string(UPDATE_STATE_REF_CB), std::move(refCb)));

    trackleLibraryInstance.setUpdateStateCallback(UpdateStateCallback);

    LOG(TRACE, "setUpdateStateCallback was correctly done");

    return;
}
/*
 *************
 *  syncState  *
 *************
 */
Napi::Boolean syncState(const Napi::CallbackInfo &info)
{
    LOG(INFO, "Called syncState");

    Napi::Env env = info.Env();

    if (!info[0].IsString())
    {
        Napi::Error::New(env, "SyncState: expects data argument to be a string!").ThrowAsJavaScriptException();
        return Napi::Boolean::New(env, false);
    }

    // Arg1
    Napi::String data = info[0].As<Napi::String>();

    bool result = trackleLibraryInstance.syncState(data ? data.Utf8Value().c_str() : "");

    LOG(INFO, "syncState was correctly done");

    return Napi::Boolean::New(env, result);
}
/*
 *************
 *  connectionStatusCallback  *
 *************
 */
void ConnectionStatusCallback(Connection_Status_Type status)

{
    LOG(TRACE, "Called ConnectionStatusCallback %d", status);

    auto iterator = systemCallbacksMap.find(CONNECTION_STATUS_REF_CB);
    Napi::Value result;
    if (iterator != systemCallbacksMap.end())
    {
        Napi::Env env = iterator->second.Env();
        // const char *strData = static_cast<const char *>(data);
        // LOG(INFO, "Data pointed by data: %s", strData);

        result = iterator->second.Call({Napi::Number::New(env, status)});
    }
    else
    {

        LOG(ERROR, "UDATE_STATE_REF_CB: Callback \"%s\" not found in map.", CONNECTION_STATUS_REF_CB.c_str());
        return;
    }

    return;
}

void setConnectionStatusCallback(const Napi::CallbackInfo &info)
{
    LOG(TRACE, "Called setConnectionStatusCallback");

    Napi::Env env = info.Env();

    if (info.Length() != 1)
    {
        Napi::Error::New(env, "setConnectionStatusCallback: expects exactly one argument as callback!").ThrowAsJavaScriptException();
        return;
    }

    if (!info[0].IsFunction())
    {
        Napi::Error::New(env, "setConnectionStatusCallback: expect a callback function!").ThrowAsJavaScriptException();
        return;
    }

    Napi::FunctionReference refCb = Napi::Persistent(info[0].As<Napi::Function>());
    refCb.SuppressDestruct();

    // Create a pair of <string,reference> to call in setSleepCallback
    systemCallbacksMap.emplace(std::make_pair<std::string, Napi::FunctionReference>(std::string(CONNECTION_STATUS_REF_CB), std::move(refCb)));

    trackleLibraryInstance.setConnectionStatusCallback(ConnectionStatusCallback);

    LOG(TRACE, "setConnectionStatusCallback was correctly done");

    return;
}

/*
 *************
 *  Subscribe  *
 *************
 */

bool startsWith(const std::string &str, const std::string &prefix)
{
    if (str.size() < prefix.size())
    {
        return false;
    }
    for (size_t i = 0; i < prefix.size(); ++i)
    {
        if (str[i] != prefix[i])
        {
            return false;
        }
    }
    return true;
}
EventHandler defaultHandler = [](const char *name, const char *data)
{
    for (const auto &entry : subscribeCallbacksMap)
    {
        std::string nameStr = name;
        std::string entryFirstStr = entry.first;

        if (startsWith(nameStr, entryFirstStr))
        {

            Napi::Env env = entry.second.Env();
            Napi::Value result = entry.second.Call({Napi::String::New(env, name), Napi::String::New(env, data)});
            if (result.IsEmpty() || result.IsUndefined())
            {
                LOG(ERROR, "defaultHandler: Callback \"%s\" returned an error or is not defined properly.", entry.first.c_str());
            }
        }
    }
};

Napi::Boolean subscribe(const Napi::CallbackInfo &info)
{
    LOG(ERROR, "Called Subscribe");
    bool result = false;
    Napi::Env env = info.Env();

    if (info.Length() < 2 || info.Length() > 4)
    {
        Napi::Error::New(env, "subscribe: expects 2 to 4 arguments!").ThrowAsJavaScriptException();
        return Napi::Boolean::New(env, false);
    }

    if (!info[0].IsString())
    {
        Napi::Error::New(env, "subscribe: expects first argument to be a string!").ThrowAsJavaScriptException();
        return Napi::Boolean::New(env, false);
    }

    if (!info[1].IsFunction())
    {
        Napi::Error::New(env, "subscribe: expects second argument to be a function!").ThrowAsJavaScriptException();
        return Napi::Boolean::New(env, false);
    }
    if (info.Length() == 4)
    {
        if (!info[3].IsString())
        {
            Napi::Error::New(env, "subscribe: expects 4th argument to be a string!").ThrowAsJavaScriptException();
            return Napi::Boolean::New(env, false);
        }
    }

    std::string subFunName = info[0].ToString().Utf8Value();
    Napi::FunctionReference refCb = Napi::Persistent(info[1].As<Napi::Function>());
    refCb.SuppressDestruct();

    Subscription_Scope_Type subScopeEnum;

    if (info.Length() == 3)
    {
        if (!info[2].IsNumber())
        {
            Napi::Error::New(env, "getFunction: expects third argument to be a number!").ThrowAsJavaScriptException();
            return Napi::Boolean::New(env, false);
        }
        subScopeEnum = (Subscription_Scope_Type)info[2].As<Napi::Number>().Uint32Value();
        result = trackleLibraryInstance.subscribe(subFunName.c_str(), defaultHandler, subScopeEnum);
    }
    else if ((info.Length() == 4))
    {

        if (!info[2].IsNumber())
        {

            std::string deviceId = info[3].ToString().Utf8Value();

            result = trackleLibraryInstance.subscribe(subFunName.c_str(), defaultHandler, deviceId.c_str());
        }

        else if (info[2].IsNumber() && info[3].IsString())
        {
            subScopeEnum = (Subscription_Scope_Type)info[2].As<Napi::Number>().Uint32Value();
            std::string deviceId = info[3].ToString().Utf8Value();
            result = trackleLibraryInstance.subscribe(subFunName.c_str(), defaultHandler, subScopeEnum, deviceId.c_str());
        }
    }

    if (info.Length() == 2)
    {

        result = trackleLibraryInstance.subscribe(subFunName.c_str(), defaultHandler);
    }

    if (result)
    {
        subscribeCallbacksMap.emplace(std::make_pair<std::string, Napi::FunctionReference>(std::string(subFunName), std::move(refCb)));
        LOG(ERROR, "Subscribe was correctly done");
    }
    else
    {
        LOG(ERROR, "Subscribe wasn't correctly done");
    }
    return Napi::Boolean::New(env, result);
}

/*
 *************
 *  unSubscribe  *
 *************
 */

Napi::Boolean unSubscribe(const Napi::CallbackInfo &info)
{
    LOG(TRACE, "Called unSubscribe");
    Napi::Env env = info.Env();

    if (info.Length() >= 1)
    {
        Napi::Error::New(env, "unSubscribe: expects to not have args").ThrowAsJavaScriptException();
        return Napi::Boolean::New(env, false);
    }

    trackleLibraryInstance.unsubscribe();
    subscribeCallbacksMap.clear();

    return Napi::Boolean::New(env, true);
}