const addon = require('./build/Release/addon.node');

//the cat is sync method here !!!
let result = addon.cat(process.argv[2], process.argv[3]);
console.log(result);
