# TEST
### table of contents 
* [introduction](#introduction)
* [Enviroment Variables:](#Enviroment-Variables)
    * [CLIENT_SECRET](#CLIENT-SECRET-&-CLIENT-ID)
    * [CLIENT_ID](#CLIENT-SECRET-&-CLIENT-ID)
    * [DEVICE_ID](#GET-A-DEVICEID-AND-A-PRIVATE-KEY)
    * [PRODUCT_ID](#PRODUCT-ID)
## introduction
This is the test for the wrapper methods, this is actually testing: 
* **`Connection`** to Trackle 
* All the **`setup params`** that are setted before the connection
* **`POST`** & **`GET`** methods
* **`PUBLISH`** method
* If your device is assigned to a product on trackle will test the **`Syncstate`** too

## Enviroment Variables
For make this work you have to define 4 variable in the .env file:
* [CLIENT_SECRET](#CLIENT-SECRET-&-CLIENT-ID)
* [CLIENT_ID](#CLIENT-SECRET-&-CLIENT-ID)
* [DEVICE_ID](#GET-A-DEVICEID-AND-A-PRIVATE-KEY)
* [PRODUCT_ID](#PRODUCT-ID)
Over these you have to create a `directory` named **Keys** in the `root` of your project and in there put the `.der` file **containing the [key](#GET-A-DEVICEID-AND-A-PRIVATE-KEY)** for the connection with Trackle

### Get a Device ID and a private key
* Create an account on Trackle Cloud (https://trackle.cloud/)
* Open "My Devices" section from the drawer
* Click the button "Claim a device"
* Select the link "I don't have a device id", then Continue
* The Device Id will be shown on the screen and the private key file will be download with name <device_id>.der where <device_id> is Device ID taken from Trackle.

### CLIENT SECRET & CLIENT ID
For gathering this two values you have to:
* Open "My Devices" section from the drawer
* On the **left nav-bar** there is a **key symbol** click it
* On the **upper-right side** of your screen ther is a orange button that says **"create new client"**, click it
* Now you have to choose **type of application**, select **Server To Server**, **give a name** and **click "obtain Client ID and Secret"**
* Now **your variable are successfully displayed** and you can insert that in the `.env `file

### PRODUCT ID
If you **already** have access to a **PRODUCT_ID** on **Trackle** platform and you want to test it, **add the device** that you are testing **to your product** and add the **env variable: PRODUCT_ID**, **else do not specify** in the `.env `file this one and the test **will automatically skip** all the test that involves a `product id` specification.