#include <ArduinoJson.h>

//Json버퍼를 만든다
StaticJsonBuffer<200> jsonBuffer;  //200은 버퍼크기

//다른곳에서도 사용하기 위해 포인터로 선언했다
JsonArray* group = &jsonBuffer.createArray();
JsonArray* olist = &group->createNestedArray();
JsonObject* option;



void setup() {
  Serial.begin(9600);

  group = &jsonBuffer.createArray();  // group 배열을 만든다 (1차원)

  olist = &group->createNestedArray();  // group 배열안에 olist 배열을 만든다 (2차원)

  option = &olist->createNestedObject();  // olist 배열에 object를 만든다
  option->set("aaa", "AAA");  // (*option)["aaa"] = "AAA";
  option->set("aab", "AAB");

  option = &olist->createNestedObject();
  option->set("aba", "ABA");
  option->set("abb", "ABB");


  olist = &group->createNestedArray();

  option = &olist->createNestedObject();
  option->set("baa", "BAA");
  option->set("bab", "BAB");

  option = &olist->createNestedObject();
  option->set("bba", "BBA");
  option->set("bbb", "BBB");
}


void loop() {
  
  //임시변수라서 무조건 참조로 받아야 된다
  JsonArray& ol = group->get(0);
  JsonObject& o = ol[0];
 
  String s = o["aaa"];  // 변수의 형태에 따라 자동 변환된다
  Serial.println(s);  // "AAA" 를 출력한다
  Serial.println(group->size()); // group 배열의 크기를 출력한다

  //Serial.println(o["aaa"].asString());  //바로 사용하려면 as<타입> 형태로 캐스팅해준다
  //o.printTo(Serial);  // json 객체를 그대로 출력하기 위한 방법
  //Serial.println("");

}
