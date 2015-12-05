#include <node.h>
#include<wiringPi.h>
#include<stdio.h>
#define PIN 7
namespace demo {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

void getSound(){
}

void Method(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  int sound = 0;
  int i;
  for(i = 0;i<50;i++){
  	if(digitalRead(PIN)== LOW){
		sound = 1;
		break;
	}
	delayMicroseconds(100);
  }

  if(sound)
  	args.GetReturnValue().Set(String::NewFromUtf8(isolate, "sound"));
  else
	args.GetReturnValue().Set(String::NewFromUtf8(isolate, "no sound"));
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "sound", Method);
  wiringPiSetup();
  pinMode(PIN,INPUT);
}

	NODE_MODULE(fc_04, init)
	
}  // namespace demo
