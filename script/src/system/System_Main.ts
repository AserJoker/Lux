import {  Scene_Base } from "../scene";

export class System_Main {
    private static _theSystem_Main: System_Main;
    public static get() {
        if (!System_Main._theSystem_Main) {
            System_Main._theSystem_Main = new System_Main();
        }
        return System_Main._theSystem_Main;
    }
    private _scene: Scene_Base;
    public constructor() {
        this._scene = Scene_Base.get("main");
        _system_event_bus.listen(EVENT.READY, () => this.onReady());
        _system_event_bus.listen(EVENT.UPDATE, () => this.onUpdate());
    }
    public loadScene(scene: Scene_Base) {
        this._scene.onUnmounted();
        this._scene = scene;
        this._scene.onMounted();
    }
    private onReady() {
        this._scene.onMounted();
    }
    private onUpdate() {
        Sprite_begin(undefined);
        this._scene.onRender();
        Sprite_end();
    }
}