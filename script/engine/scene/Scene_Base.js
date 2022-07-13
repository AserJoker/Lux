"use strict";
var __extends = (this && this.__extends) || (function () {
    var extendStatics = function (d, b) {
        extendStatics = Object.setPrototypeOf ||
            ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
            function (d, b) { for (var p in b) if (Object.prototype.hasOwnProperty.call(b, p)) d[p] = b[p]; };
        return extendStatics(d, b);
    };
    return function (d, b) {
        if (typeof b !== "function" && b !== null)
            throw new TypeError("Class extends value " + String(b) + " is not a constructor or null");
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();
Object.defineProperty(exports, "__esModule", { value: true });
exports.Scene_Base = void 0;
var base_1 = require("../base");
var Scene_Base = /** @class */ (function (_super) {
    __extends(Scene_Base, _super);
    function Scene_Base() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    Scene_Base.Scene = function (name) {
        return function (classObject) {
            Scene_Base._scenes[name] = classObject;
        };
    };
    Scene_Base.get = function (name) {
        var SceneClassObject = Scene_Base._scenes[name];
        if (SceneClassObject) {
            return new SceneClassObject();
        }
        else {
            throw new Error("unknown scene:".concat(name));
        }
    };
    Scene_Base._scenes = {};
    return Scene_Base;
}(base_1.Base));
exports.Scene_Base = Scene_Base;
