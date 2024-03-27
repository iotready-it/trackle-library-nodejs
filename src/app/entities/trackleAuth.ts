import assert from "assert";

import Utils from "../utils/utils";

interface BasicTrackleAuth {
  deviceId: string;

  getDeviceId(maxBytesLength: number): Uint8Array;
  getDeviceKey(maxBytesLength: number): Uint8Array;
}

export enum CertificateExtType {
  BINARY = ".der",
  BASE_64 = ".pem",
}

export default class TrackleAuth implements BasicTrackleAuth {
  constructor(public deviceId: string, private keyDirPath: string) {
    assert(deviceId, new Error("DeviceId has no size!"));
    assert(
      Utils.existKeyFilepath(
        keyDirPath,
        this.deviceId,
        CertificateExtType.BINARY
      ),
      new Error(
        `Certificate "${this.deviceId}${CertificateExtType.BINARY}" not found in directory "${keyDirPath}"!`
      )
    );
  }

  getDeviceId(maxBytesLength: number): Uint8Array {
    assert(
      Buffer.from(this.deviceId).byteLength <= maxBytesLength * 2,
      new Error(
        `The deviceId length (${
          Buffer.from(this.deviceId).byteLength
        }) is greater than ${maxBytesLength} bytes`
      )
    );

    const byteArray: number[] = Utils.fromHexStringToByteArray(this.deviceId);
    return Uint8Array.from(byteArray);
  }

  getDeviceKey(maxBytesLength: number): Uint8Array {
    let buffer: Buffer = Utils.readKeyFile(
      this.keyDirPath,
      this.deviceId,
      CertificateExtType.BINARY
    );

    assert(buffer.byteLength != 0, new Error(`DeviceKey has no data!`));
    assert(
      buffer.byteLength <= maxBytesLength,
      new Error(
        `The deviceKey length (${buffer.byteLength}) is greater than ${maxBytesLength} bytes`
      )
    );

    return Uint8Array.from(buffer);
  }
}
