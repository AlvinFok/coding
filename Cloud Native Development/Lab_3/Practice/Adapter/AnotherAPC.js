"use strict";
exports.__esModule = true;
exports.AnotherAPC = void 0;
var Subrecipe_1 = require("./Subrecipe");
var AnotherAPC = /** @class */ (function () {
    function AnotherAPC() {
    }
    AnotherAPC.prototype.genSubrecipe = function (wafer) {
        return new Subrecipe_1.Subrecipe('APC Subrecipe for ' + wafer.id);
    };
    AnotherAPC.prototype.execute = function (wafer, processTool) {
        var sr = this.genSubrecipe(wafer);
        if (processTool.toolName == 'A') {
            console.log('(Adapter A process subrecipe for Tool A)');
        }
        else if (processTool.toolName == 'B') {
            console.log('(Adapter B process subrecipe for Tool B)');
        }
        else {
            // default tool A
            console.log('(Adapter A process subrecipe for Tool A)');
        }
        processTool.execute(sr);
    };
    return AnotherAPC;
}());
exports.AnotherAPC = AnotherAPC;
