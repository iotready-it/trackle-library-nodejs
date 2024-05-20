"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.Event_Flags = exports.Event_Type = exports.Data_TypeDef = exports.Function_PermissionDef = exports.Connection_Type = exports.Subscription_Scope_Type = exports.Ota_Method = exports.Log_Level = void 0;
const trackle = require("bindings")("trackle_wrapper.node");
var Log_Level;
(function (Log_Level) {
    Log_Level[Log_Level["TRACKLE_TRACE"] = 1] = "TRACKLE_TRACE";
    Log_Level[Log_Level["TRACKLE_INFO"] = 30] = "TRACKLE_INFO";
    Log_Level[Log_Level["TRACKLE_WARN"] = 40] = "TRACKLE_WARN";
    Log_Level[Log_Level["TRACKLE_ERROR"] = 50] = "TRACKLE_ERROR";
    Log_Level[Log_Level["TRACKLE_PANIC"] = 60] = "TRACKLE_PANIC";
    Log_Level[Log_Level["TRACKLE_NO_LOG"] = 70] = "TRACKLE_NO_LOG";
})(Log_Level || (exports.Log_Level = Log_Level = {}));
var Ota_Method;
(function (Ota_Method) {
    Ota_Method[Ota_Method["NO_OTA"] = 0] = "NO_OTA";
    Ota_Method[Ota_Method["PUSH"] = 1] = "PUSH";
    Ota_Method[Ota_Method["SEND_URL"] = 2] = "SEND_URL";
})(Ota_Method || (exports.Ota_Method = Ota_Method = {}));
var Subscription_Scope_Type;
(function (Subscription_Scope_Type) {
    Subscription_Scope_Type[Subscription_Scope_Type["MY_DEVICES"] = 0] = "MY_DEVICES";
    Subscription_Scope_Type[Subscription_Scope_Type["ALL_DEVICES"] = 1] = "ALL_DEVICES";
})(Subscription_Scope_Type || (exports.Subscription_Scope_Type = Subscription_Scope_Type = {}));
var Connection_Type;
(function (Connection_Type) {
    Connection_Type[Connection_Type["CONNECTION_TYPE_UNDEFINED"] = 0] = "CONNECTION_TYPE_UNDEFINED";
    Connection_Type[Connection_Type["CONNECTION_TYPE_WIFI"] = 1] = "CONNECTION_TYPE_WIFI";
    Connection_Type[Connection_Type["CONNECTION_TYPE_ETHERNET"] = 2] = "CONNECTION_TYPE_ETHERNET";
    Connection_Type[Connection_Type["CONNECTION_TYPE_CELLULAR"] = 3] = "CONNECTION_TYPE_CELLULAR";
    Connection_Type[Connection_Type["CONNECTION_TYPE_LPWA"] = 4] = "CONNECTION_TYPE_LPWA";
})(Connection_Type || (exports.Connection_Type = Connection_Type = {}));
var Function_PermissionDef;
(function (Function_PermissionDef) {
    Function_PermissionDef[Function_PermissionDef["ALL_USERS"] = 1] = "ALL_USERS";
    Function_PermissionDef[Function_PermissionDef["OWNER_ONLY"] = 2] = "OWNER_ONLY";
})(Function_PermissionDef || (exports.Function_PermissionDef = Function_PermissionDef = {}));
var Data_TypeDef;
(function (Data_TypeDef) {
    Data_TypeDef[Data_TypeDef["VAR_BOOLEAN"] = 1] = "VAR_BOOLEAN";
    Data_TypeDef[Data_TypeDef["VAR_INT"] = 2] = "VAR_INT";
    Data_TypeDef[Data_TypeDef["VAR_STRING"] = 4] = "VAR_STRING";
    Data_TypeDef[Data_TypeDef["VAR_CHAR"] = 5] = "VAR_CHAR";
    Data_TypeDef[Data_TypeDef["VAR_LONG"] = 6] = "VAR_LONG";
    Data_TypeDef[Data_TypeDef["VAR_JSON"] = 7] = "VAR_JSON";
    Data_TypeDef[Data_TypeDef["VAR_DOUBLE"] = 9] = "VAR_DOUBLE";
})(Data_TypeDef || (exports.Data_TypeDef = Data_TypeDef = {}));
var Event_Type;
(function (Event_Type) {
    Event_Type["PUBLIC"] = "e";
    Event_Type["PRIVATE"] = "E";
})(Event_Type || (exports.Event_Type = Event_Type = {}));
var Event_Flags;
(function (Event_Flags) {
    Event_Flags[Event_Flags["EMPTY_FLAGS"] = 0] = "EMPTY_FLAGS";
    Event_Flags[Event_Flags["NO_ACK"] = 2] = "NO_ACK";
    Event_Flags[Event_Flags["WITH_ACK"] = 8] = "WITH_ACK";
    Event_Flags[Event_Flags["ALL_FLAGS"] = 10] = "ALL_FLAGS";
})(Event_Flags || (exports.Event_Flags = Event_Flags = {}));
const handler = {};
const proxy = new Proxy(trackle, handler);
// set default callbacks warking only for posix systems
proxy.setSendCallback();
proxy.setReceiveCallback();
proxy.setConnectCallback();
proxy.setDisconnectCallback();
exports.default = proxy;
