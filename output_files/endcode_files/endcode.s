L100
L110
L120	 movi R[1],M[12+R[0]]
	 movi M[12+R[0]],R[1]
L130	 movi R[1],M[16+R[0]]
	 movi M[16+R[0]],R[1]
L140	 movi R[1],M[12+R[0]]
	 movi R[2],M[16+R[0]]
	 addi R[3],R[1],R[2]
	 movi M[32+R[0]],R[3]
L150	 movi R[1],M[32+R[0]]
	 movi M[28+R[0]],R[1]
L160	 movi R[1],M[28+R[0]]
	 movi R[255],M[8 + R[0]]
	 movi M[R[255]],R[1]
L170	 jmp M[R[0]]
L180
L190	 movi R[1],M[12+R[0]]
	 movi R[2],M[16+R[0]]
	 cmpi R[1],R[2]
	 ja L210
L200	 jmp L230
L210	 movi R[1],M[12+R[0]]
	 outi R[1]
L220	 jmp L240
L230	 movi R[1],M[16+R[0]]
	 outi R[1]
L240	 jmp M[R[0]]
L250
L260	 movi R[1],M[12+R[0]]
	 movi R[2],1
	 subi R[3],R[1],R[2]
	 movi M[16+R[0]],R[3]
L270	 movi R[1],M[16+R[0]]
	 movi M[12+R[0]],R[1]
L280	 movi R[1],M[12+R[0]]
	 movi R[2],0
	 cmpi R[1],R[2]
	 je L260
L290	 jmp L300
L300	 jmp M[R[0]]
L310
L320	 movi R[1],M[12+R[0]]
	 movi R[2],0
	 cmpi R[1],R[2]
	 je L340
L330	 jmp L360
L340	 movi R[1],M[12+R[0]]
	 movi R[2],9
	 cmpi R[1],R[2]
	 je L380
L350	 jmp L360
L360	 movi R[1],M[12+R[0]]
	 movi R[2],10
	 cmpi R[1],R[2]
	 je L380
L370	 jmp L400
L380	 movi R[1],M[620]
	 outi R[1]
L390	 jmp L320
L400	 jmp M[R[0]]
L410	 movi R[255],M[612]
	 movi M[40 +R[0]],R[255]
L420	 movi R[255],M[616]
	 movi M[44 +R[0]],R[255]
L430	 movi R[255],M[4+R[0]]
	 movi M[32+R[0]],R[255]
	 movi R[255],28
	addi R[0],R[255],R[0]
	 movi R[255],$
	 movi R[254],15
	 addi R[255],R[255],R[254]
	 movi M[R[0]],R[255]
	 jmp L180
	 movi R[255],28
	 subi R[0],R[0],R[255]
L440	 movi R[255],M[612]
	 movi M[48 +R[0]],R[255]
L450	 movi R[255],R[0]
	 movi R[254],16
	 addi R[255],R[254],R[255]
	 movi M[52+R[0]],R[255]
L460	 movi R[255],M[4+R[0]]
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
L470	 halt
L480