# Setup

## Prerequisiti

### Pacchetti

Per poter utilizzare questo progetto sono necessari alcuni strumenti all'utilizzo della libreria `node-addon-api`.

Di seguito vengono riportati le principali dipendenze:

- NodeJS
- node-gyp
- gcc
- python

> NB: Fare comunque riferimento alla pagina della libreria: [node-addon-api](https://github.com/nodejs/node-addon-api/blob/main/README.md)

Aggiungere all'includePath anche la cartella di node per avere a disposizione la libreria <node_api.h> dipendenza della <napi.h> della libreria node-addon-api!

## Libreria

Per poter compilare la libreria saranno necessari alcuni strumenti come:

- gcc
- g++
- make

Dopodichè sarà necessario posizionare la libreria di trackle di cui si vuole wrappare il contenuto nel percorso `./lib/src/<libFolder>`

```bash
# Ad esempio
 ./lib/src/trackle-library-cpp-4/
```

**NB:** A questo punto è **OBBLIGATORIO** impostare la variabile d'ambiente `TRACKLE_LIB_FOLDER_NAME`, dove va inserito il nome della cartella che contiene la libreria del passo precedente.  
Ad esempio nel mio caso

```
export TRACKLE_LIB_FOLDER_NAME=trackle-library-cpp-4
```

## IncludePath

Aggiungere all'includePath di compilazione del proprio ide tutte le cartelle che si vogliono utilizzare per le varie compilazioni, ad esempio io ho messo queste:

```txt
- /home/scimam/.nvm/versions/node/v18.13.0/include/node = Nodejs
- ${workspaceFolder}/** = includo tutte le sottocarelle del mio workspace
- ${workspaceFolder}/node_modules/node-addon-api = cartella di node-addon-api per l'utilizzo della libreria <napi.h>
- ${workspaceFolder}/lib/src/trackle-library-cpp-4/include = cartella con gli include necessari per la build della libreria trackle

```

# Utilizzo

## Build Libreria

Per prima cosa bisogna compilare la libreria e prima di farlo, modificare il file `./build-trackle-lib.sh` ed inserire correttamente le variabili nella sezione `#Set variables`.

Dopodichè lanciare il comando

```bash
npm run build:lib
```

A questo punto se tutto è andato correttamente l'artifact potremo trovarlo in `/dist/app/lib/trackle_library.so`.

## Build Wrapper

Il codice del wrapper si trova in `./lib/src/wrapper/` e contiene un proxy per l'interfacciamento delle funzionalità tra nodejs e c++.  
Per la sua compilazione sarà necessario lanciare il comando:

```bash
npm run build:wrapper
```

così facendo verrà generato un file `trackleWrapper.node` che finirà nella cartella di destinazione standard `./dist/lib`.

> NB: cartelle di \<source\> e di \<destination\> sono modificabili nel file `./binding.gyp`.

## Progetto Node

Ora si è liberi di crearsi il proprio progetto node semplicemente importando il proxy (e/o gli enum che possono servire), dopodichè sarà sufficiente passare all'oggetto `TrackleAuth` il nome del device con la relativa cartella in cui è contenuto il file ".der" della chiave privata associata a quel device.

Di seguito un codice di esempio:

```js
import trackle, { Log_Level, ... } from "./proxy/trackleWrapper";
import TrackleAuth from "./entities/trackleAuth";

const CERTIFICATE_DIR_PATH = "/home/scimam/Downloads/";
const auth = new TrackleAuth("10af10750a1783413cbcbddd", CERTIFICATE_DIR_PATH);

// Inizio set metodi wrappati
trackle.setDeviceId(auth.getDeviceId(trackle.getMaxDeviceIdLength()));
trackle.setKeys(auth.getDeviceKey(trackle.getMaxDevicePrivateKeyLength()));
...
```

Nel caso si voglia utilizzare la connessione udp di default in c++ della libreria, basterà dichiarare i metodi che gestiscono la connessione senza parametri:

```js
trackle.setConnectCallback();
trackle.setDisconnectCallback();
trackle.setSendCallback();
trackle.setReceiveCallback();
```

## Build completo

E' possibile anche lanciare in un unico comando la compilazione di tutto per creare una `dist` in automatico.

```bash
npm run build:all
```

il quale racchiude:

```bash
npm run build:lib
npm run build:wrapper
npm run build:ts
```

# Esempio

Per lanciare il programma di esempio bisogna per prima cosa buildare l'intero progetto (lib, wrapper, ts), modificare il path e il nome del deviceId di cui si vuole fare un test in `${workspaceFolder}/src/test/example/example.test.ts`:

```js
const relativeKeyDirPath = "relative/path/to/key";
const DEVICEID = "deviceIdCorretto";
```

e lanciare

```bash
npm run example
```
