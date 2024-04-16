
# NodeJS Trackle Wrapper

## Table of contents
* [installation](#installation)
* [methods](#implemented-methods)
* [Get a Device ID and a private key](#get-a-device-id-and-a-private-key)
* [example](#example)

## Installation 
 `npm install trackle-library-nodejs`

## Get a Device ID and a private key
* Create an account on Trackle Cloud (https://trackle.cloud/)
* Open "My Devices" section from the drawer
* Click the button "Claim a device"
* Select the link "I don't have a device id", then Continue
* The Device Id will be shown on the screen and the private key file will be download with name <device_id>.der where <device_id> is Device ID taken from Trackle.

## Implemented methods  
to see the implemented methods you can check on this link [example](#example) or import trackle from the installed library and check it there, with the library you also will import 
* `Log_Level`
* `Function_PermissionDef`
* `Data_TypeDef`
* `Ota_Method`
* `Connection_Type`
* `Event_Type`
* `Event_Flags` 
this are all enum declareted types that will help you with the values that function expects

## example 

```
import fs from "fs";

import trackle, {
  Log_Level,
  Function_PermissionDef,
  Data_TypeDef,
  Connection_Type,
  Event_Type,
  Event_Flags
} from "trackle-library-nodejs";

// Define callbacks

const getMillis = () => {
  const date = new Date();
  const ms: number = date.getTime();
  return ms;
};

const setLog = (msg: string, level: number, category: string): void => {
  if (category.length === 0) {
    console.log(`[${level}] [] ${msg}`);
  } else {
    console.log(`[${level}] [${category}] ${msg}`);
  }
};

// Post callbacks declaration 

const post1 = (name: string): number => {
  console.log("called post1 : " + name);
    console.log("Post1 - Pippo");
    return 1;
}

const post2 = (name: string): number => {
  if (name) {
    console.log("Post2 - Pluto");
    return 0;
  }

  return -1;
};

const postSuccess= (name: string): number => {
  console.log(`Richiamata callback postSuccess, arg: ${name}`);
  return 1;
}

const postFailure = (name: string): number => {
  console.log(`Richiamata callback postFailure, arg: ${name}`);
  return -1;
};

// GET CALLBACKS DECLARATION

const getString = (name: string): string => {
  console.log("Called getString : " + name);
  if (name) {
    console.log("getString - ");
    return "Hello";
  }

  return "World";
};

const getChar = (name: string): string => {
  console.log("Called getChar : " + name);
  if (name) {
    console.log("getChar - ");
    return "C";
  }

  return "a";
};

const getInt = (name: string): number => {
  console.log("Called getInt : " + name);
  if (name) {
    console.log("getInt - ");
    return 5678;
  }

  return 1234;
};

const getBoolean = (name: string): boolean => {
  console.log("Called getBoolean : " + name);
  if (name) {
    console.log("getBoolean - ");
    return true;
  }

  return false;
};

const getDouble = (name: string): number => {
  console.log("Called getDouble : " + name);
  if (name) {
    console.log("getDouble - ");
    return 1.4563333;
  }

  return 0.4567812;
};


const getJson = (name: string): string => {
  console.log("Called getJson : " + name);
  if (name) {
    console.log("getJson - ");
    return JSON.stringify({ name: "pippo", surname: "pluto" });
  }

  return JSON.stringify({ name: "Hello", surname: "World" });
};

const systemTimeCallback = (
  time: number,
  param: number,
  data: Buffer | undefined
): void => {
  console.log(time);

};

// Called when a publish is completed
const completedPublishCallback = (
  error: number,
  callbackData?: number
): void => {
  console.log("msg key: "+callbackData)
  console.log("error: "+error)

};

const UpdateStateCallback = (
  function_key: string,
  arg: string
): number => {
  console.log("key value: "+function_key)
  console.log("arg: "+arg)
  return -1;

};

const ConnectionStatusCallback = (
  status: number,
) => {
  if (firstConnect && status === 2) {
    trackle.publish(
      "First",
      "Hello",
      30,
      Event_Type.PUBLIC,
      Event_Flags.WITH_ACK,
      1
    );
    firstConnect = false;
  }
};

const systemRebootCallback = (data: string) => {
  console.log("Reboot request ignored!");

};

let prevPubMillis = 0;
let msg_key = 1;
let firstConnect = true;
const PRIVATE_KEY = fs.readFileSync("Path_To_Your_.der_Key_file");

trackle.setMillis(getMillis); 
trackle.setLogLevel(Log_Level.TRACKLE_INFO);
trackle.setLogCallback(setLog);

// Set cloud credentials
trackle.setDeviceId("Your_Device_ID");
trackle.setKeys(PRIVATE_KEY);

trackle.setFirmwareVersion(1);

trackle.setConnectionType(Connection_Type.CONNECTION_TYPE_WIFI);

// set Callbacks

trackle.setSystemTimeCallback(systemTimeCallback);
trackle.setSystemRebootCallback(systemRebootCallback);
trackle.setCompletedPublishCallback(completedPublishCallback);
trackle.setUpdateStateCallback(UpdateStateCallback);


// Registering POST functions callable from cloud

trackle.post(
  "post1",
  post1,
  Function_PermissionDef.ALL_USERS
);
trackle.post(
  "post2",
  post2,
  Function_PermissionDef.ALL_USERS
);
trackle.post(
  "postSuccess",
 postSuccess,
  Function_PermissionDef.ALL_USERS
);
trackle.post(
  "postFailure",
  postFailure,
  Function_PermissionDef.ALL_USERS
);


// Registering GET functions callable from cloud

trackle.get("getInt", getInt, Data_TypeDef.VAR_INT);
trackle.get("getString", getString, Data_TypeDef.VAR_STRING);
trackle.get("getDouble", getDouble, Data_TypeDef.VAR_DOUBLE);
trackle.get("getChar", getChar, Data_TypeDef.VAR_CHAR);
trackle.get("getJson", getJson, Data_TypeDef.VAR_JSON);
trackle.get("getBool", getBoolean, Data_TypeDef.VAR_BOOLEAN);

trackle.setConnectionStatusCallback(ConnectionStatusCallback)

// Connection to trackle
trackle.connect();

console.log("Startup completed. Running...");
console.log("Starting Loop...");

setInterval(async () => {
  trackle.loop();

// Every 5 seconds make a publish

if (getMillis() - prevPubMillis > 5000) {
  
    trackle.publish(
      "greetings",
      "Hello, World!",
      30,
      Event_Type.PUBLIC,
      Event_Flags.WITH_ACK,
      msg_key
    );
    msg_key++;
    prevPubMillis = new Date().getTime();
  }
}, 10);

```