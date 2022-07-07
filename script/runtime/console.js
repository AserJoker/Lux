console = {
    log(){
        var str = "";
        for(var i =0;i<arguments.length;i++){
            if(i!==0){
                str+=",";
            }
            str+=arguments[i];
        }
        println(str);
    }
}