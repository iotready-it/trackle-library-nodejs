const trackle = require("bindings")("trackle_wrapper.node");

export enum Log_Level {
  TRACKLE_TRACE = 1,
  TRACKLE_INFO = 30,
  TRACKLE_WARN = 40,
  TRACKLE_ERROR = 50,
  TRACKLE_PANIC = 60,
  TRACKLE_NO_LOG = 70,
}

export enum Ota_Method {
  NO_OTA = 0,
  PUSH = 1,
  SEND_URL = 2,
}

export enum Connection_Type {
  CONNECTION_TYPE_UNDEFINED = 0,
  CONNECTION_TYPE_WIFI = 1,
  CONNECTION_TYPE_ETHERNET = 2,
  CONNECTION_TYPE_CELLULAR = 3,
  CONNECTION_TYPE_LPWA = 4,
}

export enum Function_PermissionDef {
  ALL_USERS = 1,
  OWNER_ONLY = 2,
}

export enum Data_TypeDef {
  VAR_BOOLEAN = 1,
  VAR_INT = 2,
  VAR_STRING = 4,
  VAR_CHAR = 5,
  VAR_LONG = 6,
  VAR_JSON = 7,
  VAR_DOUBLE = 9,
}

export enum Event_Type {
  PUBLIC = "e",
  PRIVATE = "E",
}

export enum Event_Flags {
  EMPTY_FLAGS = 0,
  NO_ACK = 0x2,
  WITH_ACK = 0x8,
  ALL_FLAGS = NO_ACK | WITH_ACK,
}

/**
 * Represents the TrackleWrapper interface.
 */
interface TrackleWrapper {
  Log_Level: any;
  Function_PermissionDef: any;
  Data_TypeDef: any;

  /**
   * Gets the maximum length of the device ID.
   * @returns The maximum length of the device ID.
   */
  getMaxDeviceIdLength(): number;

  /**
   * Gets the maximum length of the device private key.
   * @returns The maximum length of the device private key.
   */
  getMaxDevicePrivateKeyLength(): number;

  /**
   * Sets the log callback function.
   * @param callback - The log callback function.
   */
  setLogCallback(
    callback: (
      msg: string,
      level: number,
      category: string,
      attribute?: Buffer,
      reserved?: Buffer
    ) => void
  ): void;

  /**
   * Sets the log level.
   * @param logLevel - The log level.
   */
  setLogLevel(logLevel: Log_Level): void;

  /**
   * Sets the enabled status.
   * @param status - The enabled status.
   */
  setEnabled(status: boolean): void;

  /**
   * Sets the firmware version.
   * @param firmwareVersion - The firmware version.
   */
  setFirmwareVersion(firmwareVersion: number): void;

  /**
   * Sets the firmware version.
   * @param productid - The product id.
   */
  setProductId(productid: number): void;

  /**
   * Sets the OTA method.
   * @param method - The OTA method.
   */
  setOtaMethod(method: Ota_Method): void;

  /**
   * Sets the connection type.
   * @param connType - The connection type.
   */
  setConnectionType(connType: Connection_Type): void;

  /**
   * Sets the millis callback function.
   * @param callback - The millis callback function.
   */
  setMillis(callback: () => number): void;

  /**
   * Sets the device ID.
   * @param deviceId - The device ID.
   */
  setDeviceId(deviceId: String): void;

  /**
   * Sets the device keys.
   * @param deviceKey - The device keys.
   */
  setKeys(deviceKey: Uint8Array): void;

  /**
   * Sets the send callback function.
   * @default // With no parameters, the function will be called with the default c++ libraries.
   * @param callback - The send callback function.
   * @returns The result of the operation.
   */
  setSendCallback(
    callback?: (
      buffer: Buffer,
      bufferLen: number,
      tmp: any
    ) => number | Promise<number>
  ): void;

  /**
   * Sets the receive callback function.
   * @default // With no parameters, the function will be called with the default c++ libraries.
   * @param callback - The receive callback function.
   * @returns The result of the operation.
   */
  setReceiveCallback(
    callback?: (
      buffer: Buffer,
      bufferLen: number,
      tmp: any
    ) => number | Promise<number>
  ): number;

