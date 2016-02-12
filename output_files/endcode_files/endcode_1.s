L100
L110	 movi R[255],M[4+R[0]]
	 movi M[28+R[0]],R[255]
	 movi R[255],24
	addi R[0],R[255],R[0]
	 movi R[255],$
	 movi R[254],15
	 addi R[255],R[255],R[254]
	 movi M[R[0]],R[255]
	 jmp L1632263269
	 movi R[255],24
	 subi R[0],R[0],R[255]
L120	 halt
L130