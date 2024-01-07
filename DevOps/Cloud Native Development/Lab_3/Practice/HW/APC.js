"use strict";
exports.__esModule = true;
exports.APC = void 0;
var Adapter_1 = require("./Adapter");
var Adapter_2 = require("./Adapter");
var CreateSubrecipeModeFactory_1 = require("./CreateSubrecipeModeFactory");
var CreateSubrecipeModeFactory_2 = require("./CreateSubrecipeModeFactory");
var CreateSubrecipeModeFactory_3 = require("./CreateSubrecipeModeFactory");
var ToolCommand_1 = require("./ToolCommand");
var APC = /** @class */ (function () {
    function APC() {
    }
    APC.prototype.execute = function (wafer, processTool) {
        var sr = this.genSubrecipeForProd(wafer);
        if (processTool.toolName == 'A') {
            this.adapter = new Adapter_1.Adapter_A(processTool);
        }
        else if (processTool.toolName == 'B') {
            this.adapter = new Adapter_2.Adapter_B(processTool);
        }
        else {
            // default tool A
            this.adapter = new Adapter_1.Adapter_A(processTool);
        }
        var scannerJob = new ToolCommand_1.ScannerJob(sr, 'A');
        this.adapter.addJobs(scannerJob);
    };
    APC.prototype.genSubrecipeForProd = function (wafer) {
        console.log('Gen subrecipe for production.');
        var subrecipe = this.genSubrecipe(wafer);
        this.checkSubrecipeSpec(subrecipe);
        this.log(subrecipe);
        this.updateAPCModel(subrecipe);
        return subrecipe;
    };
    APC.prototype.preview = function (wafer, processTool) {
        console.log('Preview APC Subrecipe.');
        var subrecipe = this.genSubrecipe(wafer);
        this.checkSubrecipeSpec(subrecipe);
        return subrecipe;
    };
    APC.prototype.genSubrecipe = function (wafer) {
        if (wafer.genSubrecipeMode == 'ByProductStrategy') {
            this.subrecipeFactory = new CreateSubrecipeModeFactory_1.ByProductStrategyFactory();
        }
        else if (wafer.genSubrecipeMode == 'Recommend') {
            this.subrecipeFactory = new CreateSubrecipeModeFactory_2.ByRecommandFactory();
        }
        else {
            this.subrecipeFactory = new CreateSubrecipeModeFactory_3.ByFeedforwardFactory();
        }
        return this.subrecipeFactory.genCreateMode().genSubrecipe(wafer);
    };
    APC.prototype.checkSubrecipeSpec = function (subrecipe) {
        console.log('--> check subrecipe spec for ' + subrecipe.name);
    };
    APC.prototype.log = function (subrecipe) {
        console.log('--> log subrecipe for ' + subrecipe.name);
    };
    APC.prototype.updateAPCModel = function (subrecipe) {
        console.log('--> update APC model for ' + subrecipe.name);
    };
    return APC;
}());
exports.APC = APC;
