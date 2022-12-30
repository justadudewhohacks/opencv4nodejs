#!/usr/bin/env node

console.log('LOADING ../install/compileLib.js from install.js')
console.log('LOADING ../install/compileLib.js from install.js')
const compileLib = require("../install/compileLib.js");
compileLib.compileLib(process.argv);
