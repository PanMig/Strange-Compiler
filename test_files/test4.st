program test4 {
    declare x,y,z enddeclare

     function add(in x,in y){
        declare x,y,z enddeclare
            function f(in x,copy z,inout y){
                x:=10;
                y:=10;
                z:=10;
            }
            x:=f(in x);


     }

    x:=add(in x,inout y)



}
