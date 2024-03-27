import { AssertionError } from "assert";
import TrackleAuth from "../../../app/entities/trackleAuth";
import path from "path";

describe("TrackleAuth", () => {
  const deviceId = "10af10750a1783413cbcbddd";
  const relativeKeyDirPath = "../../resources/keys/";
  const keyDirPath = path.resolve(__dirname, relativeKeyDirPath);

  it("should create an instance of TrackleAuth", () => {
    const trackleAuth = new TrackleAuth(deviceId, keyDirPath);
    expect(trackleAuth).toBeInstanceOf(TrackleAuth);
  });

  describe("deviceId", () => {
    it("should throw an error if deviceId is empty", () => {
      expect(() => new TrackleAuth("", keyDirPath)).toThrowError(
        "DeviceId has no size!"
      );
    });

    it("should throw an error if the deviceId is bigger than defined max byte size", () => {
      const trackleAuth = new TrackleAuth(deviceId, keyDirPath);
      const maxBytesLength = 2;

      expect(() => {
        trackleAuth.getDeviceId(maxBytesLength);
      }).toThrow(AssertionError);
      expect(() => {
        trackleAuth.getDeviceId(maxBytesLength);
      }).toThrow("The deviceId length (24) is greater than 2 bytes");
    });

    it("should return the deviceId as Uint8Array", () => {
      const trackleAuth = new TrackleAuth(deviceId, keyDirPath);
      const maxBytesLength = 24;

      const deviceIdBytes = trackleAuth.getDeviceId(maxBytesLength);
      expect(deviceIdBytes.length).toBeLessThanOrEqual(maxBytesLength);
      expect(deviceIdBytes).toBeInstanceOf(Uint8Array);
    });
  });

  describe("deviceKey", () => {
    it("should throw an error if deviceKey is empty", () => {
      const invalidDeviceId = "x10af10750a1783413cbcbddd";

      const trackleAuth = new TrackleAuth(invalidDeviceId, keyDirPath);
      const maxBytesLength = 122;

      expect(() => trackleAuth.getDeviceKey(maxBytesLength)).toThrow(
        AssertionError
      );
      expect(() => trackleAuth.getDeviceKey(maxBytesLength)).toThrow(
        "DeviceKey has no data!"
      );
    });

    it("should throw an error if certificate file is not found", () => {
      const invalidKeyDirPath = "/path/to/invalid/keys";

      expect(() => new TrackleAuth(deviceId, invalidKeyDirPath)).toThrow(
        AssertionError
      );
      expect(() => new TrackleAuth(deviceId, invalidKeyDirPath)).toThrow(
        `Error: Certificate "${deviceId}.der" not found in directory "${invalidKeyDirPath}"!`
      );
    });

    it("should throw an error if the deviceKey is bigger than defined max byte size", () => {
      const trackleAuth = new TrackleAuth(deviceId, keyDirPath);
      const maxBytesLength = 1;

      expect(() => {
        trackleAuth.getDeviceKey(maxBytesLength);
      }).toThrow(AssertionError);
      expect(() => {
        trackleAuth.getDeviceKey(maxBytesLength);
      }).toThrow("Error: The deviceKey length (121) is greater than 1 bytes");
    });

    it("should return the deviceKey as Uint8Array", () => {
      const trackleAuth = new TrackleAuth(deviceId, keyDirPath);
      const maxBytesLength = 122;

      const deviceKeyBytes = trackleAuth.getDeviceKey(maxBytesLength);
      expect(deviceKeyBytes).toBeInstanceOf(Uint8Array);
      expect(deviceKeyBytes.length).toBeLessThanOrEqual(maxBytesLength);
    });
  });
});
