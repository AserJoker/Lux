"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.Scene_Base = void 0;
var Scene_Base = /** @class */ (function () {
    function Scene_Base() {
    }
    Scene_Base.prototype.onMounted = function () { };
    Scene_Base.prototype.onRender = function () { };
    Scene_Base.prototype.onUnmounted = function () { };
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
    Scene_Base.Attribute = function (getter, release) {
        return function (target, name) {
            var onMounted = target.onMounted;
            var onUnmounted = target.onUnmounted;
            target.onMounted = function () {
                this[name] = getter();
                onMounted.call(this);
            };
            if (release) {
                target.onUnmounted = function () {
                    onUnmounted.call(this);
                    var item = this[name];
                    if (item) {
                        release(item);
                        this[name] = null;
                    }
                };
            }
        };
    };
    Scene_Base.Font = function (token, size) {
        return Scene_Base.Attribute(function () { return Font_load(token, size); }, function (font) { return font.dispose(); });
    };
    Scene_Base.TextSprite = function (font, text, r, g, b, a) {
        return Scene_Base.Attribute(function () { return font.createSprite(text, r, g, b, a); }, function (item) { return item.dispose(); });
    };
    Scene_Base.Sprite = function () {
        var args = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            args[_i] = arguments[_i];
        }
        if (args.length === 1) {
            return Scene_Base.Attribute(function () { return Sprite_load(args[0]); }, function (sprite) { return sprite.dispose(); });
        }
        return Scene_Base.Attribute(function () {
            return Sprite_create(args[0], args[1], args[2]);
        });
    };
    Scene_Base.OnEvent = function (event) {
        return function (target, name, descriptor) {
            if (!descriptor.value) {
                throw new Error("unsupport runtime");
            }
            var handle = descriptor.value;
            var onMounted = target.onMounted;
            var onUnmounted = target.onUnmounted;
            var bindHandle;
            target.onMounted = function () {
                onMounted.call(this);
                bindHandle = handle.bind(this);
                _system_event_bus.listen(event, bindHandle);
            };
            target.onUnmounted = function () {
                if (bindHandle) {
                    _system_event_bus.remove(event, bindHandle);
                }
                onUnmounted.call(this);
            };
        };
    };
    Scene_Base._scenes = {};
    return Scene_Base;
}());
exports.Scene_Base = Scene_Base;
