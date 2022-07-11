import { Scene_Base } from "./Scene_Base";

export class Scene_Main extends Scene_Base {
    private demo: Sprite | null = null;
    private font: Font | null = null;
    private lastTime = Date.now();
    public onMounted(): void {
        this.font = Font_load("font::demo", 32);
        this.demo = Sprite_create(800,600,SpriteAccess.STREAM);
        this.font.drawText(this.demo,"hello world",100,100,255,0,0,255);
        this.demo.setVisible(true);
    }
    public onRender(): void {
        const now = Date.now();
        if (this.demo) {
            this.demo.draw();
        }
        this.lastTime = now;
    }
    public onUnmounted(): void {
        if (this.demo) {
            this.demo.dispose();
            this.demo = null;
        }
        if (this.font) {
            this.font.dispose();
            this.font = null;
        }
    }
}