"use strict";
exports.__esModule = true;
exports.NBStrategy = exports.PCStrategy = exports.MPStrategy = void 0;
var MPStrategy = /** @class */ (function () {
    function MPStrategy() {
    }
    MPStrategy.prototype.genType = function () {
        return 'MobilePhone';
    };
    return MPStrategy;
}());
exports.MPStrategy = MPStrategy;
var PCStrategy = /** @class */ (function () {
    function PCStrategy() {
    }
    PCStrategy.prototype.genType = function () {
        return 'PersonalComputer';
    };
    return PCStrategy;
}());
exports.PCStrategy = PCStrategy;
var NBStrategy = /** @class */ (function () {
    function NBStrategy() {
    }
    NBStrategy.prototype.genType = function () {
        return 'NoteBook';
    };
    return NBStrategy;
}());
exports.NBStrategy = NBStrategy;
