progr test5{

     declare x,y,z enddeclare

     function add(in x,in y){
        declare x,y,z enddeclare
            x:=x
            y:=y
            z:=x+y
            return(z)
     }
     procedure min(in x,in y){
            if([x<y]){
                print(x)
            }
            else{
                print(y)
            }
     }

     function printcond(in x){
           do{
                x:=x-1
           }while(x=0)

     }
     procedure id(in x,inout y){
        while([x=0] and [x=9] or [x=10]){
                print(z)
        }

     }

    call min(in x,in y);
    call add(in x,inout y);
    x:=id(in x,inout y);

}

