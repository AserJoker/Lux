interface Sprite {
  dispose(): void;
  draw(): void;
  setSourceRect(x: number, y: number, w: number, h: number): void;
  setTargetRect(x: number, y: number, w: number, h: number): void;
  setRotation(x: number, y: number, angle: number): void;
  setVisible(visible: boolean): void;
  setOpacity(opacity:number):void;
  getSourceRect(): [number, number, number, number];
  getTargetRect(): [number, number, number, number];
  getRotation(): [number, number, number];
  getVisible(): boolean;
  getSize():[number,number];
  getOpacity():number;
}
const enum SpriteAccess{
    STATIC = 0,
    STREAM = 1,
    TARGET = 2
}

declare const require: (path: string) => any;
declare const println: (msg: string) => void;
declare const exit: () => void;
declare function asset(token: string, type: "buffer"): ArrayBuffer | undefined;
declare function asset(token: string, type: "string"): string | undefined;
declare const _system_event_bus: {
  listen: (event: string, callback: () => void) => () => void;
  remove: (event: string, callback: () => void) => void;
};
declare function Sprite_load(token: string): Sprite;
declare function Sprite_create(width:number,height:number,access:SpriteAccess): Sprite;
declare function Sprite_setRenderTarget(sprite:Sprite|undefined):void;