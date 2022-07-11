import { Scene_Base } from "./Scene_Base";

@Scene_Base.Scene("main")
export class Scene_Main extends Scene_Base {
    @Scene_Base.Sprite(800,600,SpriteAccess.STREAM)
    private demo!: Sprite;
    @Scene_Base.Font("font::demo",32)
    private font!: Font;
    public onMounted(): void {
        super.onMounted();
        this.font.drawText(this.demo,"hello world",100,100,255,0,0,255);
        this.demo.setVisible(true);
    }
    public onRender(): void {
        super.onRender();
        this.demo.draw();
    }
    public onUnmounted(): void {
        super.onUnmounted();
    }
}