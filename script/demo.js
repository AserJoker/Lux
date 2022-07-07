const str = asset("i18n::zh_CN","string");
if(str){
    var obj = JSON.parse(str);
    println(obj.ui.exit);
}else{
    println("str is undefined");
}
const img = createImage("texture::demo");
console.log(deleteImage(img))