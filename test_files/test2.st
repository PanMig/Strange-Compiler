program test2{
    declare x,y,z enddeclare

    while([x=9] and not[x=9]){
        z:=z+1
        if([x=0 and x=1 and x=2]){
                print(x)
                return(x)
                exit;
        }
        else{
            do{
                z:=x+1
                x:=x+1

            }while(x=0 or y=1 or z<>0)
        }


    }

    forcase{
            when([x<>0]){
                print(x);
            }

    }


}













