#include <node.h>
#include<wiringPi.h>
#include<stdio.h>

#define PIN 7
#define MAX_TIME 85
#define DHT11PIN 7
#define DELAY_TIME 500
int dht11_val[5] = { 0,0,0,0,0 };
namespace dht11 {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

int dht11_read_val(){
	int returnValue = 0;

	uint8_t lststate = HIGH;
	uint8_t counter = 0;
	uint8_t j = 0, i = 0;
	float farenheit = 0;

	// ***
	// *** Initialize the values
	// ***
	for (i = 0; i < 5; i++)
	{
		dht11_val[i] = 0;
	}

	// ***
	// *** Signal the sensor to send data
	// ***
	pinMode(DHT11PIN, OUTPUT);
	digitalWrite(DHT11PIN, LOW);

	// ***
	// *** Datasheet states that we should wait 18ms
	// ***
	delay(18);

	// ***
	// *** Set the pin to high and switch to input mode
	// ***
	digitalWrite(DHT11PIN, HIGH);
	delayMicroseconds(40);
	pinMode(DHT11PIN, INPUT);

	// ***
	// *** Get the bits
	// ***
	for (i = 0; i < MAX_TIME; i++)
	{
		counter = 0;
		while (digitalRead(DHT11PIN) == lststate)
		{
			counter++;
			delayMicroseconds(1);

			if (counter == 255)
			{
				break;
			}
		}

		lststate = digitalRead(DHT11PIN);

		if (counter == 255)
		{
			break;
		}

		// ***
		// *** Top 3 transitions are ignored
		// ***
		if ((i >= 4) && (i % 2 == 0))
		{
			dht11_val[j / 8] <<= 1;

			if (counter > 16)
			{
				dht11_val[j / 8] |= 1;
			}

			j++;
		}
	}

	// ***
	// *** Verify checksum and print the verified data
	// ***
	if ((j >= 40) && (dht11_val[4] == ((dht11_val[0] + dht11_val[1] + dht11_val[2] + dht11_val[3]) & 0xFF)))
	{
		farenheit = dht11_val[2] * 9. / 5. + 32;
		// printf("Humidity = %d.%d %% Temperature = %d.%d *C (%.1f *F)\n", dht11_val[0], dht11_val[1], dht11_val[2], dht11_val[3], farenheit);
		returnValue = 1;
	}
	else
	{
		// printf("Invalid Data!!\n");
		returnValue = 0;
	}

	return returnValue;
}

void Method(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  // int sound = 0;
  // int i;
  // for(i = 0;i<50;i++){
  // 	if(digitalRead(PIN)== LOW){
  // sound = 1;
  // break;
  //
  // elayMicroseconds(100);
  // }
  int i = MAX_TIME;
  while(i-- > 0 && !dht11_read_val());
  float t = (float)(dht11_val[0] + dht11_val[1]/10);
  float h = (float)(dht11_val[2] + dht11_val[3]/10);
  Local<v8::Array> ret = v8::Array::New(isolate,2);
  ret->Set(0, v8::Integer::New(isolate,t));
  ret->Set(1, v8::Integer::New(isolate,h));
  args.GetReturnValue().Set(ret);
}
void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "sound", Method);
  wiringPiSetup();
  pinMode(PIN,INPUT);
}

	NODE_MODULE(fc_04, init)

}  // namespace demo
