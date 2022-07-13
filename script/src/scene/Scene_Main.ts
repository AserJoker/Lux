import { Scene_Base } from "./Scene_Base";

@Scene_Base.Scene("main")
export class Scene_Main extends Scene_Base {
  private demo!: Sprite;
  @Scene_Base.Font("font::demo", 32)
  private font!: Font;
  public onMounted(): void {
    super.onMounted();
    this.demo = this.font.createSprite("hello world",255,0,0,255);
    this.demo.setVisible(true);
  }
  @Scene_Base.OnEvent(EVENT.MOUSEMOTION)
  public onMouseMove(x:number,y:number){
    this.demo.setTargetRect(x,y,...this.demo.getSize());
  }
  public onRender(): void {
    super.onRender();
    this.demo.draw();
  }
  public onUnmounted(): void {
    super.onUnmounted();
    if(this.demo){
      this.demo.dispose();
    }
  }
}
