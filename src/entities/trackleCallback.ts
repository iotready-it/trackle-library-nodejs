export default class TrackleCallback {
  static setMillis = () => {
    // console.log(`    --> NodeJS MillisCallback: ()`);

    const date = new Date();
    const ms: number = date.getMilliseconds();
    return ms;
  };

  static setLog = (msg: string, level: number, category: string): void => {
    if (category.length === 0) {
      console.log(`[${level}] [] ${msg}`);
    } else {
      console.log(`[${level}] [${category}] ${msg}`);
    }
  };

  static post1(nome: string): number {
    console.log("Richiamato post1 : " + nome);
    if (nome) {
      console.log("Post1 - Pippo");
      return 1;
    }

    return 10;
  }

  static post2 = (nome: string): number => {
    if (nome) {
      console.log("Post2 - Pluto");
      return 0;
    }

    return 10;
  };

  static getString = (nome: string): string => {
    console.log("Richiamato getString : " + nome);
    if (nome) {
      console.log("getString - ");
      return "Ciao";
    }

    return "World";
  };

  static getChar = (nome: string): string => {
    console.log("Richiamato getChar : " + nome);
    if (nome) {
      console.log("getChar - ");
      return "C";
    }

    return "a";
  };

  static getInt = (nome: string): number => {
    console.log("Richiamato getInt : " + nome);
    if (nome) {
      console.log("getInt - ");
      return 5678;
    }

    return 1234;
  };

  static getBoolean = (nome: string): boolean => {
    console.log("Richiamato getBoolean : " + nome);
    if (nome) {
      console.log("getBoolean - ");
      return true;
    }

    return false;
  };

  static getDouble = (nome: string): number => {
    console.log("Richiamato getDouble : " + nome);
    if (nome) {
      console.log("getDouble - ");
      return 1.4563333;
    }

    return 0.4567812;
  };

  // NON FUNZIONA
  static getLong = (nome: string): BigInt => {
    console.log("Richiamato getLong : " + nome);
    if (nome) {
      console.log("getLong - ");
      return BigInt(123456789012345);
    }

    return BigInt(123456789012345);
  };

  static getJson = (nome: string): string => {
    console.log("Richiamato getJson : " + nome);
    if (nome) {
      console.log("getJson - ");
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
}
