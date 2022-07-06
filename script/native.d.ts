declare const native:{
    setTitle:(title:string)=>void;
    getTitle:()=>string;
    setSize:(width:number,height:number)=>void;
    getSize:()=>[number,number];
    setFullscreen:(flag:0|1|2)=>void;
}
declare const resource:{
    asset:(token:string)=>ArrayBuffer|undefined;
}