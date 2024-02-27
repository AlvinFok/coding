"use strict";
exports.__esModule = true;
exports.ByFeedforwardFactory = exports.ByRecommandFactory = exports.ByProductStrategyFactory = void 0;
var CreateSubrecipeMode_1 = require("./CreateSubrecipeMode");
var CreateSubrecipeMode_2 = require("./CreateSubrecipeMode");
var CreateSubrecipeMode_3 = require("./CreateSubrecipeMode");
var ByProductStrategyFactory = /** @class */ (function () {
    function ByProductStrategyFactory() {
    }
    ByProductStrategyFactory.prototype.genCreateMode = function () {
        return new CreateSubrecipeMode_1.ByProductStrategyMode();
    };
    return ByProductStrategyFactory;
}());
exports.ByProductStrategyFactory = ByProductStrategyFactory;
var ByRecommandFactory = /** @class */ (function () {
    function ByRecommandFactory() {
    }
    ByRecommandFactory.prototype.genCreateMode = function () {
        return new CreateSubrecipeMode_2.RecommendMode();
    };
    return ByRecommandFactory;
}());
exports.ByRecommandFactory = ByRecommandFactory;
var ByFeedforwardFactory = /** @class */ (function () {
    function ByFeedforwardFactory() {
    }
    ByFeedforwardFactory.prototype.genCreateMode = function () {
        return new CreateSubrecipeMode_3.FeedforwardMode();
    };
    return ByFeedforwardFactory;
}());
exports.ByFeedforwardFactory = ByFeedforwardFactory;
