#include <node.h>
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

namespace demo {

using namespace std;
using namespace v8;

void Method(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    // 参数长度判断
    if (args.Length() < 2) {
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    // 参数类型判断
    if (!args[0]->IsNumber() || !args[1]->IsString() || !args[2]->IsArray() || !args[3]->IsObject() || !args[4]->IsBoolean()) {
        //抛出错误
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "argumnets error")));
    }

    if (!args[0]->IsObject()) {
        printf("I am not Object\n");
    }

    if (!args[0]->IsBoolean()) {
        printf("I am not Boolean\n");
    }

    if (!args[0]->IsArray()) {
        printf("I am not Array\n");
    }

    if (!args[0]->IsString()) {
        printf("I am not String\n");
    } else {
        printf("I am String\n");
    }

    if (!args[0]->IsFunction()) {
        printf("I am not Function\n");
    }

    if (!args[0]->IsNull()) {
        printf("I am not Null\n");
    }

    if (!args[0]->IsUndefined()) {
        printf("I am not Undefined\n");
    }

    // js Number 类型转换成 v8 Number 类型
    double value = args[0].As<Number>()->Value();
    printf("from js number param 0: %lf\n", value);

    // js String 类型转换成 v8 String 类型
    // 构造一个 String::Utf8Value 类型的变量 utfValue, utfValue 可以理解为一个 **char
    String::Utf8Value utfValue(isolate, args[1].As<String>()); 
    // 通过 utfValue可以进一步构造c++中的string，或直接安装 char*处理
    cout << "from js string param 1: " << string(*utfValue) << endl;
    //printf("from js string param 1: %s\n", *utfValue);

    // js Array 类型转换成 v8 Array 类型
    Local<Array> input_array = Local<Array>::Cast(args[2]);
    //array 第一个元素为Number类型
    double ele1 = input_array->Get(0).As<Number>()->Value();
    //array 第二个类型为String类型
    String::Utf8Value ele2(isolate, input_array->Get(1).As<String>());
    printf("from js Array param ( len: %d, elements:  %f, %s)\n", input_array->Length(), ele1, *ele2);

    
    // js Object 类型转换成 v8 Object 类型
    Local<Object> obj = args[3].As<Object>();

    // 根据 key 获取对象中的值
    Local<Value> nameValue = obj->Get(String::NewFromUtf8(isolate, "name"));
    Local<Value> ageValue = obj->Get(String::NewFromUtf8(isolate, "age"));
    double age = ageValue.As<Number>()->Value();
    String::Utf8Value name(isolate, nameValue.As<String>());

    printf("from js object param { name: %s, age: %ld }\n", *name, (long)age);

    //js boolean 类型传递
    bool b = args[4].As<Boolean>()->Value();
    cout << "from js boolean param: " << b << endl;
}

void Initialize(Local<Object> exports) {
  NODE_SET_METHOD(exports, "hello", Method);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

}  // namespace demo

