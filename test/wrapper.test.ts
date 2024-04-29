import trackle, {
  Log_Level,
  Connection_Type,
  Function_PermissionDef,
  Data_TypeDef,
  Event_Flags,
  Event_Type
} from "../src/index";
import assert from 'assert';
import dotenv from 'dotenv';
import fs from 'fs';
import EventEmitter from 'events';
import EventSource from 'eventsource';
import fetch from 'sync-fetch';
import axios from "axios";
import { completedPublishCallback, systemTimeCallback, setLog, getMillis } from './calbacks/utils';
import { testGetInt, testGetBool, testGetString, testGetDouble, testGetJson } from './calbacks/get';
import { testPost } from './calbacks/post';
dotenv.config();
const myEmitter = new EventEmitter();

if (process.env.DEVICE_ID) {
  const PRIVATE_KEY = fs.readFileSync("./Keys/" + process.env.DEVICE_ID + ".der");
  trackle.setKeys(PRIVATE_KEY);
  trackle.setDeviceId(process.env.DEVICE_ID);
}

const postData = JSON.stringify({
  client_id: process.env.CLIENT_ID,
  client_secret: process.env.CLIENT_SECRET,
  grant_type: 'client_credentials'
});

const getToken = () => {
  const response = fetch('https://api.trackle.io/oauth/token', {
    method: 'POST',
    body: postData,
    headers: {
      'Content-Type': 'application/json',
      'Content-Length': postData.length.toString()
    }
  });

  const data = response.json();
  return data.access_token;
};

const token = getToken();

const sseUrlWithEvents = 'https://api.trackle.io/v1/devices/' + process.env.DEVICE_ID + '/events';
const sseUrlMessages = 'https://api.trackle.io/v1/devices/' + process.env.DEVICE_ID + '/events?type=data-only';

const headers = {
  Authorization: `Bearer ${token}`
};

const es = new EventSource(sseUrlWithEvents, { headers });
// Evento "open" per controllare la connessione

trackle.setMillis(getMillis);
trackle.setLogLevel(Log_Level.TRACKLE_INFO);
trackle.setLogCallback(setLog);
trackle.setFirmwareVersion(500);
if (process.env.PRODUCT_ID) {
  trackle.setProductId(Number(process.env.PRODUCT_ID));
}
trackle.setConnectionType(Connection_Type.CONNECTION_TYPE_WIFI);
trackle.setCompletedPublishCallback(completedPublishCallback);
trackle.setSystemTimeCallback(systemTimeCallback);

trackle.setConnectionStatusCallback((status: number) => {
  if (status === 2)
    myEmitter.emit('connected', true);
});

trackle.post(
  "testPost",
  testPost,
  Function_PermissionDef.ALL_USERS
)

trackle.get("testGetInt", testGetInt, Data_TypeDef.VAR_INT);
trackle.get("testGetBool", testGetBool, Data_TypeDef.VAR_BOOLEAN);
trackle.get("testGetDouble", testGetDouble, Data_TypeDef.VAR_DOUBLE);
trackle.get("testGetString", testGetString, Data_TypeDef.VAR_CHAR);
trackle.get("testGetJson", testGetJson, Data_TypeDef.VAR_JSON);

let loopInterval: NodeJS.Timeout;
jest.setTimeout(20000);

trackle.connect();


