import assert from "assert";
import fs from "fs";
import path from "path";

export default class Utils {
  static fromHexStringToByteArray(hexString: string): number[] {
    assert(hexString.length >= 2, new Error("Invalid hex string length"));
    assert(hexString.length % 2 === 0, new Error("Invalid hex string length"));

    let result = [];
    let _hexString = hexString;

    while (_hexString.length >= 2) {
      result.push(parseInt(_hexString.substring(0, 2), 16));
      _hexString = _hexString.substring(2, _hexString.length);
    }

    return result;
  }

  static readKeyFile(
    dirPath: string,
    fileName: string,
    fileExtension: string
  ): Buffer {
    const filepath: string = path.join(dirPath, fileName.concat(fileExtension));
    return fs.readFileSync(filepath);
  }

  static existKeyFilepath(
    dirPath: string,
    fileName: string,
    fileExtension: string
  ): boolean {
    return Utils.existFilepath(
      path.join(dirPath, fileName.concat(fileExtension))
    );
  }

  static existFilepath(filePath: string): boolean {
    return fs.existsSync(filePath);
  }
}
