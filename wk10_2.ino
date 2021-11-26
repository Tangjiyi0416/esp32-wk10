#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
const char* ssid = "tttddd";  // insert your SSID
const char* password = "idkhowto";  // insert your password
String jsonRead; //讀取response後儲存JSON資料的變數，必須是全域變數
const char* root_ca = \
                      "-----BEGIN CERTIFICATE-----\n"\
                      "MIIFsDCCA5igAwIBAgIQFci9ZUdcr7iXAF7kBtK8nTANBgkqhkiG9w0BAQUFADBe\n"\
                      "MQswCQYDVQQGEwJUVzEjMCEGA1UECgwaQ2h1bmdod2EgVGVsZWNvbSBDby4sIEx0\n"\
                      "ZC4xKjAoBgNVBAsMIWVQS0kgUm9vdCBDZXJ0aWZpY2F0aW9uIEF1dGhvcml0eTAe\n"\
                      "Fw0wNDEyMjAwMjMxMjdaFw0zNDEyMjAwMjMxMjdaMF4xCzAJBgNVBAYTAlRXMSMw\n"\
                      "IQYDVQQKDBpDaHVuZ2h3YSBUZWxlY29tIENvLiwgTHRkLjEqMCgGA1UECwwhZVBL\n"\
                      "SSBSb290IENlcnRpZmljYXRpb24gQXV0aG9yaXR5MIICIjANBgkqhkiG9w0BAQEF\n"\
                      "AAOCAg8AMIICCgKCAgEA4SUP7o3biDN1Z82tH306Tm2d0y8U82N0ywEhajfqhFAH\n"\
                      "SyZbCUNsIZ5qyNUD9WBpj8zwIuQf5/dqIjG3LBXy4P4AakP/h2XGtRrBp0xtInAh\n"\
                      "ijHyl3SJCRImHJ7K2RKilTza6We/CKBk49ZCt0Xvl/T29de1ShUCWH2YWEtgvM3X\n"\
                      "DZoTM1PRYfl61dd4s5oz9wCGzh1NlDivqOx4UXCKXBCDUSH3ET00hl7lSM2XgYI1\n"\
                      "TBnsZfZrxQWh7kcT1rMhJ5QQCtkkO7q+RBNGMD+XPNjX12ruOzjjK9SXDrkb5wdJ\n"\
                      "fzcq+Xd4z1TtW0ado4AOkUPB1ltfFLqfpo0kR0BZv3I4sjZsN/+Z0V0OWQqraffA\n"\
                      "sgRFelQArr5T9rXn4fg8ozHSqf4hUmTFpmfwdQcGlBSBVcYn5AGPF8Fqcde+S/uU\n"\
                      "WH1+ETOxQvdibBjWzwloPn9s9h6PYq2lY9sJpx8iQkEeb5mKPtf5P0B6ebClAZLS\n"\
                      "nT0IFaUQAS2zMnaolQ2zepr7BxB4EW/hj8e6DyUadCrlHJhBmd8hh+iVBmoKs2pH\n"\
                      "dmX2Os+PYhcZewoozRrSgx4hxyy/vv9haLdnG7t4TY3OZ+XkwY63I2binZB1NJip\n"\
                      "NiuKmpS5nezMirH4JYlcWrYvjB9teSSnUmjDhDXiZo1jDiVN1Rmy5nk3pyKdVDEC\n"\
                      "AwEAAaNqMGgwHQYDVR0OBBYEFB4M97Zn8uGSJglFwFU5Lnc/QkqiMAwGA1UdEwQF\n"\
                      "MAMBAf8wOQYEZyoHAAQxMC8wLQIBADAJBgUrDgMCGgUAMAcGBWcqAwAABBRFsMLH\n"\
                      "ClZ87lt4DJX5GFPBphzYEDANBgkqhkiG9w0BAQUFAAOCAgEACbODU1kBPpVJufGB\n"\
                      "uvl2ICO1J2B01GqZNF5sAFPZn/KmsSQHRGoqxqWOeBLoR9lYGxMqXnmbnwoqZ6Yl\n"\
                      "PwZpVnPDimZI+ymBV3QGypzqKOg4ZyYr8dW1P2WT+DZdjo2NQCCHGervJ8A9tDkP\n"\
                      "JXtoUHRVnAxZfVo9QZQlUgjgRywVMRnVvwdVxrsStZf0X4OFunHB2WyBEXYKCrC/\n"\
                      "gpf36j36+uwtqSiUO1bd0lEursC9CBWMd1I0ltabrNMdjmEPNXubrjlpC2JgQCA2\n"\
                      "j6/7Nu4tCEoduL+bXPjqpRugc6bY+G7gMwRfaKonh+3ZwZCc7b3jajWvY9+rGNm6\n"\
                      "5ulK6lCKD2GTHuItGeIwlDWSXQ62B68ZgI9HkFFLLk3dheLSClIKF5r8GrBQAuUB\n"\
                      "o2M3IUxExJtRmREOc5wGj1QupyheRDmHVi03vYVElOEMSyycw5KFNGHLD7ibSkNS\n"\
                      "/jQ6fbjpKdx2qcgw+BRxgMYeNkh0IkFch4LoGHGLQYlE535YW6i4jRPpp2zDR+2z\n"\
                      "Gp1iro2C6pSe3VkQw63d4k3jMdXH7OjysP6SHhYKGvzZ8/gntsm+HbRsZJB/9OTE\n"\
                      "W9c3rkIO3aQab3yIVMUWbuF6aC74Or8NpDyJO3inTmODBCEIZ43ygknQW/2xzQ+D\n"\
                      "hNQ+IIX3Sj0rnP0qCglN6oH4EZw=\n"\
                      "-----END CERTIFICATE-----\n";
