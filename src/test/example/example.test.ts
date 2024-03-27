import path from "path";
import TrackleAuth from "../../app/entities/trackleAuth";
import TrackleCallback from "./example.callbacks";

import trackle, {
  Log_Level,
  Function_PermissionDef,
  Data_TypeDef,
  Ota_Method,
  Connection_Type,
  Event_Type,
  Event_Flags,
} from "../../app/proxy/trackleWrapper";

const relativeKeyDirPath = "../resources/keys/";
const DEVICEID = "10af10750a1783413cbcbddd";
const CERTIFICATE_DIR_PATH = path.resolve(__dirname, relativeKeyDirPath);

const auth = new TrackleAuth(DEVICEID, CERTIFICATE_DIR_PATH);

console.log("Starting up NodeJS example ...\n");
console.log(`DeviceID: ${DEVICEID}`);

trackle.setLogLevel(Log_Level.TRACKLE_INFO);
trackle.setLogCallback(TrackleCallback.setLog);
trackle.setMillis(TrackleCallback.setMillis); // BUG: se non dichiarato subito, non vengono abilitati i log
trackle.setDeviceId(auth.getDeviceId(trackle.getMaxDeviceIdLength()));

// Initialize Trackle
trackle.setEnabled(true);

// Set cloud credentials
trackle.setKeys(auth.getDeviceKey(trackle.getMaxDevicePrivateKeyLength()));
trackle.setFirmwareVersion(100);
trackle.setOtaMethod(Ota_Method.SEND_URL);
trackle.setConnectionType(Connection_Type.CONNECTION_TYPE_WIFI);

// Registering internal callbacks
trackle.setSendCallback();
trackle.setReceiveCallback();
trackle.setConnectCallback();
trackle.setDisconnectCallback();
trackle.setSystemTimeCallback(TrackleCallback.systemTimeCallback);
trackle.setSystemRebootCallback(TrackleCallback.systemRebootCallback);
trackle.setPublishHealthCheckInterval(60 * 60 * 1000);
trackle.setCompletedPublishCallback(TrackleCallback.completedPublishCallback);

// TODO: Domandare se è giusto che il nome della funzione è al massimo di 14 caratteri!
//       dopodichè viene interpretato male e non permette visualizzazione di nessun altro parametro POST

// Registering POST functions callable from cloud
trackle.post(
  "postSuccessasdasdadadasdaasdsa",
  TrackleCallback.postSuccess,
  Function_PermissionDef.ALL_USERS
);
trackle.post(
  "postFailure",
  TrackleCallback.postFailure,
  Function_PermissionDef.ALL_USERS
);

// Registering values GETtable from cloud as result of a function call
trackle.get("getString", TrackleCallback.getString, Data_TypeDef.VAR_STRING);
trackle.get("getInt", TrackleCallback.getInt, Data_TypeDef.VAR_INT);
trackle.get("getLong", TrackleCallback.getLong, Data_TypeDef.VAR_LONG);
trackle.get("getDouble", TrackleCallback.getDouble, Data_TypeDef.VAR_DOUBLE);
trackle.get("getChar", TrackleCallback.getChar, Data_TypeDef.VAR_CHAR);
trackle.get("getJson", TrackleCallback.getJson, Data_TypeDef.VAR_JSON);
trackle.get("getBool", TrackleCallback.getBoolean, Data_TypeDef.VAR_BOOLEAN);

// Intercept the ctrl+c signal to stop the program
let shutdown = false;
let prevPubMillis = 0;
let msg_key = 0;

process.on("SIGINT", function () {
  console.log("Caught interrupt signal");

  shutdown = true;
});

console.log("Startup completed. Running...");

trackle.connect();

console.log("Starting Loop...");
const time = setInterval(async () => {
  trackle.loop();

  if (shutdown) {
    trackle.disconnect();
    process.exit();
  }

  if (TrackleCallback.setMillis() - prevPubMillis > 5000) {
    trackle.publish(
      "greetings",
      "Hello, World!",
      30,
      Event_Type.PRIVATE,
      Event_Flags.WITH_ACK,
      msg_key
    );
    prevPubMillis = TrackleCallback.setMillis();
    msg_key++;
  }
}, 10);
