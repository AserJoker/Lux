import { Scene_Base } from "./Scene_Base";

@Scene_Base.Scene("main")
export class Scene_Main extends Scene_Base {
  @Scene_Base.Sprite(800, 600, SpriteAccess.STREAM)
  private demo!: Sprite;
  @Scene_Base.Font("font::demo", 32)
  private font!: Font;
  private x = 100;
  private x_step = 0;
  public onMounted(): void {
    super.onMounted();
    this.demo.setVisible(true);
    _system_event_bus.listen(EVENT.KEYDOWN, (key: number) => {
      if (key === SCANCODE.RIGHT) {
        this.x_step = 1;
      } else if (key === SCANCODE.LEFT) {
        this.x_step = -1;
      }
    });
    _system_event_bus.listen(EVENT.KEYUP, (key: number) => {
      if (key === SCANCODE.RIGHT && this.x_step === 1) {
        this.x_step = 0;
      } else if (key === SCANCODE.LEFT && this.x_step === -1) {
        this.x_step = 0;
      }
    });
  }
  public onRender(): void {
    super.onRender();
    this.font.drawText(this.demo, "hello world", this.x, 100, 255, 0, 0, 255);
    this.demo.draw();
    this.x+=this.x_step;
  }
  public onUnmounted(): void {
    super.onUnmounted();
  }
}