void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}
bool pauseLoop = false;
void loop() {
  int crtl = Serial.read();
  if (crtl == '0') {
    pauseLoop = true;
    Serial.println("Paused.");
  }
  else if (crtl == '1') {
    pauseLoop = false;
    Serial.println("Resumed.");
  }
  if (pauseLoop) {
    delay(1000);
    return;
  }
  GetPM25Data();
  //將字串轉換為JSON，儲存在doc中
  DynamicJsonDocument doc(16384);
  deserializeJson(doc, jsonRead);
  JsonArray arr = doc["records"];
  Serial.print("records count: ");
  Serial.println(arr.size());
  double totalPM25 = 0;
  int siteCount = 0;
  for (JsonVariant value : arr) {
    if (value["county"] == "臺北市") {
      siteCount++;
      const char* curPM25 = value["PM25"];
      totalPM25 += String(curPM25).toInt();
    }
  }
  char* influence = GetInfluence(totalPM25 / siteCount);

  SendToWebHook(String(totalPM25 / siteCount), String(influence), String(siteCount)); //Client傳送資料
  Serial.print("PM25: ");
  Serial.println(String(totalPM25 / siteCount));
  Serial.print("Influence: ");
  Serial.println(String(influence));
  Serial.print("Sites: ");
  Serial.println(String(siteCount));
  Serial.println("--------------------");

  delay(5000); // the OWM free plan API does NOT allow more then 60 calls per minute
}

void GetPM25Data() {
  HTTPClient client;  //建立Client物件
  client.begin("https://data.epa.gov.tw/api/v1/aqx_p_02?limit=1000&api_key=9be7b239-557b-4c10-9775-78cadfc555e9&sort=ImportDate%20desc&format=json"
               , root_ca);
  int httpCode = client.GET();                                                  //Make the request

  if (httpCode > 0) { //Check for the returning code

    jsonRead = client.getString();
    Serial.println(httpCode);
    Serial.println(jsonRead);
  }
  else {
    Serial.println("Error on HTTP request");
  }
  client.end(); //Free the resources
  //回傳
}


void SendToWebHook(String value1, String value2, String value3) {

  WiFiClient client;  //建立Client物件
  const int httpPort = 80;  //預設通訊阜80
  const char* host = "maker.ifttt.com"; //IFTTT server網址
  const char* event = "line_notify2";  //IFTTT事件名稱
  const char* apiKey = "fg585E6OJ90id-DC_f2N8gFKB4itNcI7sB3ntWh877d";  //IFTTT Applet key
  String url = "";  //API url
  String JsonString = "";  //此範例不會用到

  //Client連結Server
  if (client.connect(host, httpPort)) {

    //Webhook API
    url += "/trigger/" + String(event) + "/with/key/" + String(apiKey);
    //Query String
    url += "?value1=" + value1 + "&value2=" + value2 + "&value3=" + value3;

    //Client傳送
    client.println(String("POST ") + url + " HTTP/1.1");
    client.println(String("Host: ") + host);
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(JsonString.length());
    client.println();
    client.println(JsonString);

    //等待5秒，每0.1秒偵測一次是否有接收到response資料
    int timeout = 0;
    while (!client.available() && (timeout++ <= 50)) {
      delay(100);
    }

    //如果無回應
    if (!client.available()) {
      Serial.println("No response...");
    }
    //用while迴圈一字一字讀取Response
    while (client.available()) {
      Serial.write(client.read());
    }

    //停止Client
    client.stop();
  }
}

char* GetInfluence(double pm25) {
  if (pm25 > 300)return "Hazardous";
  else if (pm25 > 200)return "Very Unhealthy";
  else if (pm25 > 150)return "Unhealthy";
  else if (pm25 > 100)return "Unhealthy for Sensitive Groups";
  else if (pm25 > 50)return "Moderate";
  else return "Good";
}
