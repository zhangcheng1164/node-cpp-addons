const addon = require('./build/Release/addon.node');

console.log(addon);
console.log(addon.test());
console.log('args called: ', addon.test().arg3());
addon.method();
