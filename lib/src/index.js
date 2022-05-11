"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const drawUtils_1 = __importDefault(require("./drawUtils"));
const deprecations_1 = __importDefault(require("./deprecations"));
const misc_1 = __importDefault(require("./misc"));
function default_1(cv) {
    // add functions  
    (0, drawUtils_1.default)(cv);
    // add functions  
    (0, misc_1.default)(cv);
    (0, deprecations_1.default)(cv);
    return cv;
}
exports.default = default_1;
