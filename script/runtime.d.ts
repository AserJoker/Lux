declare const require: (path: string) => any;
declare const println: (msg: string) => void;
declare const exit: () => void;
declare function asset(token: string, type: "buffer"): ArrayBuffer | undefined;
declare function asset(token: string, type: "string"): string | undefined;
declare const _system_event_bus: {
    listen: (event: string, callback: () => void) => () => void;
    remove: (event: string, callback: () => void) => void;
}
declare function Sprite_load(token:string):number;
declare function Sprite_dispose(handle:number):void;
declare function Sprite_draw(handle:number):void;
declare function Sprite_setSourceRect(handle:number,x:number,y:number,w:number,h:number):void;
declare function Sprite_setTargetRect(handle:number,x:number,y:number,w:number,h:number):void;
declare function Sprite_setRotation(handle: number,x:number,y:number,angle:number):void;
declare function Sprite_setVisible(handle:number,visible:boolean):void;
declare function Sprite_getSourceRect(handle:number):[number,number,number,number];
declare function Sprite_getTargetRect(handle:number):[number,number,number,number];
declare function Sprite_getRotation(handle:number):[number,number,number];
declare function Sprite_getVisible(handle:number):boolean;