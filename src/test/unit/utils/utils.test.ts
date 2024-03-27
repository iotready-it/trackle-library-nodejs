import { AssertionError } from "assert";
import Utils from "../../../app/utils/utils";
import path from "path";

describe("Utils", () => {
  describe("existKeyFilepath", () => {
    const dirPath = "/path/to/directory";
    const fileName = "test";
    const fileExtension = ".txt";
    const filePath = path.join(dirPath, fileName.concat(fileExtension));

    it("should return true if the file path exists", () => {
      jest.spyOn(Utils, "existFilepath").mockReturnValue(true);
      const result = Utils.existKeyFilepath(dirPath, fileName, fileExtension);
      expect(result).toBe(true);
      expect(Utils.existFilepath).toHaveBeenCalledWith(filePath);
    });

    it("should return false if the file path does not exist", () => {
      jest.spyOn(Utils, "existFilepath").mockReturnValue(false);
      const result = Utils.existKeyFilepath(dirPath, fileName, fileExtension);
      expect(result).toBe(false);
      expect(Utils.existFilepath).toHaveBeenCalledWith(filePath);
    });
  });

  describe("fromHexStringToByteArray", () => {
    it("should throw an error if hexString length is less than 2", () => {
      const hexString = "";

      expect(() => Utils.fromHexStringToByteArray(hexString)).toThrow(
        AssertionError
      );
      expect(() => Utils.fromHexStringToByteArray(hexString)).toThrow(
        "Error: Invalid hex string length"
      );
    });

    it("should throw an error if hexString length is odd", () => {
      const hexString = "0x1";
      expect(() => Utils.fromHexStringToByteArray(hexString)).toThrow(
        AssertionError
      );
      expect(() => Utils.fromHexStringToByteArray(hexString)).toThrow(
        "Error: Invalid hex string length"
      );
    });

    it("should return an array of numbers", () => {
      const hexString = "10af10750a1783413cbcbddd";

      const result = Utils.fromHexStringToByteArray(hexString);
      expect(result).toBeInstanceOf(Array);
      expect(result[0]).toBe(16);
    });
  });
});
