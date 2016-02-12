L100
L110	 movi R[1],M[612]
	 movi R[2],9
	 cmpi R[1],R[2]
	 je L130
L120	 jmp L380
L130	 movi R[1],M[612]
	 movi R[2],9
	 cmpi R[1],R[2]
	 je L150
L140	 jmp L380
L150	 movi R[1],M[620]
	 movi R[2],1
	 addi R[3],R[1],R[2]
	 movi M[24+R[0]],R[3]
L160	 movi R[1],M[24+R[0]]
	 movi M[620],R[1]
L170	 movi R[1],M[612]
	 movi R[2],0
	 cmpi R[1],R[2]
	 je L190
L180	 jmp L270
L190	 movi R[1],M[612]
	 movi R[2],1
	 cmpi R[1],R[2]
	 je L210
L200	 jmp L270
L210	 movi R[1],M[612]
	 movi R[2],2
	 cmpi R[1],R[2]
	 je L230
L220	 jmp L270
L230	 movi R[1],M[612]
	 outi R[1]
L240	 movi R[1],M[612]
	 movi R[255],M[8 + R[0]]
	 movi M[R[255]],R[1]
L250L260	 jmp L370
L270	 movi R[1],M[612]
	 movi R[2],1
	 addi R[3],R[1],R[2]
	 movi M[28+R[0]],R[3]
L280	 movi R[1],M[28+R[0]]
	 movi M[620],R[1]
L290	 movi R[1],M[612]
	 movi R[2],1
	 addi R[3],R[1],R[2]
	 movi M[32+R[0]],R[3]
L300	 movi R[1],M[32+R[0]]
	 movi M[612],R[1]
L310	 movi R[1],M[612]
	 movi R[2],0
	 cmpi R[1],R[2]
	 je L270
L320	 jmp L330
L330	 movi R[1],M[616]
	 movi R[2],1
	 cmpi R[1],R[2]
	 je L270
L340	 jmp L350
L350	 movi R[1],M[620]
	 movi R[2],0
	 cmpi R[1],R[2]
	 jne L270
L360	 jmp L370
L370	 jmp L110
L380	 movi R[1],M[612]
	 movi R[2],0
	 cmpi R[1],R[2]
	 jne L400
L390	 jmp L420
L400	 movi R[1],M[612]
	 outi R[1]
L410	 jmp L380
L420	 halt
L430