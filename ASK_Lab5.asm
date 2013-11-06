__asm{
		mov al, a
		mov ah, b
		xor bx, bx
		xor cx, cx
petla:
		cmp cx, 8
		jae koniec_petli
		mov dx, 1
		shl dx, cl
		test al, dl
		jnz mnoz
		jmp inkrementuj
		mnoz:
			xor dx, dx
			mov dl, ah
			shl dx, cl
			add bx, dx
		inkrementuj:
			inc cx
			jmp petla
koniec_petli: 
    mov wynik, bx
	};