describe('Trackle tests', () => {
  beforeEach(() => {
    loopInterval = setInterval(async () => {
      trackle.loop();
    }, 10);
  })
  afterEach(() => {
    clearInterval(loopInterval);
  })

  /*
 *************
 *  TEST CONNECTION  *
 *************
 */

  it('Should controll if the device is connecting succesfuly to Trackle', (done) => {
    myEmitter.once('connected', (connected) => {
      assert.strictEqual(connected, true);
    });

    es.addEventListener('trackle/status', (message: any) => {
      assert.strictEqual(JSON.parse(message.data).data, "online");
      done();
    });
  });

  /*
 *************
 * TEST PARAMS  *
 *************
 */

  it('should check if the device parameters are setted correctly', (done) => {
    const response = fetch('https://api.trackle.io/v1/devices/' + process.env.DEVICE_ID, {
      method: 'GET',
      headers: {
        Authorization: `Bearer ${token}`
      }
    });
    const data = response.json();
    assert.strictEqual(data.connection_type, 'wifi');
    assert.strictEqual(data.firmware_version, 500);
    if (process.env.PRODUCT_ID) {
      assert.strictEqual(data.product_id, Number(process.env.PRODUCT_ID));
    }

    assert.strictEqual(data.functions[0], "testPost");

    assert.strictEqual(data.variables.testGetInt, "int32");
    assert.strictEqual(data.variables.testGetBool, "bool");
    assert.strictEqual(data.variables.testGetDouble, "double");
    assert.strictEqual(data.variables.testGetString, "string");
    assert.strictEqual(data.variables.testGetJson, "json");

    done();
  });
  /*
   *************
   * TEST POST  *
   *************
   */
  it('should check if the testPOST function works correctly', async () => {

    const OKargs = { args: "pluto" };
    const NoOKargs = { args: "" }

    const OKresponse = await axios.post('https://api.trackle.io/v1/devices/' + process.env.DEVICE_ID + '/testPost', OKargs, {
      headers: {
        'Content-Type': 'application/json',
        Authorization: `Bearer ${token}`
      }
    });
    const NoOKresponse = await axios.post('https://api.trackle.io/v1/devices/' + process.env.DEVICE_ID + '/testPost', NoOKargs, {
      headers: {
        Authorization: `Bearer ${token}`
      }
    });

    expect(OKresponse.data.return_value).toBe(1)
    expect(NoOKresponse.data.return_value).toBe(-1)

  });
  /*
   *************
   * TEST PUBLISH  *
   *************
   */
  it('should check if the publish method works correctly', (done) => {
    trackle.publish(
      "test",
      "Hello, World!",
      30,
      Event_Type.PUBLIC,
      Event_Flags.WITH_ACK,
      1
    );
    es.addEventListener('test', (message: any) => {
      assert.strictEqual(JSON.parse(message.data).data, "Hello, World!");
      done();
    });
  });
  /*
   *************
   * TEST GET  *
   *************
   */

  /*
   *************
   *   TEST GETint  *
   *************
   */

  it('should check if the testGetInt function works correctly', async () => {
    const randomNum = Math.floor(Math.random() * 1000);

    const OKargs = { args: randomNum.toString() };
    const NoOKargs = { args: "" };

    const OKresponse = await axios.get('https://api.trackle.io/v1/devices/' + process.env.DEVICE_ID + '/testGetInt', {
      params: OKargs,
      headers: {
        'Content-Type': 'application/json',
        Authorization: `Bearer ${token}`
      }
    });

    const NoOKresponse = await axios.get('https://api.trackle.io/v1/devices/' + process.env.DEVICE_ID + '/testGetInt', {
      params: NoOKargs,
      headers: {
        'Content-Type': 'application/json',
        Authorization: `Bearer ${token}`
      }
    });

    expect(OKresponse.data.result).toBe(randomNum);
    expect(NoOKresponse.data.result).toBe(-1);
  });
  /*
*************
*   TEST GETbool  *
*************
*/

  it('should check if the testGetBool function works correctly', async () => {

    const OKargs = { args: "true" };
    const NoOKargs = { args: "" };

    const OKresponse = await axios.get('https://api.trackle.io/v1/devices/' + process.env.DEVICE_ID + '/testGetBool', {
      params: OKargs,
      headers: {
        'Content-Type': 'application/json',
        Authorization: `Bearer ${token}`
      }
    });

    const NoOKresponse = await axios.get('https://api.trackle.io/v1/devices/' + process.env.DEVICE_ID + '/testGetBool', {
      params: NoOKargs,
      headers: {
        'Content-Type': 'application/json',
        Authorization: `Bearer ${token}`
      }
    });

    expect(OKresponse.data.result).toBe(true);
    expect(NoOKresponse.data.result).toBe(false);
  });

  /*
*************
*   TEST GETstring *
*************
*/

  it('should check if the testGetString function works correctly', async () => {
    const characters = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';
    const length = 10;
    let randomString = '';
    for (let i = 0; i < length; i++) {
      randomString += characters.charAt(Math.floor(Math.random() * characters.length));
    }

    const OKargs = { args: randomString };
    const NoOKargs = { args: "" };

    const OKresponse = await axios.get('https://api.trackle.io/v1/devices/' + process.env.DEVICE_ID + '/testGetString', {
      params: OKargs,
      headers: {
        'Content-Type': 'application/json',
        Authorization: `Bearer ${token}`
      }
    });

    const NoOKresponse = await axios.get('https://api.trackle.io/v1/devices/' + process.env.DEVICE_ID + '/testGetString', {
      params: NoOKargs,
      headers: {
        'Content-Type': 'application/json',
        Authorization: `Bearer ${token}`
      }
    });

    expect(OKresponse.data.result).toBe(randomString);
    expect(NoOKresponse.data.result).toBe("noArgs");
  });
  /*
 *************
 *   TEST GETdouble *
 *************
 */

  it('should check if the testGetDouble function works correctly', async () => {
    const randomDouble = Math.random() * 100;

    const OKargs = { args: randomDouble.toString() };
    const NoOKargs = { args: "" };

    const OKresponse = await axios.get('https://api.trackle.io/v1/devices/' + process.env.DEVICE_ID + '/testGetDouble', {
      params: OKargs,
      headers: {
        'Content-Type': 'application/json',
        Authorization: `Bearer ${token}`
      }
    });

    const NoOKresponse = await axios.get('https://api.trackle.io/v1/devices/' + process.env.DEVICE_ID + '/testGetDouble', {
      params: NoOKargs,
      headers: {
        'Content-Type': 'application/json',
        Authorization: `Bearer ${token}`
      }
    });

    expect(OKresponse.data.result).toBe(randomDouble);
    expect(NoOKresponse.data.result).toBe(3.14159265);
  });
  /*
  *************
  *   TEST GETjson *
  *************
  */

  it('should check if the testGetJson function works correctly', async () => {
    const random = Math.random() * 100;

    const OKargs = { args: random.toString() };
    const NoOKargs = { args: "" };

    const OKresponse = await axios.get('https://api.trackle.io/v1/devices/' + process.env.DEVICE_ID + '/testGetJson', {
      params: OKargs,
      headers: {
        'Content-Type': 'application/json',
        Authorization: `Bearer ${token}`
      }
    });

    const NoOKresponse = await axios.get('https://api.trackle.io/v1/devices/' + process.env.DEVICE_ID + '/testGetJson', {
      params: NoOKargs,
      headers: {
        'Content-Type': 'application/json',
        Authorization: `Bearer ${token}`
      }
    });
    expect(OKresponse.data.result.args).toBe(random.toString());
    expect(NoOKresponse.data.result.args).toBe("noArgs");
  });
  /*
  *************
  *   TEST SYNCSTATE *
  *************
  */

  if (process.env.PRODUCT_ID) {
    it('should check if the Syncstate method works correctly', (done) => {
      const random = Math.random() * 100;
      trackle.syncState(
        JSON.stringify({ hello: random.toString() })
      );
      const response = fetch('https://api.trackle.io/v1/devices/' + process.env.DEVICE_ID, {
        method: 'GET',
        headers: {
          Authorization: `Bearer ${token}`
        }
      });
      const data = response.json();
      console.log(data)
      assert.strictEqual(data.state.hello, random.toString());


      done();
    });
  } else {
    // Salta il test se PRODUCT_ID non è definito
    it.skip('should check if the Syncstate method works correctly', () => {
      console.log('Skipping test because PRODUCT_ID is not defined.');
    });
  }
  afterAll(() => {
    es.close();
  });
});
