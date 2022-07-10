interface Sprite {
  dispose(): void;
  draw(): void;
  setSourceRect(x: number, y: number, w: number, h: number): void;
  setTargetRect(x: number, y: number, w: number, h: number): void;
  setRotation(x: number, y: number, angle: number): void;
  setVisible(visible: boolean): void;
  setOpacity(opacity: number): void;
  getSourceRect(): [number, number, number, number];
  getTargetRect(): [number, number, number, number];
  getRotation(): [number, number, number];
  getVisible(): boolean;
  getSize(): [number, number];
  getOpacity(): number;
}
interface Font {
  drawText(text: string, r: number, g: number, b: number, a: number): Sprite;
  dispose(): void;
}
const enum SpriteAccess {
  STATIC = 0,
  STREAM = 1,
  TARGET = 2
}
const enum EVENT {
  READY = "lux::system::Application.ready",
  UPDATE = "lux::system::Graphic.loop"
}
declare const __dirname: string;
declare const __filename: string;
declare const _system_event_bus: {
  listen: (event: string, callback: () => void) => () => void;
  remove: (event: string, callback: () => void) => void;
};
declare function require(path: string): any;
declare function println(msg: string): void;
declare function exit(): void;
declare function asset(token: string, type: "buffer"): ArrayBuffer | undefined;
declare function asset(token: string, type: "string"): string | undefined;
declare function setTimeout(cb: Function, delay: number): number;
declare function clearTimeout(id: number): void;
declare function nextTick(cb: Function): void;
declare function Sprite_load(token: string): Sprite;
declare function Sprite_create(width: number, height: number, access: SpriteAccess): Sprite;
declare function Sprite_begin(target: Sprite | undefined): void;
declare function Sprite_end(): void;
declare function Font_load(token: string, size: number): Font;