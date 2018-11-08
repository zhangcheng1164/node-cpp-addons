#include <node.h>
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

namespace demo {

using namespace std;
using namespace v8;

void Cat(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    //1. get string param from js
    if (args.Length() < 2) {
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "usage: cat(string, string)")));
        return;
    }

    if (!args[0]->IsString() || !args[1]->IsString()) {
        //抛出错误
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "usage: cat(string, string)")));
    }

    String::Utf8Value utfArg0(isolate, args[0].As<String>()); 
    char* arg0 = *utfArg0;

    String::Utf8Value utfArg1(isolate, args[1].As<String>()); 
    char* arg1 = *utfArg1;

    //cout << "arg0: " << arg0 << " arg1: " << arg1 << endl;

    //2. dynamic link so lib
    void *handle = dlopen("libcat_c.so", RTLD_LAZY);
    
    if(!handle)
    {
        printf("open lib error\n");
        cout<<dlerror()<<endl;
        return;
    }
    
    typedef char* (*cat_t)(char* buf, const char* a, const char* b);
    cat_t cat = (cat_t) dlsym(handle, "cat");
    if(!cat)
    {
        cout<<dlerror()<<endl;
        dlclose(handle);
        return;
    }
    
    //use malloc will occure unreadable words, dont know why !
    char *buf = (char *)calloc(100, sizeof(char)); 
    cat(buf, arg0, arg1);
    dlclose(handle);

    //3. return string result to js 
    Local<String> str = String::NewFromUtf8(isolate, buf);
    args.GetReturnValue().Set(str);
    
    free(buf);
}

void Initialize(Local<Object> exports) {
  NODE_SET_METHOD(exports, "cat", Cat);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

}  // namespace demo

