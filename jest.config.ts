import type { Config } from "@jest/types";

const baseDir = "<rootDir>/src";
const baseTestDir = "<rootDir>/test";

const config: Config.InitialOptions = {
  preset: "ts-jest",
  testEnvironment: "node",
  verbose: true,

  collectCoverage: true,
  collectCoverageFrom: [`${baseDir}/**/*.ts`],
  testMatch: [`${baseTestDir}/**/*test.ts`, `${baseTestDir}/**/*test.ts`],

  modulePathIgnorePatterns: [`${baseTestDir}/example`],
};

export default config;
