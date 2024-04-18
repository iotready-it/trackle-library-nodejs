#ifndef _TRACKLE_API_
#define _TRACKLE_API_

#include <napi.h>
#include <defines.h>

// Constant key names for map reference callbacks
static const std::string REF_CB_PREFIX = "#CX#_";
static const std::string LOG_REF_CB = REF_CB_PREFIX + "log_ref_cb";
static const std::string MILLIS_REF_CB = REF_CB_PREFIX + "millis_ref_cb";
static const std::string SEND_REF_CB = REF_CB_PREFIX + "send_ref_cb";
static const std::string RECEIVE_REF_CB = REF_CB_PREFIX + "receive_ref_cb";
static const std::string CONNECT_REF_CB = REF_CB_PREFIX + "connect_ref_cb";
static const std::string DISCONNECT_REF_CB = REF_CB_PREFIX + "disconnect_ref_cb";
static const std::string SYSTEM_TIME_REF_CB = REF_CB_PREFIX + "system_time_ref_cb";
static const std::string SYS_REBOOT_REF_CB = REF_CB_PREFIX + "sys_reboot_ref_cb";
static const std::string COMPLETE_PUBLISH_REF_CB = REF_CB_PREFIX + "complete_publish_ref_cb";
static const std::string UPDATE_STATE_REF_CB = REF_CB_PREFIX + "update_state_ref_cb";
static const std::string CONNECTION_STATUS_REF_CB = REF_CB_PREFIX + "connection_status_ref_cb";

// Map to store Callbacks reference
static std::unordered_map<std::string, Napi::FunctionReference> callbacksMap;

// Setup Config
Napi::Number getMaxDeviceIdLength(const Napi::CallbackInfo &info);
Napi::Number getMaxDevicePrivateKeyLength(const Napi::CallbackInfo &info);

void setLogCallback(const Napi::CallbackInfo &info);
void setLogLevel(const Napi::CallbackInfo &info);
void setEnabled(const Napi::CallbackInfo &info);
void setFirmwareVersion(const Napi::CallbackInfo &info);
void setProductId(const Napi::CallbackInfo &info);
void setOtaMethod(const Napi::CallbackInfo &info);
void setConnectionType(const Napi::CallbackInfo &info);

// Inizialization
void setMillis(const Napi::CallbackInfo &info);

// Authentication
void setDeviceId(const Napi::CallbackInfo &info);
void setKeys(const Napi::CallbackInfo &info);

// Config communication
void setSendCallback(const Napi::CallbackInfo &info);
void setReceiveCallback(const Napi::CallbackInfo &info);
void setConnectCallback(const Napi::CallbackInfo &info);
void setOverrideConnection(const Napi::CallbackInfo &info);
void setDisconnectCallback(const Napi::CallbackInfo &info);

void setSystemTimeCallback(const Napi::CallbackInfo &info);
void setSystemRebootCallback(const Napi::CallbackInfo &info);
void setPublishHealthCheckInterval(const Napi::CallbackInfo &info);
void setCompletedPublishCallback(const Napi::CallbackInfo &info);
void setConnectionStatusCallback(const Napi::CallbackInfo &info);

// Connection
Napi::Number connect(const Napi::CallbackInfo &info);
void disconnect(const Napi::CallbackInfo &info);
void loop(const Napi::CallbackInfo &info);

Napi::Boolean post(const Napi::CallbackInfo &info);
Napi::Boolean get(const Napi::CallbackInfo &info);

Napi::Boolean publish(const Napi::CallbackInfo &info);

Napi::Boolean syncState(const Napi::CallbackInfo &info);

void setUpdateStateCallback(const Napi::CallbackInfo &info);

class CallbackWrapper
{
public:
    CallbackWrapper();
    ~CallbackWrapper();
    void setWrapper(napi_env env, napi_value callback);
    int callCallback(const char *paramString);

private:
    napi_env m_env;
    napi_ref m_callback;
    static napi_value jsCallback(napi_env env, napi_callback_info info);
};

Napi::Value setEmitter(const Napi::CallbackInfo &info);

#endif