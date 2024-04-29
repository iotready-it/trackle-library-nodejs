export const testGetInt = (name: string): number => {
  if (name) {
    const parsedInt = parseInt(name);
    if (!isNaN(parsedInt)) {
      return parsedInt;
    } else {
      return -1; 
    }
  } else {
    return -1; 
  }
}


export const testGetBool = (name: string): boolean => {
  if (name === "true") {
    return true;
  } else {
    return false;
  }
}


export const testGetString = (name: string): string => {
  if (name) {
    return name;
  } else {
    return "noArgs";
  }
}

export const testGetDouble = (name: string): number => {
  if (name) {
    return parseFloat(name);
  } else {
    return 3.14159265;
  }
}

export const testGetJson = (name: string): any => {
  if (name) {
    return JSON.stringify({ args: name });
  } else {
    return JSON.stringify({ args: "noArgs" });
  }
}
