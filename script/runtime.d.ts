declare const require: (path: string) => any;
declare const println: (msg: string) => void;
declare const exit: () => void;
declare function asset(token: string, type: "buffer"): ArrayBuffer | undefined;
declare function asset (token: string, type: "string") : string | undefined;
declare function createImage(token:string):number;
declare function deleteImage(handle:number):boolean;
declare const _system_event_bus:{
    listen:(event:string,callback:()=>void)=>()=>void;
    remove:(event:string,callback:()=>void)=>void;
}