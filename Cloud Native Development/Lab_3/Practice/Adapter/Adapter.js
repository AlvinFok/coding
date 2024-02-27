"use strict";
exports.__esModule = true;
exports.Adapter_C = exports.Adapter_B = exports.Adapter_A = void 0;
var Adapter_A = /** @class */ (function () {
    function Adapter_A(processTool) {
        this.processTool_A = processTool;
    }
    Adapter_A.prototype.execute = function (sr) {
        console.log('(Adapter A process subrecipe for Tool A)');
        this.processTool_A.execute(sr);
    };
    return Adapter_A;
}());
exports.Adapter_A = Adapter_A;
var Adapter_B = /** @class */ (function () {
    function Adapter_B(processTool) {
        this.processTool_B = processTool;
    }
    Adapter_B.prototype.execute = function (sr) {
        console.log('(Adapter B process subrecipe for Tool B)');
        this.processTool_B.execute(sr);
    };
    return Adapter_B;
}());
exports.Adapter_B = Adapter_B;
var Adapter_C = /** @class */ (function () {
    function Adapter_C(processTool) {
        this.processTool_C = processTool;
    }
    Adapter_C.prototype.execute = function (sr) {
        console.log('(Adapter C process subrecipe for Tool C)');
        this.processTool_C.execute(sr);
    };
    return Adapter_C;
}());
exports.Adapter_C = Adapter_C;
