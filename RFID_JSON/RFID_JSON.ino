#include <ArduinoJson.h>
 
// Enough space for: 멤버가 3개인 오브젝트 1개와 멤버가 1개인 오브젝트 2개가 있는 Json문서 크기
// + 1 object with 3 members 
// + 2 objects with 1 member 
//const int capacity = JSON_OBJECT_SIZE(3) + 2 * JSON_OBJECT_SIZE(1);
 
// JSON_OBJECT_SIZE(the number of members in the object) : JSON 오브젝트 크기 계산(인자는 멤버의 수)
// 멤버가 8개인 오브젝트 40개(날씨정보), 멤버가 2개인 오브젝트 1개(헤더), 멤버가 5개인 오브젝트 1개(response)
const int capacity = 40 * JSON_OBJECT_SIZE(8) + JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(5);
 
// Using a char[], as shown here, enables the "zero-copy" mode. This mode uses
// the minimal amount of memory because the JsonDocument stores pointers to
// the input buffer.
// If you use another type of input, ArduinoJson must copy the strings from
// the input to the JsonDocument, so you need to increase the capacity of the
// JsonDocument.
// json 내용을 char[]로 받아야 zero-copy 모드가 된다고 함. zero-copy 모드는 메모리를 적게 사용. 
// 다른 타입을 사용할 때는 ArduinoJson 라이브러리에서 문자열을 복사하므로 Json문서 크기를 더 크게 잡야줘야 함.
const char json[] = "{\"response\":{\"header\":{\"resultCode\":\"0000\",\"resultMsg\":\"OK\"},\"body\":{\"items\":{\"item\":[{\"baseDate\":20190418,\"baseTime\":\"0200\",\"category\":\"POP\",\"fcstDate\":20190418,\"fcstTime\":\"0600\",\"fcstValue\":10,\"nx\":62,\"ny\":121},{\"baseDate\":20190418,\"baseTime\":\"0200\",\"category\":\"PTY\",\"fcstDate\":20190418,\"fcstTime\":\"0600\",\"fcstValue\":0,\"nx\":62,\"ny\":121},{\"baseDate\":20190418,\"baseTime\":\"0200\",\"category\":\"R06\",\"fcstDate\":20190418,\"fcstTime\":\"0600\",\"fcstValue\":0,\"nx\":62,\"ny\":121},{\"baseDate\":20190418,\"baseTime\":\"0200\",\"category\":\"REH\",\"fcstDate\":20190418,\"fcstTime\":\"0600\",\"fcstValue\":80,\"nx\":62,\"ny\":121},{\"baseDate\":20190418,\"baseTime\":\"0200\",\"category\":\"S06\",\"fcstDate\":20190418,\"fcstTime\":\"0600\",\"fcstValue\":0,\"nx\":62,\"ny\":121},{\"baseDate\":20190418,\"baseTime\":\"0200\",\"category\":\"SKY\",\"fcstDate\":20190418,\"fcstTime\":\"0600\",\"fcstValue\":2,\"nx\":62,\"ny\":121},{\"baseDate\":20190418,\"baseTime\":\"0200\",\"category\":\"T3H\",\"fcstDate\":20190418,\"fcstTime\":\"0600\",\"fcstValue\":10,\"nx\":62,\"ny\":121},{\"baseDate\":20190418,\"baseTime\":\"0200\",\"category\":\"TMN\",\"fcstDate\":20190418,\"fcstTime\":\"0600\",\"fcstValue\":9.0,\"nx\":62,\"ny\":121},{\"baseDate\":20190418,\"baseTime\":\"0200\",\"category\":\"UUU\",\"fcstDate\":20190418,\"fcstTime\":\"0600\",\"fcstValue\":-0.3,\"nx\":62,\"ny\":121},{\"baseDate\":20190418,\"baseTime\":\"0200\",\"category\":\"VEC\",\"fcstDate\":20190418,\"fcstTime\":\"0600\",\"fcstValue\":172,\"nx\":62,\"ny\":121},{\"baseDate\":20190418,\"baseTime\":\"0200\",\"category\":\"VVV\",\"fcstDate\":20190418,\"fcstTime\":\"0600\",\"fcstValue\":2.7,\"nx\":62,\"ny\":121},{\"baseDate\":20190418,\"baseTime\":\"0200\",\"category\":\"WSD\",\"fcstDate\":20190418,\"fcstTime\":\"0600\",\"fcstValue\":2.7,\"nx\":62,\"ny\":121}]},\"numOfRows\":12,\"pageNo\":1,\"totalCount\":155}}}";
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial) continue;
  delay(100);
  Serial.println("setup() START");
  Serial.println(capacity);
 
  // Json문서의 크기가 작으면 stack을 사용해서 실행 크기를 줄이고 성능을 높일 수 있다고 함.(StaticJsonDocument 사용)
  // Json문서의 크기가 크면 heap을 쓰는게 타당하다고.(DynamicJsonDocument 사용)
  //StaticJsonDocument<capacity> doc;
  DynamicJsonDocument doc(capacity);
 
  // Deserialize the JSON document : Json문서 분석
  DeserializationError error = deserializeJson(doc, json);
 
  // Test if parsing succeeds. : 파싱 에러 발생 시 출력
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return;
  }
 
  // Fetch values.
  // Most of the time, you can rely on the implicit casts.
  // In other case, you can do doc["time"].as<long>();
  const char* resultCode = doc["response"]["header"]["resultCode"];
  int baseDate = doc["response"]["body"]["items"]["item"][0]["baseDate"];
  const char* category = doc["response"]["body"]["items"]["item"][1]["category"];
 
  // Print values.
  Serial.println(resultCode);
  Serial.println(baseDate);
  Serial.println(category);
}
 
void loop() {
  // put your main code here, to run repeatedly:
 
}
