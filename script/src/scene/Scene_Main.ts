import { Scene_Base } from "./Scene_Base";

@Scene_Base.Scene("main")
export class Scene_Main extends Scene_Base {
    @Scene_Base.Sprite(800,600,SpriteAccess.STREAM)
    private demo!: Sprite;
    @Scene_Base.Font("font::demo",32)
    private font!: Font;
    private x = 100;
    public onMounted(): void {
        super.onMounted();
        this.demo.setVisible(true);
        _system_event_bus.listen(EVENT.KEYDOWN,(code:number)=>{
            console.log(code);
        })
    }
    public onRender(): void {
        super.onRender();
        this.font.drawText(this.demo,"hello world",this.x,100,255,0,0,255);
        this.demo.draw();
        this.x+=0.01;
    }
    public onUnmounted(): void {
        super.onUnmounted();
    }
}