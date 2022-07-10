import { Scene_Base } from "./Scene_Base";

export class Scene_Main extends Scene_Base {
    private demo: Sprite | null = null;
    private font: Font | null = null;
    private lastTime = Date.now();
    public onMounted(): void {
        this.demo = Sprite_load("texture::demo");
        this.demo.setVisible(true);
        this.font = Font_load("font::demo", 32);
    }
    public onRender(): void {
        const now = Date.now();
        if (this.demo) {
            this.demo.draw();
        }
        if (this.font) {
            this.font.drawText(`FPS:${1000 / (now - this.lastTime)}`.substring(0, 8), 120, 120, 255, 0, 0, 255);
        }
        console.log(1000 / (now - this.lastTime))
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