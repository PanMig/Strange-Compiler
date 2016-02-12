L100
L110
L120
L130
L140	 movi R[1],M[12+R[0]]
	 movi R[255],M[R[0]+4]
	 movi R[255],M[4+R[255]]
	 movi R[254],20
	 addi R[255],R[254],R[255]
	 movi M[R[255]],R[1]
L150	 movi R[255],M[R[0]+4]
	 movi R[255],M[4+R[255]]
	 movi R[254],12
	 addi R[255],R[254],R[255]
	 movi R[1],M[R[255]]
	 movi R[255],M[R[0]+4]
	 movi R[255],M[4+R[255]]
	 movi R[254],16
	 addi R[255],R[254],R[255]
	 movi R[255],M[R[255]]
	 movi M[R[255]],R[1]
L160	 movi R[255],M[612]
	 movi M[32 +R[0]],R[255]
L170	 movi R[255],R[0]
	 movi R[254],16
	 addi R[255],R[254],R[255]
	 movi M[28+R[0]],R[255]
L180	 movi R[255],M[4+R[0]]
	 movi M[24+R[0]],R[255]
	 movi R[255],20
	addi R[0],R[255],R[0]
	 movi R[255],$
	 movi R[254],15
	 addi R[255],R[255],R[254]
	 movi M[R[0]],R[255]
	 jmp L0
	 movi R[255],20
	 subi R[0],R[0],R[255]
L190	 movi R[1],M[16+R[0]]
	 movi M[20+R[0]],R[1]
L200	 movi R[1],M[20+R[0]]
	 movi R[255],M[8 + R[0]]
	 movi M[R[255]],R[1]
L210	 jmp M[R[0]]
L220	 jmp M[R[0]]
L230	 jmp M[R[0]]
L240	 movi R[255],M[612]
	 movi M[40 +R[0]],R[255]
L250	 movi R[255],R[0]
	 movi R[254],16
	 addi R[255],R[254],R[255]
	 movi M[44+R[0]],R[255]
L260	 movi R[255],R[0]
	 movi R[254],20
	 addi R[255],R[254],R[255]
	 movi M[32+R[0]],R[255]
L270	 movi R[255],M[4+R[0]]
	 movi M[28+R[0]],R[255]
	 movi R[255],24
	addi R[0],R[255],R[0]
	 movi R[255],$
	 movi R[254],15
	 addi R[255],R[255],R[254]
	 movi M[R[0]],R[255]
	 jmp L110
	 movi R[255],24
	 subi R[0],R[0],R[255]
L280	 movi R[1],M[20+R[0]]
	 movi M[612],R[1]
L290	 halt
L300