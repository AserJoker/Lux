const str = resource.asset("i18n::zh_CN","string");
if(str){
    var obj = JSON.parse(str);
    println(obj.ui.exit);
}else{
    println("str is undefined");
}
