"use strict";
exports.__esModule = true;
exports.APC = void 0;
var Subrecipe_1 = require("./Subrecipe");
var Adapter_1 = require("./Adapter");
var Adapter_2 = require("./Adapter");
var Adapter_3 = require("./Adapter");
var APC = /** @class */ (function () {
    function APC() {
    }
    APC.prototype.genSubrecipe = function (wafer) {
        return new Subrecipe_1.Subrecipe('APC Subrecipe for ' + wafer.id);
    };
    APC.prototype.execute = function (wafer, processTool) {
        var sr = this.genSubrecipe(wafer);
        if (processTool.toolName == 'A') {
            this.adapter = new Adapter_1.Adapter_A(processTool);
        }
        else if (processTool.toolName == 'B') {
            this.adapter = new Adapter_2.Adapter_B(processTool);
        }
        else if (processTool.toolName == 'C') {
            this.adapter = new Adapter_3.Adapter_C(processTool);
        }
        else {
            // default tool A
            this.adapter = new Adapter_1.Adapter_A(processTool);
        }
        this.adapter.execute(sr);
    };
    return APC;
}());
exports.APC = APC;
