"use strict";
exports.__esModule = true;
exports.ProcessTool = void 0;
var ProcessTool = /** @class */ (function () {
    function ProcessTool(toolName) {
        this.toolName = toolName;
    }
    ;
    ProcessTool.prototype.execute = function (sr) {
        console.log('Process Tool ' + this.toolName + ' execute subrecipe[ ' + sr.name + ' ]');
    };
    ;
    return ProcessTool;
}());
exports.ProcessTool = ProcessTool;
