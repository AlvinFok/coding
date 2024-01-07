"use strict";
exports.__esModule = true;
exports.Adapter_B = exports.Adapter_A = void 0;
var Adapter_A = /** @class */ (function () {
    function Adapter_A(processTool) {
        this.processTool_A = processTool;
    }
    Adapter_A.prototype.execute = function (sr) {
        console.log('(Adapter A process subrecipe for Tool A)');
        this.processTool_A.execute(sr);
    };
    Adapter_A.prototype.addJobs = function (job) {
        console.log('(Adapter A process subrecipe for Tool A)');
        console.log('(Adapter A add job to Tool A)');
        this.processTool_A.addJobs(job);
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
    Adapter_B.prototype.addJobs = function (job) {
        console.log('(Adapter B process subrecipe for Tool B)');
        console.log('(Adapter A add job to Tool A)');
        this.processTool_B.addJobs(job);
    };
    return Adapter_B;
}());
exports.Adapter_B = Adapter_B;
