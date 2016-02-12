L100
L110
L120
L130	 movi R[1],10
	 movi M[12+R[0]],R[1]
L140	 movi R[1],10
	 movi R[255],M[20+R[0]]
	 movi M[R[255]],R[1]
L150	 movi R[1],10
L160	 jmp M[R[0]]
L170	 movi R[255],M[12+R[0]]
	 movi M[60 +R[0]],R[255]
L180	 movi R[255],R[0]
	 movi R[254],32
	 addi R[255],R[254],R[255]
	 movi M[44+R[0]],R[255]
L190	 movi R[255],M[4+R[0]]
	 movi M[40+R[0]],R[255]
	 movi R[255],36
	addi R[0],R[255],R[0]
	 movi R[255],$
	 movi R[254],15
	 addi R[255],R[255],R[254]
	 movi M[R[0]],R[255]
	 jmp L120
	 movi R[255],36
	 subi R[0],R[0],R[255]
L200	 movi R[1],M[32+R[0]]
	 movi M[12+R[0]],R[1]
L210	 jmp M[R[0]]
L220	 movi R[255],M[612]
	 movi M[56 +R[0]],R[255]
L230	 movi R[255],R[0]
	 movi R[254],16
	 addi R[255],R[254],R[255]
	 movi M[60+R[0]],R[255]
L240	 movi R[255],R[0]
	 movi R[254],24
	 addi R[255],R[254],R[255]
	 movi M[36+R[0]],R[255]
L250	 movi R[255],M[4+R[0]]
	 movi M[32+R[0]],R[255]
	 movi R[255],28
	addi R[0],R[255],R[0]
	 movi R[255],$
	 movi R[254],15
	 addi R[255],R[255],R[254]
	 movi M[R[0]],R[255]
	 jmp L110
	 movi R[255],28
	 subi R[0],R[0],R[255]
L260	 movi R[1],M[24+R[0]]
	 movi M[612],R[1]
L270	 halt
L280