  /**
   * Sets the connect callback function.
   * @default // With no parameters, the function will be called with the default c++ libraries.
   * @param callback - The connect callback function.
   * @returns The result of the operation.
   */
  setConnectCallback(
    callback?: (address: string, port: number) => number | Promise<number>
  ): void;

  /**
   * Sets the disconnect callback function.
   * @default // With no parameters, the function will be called with the default c++ libraries.
   * @param callback - The disconnect callback function.
   * @returns The result of the operation.
   */
  setDisconnectCallback(callback?: () => number | Promise<number>): void;

  /**
   * Sets the system time callback function.
   * @param callback - The system time callback function.
   */
  setSystemTimeCallback(
    callback: (time: number, param: number, data?: Buffer) => void
  ): void;

  /**
   * Sets the system reboot callback function.
   * @param callback - The system reboot callback function.
   */
  setSystemRebootCallback(callback: (data: string) => void): void;

  /**
   * Sets the publish health check interval.
   * @param interval - The publish health check interval.
   */
  setPublishHealthCheckInterval(interval: number): void;

  /**
   * Sets the completed publish callback function.
   * @param callback - The completed publish callback function.
   */
  setCompletedPublishCallback(
    callback: (
      error: number,
      callbackData?: number
    ) => void
  ): void;

  /**
   * Connects to the server.
   * @returns The result of the operation.
   */
  connect(): number;

  /**
   * Disconnects from the server.
   */
  disconnect(): void;

  /**
   * Performs the main loop.
   */
  loop(): void;

  /**
   * Posts a function to the server.
   * @param callbackName - The name of the callback function.
   * @param callback - The callback function.
   * @param permission - The function permission definition.
   * @returns A boolean indicating if the operation was successful.
   */
  post(
    callbackName: string,
    callback: (arg: string, args?: []) => number,
    permission: Function_PermissionDef
  ): boolean;

  /**
   * Gets a function from the server.
   * @param callbackName - The name of the callback function.
   * @param callback - The callback function.
   * @param returnType - The data type of the return value.
   * @returns A boolean indicating if the operation was successful.
   */
  get(
    callbackName: string,
    callback: (arg: string) => any,
    returnType: Data_TypeDef
  ): boolean;

  /**
   * Publishes an event to the server.
   * @param eventName - The name of the event.
   * @param data - The data to be published.
   * @param ttl - The time-to-live of the event.
   * @param eventType - The type of the event.
   * @param eventFlags - The flags of the event.
   * @param msgKey - The message key.
   * @returns A boolean indicating if the operation was successful.
   */
  publish(
    eventName: string,
    data: string,
    ttl?: number,
    eventType?: Event_Type,
    eventFlags?: Event_Flags,
    msgKey?: number
  ): boolean;

  /**
   * setUpdateStateCallback to the server.
   * @param arg - The name of the func.
   * @param function_key - the key of the func.
   * @returns 1 if it was succesful -1 unsuccesful.
   */
  setUpdateStateCallback(
    callback: (
      function_key: string,
      arg: string
    ) => number | Promise<number>
  ): void;

    /**
   * setConnectionStatusCallback to the server.
   * @param status - The name of the func.
   */
    setConnectionStatusCallback(
      callback: (
        status: number
      ) => void
    ): void;
  

  /**
   * syncState an event to the server.
   * @param data - The data to be published.
   * @returns A boolean indicating if the operation was successful.
   */
  syncState(
    data: string,
  ): boolean;

  /**
   * syncState an event to the server.
   * @param ipAddress - The Ip of your server.
   * @param port - The port of your server.
   * @returns A boolean indicating if the operation was successful.
   */
  setOverrideConnection(
    ipAddress: string,
    port: number
  ): void;


}

const handler = {};

const proxy: TrackleWrapper = new Proxy(trackle, handler);

// set default callbacks warking only for posix systems
proxy.setSendCallback();
proxy.setReceiveCallback();
proxy.setConnectCallback();
proxy.setDisconnectCallback();

export default proxy;
