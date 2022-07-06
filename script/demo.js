function ArrayBufferUTF8ToStr(array){
    var out,i,len,c;
    var char2,char3;
    out = "";
    len = array.length;
    i=0;
    while(i<len){
         c = array[i++];
        // if(c>>4<=7){
        //     out+=String.fromCharCode(c);
        // }else if(c>>4===12||c>>4===13){
        //     char2 = array[i++];
        //     out+=String.fromCharCode(((c&0x1f)<<6)|(char2&0x3f));
        // }else if(c>>4===14){
        //     char2 = array[i++];
        //     char3 = array[i++];
        //     out+=String.fromCharCode(((c&0xf)<<12)|((char2&0x3f)<<6)|((char3&0x3f)));
        // }
        out+=String.fromCharCode(c);
    }
    return out;
}
const buffer = resource.asset("i18n::zh_CN");
if(buffer){
    const view =new Uint8Array(buffer);
    var str = ArrayBufferUTF8ToStr(view);
    var obj = JSON.parse(str);
    println(obj.ui.exit);
}else{
    println("buffer is undefined");
}
