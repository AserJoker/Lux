import { Base } from "../base";

export class Scene_Base extends Base {
  private static _scenes: Record<string, typeof Scene_Base> = {};
  public static Scene(name: string) {
    return <T extends typeof Scene_Base>(classObject: T) => {
      Scene_Base._scenes[name] = classObject;
    };
  }
  public static get(name: string) {
    const SceneClassObject = Scene_Base._scenes[name];
    if (SceneClassObject) {
      return new SceneClassObject();
    } else {
      throw new Error(`unknown scene:${name}`);
    }
  }
}
