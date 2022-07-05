declare const native: {
    println: (msg: string) => void;
    loadModule: (path: string) => any;
    load: (path: string) => any;
    exists: (path: string) => boolean;
}
declare const require: (path: string) => any;