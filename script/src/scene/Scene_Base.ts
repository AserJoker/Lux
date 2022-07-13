export class Scene_Base {
  private static _scenes: Record<string, typeof Scene_Base> = {};
  public onMounted() {}
  public onRender() {}
  public onUnmounted() {}
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
  public static Attribute<T>(getter: () => T, release?: (item: T) => void) {
    return <C extends Scene_Base>(target: C, name: string) => {
      const onMounted = target.onMounted;
      const onUnmounted = target.onUnmounted;
      target.onMounted = function <K extends keyof C>(this: C) {
        this[name as K] = getter() as unknown as C[K];
        onMounted.call(this);
      };
      if (release) {
        target.onUnmounted = function <K extends keyof C>(this: C) {
          onUnmounted.call(this);
          const item = this[name as K] as unknown as T;
          if (item) {
            release(item);
            (this[name as K] as unknown) = null;
          }
        };
      }
    };
  }
  public static Font(token: string, size: number) {
    return Scene_Base.Attribute(
      () => Font_load(token, size),
      (font) => font.dispose()
    );
  }
  public static TextSprite(
    font: Font,
    text: string,
    r: number,
    g: number,
    b: number,
    a: number
  ) {
    return Scene_Base.Attribute(
      () => font.createSprite(text, r, g, b, a),
      (item) => item.dispose()
    );
  }
  public static Sprite(
    token: string
  ): <C extends Scene_Base>(target: C, name: string) => void;
  public static Sprite(
    width: number,
    height: number,
    access: SpriteAccess
  ): <C extends Scene_Base>(target: C, name: string) => void;
  public static Sprite(...args: unknown[]) {
    if (args.length === 1) {
      return Scene_Base.Attribute(
        () => Sprite_load(args[0] as string),
        (sprite) => sprite.dispose()
      );
    }
    return Scene_Base.Attribute(() =>
      Sprite_create(
        args[0] as number,
        args[1] as number,
        args[2] as SpriteAccess
      )
    );
  }
  public static OnEvent(event: EVENT) {
    return <C extends Scene_Base, K extends Function>(
      target: C,
      name: string,
      descriptor: TypedPropertyDescriptor<K>
    ) => {
      if (!descriptor.value) {
        throw new Error("unsupport runtime");
      }
      const handle = descriptor.value as Function as (...args: any[]) => void;
      const onMounted = target.onMounted;
      const onUnmounted = target.onUnmounted;
      let bindHandle: (...args: any[]) => void;
      target.onMounted = function (this: C) {
        onMounted.call(this);
        bindHandle = handle.bind(this);
        _system_event_bus.listen(event, bindHandle);
      };
      target.onUnmounted = function (this: C) {
        if (bindHandle) {
          _system_event_bus.remove(event, bindHandle);
        }
        onUnmounted.call(this);
      };
    };
  }
}
