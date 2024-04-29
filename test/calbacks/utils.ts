export const getMillis = () => {
  const date = new Date();
  const ms: number = date.getTime();
  return ms;
};

export const setLog = (msg: string, level: number, category: string): void => {
  if (category.length === 0) {
    console.log(`[${level}] [] ${msg}`);
  } else {
    console.log(`[${level}] [${category}] ${msg}`);
  }
};
export const systemTimeCallback = (
  time: number,
  param: number,
  data: Buffer | undefined
): void => {
  console.log(time);

};

export const completedPublishCallback = (
  error: number,
  callbackData?: number
): void => {
  console.log("msg key: " + callbackData)
  console.log("error: " + error)

};
