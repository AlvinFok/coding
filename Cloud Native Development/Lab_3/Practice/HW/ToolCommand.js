"use strict";
exports.__esModule = true;
exports.ReticleJob = exports.ScannerJob = void 0;
var ScannerJob = /** @class */ (function () {
    function ScannerJob(subrecipe, toolName) {
        this.subrecipe = subrecipe;
        this.toolName = toolName;
    }
    ScannerJob.prototype.execute = function () {
        console.log('Execute ScannerJob for tool[', this.toolName, '] subrecipe[', this.subrecipe.name, ']');
    };
    return ScannerJob;
}());
exports.ScannerJob = ScannerJob;
var ReticleJob = /** @class */ (function () {
    function ReticleJob(action) {
        this.action = action;
    }
    ReticleJob.prototype.execute = function () {
        console.log('Execute ReticleJob ', this.action);
    };
    return ReticleJob;
}());
exports.ReticleJob = ReticleJob;
