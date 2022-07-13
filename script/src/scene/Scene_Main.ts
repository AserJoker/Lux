import { System_Main } from "../system";
import { Scene_Base } from "./Scene_Base";

@Scene_Base.Scene("main")
export class Scene_Main extends Scene_Base {
  private $system!:System_Main;
  private x=0;
  private y=0;
  public onMounted(): void {
    super.onMounted();
    this.$system = System_Main.get();
    this.$system.$map.loadTile("tile::grass")
  }
  public onRender(): void {
    super.onRender();
    const [x,y] = this.$system.$camera.trasformToNative(this.x,this.y);
    this.$system.$map.draw(x,y,"grass",0);
    console.log(this.$system.$camera.getPosition().join(','))
  }
  public onUnmounted(): void {
    super.onUnmounted();
  }
  @Scene_Base.OnEvent(EVENT.KEYDOWN)
  private onKeydown(key:number){
    if(key===SCANCODE.D){
      this.x+=1;
      this.$system.$camera.move(1,0);
    }
    if(key===SCANCODE.A){
      this.x-=1;
      this.$system.$camera.move(-1,0);
    }
  }
}
