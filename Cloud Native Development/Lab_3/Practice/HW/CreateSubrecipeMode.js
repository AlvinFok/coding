"use strict";
exports.__esModule = true;
exports.FeedforwardMode = exports.RecommendMode = exports.ByProductStrategyMode = void 0;
var Subrecipe_1 = require("./Subrecipe");
var ProductStrategy_1 = require("./ProductStrategy");
var ProductStrategy_2 = require("./ProductStrategy");
var ProductStrategy_3 = require("./ProductStrategy");
var TeachStrategy_1 = require("./TeachStrategy");
var ByProductStrategyMode = /** @class */ (function () {
    function ByProductStrategyMode() {
    }
    ByProductStrategyMode.prototype.decideProductStrategy = function (wafer) {
        if (wafer.product == 'Mobile Phone') {
            return new ProductStrategy_1.MPStrategy();
        }
        else if (wafer.product == 'Personal Computer') {
            return new ProductStrategy_2.PCStrategy();
        }
        else {
            return new ProductStrategy_3.NBStrategy();
        }
    };
    ByProductStrategyMode.prototype.decideTeachStrategy = function (wafer) {
        if (wafer.teach == "N7") {
            return new TeachStrategy_1.N7Strategy();
        }
        else if (wafer.teach == "N5") {
            return new TeachStrategy_1.N5Strategy();
        }
        else {
            return new TeachStrategy_1.N3Strategy();
        }
    };
    ByProductStrategyMode.prototype.genSubrecipe = function (wafer) {
        this.productStrategy = this.decideProductStrategy(wafer);
        var type = this.productStrategy.genType();
        this.teachStrategy = this.decideTeachStrategy(wafer);
        var teach = this.teachStrategy.genTeach();
        return new Subrecipe_1.Subrecipe('APC Subrecipe for[' + wafer.id + ']: A+B*(Fn of ' + type + ')' + ' + (Fn of ' + teach + ')');
    };
    return ByProductStrategyMode;
}());
exports.ByProductStrategyMode = ByProductStrategyMode;
var RecommendMode = /** @class */ (function () {
    function RecommendMode() {
    }
    RecommendMode.prototype.genSubrecipe = function (wafer) {
        return new Subrecipe_1.Subrecipe('Recommend Subrecipe for[' + wafer.id + ']');
    };
    return RecommendMode;
}());
exports.RecommendMode = RecommendMode;
var FeedforwardMode = /** @class */ (function () {
    function FeedforwardMode() {
    }
    FeedforwardMode.prototype.genSubrecipe = function (wafer) {
        return new Subrecipe_1.Subrecipe('Feedforward Subrecipe for[' + wafer.id + ']');
    };
    return FeedforwardMode;
}());
exports.FeedforwardMode = FeedforwardMode;
