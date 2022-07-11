import {  Scene_Base } from "./scene";

export class GameMain {
    private static _theGameMain: GameMain;
    public static get() {
        if (!GameMain._theGameMain) {
            GameMain._theGameMain = new GameMain();
        }
        return GameMain._theGameMain;
    }
    private _scene: Scene_Base;
    public constructor() {
        _system_event_bus.listen(EVENT.READY, () => this.onReady());
        _system_event_bus.listen(EVENT.UPDATE, () => this.onUpdate());
        this._scene = Scene_Base.get("main");
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