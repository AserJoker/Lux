"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.Element_Base = void 0;
var Element_Base = /** @class */ (function () {
    function Element_Base() {
        this._next = null;
        this._children = null;
        this._parent = null;
        this._ready = false;
    }
    Element_Base.prototype.onMounted = function () { };
    Element_Base.prototype.onRener = function () {
        var child = this._children;
        while (child) {
            child.onRener();
            child = child._next;
        }
    };
    Element_Base.prototype.onUnmounted = function () {
        var child = this._children;
        while (child) {
            child.onUnmounted();
            child = child._next;
        }
    };
    Element_Base.prototype.append = function (ele) {
        if (!this._children) {
            this._children = ele;
        }
        else {
            var child = this._children;
            while (child._next !== null) {
                child = child._next;
            }
            child._next = ele;
        }
        ele._parent = this;
        ele.onMounted();
    };
    Element_Base.prototype.remove = function (ele) {
        if (!this._children) {
            return;
        }
        var child = this._children;
        while (child._next !== ele && child._next !== null) {
            child = child._next;
        }
        if (child._next === null) {
            return;
        }
        ele.onUnmounted();
        child._next = ele._next;
        ele._parent = null;
    };
    return Element_Base;
}());
exports.Element_Base = Element_Base;
