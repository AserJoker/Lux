declare const require: (path: string) => any;
declare const println: (msg: string) => void;
declare const exit: () => void;
declare function asset(token: string, type: "buffer"): ArrayBuffer | undefined;
declare function asset (token: string, type: "string") : string | undefined;
declare function createImage(token:string):number;
declare function deleteImage(handle:number):boolean;