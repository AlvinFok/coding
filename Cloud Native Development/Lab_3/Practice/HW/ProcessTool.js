"use strict";
exports.__esModule = true;
exports.ProcessTool = void 0;
var ProcessTool = /** @class */ (function () {
    function ProcessTool(toolName) {
        this.toolName = toolName;
        this.jobs = new Array();
    }
    ProcessTool.prototype.addJobs = function (job) {
        this.jobs.push(job);
    };
    ProcessTool.prototype.execute = function (sr) {
        console.log('Process Tool ' + this.toolName + ' execute subrecipe[ ' + sr.name + ' ]');
    };
    ;
    ProcessTool.prototype.executeCommand = function () {
        console.log('Tool[', this.toolName, '] start to execute jobs.');
        this.jobs.forEach(function (job) {
            job.execute();
        });
    };
    ;
    return ProcessTool;
}());
exports.ProcessTool = ProcessTool;
