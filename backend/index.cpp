#include <napi.h>
#include <string>
#include "check.h"

// native C++ function that is assigned to `check` property on `exports` object
Napi::String check(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    // call `get_users` function from `check.cpp` file
    std::u16string result = get_users();

    // return new `Napi::String` value
    return Napi::String::New(env, result);
}

// callback method when module is registered with Node.js
Napi::Object Init(Napi::Env env, Napi::Object exports) {

    // set a key on `exports` object
    exports.Set(
        Napi::String::New(env, "check"), // property name => "get_users"
        Napi::Function::New(env, check) // property value => `get_users` function
    );

    // return `exports` object (always)
    return exports;
}

// register `checkq` module which calls `Init` method
NODE_API_MODULE(checkq, Init)