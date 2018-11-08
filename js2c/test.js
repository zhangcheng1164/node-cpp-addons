const addon = require('./build/Release/addon.node');

addon.hello(11, 'hello world', [1, 'element in array'], {name: 'zhangsan', age: 11}, false);

