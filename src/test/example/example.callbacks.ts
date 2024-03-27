export default class TrackleCallback {
  static setMillis = () => {
    const date = new Date();
    const ms: number = date.getMilliseconds();
    return ms;
  };

  static setLog = (msg: string, level: number, category: string): void => {
    console.log(`[${level}] [${category ?? ""}] ${msg}`);
  };

  static postSuccess(nome: string): number {
    console.log(`Richiamata callback postSuccess, arg: ${nome}`);
    return 1;
  }

  static postFailure = (nome: string): number => {
    console.log(`Richiamata callback postFailure, arg: ${nome}`);
    return -1;
  };

  static getString = (nome: string): string => {
    console.log(`Richiamata callback getString, arg: ${nome}`);
    if (nome) {
      return `Arg passed: ${nome}!`;
    }

    return "No args!";
  };

  static getChar = (nome: string): string => {
    console.log(`Richiamata callback getChar, arg: ${nome}`);
    if (nome) {
      return "A";
    }

    return "a";
  };

  static getInt = (nome: string): number => {
    console.log(`Richiamata callback getInt, arg: ${nome}`);
    if (nome) {
      return 5678;
    }

    return 1234;
  };

  static getBoolean = (nome: string): boolean => {
    console.log(`Richiamata callback getBoolean, arg: ${nome}`);
    // FIXME: non funziona ritorna BLANK
    if (nome) {
      return true;
    }

    return false;
  };

  static getDouble = (nome: string): number => {
    console.log(`Richiamata callback getDouble, arg: ${nome}`);
    if (nome) {
      return 1.4563333;
    }

    return 0.4567812;
  };

  // FIXME: NON FUNZIONA
  static getLong = (nome: string): BigInt => {
    console.log(`Richiamata callback getLong, arg: ${nome}`);
    if (nome) {
      return BigInt(123456789012345);
    }

    return BigInt(123456789012345);
  };

  static getJson = (nome: string): string => {
    console.log(`Richiamata callback getJson, arg: ${nome}`);
    if (nome) {
      return JSON.stringify({ nome: "pippo", cognome: "pluto" });
    }

    return JSON.stringify({ nome: "", cognome: "" });
  };

  static systemTimeCallback = (
    time: number,
    param: number,
    data: Buffer | undefined
  ): void => {
    console.log(time);
    return;
  };

  static systemRebootCallback = (data: string) => {
    console.log("Reboot request ignored!");
  };

  static completedPublishCallback = (
    error: number,
    data?: any,
    callbackData?: any,
    reserved?: any
  ): void => {
    console.log(
      `callback_complete_publish (msg_key: ${callbackData as number}, token: ${
        reserved as string
      }, result: ${error})`
    );
  };
}
