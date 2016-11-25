	.386p
	ifdef ??version
	if    ??version GT 500H
	.mmx
	endif
	endif
	model flat
	ifndef	??version
	?debug	macro
	endm
	endif
	?debug	S "E:\usr\prj\Shacira\Extern\STYX\src\LIBBASE\Sysbase1.c"
	?debug	T "E:\usr\prj\Shacira\Extern\STYX\src\LIBBASE\Sysbase1.c"
_TEXT	segment dword public use32 'CODE'
_TEXT	ends
_DATA	segment dword public use32 'DATA'
_DATA	ends
_BSS	segment dword public use32 'BSS'
_BSS	ends
$$BSYMS	segment byte public use32 'DEBSYM'
$$BSYMS	ends
$$BTYPES	segment byte public use32 'DEBTYP'
$$BTYPES	ends
$$BNAMES	segment byte public use32 'DEBNAM'
$$BNAMES	ends
$$BROWSE	segment byte public use32 'DEBSYM'
$$BROWSE	ends
$$BROWFILE	segment byte public use32 'DEBSYM'
$$BROWFILE	ends
DGROUP	group	_BSS,_DATA
_TEXT	segment dword public use32 'CODE'
_BytCopy	proc	near
?live1@0:
	?debug L 20
	push      ebp
	mov       ebp,esp
	add       esp,-12
	?debug L 24
@1:
	mov       eax,dword ptr [ebp+8]
	mov       dword ptr [ebp-8],eax
	?debug L 25
	push      dword ptr [ebp+12]
	call      _NewMem
	pop       ecx
	mov       dword ptr [ebp-4],eax
	?debug L 26
	xor       edx,edx
	mov       dword ptr [ebp-12],edx
	mov       ecx,dword ptr [ebp-12]
	cmp       ecx,dword ptr [ebp+12]
	jge       short @3
	?debug L 27
@2:
	mov       eax,dword ptr [ebp-8]
	mov       edx,dword ptr [ebp-12]
	mov       cl,byte ptr [eax+edx]
	mov       eax,dword ptr [ebp-12]
	mov       edx,dword ptr [ebp-4]
	mov       byte ptr [edx+eax],cl
	inc       dword ptr [ebp-12]
	mov       ecx,dword ptr [ebp-12]
	cmp       ecx,dword ptr [ebp+12]
	jl        short @2
	?debug L 28
@3:
	mov       eax,dword ptr [ebp-4]
	?debug L 29
@6:
@5:
	mov       esp,ebp
	pop       ebp
	ret 
	?debug L 0
_BytCopy	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	db	2
	db	0
	db	0
	db	0
	dw	55
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch1
	dd	?patch2
	dd	?patch3
	df	_BytCopy
	dw	0
	dw	4096
	dw	0
	dw	1
	dw	0
	dw	0
	dw	0
	db	8
	db	95
	db	66
	db	121
	db	116
	db	67
	db	111
	db	112
	db	121
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1027
	dw	0
	dw	2
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	18
	dw	0
	dw	3
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65524
	dw	65535
	dw	18
	dw	0
	dw	4
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65528
	dw	65535
	dw	1056
	dw	0
	dw	5
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	1056
	dw	0
	dw	6
	dw	0
	dw	0
	dw	0
?patch1	equ	@6-_BytCopy+4
?patch2	equ	0
?patch3	equ	@6-_BytCopy
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_BytToBStrCopy	proc	near
?live1@112:
	?debug L 31
	push      ebp
	mov       ebp,esp
	push      ecx
	?debug L 37
@7:
	mov       eax,dword ptr [ebp+12]
	add       eax,4
	push      eax
	call      _NewMem
	pop       ecx
	mov       dword ptr [ebp-4],eax
	?debug L 38
	push      4
	lea       edx,dword ptr [ebp+12]
	push      edx
	push      dword ptr [ebp-4]
	call      _memcpy
	add       esp,12
	?debug L 39
	push      dword ptr [ebp+12]
	push      dword ptr [ebp+8]
	mov       ecx,dword ptr [ebp-4]
	add       ecx,4
	push      ecx
	call      _memcpy
	add       esp,12
	?debug L 40
	mov       eax,dword ptr [ebp-4]
	?debug L 41
@9:
@8:
	pop       ecx
	pop       ebp
	ret 
	?debug L 0
_BytToBStrCopy	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	61
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch4
	dd	?patch5
	dd	?patch6
	df	_BytToBStrCopy
	dw	0
	dw	4098
	dw	0
	dw	7
	dw	0
	dw	0
	dw	0
	db	14
	db	95
	db	66
	db	121
	db	116
	db	84
	db	111
	db	66
	db	83
	db	116
	db	114
	db	67
	db	111
	db	112
	db	121
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1027
	dw	0
	dw	8
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	18
	dw	0
	dw	9
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	1056
	dw	0
	dw	10
	dw	0
	dw	0
	dw	0
?patch4	equ	@9-_BytToBStrCopy+3
?patch5	equ	0
?patch6	equ	@9-_BytToBStrCopy
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_BytToHStrCopy	proc	near
?live1@208:
	?debug L 43
	push      ebp
	mov       ebp,esp
	add       esp,-16
	?debug L 48
@10:
	mov       eax,dword ptr [ebp+12]
	add       eax,eax
	mov       dword ptr [ebp-8],eax
	?debug L 49
	mov       edx,dword ptr [ebp-8]
	inc       edx
	push      edx
	call      _NewMem
	pop       ecx
	mov       dword ptr [ebp-4],eax
	?debug L 50
	xor       ecx,ecx
	mov       dword ptr [ebp-16],ecx
	mov       dword ptr [ebp-12],ecx
	mov       eax,dword ptr [ebp-12]
	cmp       eax,dword ptr [ebp+12]
	jge       short @12
	?debug L 51
@11:
	mov       edx,dword ptr [ebp+8]
	mov       eax,dword ptr [ebp-12]
	movzx     edx,byte ptr [edx+eax]
	push      edx
	push      offset s@
	mov       ecx,dword ptr [ebp-4]
	add       ecx,dword ptr [ebp-16]
	push      ecx
	call      _sprintf
	add       esp,12
	inc       dword ptr [ebp-12]
	add       dword ptr [ebp-16],2
	mov       eax,dword ptr [ebp-12]
	cmp       eax,dword ptr [ebp+12]
	jl        short @11
	?debug L 52
@12:
	mov       edx,dword ptr [ebp-4]
	mov       ecx,dword ptr [ebp-8]
	mov       byte ptr [edx+ecx],0
	?debug L 53
	mov       eax,dword ptr [ebp-4]
	?debug L 54
@15:
@14:
	mov       esp,ebp
	pop       ebp
	ret 
	?debug L 0
_BytToHStrCopy	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	61
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch7
	dd	?patch8
	dd	?patch9
	df	_BytToHStrCopy
	dw	0
	dw	4100
	dw	0
	dw	11
	dw	0
	dw	0
	dw	0
	db	14
	db	95
	db	66
	db	121
	db	116
	db	84
	db	111
	db	72
	db	83
	db	116
	db	114
	db	67
	db	111
	db	112
	db	121
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1027
	dw	0
	dw	12
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	18
	dw	0
	dw	13
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65520
	dw	65535
	dw	18
	dw	0
	dw	14
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65524
	dw	65535
	dw	18
	dw	0
	dw	15
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65528
	dw	65535
	dw	18
	dw	0
	dw	16
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	1040
	dw	0
	dw	17
	dw	0
	dw	0
	dw	0
?patch7	equ	@15-_BytToHStrCopy+4
?patch8	equ	0
?patch9	equ	@15-_BytToHStrCopy
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_BStrToHStrCopy	proc	near
?live1@336:
	?debug L 56
	push      ebp
	mov       ebp,esp
	add       esp,-20
	?debug L 62
@16:
	push      4
	push      dword ptr [ebp+8]
	lea       eax,dword ptr [ebp-8]
	push      eax
	call      _memcpy
	add       esp,12
	?debug L 63
	mov       edx,dword ptr [ebp-8]
	add       edx,edx
	mov       dword ptr [ebp-12],edx
	?debug L 64
	mov       ecx,dword ptr [ebp-12]
	inc       ecx
	push      ecx
	call      _NewMem
	pop       ecx
	mov       dword ptr [ebp-4],eax
	?debug L 65
	mov       eax,dword ptr [ebp-8]
	add       eax,4
	mov       dword ptr [ebp-8],eax
	?debug L 66
	mov       dword ptr [ebp-16],4
	xor       edx,edx
	mov       dword ptr [ebp-20],edx
	mov       ecx,dword ptr [ebp-16]
	cmp       ecx,dword ptr [ebp-8]
	jge       short @18
	?debug L 67
@17:
	mov       eax,dword ptr [ebp+8]
	mov       edx,dword ptr [ebp-16]
	xor       ecx,ecx
	mov       cl,byte ptr [eax+edx]
	push      ecx
	push      offset s@+5
	mov       eax,dword ptr [ebp-4]
	add       eax,dword ptr [ebp-20]
	push      eax
	call      _sprintf
	add       esp,12
	inc       dword ptr [ebp-16]
	add       dword ptr [ebp-20],2
	mov       edx,dword ptr [ebp-16]
	cmp       edx,dword ptr [ebp-8]
	jl        short @17
	?debug L 68
@18:
	mov       ecx,dword ptr [ebp-4]
	mov       eax,dword ptr [ebp-12]
	mov       byte ptr [ecx+eax],0
	?debug L 69
	mov       eax,dword ptr [ebp-4]
	?debug L 70
@21:
@20:
	mov       esp,ebp
	pop       ebp
	ret 
	?debug L 0
_BStrToHStrCopy	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	62
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch10
	dd	?patch11
	dd	?patch12
	df	_BStrToHStrCopy
	dw	0
	dw	4102
	dw	0
	dw	18
	dw	0
	dw	0
	dw	0
	db	15
	db	95
	db	66
	db	83
	db	116
	db	114
	db	84
	db	111
	db	72
	db	83
	db	116
	db	114
	db	67
	db	111
	db	112
	db	121
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1056
	dw	0
	dw	19
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65516
	dw	65535
	dw	18
	dw	0
	dw	20
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65520
	dw	65535
	dw	18
	dw	0
	dw	21
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65524
	dw	65535
	dw	18
	dw	0
	dw	22
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65528
	dw	65535
	dw	18
	dw	0
	dw	23
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	1040
	dw	0
	dw	24
	dw	0
	dw	0
	dw	0
?patch10	equ	@21-_BStrToHStrCopy+4
?patch11	equ	0
?patch12	equ	@21-_BStrToHStrCopy
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_IsSpaceStr	proc	near
?live1@496:
	?debug L 72
	push      ebp
	mov       ebp,esp
	?debug L 77
@22:
	cmp       dword ptr [ebp+8],0
	je        short @24
	mov       eax,dword ptr [ebp+8]
	cmp       byte ptr [eax],0
	jne       short @27
@24:
	mov       eax,1
@30:
	pop       ebp
	ret 
	?debug L 80
@26:
@27:
	mov       edx,dword ptr [ebp+8]
	inc       dword ptr [ebp+8]
	movsx     ecx,byte ptr [edx]
	test      byte ptr [__chartype+2+2*ecx],8
	jne       short @26
	?debug L 82
	mov       eax,dword ptr [ebp+8]
	cmp       byte ptr [eax],0
	sete      al
	and       eax,1
	?debug L 84
@29:
@25:
	pop       ebp
	ret 
	?debug L 0
_IsSpaceStr	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	58
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch13
	dd	?patch14
	dd	?patch15
	df	_IsSpaceStr
	dw	0
	dw	4104
	dw	0
	dw	25
	dw	0
	dw	0
	dw	0
	db	11
	db	95
	db	73
	db	115
	db	83
	db	112
	db	97
	db	99
	db	101
	db	83
	db	116
	db	114
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1040
	dw	0
	dw	26
	dw	0
	dw	0
	dw	0
	dw	8
	dw	530
	dd	@30-_IsSpaceStr
	dw	2
?patch13	equ	@29-_IsSpaceStr+2
?patch14	equ	0
?patch15	equ	@29-_IsSpaceStr
	dw	2
	dw	6
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_WCStrLen	proc	near
?live1@576:
	?debug L 86
	push      ebp
	mov       ebp,esp
	add       esp,-8
	?debug L 90
@31:
	xor       eax,eax
	mov       dword ptr [ebp-4],eax
	xor       edx,edx
	mov       dword ptr [ebp-8],edx
	jmp       short @33
	?debug L 93
@32:
	inc       dword ptr [ebp-4]
	inc       dword ptr [ebp-8]
	?debug L 91
@33:
	mov       ecx,dword ptr [ebp+8]
	mov       eax,dword ptr [ebp-8]
	cmp       word ptr [ecx+2*eax],0
	jne       short @32
	?debug L 95
	mov       eax,dword ptr [ebp-4]
	?debug L 96
@35:
@34:
	pop       ecx
	pop       ecx
	pop       ebp
	ret 
	?debug L 0
_WCStrLen	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	56
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch16
	dd	?patch17
	dd	?patch18
	df	_WCStrLen
	dw	0
	dw	4106
	dw	0
	dw	27
	dw	0
	dw	0
	dw	0
	db	9
	db	95
	db	87
	db	67
	db	83
	db	116
	db	114
	db	76
	db	101
	db	110
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1057
	dw	0
	dw	28
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65528
	dw	65535
	dw	117
	dw	0
	dw	29
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	117
	dw	0
	dw	30
	dw	0
	dw	0
	dw	0
?patch16	equ	@35-_WCStrLen+4
?patch17	equ	0
?patch18	equ	@35-_WCStrLen
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_SubWCStrCopy	proc	near
?live1@672:
	?debug L 98
	push      ebp
	mov       ebp,esp
	push      ecx
	?debug L 103
@36:
	mov       eax,dword ptr [ebp+12]
	inc       eax
	add       eax,eax
	push      eax
	push      dword ptr [ebp+8]
	call      _BytCopy
	add       esp,8
	mov       dword ptr [ebp-4],eax
	?debug L 104
	mov       edx,dword ptr [ebp+12]
	mov       ecx,dword ptr [ebp-4]
	mov       word ptr [ecx+2*edx],0
	?debug L 105
	mov       eax,dword ptr [ebp-4]
	?debug L 106
@38:
@37:
	pop       ecx
	pop       ebp
	ret 
	?debug L 0
_SubWCStrCopy	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	60
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch19
	dd	?patch20
	dd	?patch21
	df	_SubWCStrCopy
	dw	0
	dw	4108
	dw	0
	dw	31
	dw	0
	dw	0
	dw	0
	db	13
	db	95
	db	83
	db	117
	db	98
	db	87
	db	67
	db	83
	db	116
	db	114
	db	67
	db	111
	db	112
	db	121
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1057
	dw	0
	dw	32
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	18
	dw	0
	dw	33
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	1057
	dw	0
	dw	34
	dw	0
	dw	0
	dw	0
?patch19	equ	@38-_SubWCStrCopy+3
?patch20	equ	0
?patch21	equ	@38-_SubWCStrCopy
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_WCStrCopy	proc	near
?live1@752:
	?debug L 108
	push      ebp
	mov       ebp,esp
	?debug L 111
@39:
	push      dword ptr [ebp+8]
	call      _WCStrLen
	pop       ecx
	push      eax
	push      dword ptr [ebp+8]
	call      _SubWCStrCopy
	add       esp,8
	?debug L 112
@41:
@40:
	pop       ebp
	ret 
	?debug L 0
_WCStrCopy	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	57
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch22
	dd	?patch23
	dd	?patch24
	df	_WCStrCopy
	dw	0
	dw	4110
	dw	0
	dw	35
	dw	0
	dw	0
	dw	0
	db	10
	db	95
	db	87
	db	67
	db	83
	db	116
	db	114
	db	67
	db	111
	db	112
	db	121
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1057
	dw	0
	dw	36
	dw	0
	dw	0
	dw	0
?patch22	equ	@41-_WCStrCopy+2
?patch23	equ	0
?patch24	equ	@41-_WCStrCopy
	dw	2
	dw	6
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_WCToStrCopy	proc	near
?live1@800:
	?debug L 114
	push      ebp
	mov       ebp,esp
	add       esp,-12
	?debug L 118
@42:
	push      dword ptr [ebp+8]
	call      _WCStrLen
	pop       ecx
	mov       dword ptr [ebp-4],eax
	?debug L 119
	mov       eax,dword ptr [ebp-4]
	inc       eax
	push      eax
	call      _NewMem
	pop       ecx
	mov       dword ptr [ebp-12],eax
	?debug L 120
	xor       edx,edx
	mov       dword ptr [ebp-8],edx
	mov       ecx,dword ptr [ebp-8]
	cmp       ecx,dword ptr [ebp-4]
	jae       short @44
	?debug L 121
@43:
	mov       eax,dword ptr [ebp+8]
	mov       edx,dword ptr [ebp-8]
	mov       cl,byte ptr [eax+2*edx]
	mov       eax,dword ptr [ebp-8]
	mov       edx,dword ptr [ebp-12]
	mov       byte ptr [edx+eax],cl
	inc       dword ptr [ebp-8]
	mov       ecx,dword ptr [ebp-8]
	cmp       ecx,dword ptr [ebp-4]
	jb        short @43
	?debug L 122
@44:
	mov       eax,dword ptr [ebp-8]
	mov       edx,dword ptr [ebp-12]
	mov       byte ptr [edx+eax],0
	?debug L 123
	mov       eax,dword ptr [ebp-12]
	?debug L 124
@47:
@46:
	mov       esp,ebp
	pop       ebp
	ret 
	?debug L 0
_WCToStrCopy	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	59
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch25
	dd	?patch26
	dd	?patch27
	df	_WCToStrCopy
	dw	0
	dw	4112
	dw	0
	dw	37
	dw	0
	dw	0
	dw	0
	db	12
	db	95
	db	87
	db	67
	db	84
	db	111
	db	83
	db	116
	db	114
	db	67
	db	111
	db	112
	db	121
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1057
	dw	0
	dw	38
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65524
	dw	65535
	dw	1040
	dw	0
	dw	39
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65528
	dw	65535
	dw	117
	dw	0
	dw	40
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	117
	dw	0
	dw	41
	dw	0
	dw	0
	dw	0
?patch25	equ	@47-_WCToStrCopy+4
?patch26	equ	0
?patch27	equ	@47-_WCToStrCopy
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_WCStrToLower	proc	near
?live1@928:
	?debug L 126
	push      ebp
	mov       ebp,esp
	push      ecx
	?debug L 132
@48:
	mov       eax,dword ptr [ebp+8]
	mov       dword ptr [ebp-4],eax
	jmp       short @50
@49:
	mov       edx,dword ptr [ebp-4]
	xor       ecx,ecx
	mov       cl,byte ptr [edx]
	mov       eax,dword ptr [ebp-4]
	cmp       cx,word ptr [eax]
	jne       short @51
	mov       edx,dword ptr [ebp-4]
	movzx     ecx,word ptr [edx]
	test      byte ptr [__chartype+2+2*ecx],1
	je        short @51
	mov       eax,dword ptr [ebp-4]
	movzx     edx,word ptr [eax]
	push      edx
	call      _tolower
	pop       ecx
	mov       ecx,dword ptr [ebp-4]
	mov       word ptr [ecx],ax
@51:
	add       dword ptr [ebp-4],2
@50:
	mov       eax,dword ptr [ebp-4]
	cmp       word ptr [eax],0
	jne       short @49
	?debug L 134
	mov       eax,dword ptr [ebp+8]
	?debug L 135
@54:
@53:
	pop       ecx
	pop       ebp
	ret 
	?debug L 0
_WCStrToLower	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	60
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch28
	dd	?patch29
	dd	?patch30
	df	_WCStrToLower
	dw	0
	dw	4114
	dw	0
	dw	42
	dw	0
	dw	0
	dw	0
	db	13
	db	95
	db	87
	db	67
	db	83
	db	116
	db	114
	db	84
	db	111
	db	76
	db	111
	db	119
	db	101
	db	114
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1057
	dw	0
	dw	43
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	1057
	dw	0
	dw	44
	dw	0
	dw	0
	dw	0
?patch28	equ	@54-_WCStrToLower+3
?patch29	equ	0
?patch30	equ	@54-_WCStrToLower
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_WCStrToUpper	proc	near
?live1@992:
	?debug L 137
	push      ebp
	mov       ebp,esp
	push      ecx
	?debug L 143
@55:
	mov       eax,dword ptr [ebp+8]
	mov       dword ptr [ebp-4],eax
	jmp       short @57
@56:
	mov       edx,dword ptr [ebp-4]
	xor       ecx,ecx
	mov       cl,byte ptr [edx]
	mov       eax,dword ptr [ebp-4]
	cmp       cx,word ptr [eax]
	jne       short @58
	mov       edx,dword ptr [ebp-4]
	movzx     ecx,word ptr [edx]
	test      byte ptr [__chartype+2+2*ecx],2
	je        short @58
	mov       eax,dword ptr [ebp-4]
	movzx     edx,word ptr [eax]
	push      edx
	call      _toupper
	pop       ecx
	mov       ecx,dword ptr [ebp-4]
	mov       word ptr [ecx],ax
@58:
	add       dword ptr [ebp-4],2
@57:
	mov       eax,dword ptr [ebp-4]
	cmp       word ptr [eax],0
	jne       short @56
	?debug L 145
	mov       eax,dword ptr [ebp+8]
	?debug L 146
@61:
@60:
	pop       ecx
	pop       ebp
	ret 
	?debug L 0
_WCStrToUpper	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	60
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch31
	dd	?patch32
	dd	?patch33
	df	_WCStrToUpper
	dw	0
	dw	4116
	dw	0
	dw	45
	dw	0
	dw	0
	dw	0
	db	13
	db	95
	db	87
	db	67
	db	83
	db	116
	db	114
	db	84
	db	111
	db	85
	db	112
	db	112
	db	101
	db	114
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1057
	dw	0
	dw	46
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	1057
	dw	0
	dw	47
	dw	0
	dw	0
	dw	0
?patch31	equ	@61-_WCStrToUpper+3
?patch32	equ	0
?patch33	equ	@61-_WCStrToUpper
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_SubStrCopy	proc	near
?live1@1056:
	?debug L 148
	push      ebp
	mov       ebp,esp
	push      ecx
	?debug L 153
@62:
	mov       eax,dword ptr [ebp+12]
	inc       eax
	push      eax
	push      dword ptr [ebp+8]
	call      _BytCopy
	add       esp,8
	mov       dword ptr [ebp-4],eax
	?debug L 154
	mov       edx,dword ptr [ebp+12]
	mov       ecx,dword ptr [ebp-4]
	mov       byte ptr [ecx+edx],0
	?debug L 155
	mov       eax,dword ptr [ebp-4]
	?debug L 156
@64:
@63:
	pop       ecx
	pop       ebp
	ret 
	?debug L 0
_SubStrCopy	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	58
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch34
	dd	?patch35
	dd	?patch36
	df	_SubStrCopy
	dw	0
	dw	4118
	dw	0
	dw	48
	dw	0
	dw	0
	dw	0
	db	11
	db	95
	db	83
	db	117
	db	98
	db	83
	db	116
	db	114
	db	67
	db	111
	db	112
	db	121
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1040
	dw	0
	dw	49
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	18
	dw	0
	dw	50
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	1040
	dw	0
	dw	51
	dw	0
	dw	0
	dw	0
?patch34	equ	@64-_SubStrCopy+3
?patch35	equ	0
?patch36	equ	@64-_SubStrCopy
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_StrCopy	proc	near
?live1@1136:
	?debug L 158
	push      ebp
	mov       ebp,esp
	?debug L 161
@65:
	push      dword ptr [ebp+8]
	call      _strlen
	pop       ecx
	push      eax
	push      dword ptr [ebp+8]
	call      _SubStrCopy
	add       esp,8
	?debug L 162
@67:
@66:
	pop       ebp
	ret 
	?debug L 0
_StrCopy	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	55
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch37
	dd	?patch38
	dd	?patch39
	df	_StrCopy
	dw	0
	dw	4120
	dw	0
	dw	52
	dw	0
	dw	0
	dw	0
	db	8
	db	95
	db	83
	db	116
	db	114
	db	67
	db	111
	db	112
	db	121
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1040
	dw	0
	dw	53
	dw	0
	dw	0
	dw	0
?patch37	equ	@67-_StrCopy+2
?patch38	equ	0
?patch39	equ	@67-_StrCopy
	dw	2
	dw	6
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_StrToLower	proc	near
?live1@1184:
	?debug L 164
	push      ebp
	mov       ebp,esp
	push      ecx
	?debug L 167
@68:
	mov       eax,dword ptr [ebp+8]
	mov       dword ptr [ebp-4],eax
	jmp       short @70
@69:
	mov       edx,dword ptr [ebp-4]
	movsx     ecx,byte ptr [edx]
	test      byte ptr [__chartype+2+2*ecx],1
	je        short @71
	mov       eax,dword ptr [ebp-4]
	movsx     edx,byte ptr [eax]
	push      edx
	call      _tolower
	pop       ecx
	mov       ecx,dword ptr [ebp-4]
	mov       byte ptr [ecx],al
@71:
	inc       dword ptr [ebp-4]
@70:
	mov       eax,dword ptr [ebp-4]
	cmp       byte ptr [eax],0
	jne       short @69
	?debug L 168
	mov       eax,dword ptr [ebp+8]
	?debug L 169
@74:
@73:
	pop       ecx
	pop       ebp
	ret 
	?debug L 0
_StrToLower	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	58
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch40
	dd	?patch41
	dd	?patch42
	df	_StrToLower
	dw	0
	dw	4122
	dw	0
	dw	54
	dw	0
	dw	0
	dw	0
	db	11
	db	95
	db	83
	db	116
	db	114
	db	84
	db	111
	db	76
	db	111
	db	119
	db	101
	db	114
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1040
	dw	0
	dw	55
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	1040
	dw	0
	dw	56
	dw	0
	dw	0
	dw	0
?patch40	equ	@74-_StrToLower+3
?patch41	equ	0
?patch42	equ	@74-_StrToLower
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_StrToUpper	proc	near
?live1@1248:
	?debug L 171
	push      ebp
	mov       ebp,esp
	push      ecx
	?debug L 174
@75:
	mov       eax,dword ptr [ebp+8]
	mov       dword ptr [ebp-4],eax
	jmp       short @77
@76:
	mov       edx,dword ptr [ebp-4]
	movsx     ecx,byte ptr [edx]
	test      byte ptr [__chartype+2+2*ecx],2
	je        short @78
	mov       eax,dword ptr [ebp-4]
	movsx     edx,byte ptr [eax]
	push      edx
	call      _toupper
	pop       ecx
	mov       ecx,dword ptr [ebp-4]
	mov       byte ptr [ecx],al
@78:
	inc       dword ptr [ebp-4]
@77:
	mov       eax,dword ptr [ebp-4]
	cmp       byte ptr [eax],0
	jne       short @76
	?debug L 175
	mov       eax,dword ptr [ebp+8]
	?debug L 176
@81:
@80:
	pop       ecx
	pop       ebp
	ret 
	?debug L 0
_StrToUpper	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	58
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch43
	dd	?patch44
	dd	?patch45
	df	_StrToUpper
	dw	0
	dw	4124
	dw	0
	dw	57
	dw	0
	dw	0
	dw	0
	db	11
	db	95
	db	83
	db	116
	db	114
	db	84
	db	111
	db	85
	db	112
	db	112
	db	101
	db	114
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1040
	dw	0
	dw	58
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	1040
	dw	0
	dw	59
	dw	0
	dw	0
	dw	0
?patch43	equ	@81-_StrToUpper+3
?patch44	equ	0
?patch45	equ	@81-_StrToUpper
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_GetArgLst	proc	near
?live1@1312:
	?debug L 181
	push      ebp
	mov       ebp,esp
	add       esp,-12
	?debug L 185
@82:
	add       dword ptr [ebp+8],4
	mov       eax,dword ptr [ebp+8]
	mov       edx,dword ptr [eax-4]
	mov       dword ptr [ebp-8],edx
	?debug L 186
	mov       ecx,dword ptr [ebp-8]
	inc       ecx
	shl       ecx,2
	push      ecx
	call      _NewMem
	pop       ecx
	mov       dword ptr [ebp-4],eax
	?debug L 187
	mov       eax,dword ptr [ebp-8]
	mov       edx,dword ptr [ebp-4]
	mov       dword ptr [edx],eax
	?debug L 188
	xor       ecx,ecx
	mov       dword ptr [ebp-12],ecx
	mov       eax,dword ptr [ebp-12]
	cmp       eax,dword ptr [ebp-8]
	jge       short @84
@83:
	add       dword ptr [ebp+8],4
	mov       edx,dword ptr [ebp+8]
	mov       ecx,dword ptr [edx-4]
	mov       eax,dword ptr [ebp-12]
	mov       edx,dword ptr [ebp-4]
	mov       dword ptr [edx+4*eax+4],ecx
	inc       dword ptr [ebp-12]
	mov       ecx,dword ptr [ebp-12]
	cmp       ecx,dword ptr [ebp-8]
	jl        short @83
	?debug L 189
@84:
	mov       eax,dword ptr [ebp-4]
	?debug L 190
@87:
@86:
	mov       esp,ebp
	pop       ebp
	ret 
	?debug L 0
_GetArgLst	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	57
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch46
	dd	?patch47
	dd	?patch48
	df	_GetArgLst
	dw	0
	dw	4126
	dw	0
	dw	60
	dw	0
	dw	0
	dw	0
	db	10
	db	95
	db	71
	db	101
	db	116
	db	65
	db	114
	db	103
	db	76
	db	115
	db	116
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1027
	dw	0
	dw	61
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65524
	dw	65535
	dw	116
	dw	0
	dw	62
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65528
	dw	65535
	dw	116
	dw	0
	dw	63
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	4127
	dw	0
	dw	64
	dw	0
	dw	0
	dw	0
?patch46	equ	@87-_GetArgLst+4
?patch47	equ	0
?patch48	equ	@87-_GetArgLst
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_strstr_aux	proc	near
?live1@1424:
	?debug L 194
	push      ebp
	mov       ebp,esp
	add       esp,-12
	?debug L 196
@88:
	xor       eax,eax
	mov       dword ptr [ebp-4],eax
	mov       edx,dword ptr [ebp+8]
	mov       dword ptr [ebp-8],edx
	?debug L 197
	cmp       dword ptr [ebp+8],0
	jne       short @89
	cmp       dword ptr [ebp+12],0
	je        short @90
	?debug L 198
@89:
@91:
	push      dword ptr [ebp+12]
	call      _strlen
	pop       ecx
	mov       dword ptr [ebp-12],eax
	jmp       short @93
	?debug L 201
@92:
	push      dword ptr [ebp-12]
	push      dword ptr [ebp+12]
	push      dword ptr [ebp-8]
	call      _strncmp
	add       esp,12
	test      eax,eax
	jne       short @94
	?debug L 203
	mov       ecx,dword ptr [ebp-8]
	mov       dword ptr [ebp-4],ecx
	jmp       short @95
	?debug L 205
@94:
	inc       dword ptr [ebp-8]
	?debug L 199
@93:
	mov       eax,dword ptr [ebp-8]
	cmp       byte ptr [eax],0
	jne       short @92
	?debug L 208
@95:
@97:
@90:
	mov       eax,dword ptr [ebp-4]
	?debug L 209
@99:
@98:
	mov       esp,ebp
	pop       ebp
	ret 
	?debug L 0
_strstr_aux	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	58
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch49
	dd	?patch50
	dd	?patch51
	df	_strstr_aux
	dw	0
	dw	4129
	dw	0
	dw	65
	dw	0
	dw	0
	dw	0
	db	11
	db	95
	db	115
	db	116
	db	114
	db	115
	db	116
	db	114
	db	95
	db	97
	db	117
	db	120
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1040
	dw	0
	dw	66
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	1040
	dw	0
	dw	67
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65528
	dw	65535
	dw	1040
	dw	0
	dw	68
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	1040
	dw	0
	dw	69
	dw	0
	dw	0
	dw	0
	dw	24
	dw	519
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch52
	df	@91
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65524
	dw	65535
	dw	116
	dw	0
	dw	70
	dw	0
	dw	0
	dw	0
?patch52	equ	@97-@91
	dw	2
	dw	6
?patch49	equ	@99-_strstr_aux+4
?patch50	equ	0
?patch51	equ	@99-_strstr_aux
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_strchr_aux	proc	near
?live1@1584:
	?debug L 211
	push      ebp
	mov       ebp,esp
	add       esp,-8
	?debug L 213
@100:
	xor       eax,eax
	mov       dword ptr [ebp-4],eax
	mov       edx,dword ptr [ebp+8]
	mov       dword ptr [ebp-8],edx
	?debug L 214
	cmp       dword ptr [ebp+8],0
	je        short @102
	jmp       short @104
	?debug L 218
@103:
	mov       ecx,dword ptr [ebp-8]
	movsx     eax,byte ptr [ecx]
	cmp       eax,dword ptr [ebp+12]
	jne       short @105
	?debug L 220
	mov       edx,dword ptr [ebp-8]
	mov       dword ptr [ebp-4],edx
	jmp       short @106
	?debug L 222
@105:
	inc       dword ptr [ebp-8]
	?debug L 216
@104:
	mov       ecx,dword ptr [ebp-8]
	cmp       byte ptr [ecx],0
	jne       short @103
	?debug L 225
@106:
@102:
	mov       eax,dword ptr [ebp-4]
	?debug L 226
@109:
@108:
	pop       ecx
	pop       ecx
	pop       ebp
	ret 
	?debug L 0
_strchr_aux	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	58
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch53
	dd	?patch54
	dd	?patch55
	df	_strchr_aux
	dw	0
	dw	4131
	dw	0
	dw	71
	dw	0
	dw	0
	dw	0
	db	11
	db	95
	db	115
	db	116
	db	114
	db	99
	db	104
	db	114
	db	95
	db	97
	db	117
	db	120
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1040
	dw	0
	dw	72
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	116
	dw	0
	dw	73
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65528
	dw	65535
	dw	1040
	dw	0
	dw	74
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	1040
	dw	0
	dw	75
	dw	0
	dw	0
	dw	0
?patch53	equ	@109-_strchr_aux+4
?patch54	equ	0
?patch55	equ	@109-_strchr_aux
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_strrchr_aux	proc	near
?live1@1728:
	?debug L 228
	push      ebp
	mov       ebp,esp
	add       esp,-12
	?debug L 230
@110:
	xor       eax,eax
	mov       dword ptr [ebp-4],eax
	?debug L 231
	cmp       dword ptr [ebp+8],0
	je        short @112
	?debug L 232
@113:
	push      dword ptr [ebp+8]
	call      _strlen
	pop       ecx
	mov       dword ptr [ebp-12],eax
	?debug L 233
	mov       edx,dword ptr [ebp+8]
	add       edx,dword ptr [ebp-12]
	mov       dword ptr [ebp-8],edx
	?debug L 234
	cmp       dword ptr [ebp-12],0
	jl        short @115
	?debug L 236
@114:
	mov       ecx,dword ptr [ebp-8]
	movsx     eax,byte ptr [ecx]
	cmp       eax,dword ptr [ebp+12]
	jne       short @116
	?debug L 238
	mov       edx,dword ptr [ebp-8]
	mov       dword ptr [ebp-4],edx
	jmp       short @117
	?debug L 242
@116:
	dec       dword ptr [ebp-8]
	dec       dword ptr [ebp-12]
	?debug L 234
	cmp       dword ptr [ebp-12],0
	jge       short @114
	?debug L 246
@115:
@117:
@119:
@112:
	mov       eax,dword ptr [ebp-4]
	?debug L 247
@121:
@120:
	mov       esp,ebp
	pop       ebp
	ret 
	?debug L 0
_strrchr_aux	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	59
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch56
	dd	?patch57
	dd	?patch58
	df	_strrchr_aux
	dw	0
	dw	4133
	dw	0
	dw	76
	dw	0
	dw	0
	dw	0
	db	12
	db	95
	db	115
	db	116
	db	114
	db	114
	db	99
	db	104
	db	114
	db	95
	db	97
	db	117
	db	120
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1040
	dw	0
	dw	77
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	116
	dw	0
	dw	78
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65528
	dw	65535
	dw	1040
	dw	0
	dw	79
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	1040
	dw	0
	dw	80
	dw	0
	dw	0
	dw	0
	dw	24
	dw	519
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch59
	df	@113
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65524
	dw	65535
	dw	116
	dw	0
	dw	81
	dw	0
	dw	0
	dw	0
?patch59	equ	@119-@113
	dw	2
	dw	6
?patch56	equ	@121-_strrchr_aux+4
?patch57	equ	0
?patch58	equ	@121-_strrchr_aux
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_strcspn_aux	proc	near
?live1@1920:
	?debug L 249
	push      ebp
	mov       ebp,esp
	add       esp,-16
	?debug L 251
@122:
	xor       eax,eax
	mov       dword ptr [ebp-4],eax
	?debug L 252
	mov       edx,dword ptr [ebp+8]
	mov       dword ptr [ebp-16],edx
	?debug L 253
	cmp       dword ptr [ebp+8],0
	je        short @123
	cmp       dword ptr [ebp+12],0
	je        short @123
	?debug L 255
	push      dword ptr [ebp+12]
	call      _strlen
	pop       ecx
	mov       dword ptr [ebp-8],eax
	jmp       short @125
	?debug L 258
@124:
	xor       ecx,ecx
	mov       dword ptr [ebp-12],ecx
	mov       eax,dword ptr [ebp-12]
	cmp       eax,dword ptr [ebp-8]
	jge       short @127
	?debug L 259
@126:
	mov       edx,dword ptr [ebp+12]
	mov       ecx,dword ptr [ebp-12]
	mov       al,byte ptr [edx+ecx]
	mov       edx,dword ptr [ebp-16]
	cmp       al,byte ptr [edx]
	jne       short @128
	mov       eax,dword ptr [ebp-4]
	jmp       short @129
@128:
	inc       dword ptr [ebp-12]
	mov       edx,dword ptr [ebp-12]
	cmp       edx,dword ptr [ebp-8]
	jl        short @126
	?debug L 260
@127:
	inc       dword ptr [ebp-4]
	inc       dword ptr [ebp-16]
	?debug L 256
@125:
	mov       ecx,dword ptr [ebp-16]
	cmp       byte ptr [ecx],0
	jne       short @124
	?debug L 263
@123:
	mov       eax,dword ptr [ebp-4]
	?debug L 264
@131:
@129:
	mov       esp,ebp
	pop       ebp
	ret 
	?debug L 0
_strcspn_aux	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	59
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch60
	dd	?patch61
	dd	?patch62
	df	_strcspn_aux
	dw	0
	dw	4135
	dw	0
	dw	82
	dw	0
	dw	0
	dw	0
	db	12
	db	95
	db	115
	db	116
	db	114
	db	99
	db	115
	db	112
	db	110
	db	95
	db	97
	db	117
	db	120
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1040
	dw	0
	dw	83
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	1040
	dw	0
	dw	84
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65520
	dw	65535
	dw	1040
	dw	0
	dw	85
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65524
	dw	65535
	dw	116
	dw	0
	dw	86
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65528
	dw	65535
	dw	116
	dw	0
	dw	87
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	116
	dw	0
	dw	88
	dw	0
	dw	0
	dw	0
?patch60	equ	@131-_strcspn_aux+4
?patch61	equ	0
?patch62	equ	@131-_strcspn_aux
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_memcpy_aux	proc	near
?live1@2096:
	?debug L 266
	push      ebp
	mov       ebp,esp
	push      ecx
	?debug L 269
@132:
	cmp       dword ptr [ebp+8],0
	je        short @133
	cmp       dword ptr [ebp+12],0
	je        short @133
	cmp       dword ptr [ebp+16],0
	jl        short @133
	?debug L 271
@134:
	xor       eax,eax
	mov       dword ptr [ebp-4],eax
	mov       edx,dword ptr [ebp-4]
	cmp       edx,dword ptr [ebp+16]
	jge       short @136
@135:
	mov       ecx,dword ptr [ebp+12]
	mov       eax,dword ptr [ebp-4]
	mov       dl,byte ptr [ecx+eax]
	mov       ecx,dword ptr [ebp-4]
	mov       eax,dword ptr [ebp+8]
	mov       byte ptr [eax+ecx],dl
	inc       dword ptr [ebp-4]
	mov       edx,dword ptr [ebp-4]
	cmp       edx,dword ptr [ebp+16]
	jl        short @135
	?debug L 273
@136:
@138:
@133:
	mov       eax,dword ptr [ebp+8]
	?debug L 274
@140:
@139:
	pop       ecx
	pop       ebp
	ret 
	?debug L 0
_memcpy_aux	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	58
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch63
	dd	?patch64
	dd	?patch65
	df	_memcpy_aux
	dw	0
	dw	4137
	dw	0
	dw	89
	dw	0
	dw	0
	dw	0
	db	11
	db	95
	db	109
	db	101
	db	109
	db	99
	db	112
	db	121
	db	95
	db	97
	db	117
	db	120
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1027
	dw	0
	dw	90
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	1027
	dw	0
	dw	91
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	16
	dw	0
	dw	116
	dw	0
	dw	92
	dw	0
	dw	0
	dw	0
	dw	24
	dw	519
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch66
	df	@134
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	116
	dw	0
	dw	93
	dw	0
	dw	0
	dw	0
?patch66	equ	@138-@134
	dw	2
	dw	6
?patch63	equ	@140-_memcpy_aux+3
?patch64	equ	0
?patch65	equ	@140-_memcpy_aux
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_memcmp_aux	proc	near
?live1@2176:
	?debug L 276
	push      ebp
	mov       ebp,esp
	push      ecx
	?debug L 279
@141:
	cmp       dword ptr [ebp+8],0
	je        short @142
	cmp       dword ptr [ebp+12],0
	je        short @142
	cmp       dword ptr [ebp+16],0
	jl        short @142
	?debug L 281
@143:
	xor       eax,eax
	mov       dword ptr [ebp-4],eax
	mov       edx,dword ptr [ebp-4]
	cmp       edx,dword ptr [ebp+16]
	jge       short @145
	?debug L 282
@144:
	mov       ecx,dword ptr [ebp+12]
	mov       eax,dword ptr [ebp-4]
	mov       dl,byte ptr [ecx+eax]
	mov       ecx,dword ptr [ebp-4]
	mov       eax,dword ptr [ebp+8]
	cmp       dl,byte ptr [eax+ecx]
	jbe       short @146
	?debug L 283
	or        eax,-1
@154:
	pop       ecx
	pop       ebp
	ret 
	?debug L 285
@146:
	mov       edx,dword ptr [ebp+12]
	mov       ecx,dword ptr [ebp-4]
	mov       al,byte ptr [edx+ecx]
	mov       edx,dword ptr [ebp-4]
	mov       ecx,dword ptr [ebp+8]
	cmp       al,byte ptr [ecx+edx]
	jae       short @148
	?debug L 286
	mov       eax,1
@155:
	pop       ecx
	pop       ebp
	ret 
@148:
	inc       dword ptr [ebp-4]
	mov       edx,dword ptr [ebp-4]
	cmp       edx,dword ptr [ebp+16]
	jl        short @144
	?debug L 287
@145:
	xor       eax,eax
@156:
	pop       ecx
	pop       ebp
	ret 
	?debug L 288
@151:
@157:
	pop       ecx
	pop       ebp
	ret 
	?debug L 289
@142:
	mov       eax,dword ptr [ebp+8]
	sub       eax,dword ptr [ebp+12]
	?debug L 290
@152:
@153:
@147:
	pop       ecx
	pop       ebp
	ret 
	?debug L 0
_memcmp_aux	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	58
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch67
	dd	?patch68
	dd	?patch69
	df	_memcmp_aux
	dw	0
	dw	4139
	dw	0
	dw	94
	dw	0
	dw	0
	dw	0
	db	11
	db	95
	db	109
	db	101
	db	109
	db	99
	db	109
	db	112
	db	95
	db	97
	db	117
	db	120
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1027
	dw	0
	dw	95
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	1027
	dw	0
	dw	96
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	16
	dw	0
	dw	116
	dw	0
	dw	97
	dw	0
	dw	0
	dw	0
	dw	24
	dw	519
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch70
	df	@143
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	116
	dw	0
	dw	98
	dw	0
	dw	0
	dw	0
?patch70	equ	@151-@143
	dw	2
	dw	6
	dw	8
	dw	530
	dd	@157-_memcmp_aux
	dw	3
	dw	8
	dw	530
	dd	@156-_memcmp_aux
	dw	3
	dw	8
	dw	530
	dd	@155-_memcmp_aux
	dw	3
	dw	8
	dw	530
	dd	@154-_memcmp_aux
	dw	3
?patch67	equ	@153-_memcmp_aux+3
?patch68	equ	0
?patch69	equ	@153-_memcmp_aux
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_getcwd_aux	proc	near
?live1@2352:
	?debug L 292
	push      ebp
	mov       ebp,esp
	push      ecx
	?debug L 294
@158:
	push      offset s@+10
	call      _getenv
	pop       ecx
	mov       dword ptr [ebp-4],eax
	?debug L 295
	cmp       dword ptr [ebp-4],0
	je        short @159
	push      dword ptr [ebp-4]
	call      _strlen
	pop       ecx
	cmp       eax,dword ptr [ebp+12]
	jae       short @159
	?debug L 297
	push      dword ptr [ebp-4]
	push      dword ptr [ebp+8]
	call      _strcpy
	add       esp,8
	mov       eax,dword ptr [ebp+8]
@163:
	pop       ecx
	pop       ebp
	ret 
	?debug L 299
@159:
	xor       eax,eax
	?debug L 300
@162:
@160:
	pop       ecx
	pop       ebp
	ret 
	?debug L 0
_getcwd_aux	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	58
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch71
	dd	?patch72
	dd	?patch73
	df	_getcwd_aux
	dw	0
	dw	4141
	dw	0
	dw	99
	dw	0
	dw	0
	dw	0
	db	11
	db	95
	db	103
	db	101
	db	116
	db	99
	db	119
	db	100
	db	95
	db	97
	db	117
	db	120
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1040
	dw	0
	dw	100
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	116
	dw	0
	dw	101
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	1040
	dw	0
	dw	102
	dw	0
	dw	0
	dw	0
	dw	8
	dw	530
	dd	@163-_getcwd_aux
	dw	3
?patch71	equ	@162-_getcwd_aux+3
?patch72	equ	0
?patch73	equ	@162-_getcwd_aux
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_GetSystemError	proc	near
?live1@2448:
	?debug L 306
	push      ebp
	mov       ebp,esp
	add       esp,-12
	?debug L 309
@164:
	xor       eax,eax
	mov       dword ptr [ebp-8],eax
	?debug L 311
	push      0
	push      0
	lea       edx,dword ptr [ebp-8]
	push      edx
	push      1024
	call      GetLastError
	push      eax
	push      0
	push      4352
	call      FormatMessageA
	mov       dword ptr [ebp-4],eax
	?debug L 321
	cmp       dword ptr [ebp-4],0
	jne       short @165
	push      offset s@+14
	call      _StrCopy
	pop       ecx
	mov       dword ptr [ebp-12],eax
	jmp       short @166
	?debug L 322
@165:
	push      dword ptr [ebp-8]
	call      _StrCopy
	pop       ecx
	mov       dword ptr [ebp-12],eax
	?debug L 323
@166:
	cmp       dword ptr [ebp-8],0
	je        short @167
	push      dword ptr [ebp-8]
	call      LocalFree
	?debug L 324
@167:
	mov       eax,dword ptr [ebp-12]
	?debug L 325
@169:
@168:
	mov       esp,ebp
	pop       ebp
	ret 
	?debug L 0
_GetSystemError	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	62
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch74
	dd	?patch75
	dd	?patch76
	df	_GetSystemError
	dw	0
	dw	4143
	dw	0
	dw	103
	dw	0
	dw	0
	dw	0
	db	15
	db	95
	db	71
	db	101
	db	116
	db	83
	db	121
	db	115
	db	116
	db	101
	db	109
	db	69
	db	114
	db	114
	db	111
	db	114
	dw	18
	dw	512
	dw	65524
	dw	65535
	dw	1040
	dw	0
	dw	104
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65528
	dw	65535
	dw	1027
	dw	0
	dw	105
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	18
	dw	0
	dw	106
	dw	0
	dw	0
	dw	0
?patch74	equ	@169-_GetSystemError+4
?patch75	equ	0
?patch76	equ	@169-_GetSystemError
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_GetSystemError_noalloc	proc	near
?live1@2576:
	?debug L 327
	push      ebp
	mov       ebp,esp
	push      ecx
	?debug L 330
@170:
	cmp       dword ptr [ebp+8],0
	je        short @171
	?debug L 332
	push      0
	push      dword ptr [ebp+12]
	push      dword ptr [ebp+8]
	push      1024
	call      GetLastError
	push      eax
	push      0
	push      4096
	call      FormatMessageA
	mov       dword ptr [ebp-4],eax
	?debug L 342
	cmp       dword ptr [ebp-4],0
	jne       short @172
	mov       eax,dword ptr [ebp+8]
	mov       byte ptr [eax],0
	?debug L 344
@172:
@171:
	mov       eax,dword ptr [ebp+8]
	?debug L 345
@174:
@173:
	pop       ecx
	pop       ebp
	ret 
	?debug L 0
_GetSystemError_noalloc	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	70
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch77
	dd	?patch78
	dd	?patch79
	df	_GetSystemError_noalloc
	dw	0
	dw	4145
	dw	0
	dw	107
	dw	0
	dw	0
	dw	0
	db	23
	db	95
	db	71
	db	101
	db	116
	db	83
	db	121
	db	115
	db	116
	db	101
	db	109
	db	69
	db	114
	db	114
	db	111
	db	114
	db	95
	db	110
	db	111
	db	97
	db	108
	db	108
	db	111
	db	99
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1040
	dw	0
	dw	108
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	116
	dw	0
	dw	109
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	18
	dw	0
	dw	110
	dw	0
	dw	0
	dw	0
?patch77	equ	@174-_GetSystemError_noalloc+3
?patch78	equ	0
?patch79	equ	@174-_GetSystemError_noalloc
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_runprg	proc	near
?live1@2672:
	?debug L 374
	push      ebp
	mov       ebp,esp
	add       esp,-92
	?debug L 378
@175:
	xor       eax,eax
	mov       dword ptr [ebp-4],eax
	?debug L 379
	lea       edx,dword ptr [ebp-76]
	push      edx
	call      GetStartupInfoA
	?debug L 380
	lea       ecx,dword ptr [ebp-92]
	push      ecx
	lea       eax,dword ptr [ebp-76]
	push      eax
	push      0
	push      0
	push      512
	push      0
	push      0
	push      0
	push      dword ptr [ebp+8]
	push      0
	call      CreateProcessA
	test      eax,eax
	jne       short @176
	?debug L 386
	call      GetLastError
	mov       dword ptr [ebp-4],eax
	jmp       short @177
	?debug L 388
@176:
	cmp       dword ptr [ebp+12],2
	jne       short @178
	?debug L 390
	push      -1
	push      dword ptr [ebp-92]
	call      WaitForSingleObject
	mov       dword ptr [ebp-8],eax
	?debug L 391
	cmp       dword ptr [ebp-8],-1
	jne       short @179
	?debug L 392
	call      GetLastError
	mov       dword ptr [ebp-4],eax
	jmp       short @177
	?debug L 394
@179:
	lea       edx,dword ptr [ebp-4]
	push      edx
	push      dword ptr [ebp-92]
	call      GetExitCodeProcess
	test      eax,eax
	jne       short @177
	?debug L 395
	call      GetLastError
	mov       dword ptr [ebp-4],eax
	?debug L 396
	jmp       short @177
	?debug L 398
@178:
	cmp       dword ptr [ebp+12],1
	jne       short @181
	?debug L 400
	push      -1
	push      dword ptr [ebp-92]
	call      WaitForInputIdle
	test      eax,eax
	je        short @182
	?debug L 401
	call      GetLastError
	mov       dword ptr [ebp-4],eax
	?debug L 403
@182:
@181:
@177:
	mov       eax,dword ptr [ebp-4]
	?debug L 404
@184:
@183:
	mov       esp,ebp
	pop       ebp
	ret 
	?debug L 0
_runprg	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	54
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch80
	dd	?patch81
	dd	?patch82
	df	_runprg
	dw	0
	dw	4147
	dw	0
	dw	111
	dw	0
	dw	0
	dw	0
	db	7
	db	95
	db	114
	db	117
	db	110
	db	112
	db	114
	db	103
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1040
	dw	0
	dw	112
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	116
	dw	0
	dw	113
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65528
	dw	65535
	dw	18
	dw	0
	dw	138
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	18
	dw	0
	dw	139
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65444
	dw	65535
	dw	4149
	dw	0
	dw	140
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65460
	dw	65535
	dw	4151
	dw	0
	dw	141
	dw	0
	dw	0
	dw	0
?patch80	equ	@184-_runprg+4
?patch81	equ	0
?patch82	equ	@184-_runprg
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_apply_fun_portable	proc	near
?live1@2944:
	?debug L 457
	push      ebp
	mov       ebp,esp
	?debug L 463
@185:
	mov       eax,dword ptr [ebp+12]
	cmp       eax,9
	ja        @186
	jmp       dword ptr [@198+4*eax]
@198:
	dd        @197
	dd        @196
	dd        @195
	dd        @194
	dd        @193
	dd        @192
	dd        @191
	dd        @190
	dd        @189
	dd        @188
	?debug L 465
@197:
	call      dword ptr [ebp+8]
@202:
	pop       ebp
	ret 
	?debug L 466
@196:
	mov       edx,dword ptr [ebp+16]
	push      dword ptr [edx]
	call      dword ptr [ebp+8]
	pop       ecx
@203:
	pop       ebp
	ret 
	?debug L 467
@195:
	mov       ecx,dword ptr [ebp+16]
	push      dword ptr [ecx+4]
	mov       eax,dword ptr [ebp+16]
	push      dword ptr [eax]
	call      dword ptr [ebp+8]
	add       esp,8
@204:
	pop       ebp
	ret 
	?debug L 468
@194:
	mov       edx,dword ptr [ebp+16]
	push      dword ptr [edx+8]
	mov       ecx,dword ptr [ebp+16]
	push      dword ptr [ecx+4]
	mov       eax,dword ptr [ebp+16]
	push      dword ptr [eax]
	call      dword ptr [ebp+8]
	add       esp,12
@205:
	pop       ebp
	ret 
	?debug L 469
@193:
	mov       edx,dword ptr [ebp+16]
	push      dword ptr [edx+12]
	mov       ecx,dword ptr [ebp+16]
	push      dword ptr [ecx+8]
	mov       eax,dword ptr [ebp+16]
	push      dword ptr [eax+4]
	mov       edx,dword ptr [ebp+16]
	push      dword ptr [edx]
	call      dword ptr [ebp+8]
	add       esp,16
@206:
	pop       ebp
	ret 
	?debug L 470
@192:
	mov       ecx,dword ptr [ebp+16]
	push      dword ptr [ecx+16]
	mov       eax,dword ptr [ebp+16]
	push      dword ptr [eax+12]
	mov       edx,dword ptr [ebp+16]
	push      dword ptr [edx+8]
	mov       ecx,dword ptr [ebp+16]
	push      dword ptr [ecx+4]
	mov       eax,dword ptr [ebp+16]
	push      dword ptr [eax]
	call      dword ptr [ebp+8]
	add       esp,20
@207:
	pop       ebp
	ret 
	?debug L 471
@191:
	mov       edx,dword ptr [ebp+16]
	push      dword ptr [edx+20]
	mov       ecx,dword ptr [ebp+16]
	push      dword ptr [ecx+16]
	mov       eax,dword ptr [ebp+16]
	push      dword ptr [eax+12]
	mov       edx,dword ptr [ebp+16]
	push      dword ptr [edx+8]
	mov       ecx,dword ptr [ebp+16]
	push      dword ptr [ecx+4]
	mov       eax,dword ptr [ebp+16]
	push      dword ptr [eax]
	call      dword ptr [ebp+8]
	add       esp,24
@208:
	pop       ebp
	ret 
	?debug L 472
@190:
	mov       edx,dword ptr [ebp+16]
	push      dword ptr [edx+24]
	mov       ecx,dword ptr [ebp+16]
	push      dword ptr [ecx+20]
	mov       eax,dword ptr [ebp+16]
	push      dword ptr [eax+16]
	mov       edx,dword ptr [ebp+16]
	push      dword ptr [edx+12]
	mov       ecx,dword ptr [ebp+16]
	push      dword ptr [ecx+8]
	mov       eax,dword ptr [ebp+16]
	push      dword ptr [eax+4]
	mov       edx,dword ptr [ebp+16]
	push      dword ptr [edx]
	call      dword ptr [ebp+8]
	add       esp,28
@209:
	pop       ebp
	ret 
	?debug L 473
@189:
	mov       ecx,dword ptr [ebp+16]
	push      dword ptr [ecx+28]
	mov       eax,dword ptr [ebp+16]
	push      dword ptr [eax+24]
	mov       edx,dword ptr [ebp+16]
	push      dword ptr [edx+20]
	mov       ecx,dword ptr [ebp+16]
	push      dword ptr [ecx+16]
	mov       eax,dword ptr [ebp+16]
	push      dword ptr [eax+12]
	mov       edx,dword ptr [ebp+16]
	push      dword ptr [edx+8]
	mov       ecx,dword ptr [ebp+16]
	push      dword ptr [ecx+4]
	mov       eax,dword ptr [ebp+16]
	push      dword ptr [eax]
	call      dword ptr [ebp+8]
	add       esp,32
@210:
	pop       ebp
	ret 
	?debug L 474
@188:
	mov       edx,dword ptr [ebp+16]
	push      dword ptr [edx+32]
	mov       ecx,dword ptr [ebp+16]
	push      dword ptr [ecx+28]
	mov       eax,dword ptr [ebp+16]
	push      dword ptr [eax+24]
	mov       edx,dword ptr [ebp+16]
	push      dword ptr [edx+20]
	mov       ecx,dword ptr [ebp+16]
	push      dword ptr [ecx+16]
	mov       eax,dword ptr [ebp+16]
	push      dword ptr [eax+12]
	mov       edx,dword ptr [ebp+16]
	push      dword ptr [edx+8]
	mov       ecx,dword ptr [ebp+16]
	push      dword ptr [ecx+4]
	mov       eax,dword ptr [ebp+16]
	push      dword ptr [eax]
	call      dword ptr [ebp+8]
	add       esp,36
@211:
	pop       ebp
	ret 
	?debug L 476
@186:
	push      offset s@+84
	push      0
	push      476
	push      offset s@+30
	push      offset s@+15
	call      __AssCheck
	add       esp,12
	call      eax
	add       esp,8
	xor       eax,eax
	?debug L 478
@201:
@199:
	pop       ebp
	ret 
	?debug L 0
_apply_fun_portable	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	66
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch83
	dd	?patch84
	dd	?patch85
	df	_apply_fun_portable
	dw	0
	dw	4153
	dw	0
	dw	142
	dw	0
	dw	0
	dw	0
	db	19
	db	95
	db	97
	db	112
	db	112
	db	108
	db	121
	db	95
	db	102
	db	117
	db	110
	db	95
	db	112
	db	111
	db	114
	db	116
	db	97
	db	98
	db	108
	db	101
	dw	18
	dw	512
	dw	8
	dw	0
	dw	4154
	dw	0
	dw	143
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	116
	dw	0
	dw	144
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	16
	dw	0
	dw	4127
	dw	0
	dw	145
	dw	0
	dw	0
	dw	0
	dw	8
	dw	530
	dd	@211-_apply_fun_portable
	dw	2
	dw	8
	dw	530
	dd	@210-_apply_fun_portable
	dw	2
	dw	8
	dw	530
	dd	@209-_apply_fun_portable
	dw	2
	dw	8
	dw	530
	dd	@208-_apply_fun_portable
	dw	2
	dw	8
	dw	530
	dd	@207-_apply_fun_portable
	dw	2
	dw	8
	dw	530
	dd	@206-_apply_fun_portable
	dw	2
	dw	8
	dw	530
	dd	@205-_apply_fun_portable
	dw	2
	dw	8
	dw	530
	dd	@204-_apply_fun_portable
	dw	2
	dw	8
	dw	530
	dd	@203-_apply_fun_portable
	dw	2
	dw	8
	dw	530
	dd	@202-_apply_fun_portable
	dw	2
?patch83	equ	@201-_apply_fun_portable+2
?patch84	equ	0
?patch85	equ	@201-_apply_fun_portable
	dw	2
	dw	6
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_apply_fun	proc	near
?live1@3168:
	?debug L 490
	push      ebp
	mov       ebp,esp
	add       esp,-8
	push      ebx
	?debug L 496
@212:
	mov       eax,dword ptr [ebp+12]
	dec       eax
	mov       dword ptr [ebp-4],eax
	cmp       dword ptr [ebp-4],0
	jl        short @214
	?debug L 498
@213:
	mov       edx,dword ptr [ebp-4]
	mov       ecx,dword ptr [ebp+16]
	mov       eax,dword ptr [ecx+4*edx]
	mov       dword ptr [ebp-8],eax
	?debug L 500
 	mov	 eax, dword ptr [ebp-8]
	?debug L 501
 	push	 eax
@215:
	dec       dword ptr [ebp-4]
	cmp       dword ptr [ebp-4],0
	jge       short @213
	?debug L 506
@214:
 	call	 dword ptr [ebp+8]
	?debug L 507
@216:
	pop       ebx
	pop       ecx
	pop       ecx
	pop       ebp
	ret 
	?debug L 0
_apply_fun	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	57
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch86
	dd	?patch87
	dd	?patch88
	df	_apply_fun
	dw	0
	dw	4158
	dw	0
	dw	146
	dw	0
	dw	0
	dw	0
	db	10
	db	95
	db	97
	db	112
	db	112
	db	108
	db	121
	db	95
	db	102
	db	117
	db	110
	dw	18
	dw	512
	dw	8
	dw	0
	dw	4154
	dw	0
	dw	147
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	116
	dw	0
	dw	148
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	16
	dw	0
	dw	4127
	dw	0
	dw	149
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65528
	dw	65535
	dw	1027
	dw	0
	dw	150
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	116
	dw	0
	dw	151
	dw	0
	dw	0
	dw	0
?patch86	equ	@216-_apply_fun+5
?patch87	equ	0
?patch88	equ	@216-_apply_fun
	dw	2
	dw	6
	dw	8
	dw	531
	dw	1
	dw	65524
	dw	65535
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_DL_open	proc	near
?live1@3280:
	?debug L 555
	push      ebp
	mov       ebp,esp
	push      ecx
	?debug L 556
@217:
	push      dword ptr [ebp+8]
	call      LoadLibraryA
	mov       dword ptr [ebp-4],eax
	?debug L 557
	mov       eax,dword ptr [ebp-4]
	?debug L 558
@219:
@218:
	pop       ecx
	pop       ebp
	ret 
	?debug L 0
_DL_open	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	55
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch89
	dd	?patch90
	dd	?patch91
	df	_DL_open
	dw	0
	dw	4160
	dw	0
	dw	152
	dw	0
	dw	0
	dw	0
	db	8
	db	95
	db	68
	db	76
	db	95
	db	111
	db	112
	db	101
	db	110
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1040
	dw	0
	dw	153
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	116
	dw	0
	dw	154
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	4162
	dw	0
	dw	157
	dw	0
	dw	0
	dw	0
?patch89	equ	@219-_DL_open+3
?patch90	equ	0
?patch91	equ	@219-_DL_open
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_DL_close	proc	near
?live1@3344:
	?debug L 560
	push      ebp
	mov       ebp,esp
	?debug L 562
@220:
	push      dword ptr [ebp+8]
	call      FreeLibrary
	dec       eax
	jne       short @221
	xor       eax,eax
@225:
	pop       ebp
	ret 
	?debug L 563
@221:
	mov       eax,1
	?debug L 564
@224:
@222:
	pop       ebp
	ret 
	?debug L 0
_DL_close	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	56
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch92
	dd	?patch93
	dd	?patch94
	df	_DL_close
	dw	0
	dw	4165
	dw	0
	dw	158
	dw	0
	dw	0
	dw	0
	db	9
	db	95
	db	68
	db	76
	db	95
	db	99
	db	108
	db	111
	db	115
	db	101
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1027
	dw	0
	dw	159
	dw	0
	dw	0
	dw	0
	dw	8
	dw	530
	dd	@225-_DL_close
	dw	2
?patch92	equ	@224-_DL_close+2
?patch93	equ	0
?patch94	equ	@224-_DL_close
	dw	2
	dw	6
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_DL_symbol	proc	near
?live1@3408:
	?debug L 566
	push      ebp
	mov       ebp,esp
	push      ecx
	?debug L 568
@226:
	push      dword ptr [ebp+12]
	push      dword ptr [ebp+8]
	call      GetProcAddress
	mov       dword ptr [ebp-4],eax
	?debug L 569
	mov       eax,dword ptr [ebp-4]
	?debug L 570
@228:
@227:
	pop       ecx
	pop       ebp
	ret 
	?debug L 0
_DL_symbol	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	57
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch95
	dd	?patch96
	dd	?patch97
	df	_DL_symbol
	dw	0
	dw	4167
	dw	0
	dw	160
	dw	0
	dw	0
	dw	0
	db	10
	db	95
	db	68
	db	76
	db	95
	db	115
	db	121
	db	109
	db	98
	db	111
	db	108
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1027
	dw	0
	dw	161
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	1040
	dw	0
	dw	162
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	4169
	dw	0
	dw	163
	dw	0
	dw	0
	dw	0
?patch95	equ	@228-_DL_symbol+3
?patch96	equ	0
?patch97	equ	@228-_DL_symbol
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_DL_error	proc	near
?live1@3472:
	?debug L 572
	push      ebp
	mov       ebp,esp
	?debug L 574
@229:
	call      _GetSystemError
	?debug L 575
@231:
@230:
	pop       ebp
	ret 
	?debug L 0
_DL_error	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	56
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch98
	dd	?patch99
	dd	?patch100
	df	_DL_error
	dw	0
	dw	4172
	dw	0
	dw	164
	dw	0
	dw	0
	dw	0
	db	9
	db	95
	db	68
	db	76
	db	95
	db	101
	db	114
	db	114
	db	111
	db	114
?patch98	equ	@231-_DL_error+2
?patch99	equ	0
?patch100	equ	@231-_DL_error
	dw	2
	dw	6
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_DL_error_noalloc	proc	near
?live1@3520:
	?debug L 577
	push      ebp
	mov       ebp,esp
	?debug L 579
@232:
	push      dword ptr [ebp+12]
	push      dword ptr [ebp+8]
	call      _GetSystemError_noalloc
	add       esp,8
	?debug L 580
@234:
@233:
	pop       ebp
	ret 
	?debug L 0
_DL_error_noalloc	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	64
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch101
	dd	?patch102
	dd	?patch103
	df	_DL_error_noalloc
	dw	0
	dw	4174
	dw	0
	dw	165
	dw	0
	dw	0
	dw	0
	db	17
	db	95
	db	68
	db	76
	db	95
	db	101
	db	114
	db	114
	db	111
	db	114
	db	95
	db	110
	db	111
	db	97
	db	108
	db	108
	db	111
	db	99
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1040
	dw	0
	dw	166
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	116
	dw	0
	dw	167
	dw	0
	dw	0
	dw	0
?patch101	equ	@234-_DL_error_noalloc+2
?patch102	equ	0
?patch103	equ	@234-_DL_error_noalloc
	dw	2
	dw	6
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
_UserName	proc	near
?live1@3568:
	?debug L 673
	push      ebp
	mov       ebp,esp
	add       esp,-1004
	?debug L 675
@235:
	mov       dword ptr [ebp-4],999
	?debug L 676
	lea       eax,dword ptr [ebp-4]
	push      eax
	lea       edx,dword ptr [ebp-1004]
	push      edx
	call      GetUserNameA
	?debug L 677
	lea       ecx,dword ptr [ebp-1004]
	push      ecx
	call      _StrToLower
	pop       ecx
	push      eax
	call      _StrCopy
	pop       ecx
	?debug L 678
@237:
@236:
	mov       esp,ebp
	pop       ebp
	ret 
	?debug L 0
_UserName	endp
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	56
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch104
	dd	?patch105
	dd	?patch106
	df	_UserName
	dw	0
	dw	4176
	dw	0
	dw	168
	dw	0
	dw	0
	dw	0
	db	9
	db	95
	db	85
	db	115
	db	101
	db	114
	db	78
	db	97
	db	109
	db	101
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	18
	dw	0
	dw	169
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	64532
	dw	65535
	dw	4178
	dw	0
	dw	170
	dw	0
	dw	0
	dw	0
?patch104	equ	@237-_UserName+4
?patch105	equ	0
?patch106	equ	@237-_UserName
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_DATA	segment dword public use32 'DATA'
s@	label	byte
	;	s@+0:
	db	"%02x",0
	;	s@+5:
	db	"%02x",0
	;	s@+10:
	db	"PWD",0,0
	;	s@+15:
	db	"Internal error",0
	;	s@+30:
	db	"E:\usr\prj\Shacira\Extern\STYX\src\LIBBASE\Sysbase1.c",0,0
	align	4
_DATA	ends
_TEXT	segment dword public use32 'CODE'
_TEXT	ends
	?debug	C FB040E466F726D61744D6573736167654102000000
	?debug	C FB040C4765744C6173744572726F7202000000
	?debug	C FB04094C6F63616C4672656502000000
	?debug	C FB040F47657453746172747570496E666F4102000000
	?debug	C FB040E43726561746550726F636573734102000000
	?debug	C FB041357616974466F7253696E676C654F626A65637402000000
	?debug	C FB041247657445786974436F646550726F6365737302000000
	?debug	C FB041057616974466F72496E70757449646C6502000000
	?debug	C FB040C4C6F61644C6962726172794102000000
	?debug	C FB040B467265654C69627261727902000000
	?debug	C FB040E47657450726F634164647265737302000000
	?debug	C FB040C476574557365724E616D654102000000
	extrn	__chartype:word
	public	_BytCopy
	extrn	_NewMem:near
	public	_BytToBStrCopy
	extrn	_memcpy:near
	public	_BytToHStrCopy
	extrn	_sprintf:near
	public	_BStrToHStrCopy
	public	_IsSpaceStr
	public	_WCStrLen
	public	_SubWCStrCopy
	public	_WCStrCopy
	public	_WCToStrCopy
	public	_WCStrToLower
	extrn	_tolower:near
	public	_WCStrToUpper
	extrn	_toupper:near
	public	_SubStrCopy
	public	_StrCopy
	extrn	_strlen:near
	public	_StrToLower
	public	_StrToUpper
	public	_GetArgLst
	public	_strstr_aux
	extrn	_strncmp:near
	public	_strchr_aux
	public	_strrchr_aux
	public	_strcspn_aux
	public	_memcpy_aux
	public	_memcmp_aux
	public	_getcwd_aux
	extrn	_getenv:near
	extrn	_strcpy:near
	public	_GetSystemError
	extrn	FormatMessageA:near
	extrn	GetLastError:near
	extrn	LocalFree:near
	public	_GetSystemError_noalloc
	public	_runprg
	extrn	GetStartupInfoA:near
	extrn	CreateProcessA:near
	extrn	WaitForSingleObject:near
	extrn	GetExitCodeProcess:near
	extrn	WaitForInputIdle:near
	public	_apply_fun_portable
	extrn	__AssCheck:near
	public	_apply_fun
	public	_DL_open
	extrn	LoadLibraryA:near
	public	_DL_close
	extrn	FreeLibrary:near
	public	_DL_symbol
	extrn	GetProcAddress:near
	public	_DL_error
	public	_DL_error_noalloc
	public	_UserName
	extrn	GetUserNameA:near
	?debug	C 9F757569642E6C6962
	?debug	C 9F757569642E6C6962
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	16
	dw	4
	dw	117
	dw	0
	dw	0
	dw	175
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	116
	dw	0
	dw	0
	dw	176
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	33
	dw	0
	dw	0
	dw	177
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	33
	dw	0
	dw	0
	dw	178
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	33
	dw	0
	dw	0
	dw	179
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	18
	dw	0
	dw	0
	dw	180
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	181
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	18
	dw	0
	dw	0
	dw	182
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	18
	dw	0
	dw	0
	dw	183
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	17
	dw	0
	dw	0
	dw	184
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	17
	dw	0
	dw	0
	dw	185
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	17
	dw	0
	dw	0
	dw	186
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	17
	dw	0
	dw	0
	dw	187
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	116
	dw	0
	dw	0
	dw	188
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	116
	dw	0
	dw	0
	dw	189
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	18
	dw	0
	dw	0
	dw	190
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	16
	dw	0
	dw	0
	dw	191
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	16
	dw	0
	dw	0
	dw	192
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	32
	dw	0
	dw	0
	dw	193
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	16
	dw	0
	dw	0
	dw	194
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	116
	dw	0
	dw	0
	dw	195
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	34
	dw	0
	dw	0
	dw	196
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1058
	dw	0
	dw	0
	dw	197
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	33
	dw	0
	dw	0
	dw	198
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1057
	dw	0
	dw	0
	dw	199
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	32
	dw	0
	dw	0
	dw	200
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1056
	dw	0
	dw	0
	dw	201
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1040
	dw	0
	dw	0
	dw	202
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	34
	dw	0
	dw	0
	dw	203
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	116
	dw	0
	dw	0
	dw	204
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	32
	dw	0
	dw	0
	dw	205
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	33
	dw	0
	dw	0
	dw	206
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	64
	dw	0
	dw	0
	dw	207
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1056
	dw	0
	dw	0
	dw	208
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1056
	dw	0
	dw	0
	dw	209
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1057
	dw	0
	dw	0
	dw	210
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1057
	dw	0
	dw	0
	dw	211
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1058
	dw	0
	dw	0
	dw	212
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1058
	dw	0
	dw	0
	dw	213
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	214
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	4183
	dw	0
	dw	0
	dw	215
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	116
	dw	0
	dw	0
	dw	216
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	117
	dw	0
	dw	0
	dw	217
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	34
	dw	0
	dw	0
	dw	218
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	219
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	220
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	16
	dw	0
	dw	0
	dw	221
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	17
	dw	0
	dw	0
	dw	222
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	18
	dw	0
	dw	0
	dw	223
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	33
	dw	0
	dw	0
	dw	224
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1057
	dw	0
	dw	0
	dw	225
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1057
	dw	0
	dw	0
	dw	226
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1057
	dw	0
	dw	0
	dw	227
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1057
	dw	0
	dw	0
	dw	228
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1057
	dw	0
	dw	0
	dw	229
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1057
	dw	0
	dw	0
	dw	230
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1040
	dw	0
	dw	0
	dw	231
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1040
	dw	0
	dw	0
	dw	232
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1040
	dw	0
	dw	0
	dw	233
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	4187
	dw	0
	dw	0
	dw	234
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	4187
	dw	0
	dw	0
	dw	235
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1040
	dw	0
	dw	0
	dw	236
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1040
	dw	0
	dw	0
	dw	237
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1040
	dw	0
	dw	0
	dw	238
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	4187
	dw	0
	dw	0
	dw	239
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	4187
	dw	0
	dw	0
	dw	240
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	16
	dw	0
	dw	0
	dw	241
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1040
	dw	0
	dw	0
	dw	242
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	32
	dw	0
	dw	0
	dw	243
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1056
	dw	0
	dw	0
	dw	244
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1040
	dw	0
	dw	0
	dw	245
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1040
	dw	0
	dw	0
	dw	246
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1040
	dw	0
	dw	0
	dw	247
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1040
	dw	0
	dw	0
	dw	248
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	4187
	dw	0
	dw	0
	dw	249
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	250
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	4127
	dw	0
	dw	0
	dw	251
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	32
	dw	0
	dw	0
	dw	252
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	33
	dw	0
	dw	0
	dw	253
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	34
	dw	0
	dw	0
	dw	254
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	18
	dw	0
	dw	0
	dw	255
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	16
	dw	0
	dw	0
	dw	256
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	34
	dw	0
	dw	0
	dw	257
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1058
	dw	0
	dw	0
	dw	258
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	33
	dw	0
	dw	0
	dw	259
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	118
	dw	0
	dw	0
	dw	260
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	119
	dw	0
	dw	0
	dw	261
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	118
	dw	0
	dw	0
	dw	262
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	32
	dw	0
	dw	0
	dw	263
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1056
	dw	0
	dw	0
	dw	264
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	34
	dw	0
	dw	0
	dw	265
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1058
	dw	0
	dw	0
	dw	266
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	267
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	268
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	269
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	34
	dw	0
	dw	0
	dw	270
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1058
	dw	0
	dw	0
	dw	271
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	33
	dw	0
	dw	0
	dw	272
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1057
	dw	0
	dw	0
	dw	273
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	32
	dw	0
	dw	0
	dw	274
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1056
	dw	0
	dw	0
	dw	275
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	34
	dw	0
	dw	0
	dw	276
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1058
	dw	0
	dw	0
	dw	277
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	34
	dw	0
	dw	0
	dw	278
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	117
	dw	0
	dw	0
	dw	279
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	18
	dw	0
	dw	0
	dw	280
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	18
	dw	0
	dw	0
	dw	281
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	33
	dw	0
	dw	0
	dw	282
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	4127
	dw	0
	dw	0
	dw	283
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	4127
	dw	0
	dw	0
	dw	284
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	285
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	286
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	287
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	288
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	4169
	dw	0
	dw	0
	dw	289
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	290
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	4163
	dw	0
	dw	1
	dw	291
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	4162
	dw	0
	dw	0
	dw	292
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	4162
	dw	0
	dw	0
	dw	293
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	116
	dw	0
	dw	0
	dw	294
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	34
	dw	0
	dw	0
	dw	295
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1058
	dw	0
	dw	0
	dw	296
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	4213
	dw	0
	dw	1
	dw	297
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	4213
	dw	0
	dw	0
	dw	298
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	4212
	dw	0
	dw	0
	dw	299
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	4212
	dw	0
	dw	0
	dw	300
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	4149
	dw	0
	dw	1
	dw	301
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	4149
	dw	0
	dw	0
	dw	302
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	4215
	dw	0
	dw	0
	dw	303
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	4215
	dw	0
	dw	0
	dw	304
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	4151
	dw	0
	dw	1
	dw	305
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	4151
	dw	0
	dw	0
	dw	306
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	4209
	dw	0
	dw	0
	dw	307
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	4151
	dw	0
	dw	0
	dw	308
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	4209
	dw	0
	dw	0
	dw	309
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	310
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	18
	dw	0
	dw	0
	dw	311
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	18
	dw	0
	dw	0
	dw	312
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	18
	dw	0
	dw	0
	dw	313
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	18
	dw	0
	dw	0
	dw	314
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	32
	dw	0
	dw	0
	dw	315
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	33
	dw	0
	dw	0
	dw	316
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	317
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	3
	dw	0
	dw	0
	dw	318
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	3
	dw	0
	dw	0
	dw	319
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	3
	dw	0
	dw	0
	dw	320
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	321
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	322
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	323
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	324
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	4127
	dw	0
	dw	0
	dw	325
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	34
	dw	0
	dw	0
	dw	326
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	34
	dw	0
	dw	0
	dw	327
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	34
	dw	0
	dw	0
	dw	328
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	34
	dw	0
	dw	0
	dw	329
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	34
	dw	0
	dw	0
	dw	330
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	117
	dw	0
	dw	0
	dw	331
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	117
	dw	0
	dw	0
	dw	332
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1057
	dw	0
	dw	0
	dw	333
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1057
	dw	0
	dw	0
	dw	334
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	34
	dw	0
	dw	0
	dw	335
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1040
	dw	0
	dw	0
	dw	336
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	34
	dw	0
	dw	0
	dw	337
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	117
	dw	0
	dw	0
	dw	338
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	339
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	18
	dw	0
	dw	0
	dw	340
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	341
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	342
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	343
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	344
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	345
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	4127
	dw	0
	dw	0
	dw	346
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	347
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	348
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	33
	dw	0
	dw	0
	dw	349
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	33
	dw	0
	dw	0
	dw	350
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	32
	dw	0
	dw	0
	dw	351
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	33
	dw	0
	dw	0
	dw	352
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	117
	dw	0
	dw	0
	dw	353
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	34
	dw	0
	dw	0
	dw	354
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	117
	dw	0
	dw	0
	dw	355
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	34
	dw	0
	dw	0
	dw	356
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1058
	dw	0
	dw	0
	dw	357
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	34
	dw	0
	dw	0
	dw	358
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	117
	dw	0
	dw	0
	dw	359
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	117
	dw	0
	dw	0
	dw	360
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	34
	dw	0
	dw	0
	dw	361
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	34
	dw	0
	dw	0
	dw	362
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	34
	dw	0
	dw	0
	dw	363
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	364
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	365
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	366
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	367
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	368
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	32
	dw	0
	dw	0
	dw	369
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	32
	dw	0
	dw	0
	dw	370
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	371
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	34
	dw	0
	dw	0
	dw	372
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1056
	dw	0
	dw	0
	dw	373
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	34
	dw	0
	dw	0
	dw	374
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	375
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	376
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	33
	dw	0
	dw	0
	dw	377
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1057
	dw	0
	dw	0
	dw	378
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	65
	dw	0
	dw	0
	dw	379
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	119
	dw	0
	dw	0
	dw	380
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	18
	dw	0
	dw	0
	dw	381
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	382
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	33
	dw	0
	dw	0
	dw	383
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	384
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	65
	dw	0
	dw	0
	dw	385
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1057
	dw	0
	dw	0
	dw	386
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	17
	dw	0
	dw	0
	dw	387
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	33
	dw	0
	dw	0
	dw	388
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	34
	dw	0
	dw	0
	dw	389
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1057
	dw	0
	dw	0
	dw	390
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	34
	dw	0
	dw	0
	dw	391
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	392
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	18
	dw	0
	dw	0
	dw	393
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	18
	dw	0
	dw	0
	dw	394
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	34
	dw	0
	dw	0
	dw	395
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	396
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	4127
	dw	0
	dw	0
	dw	397
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	34
	dw	0
	dw	0
	dw	398
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	399
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	400
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	16
	dw	0
	dw	0
	dw	401
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	17
	dw	0
	dw	0
	dw	402
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	18
	dw	0
	dw	0
	dw	403
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	32
	dw	0
	dw	0
	dw	404
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	33
	dw	0
	dw	0
	dw	405
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	34
	dw	0
	dw	0
	dw	406
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	118
	dw	0
	dw	0
	dw	407
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	119
	dw	0
	dw	0
	dw	408
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	409
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	410
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	32
	dw	0
	dw	0
	dw	411
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	33
	dw	0
	dw	0
	dw	412
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	33
	dw	0
	dw	0
	dw	413
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1056
	dw	0
	dw	0
	dw	414
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1040
	dw	0
	dw	0
	dw	415
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	33
	dw	0
	dw	0
	dw	416
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	33
	dw	0
	dw	0
	dw	417
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1057
	dw	0
	dw	0
	dw	418
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	4224
	dw	0
	dw	0
	dw	419
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	4154
	dw	0
	dw	0
	dw	420
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	1027
	dw	0
	dw	0
	dw	421
	dw	0
	dw	0
	dw	0
	dw	?patch107
	dw	1
	db	2
	db	0
	db	8
	db	24
	db	6
	db	66
	db	67
	db	52
	db	46
	db	48
	db	48
?patch107	equ	13
$$BSYMS	ends
$$BTYPES	segment byte public use32 'DEBTYP'
	db        2,0,0,0,14,0,8,0,3,4,0,0,0,0,2,0
	db        1,16,0,0,12,0,1,2,2,0,3,4,0,0,18,0
	db        0,0,14,0,8,0,32,4,0,0,0,0,2,0,3,16
	db        0,0,12,0,1,2,2,0,3,4,0,0,18,0,0,0
	db        14,0,8,0,16,4,0,0,0,0,2,0,5,16,0,0
	db        12,0,1,2,2,0,3,4,0,0,18,0,0,0,14,0
	db        8,0,16,4,0,0,0,0,1,0,7,16,0,0,8,0
	db        1,2,1,0,32,4,0,0,14,0,8,0,116,0,0,0
	db        0,0,1,0,9,16,0,0,8,0,1,2,1,0,16,4
	db        0,0,14,0,8,0,117,0,0,0,0,0,1,0,11,16
	db        0,0,8,0,1,2,1,0,33,4,0,0,14,0,8,0
	db        33,4,0,0,0,0,2,0,13,16,0,0,12,0,1,2
	db        2,0,33,4,0,0,18,0,0,0,14,0,8,0,33,4
	db        0,0,0,0,1,0,15,16,0,0,8,0,1,2,1,0
	db        33,4,0,0,14,0,8,0,16,4,0,0,0,0,1,0
	db        17,16,0,0,8,0,1,2,1,0,33,4,0,0,14,0
	db        8,0,33,4,0,0,0,0,1,0,19,16,0,0,8,0
	db        1,2,1,0,33,4,0,0,14,0,8,0,33,4,0,0
	db        0,0,1,0,21,16,0,0,8,0,1,2,1,0,33,4
	db        0,0,14,0,8,0,16,4,0,0,0,0,2,0,23,16
	db        0,0,12,0,1,2,2,0,16,4,0,0,18,0,0,0
	db        14,0,8,0,16,4,0,0,0,0,1,0,25,16,0,0
	db        8,0,1,2,1,0,16,4,0,0,14,0,8,0,16,4
	db        0,0,0,0,1,0,27,16,0,0,8,0,1,2,1,0
	db        16,4,0,0,14,0,8,0,16,4,0,0,0,0,1,0
	db        29,16,0,0,8,0,1,2,1,0,16,4,0,0,14,0
	db        8,0,31,16,0,0,0,0,1,0,32,16,0,0,8,0
	db        2,0,10,0,3,4,0,0,8,0,1,2,1,0,3,4
	db        0,0,14,0,8,0,16,4,0,0,0,0,2,0,34,16
	db        0,0,12,0,1,2,2,0,16,4,0,0,16,4,0,0
	db        14,0,8,0,16,4,0,0,0,0,2,0,36,16,0,0
	db        12,0,1,2,2,0,16,4,0,0,116,0,0,0,14,0
	db        8,0,16,4,0,0,0,0,2,0,38,16,0,0,12,0
	db        1,2,2,0,16,4,0,0,116,0,0,0,14,0,8,0
	db        116,0,0,0,0,0,2,0,40,16,0,0,12,0,1,2
	db        2,0,16,4,0,0,16,4,0,0,14,0,8,0,3,4
	db        0,0,0,0,3,0,42,16,0,0,16,0,1,2,3,0
	db        3,4,0,0,3,4,0,0,116,0,0,0,14,0,8,0
	db        116,0,0,0,0,0,3,0,44,16,0,0,16,0,1,2
	db        3,0,3,4,0,0,3,4,0,0,116,0,0,0,14,0
	db        8,0,16,4,0,0,0,0,2,0,46,16,0,0,12,0
	db        1,2,2,0,16,4,0,0,116,0,0,0,14,0,8,0
	db        16,4,0,0,0,0,0,0,48,16,0,0,4,0,1,2
	db        0,0,14,0,8,0,16,4,0,0,0,0,2,0,50,16
	db        0,0,12,0,1,2,2,0,16,4,0,0,116,0,0,0
	db        14,0,8,0,116,0,0,0,0,0,2,0,52,16,0,0
	db        12,0,1,2,2,0,16,4,0,0,116,0,0,0,28,0
	db        5,0,4,0,54,16,0,0,0,0,0,0,0,0,0,0
	db        0,0,0,0,0,0,114,0,0,0,16,0,80,0,4,2
	db        6,4,3,4,0,0,0,0,115,0,0,0,0,0,0,0
	db        0,0,242,241,6,4,3,4,0,0,0,0,116,0,0,0
	db        0,0,0,0,4,0,242,241,6,4,34,0,0,0,0,0
	db        117,0,0,0,0,0,0,0,8,0,242,241,6,4,34,0
	db        0,0,0,0,118,0,0,0,0,0,0,0,12,0,28,0
	db        5,0,18,0,56,16,0,0,0,0,0,0,0,0,0,0
	db        0,0,0,0,0,0,119,0,0,0,68,0,104,1,4,2
	db        6,4,34,0,0,0,0,0,120,0,0,0,0,0,0,0
	db        0,0,242,241,6,4,16,4,0,0,0,0,121,0,0,0
	db        0,0,0,0,4,0,242,241,6,4,16,4,0,0,0,0
	db        122,0,0,0,0,0,0,0,8,0,242,241,6,4,16,4
	db        0,0,0,0,123,0,0,0,0,0,0,0,12,0,242,241
	db        6,4,34,0,0,0,0,0,124,0,0,0,0,0,0,0
	db        16,0,242,241,6,4,34,0,0,0,0,0,125,0,0,0
	db        0,0,0,0,20,0,242,241,6,4,34,0,0,0,0,0
	db        126,0,0,0,0,0,0,0,24,0,242,241,6,4,34,0
	db        0,0,0,0,127,0,0,0,0,0,0,0,28,0,242,241
	db        6,4,34,0,0,0,0,0,128,0,0,0,0,0,0,0
	db        32,0,242,241,6,4,34,0,0,0,0,0,129,0,0,0
	db        0,0,0,0,36,0,242,241,6,4,34,0,0,0,0,0
	db        130,0,0,0,0,0,0,0,40,0,242,241,6,4,34,0
	db        0,0,0,0,131,0,0,0,0,0,0,0,44,0,242,241
	db        6,4,33,0,0,0,0,0,132,0,0,0,0,0,0,0
	db        48,0,242,241,6,4,33,0,0,0,0,0,133,0,0,0
	db        0,0,0,0,50,0,242,241,6,4,32,4,0,0,0,0
	db        134,0,0,0,0,0,0,0,52,0,242,241,6,4,3,4
	db        0,0,0,0,135,0,0,0,0,0,0,0,56,0,242,241
	db        6,4,3,4,0,0,0,0,136,0,0,0,0,0,0,0
	db        60,0,242,241,6,4,3,4,0,0,0,0,137,0,0,0
	db        0,0,0,0,64,0,14,0,8,0,3,4,0,0,0,0
	db        3,0,61,16,0,0,8,0,2,0,10,0,59,16,0,0
	db        14,0,8,0,3,4,0,0,0,0,0,0,60,16,0,0
	db        4,0,1,2,0,0,16,0,1,2,3,0,58,16,0,0
	db        116,0,0,0,31,16,0,0,14,0,8,0,3,4,0,0
	db        0,0,3,0,63,16,0,0,16,0,1,2,3,0,58,16
	db        0,0,116,0,0,0,31,16,0,0,14,0,8,0,3,4
	db        0,0,0,0,2,0,65,16,0,0,12,0,1,2,2,0
	db        16,4,0,0,116,0,0,0,8,0,2,0,10,0,67,16
	db        0,0,28,0,5,0,1,0,68,16,0,0,0,0,0,0
	db        0,0,0,0,0,0,0,0,0,0,155,0,0,0,4,0
	db        20,0,4,2,6,4,116,0,0,0,0,0,156,0,0,0
	db        0,0,0,0,0,0,14,0,8,0,116,0,0,0,0,0
	db        1,0,70,16,0,0,8,0,1,2,1,0,3,4,0,0
	db        14,0,8,0,3,4,0,0,0,0,2,0,72,16,0,0
	db        12,0,1,2,2,0,3,4,0,0,16,4,0,0,8,0
	db        2,0,10,0,74,16,0,0,14,0,8,0,116,0,0,0
	db        7,0,0,0,75,16,0,0,4,0,1,2,0,0,14,0
	db        8,0,16,4,0,0,0,0,0,0,77,16,0,0,4,0
	db        1,2,0,0,14,0,8,0,16,4,0,0,0,0,2,0
	db        79,16,0,0,12,0,1,2,2,0,16,4,0,0,116,0
	db        0,0,14,0,8,0,16,4,0,0,0,0,0,0,81,16
	db        0,0,4,0,1,2,0,0,18,0,3,0,16,0,0,0
	db        17,0,0,0,0,0,0,0,232,3,232,3,18,0,3,0
	db        33,0,0,0,17,0,0,0,0,0,0,0,2,2,1,1
	db        14,0,8,0,3,4,0,0,0,0,1,0,85,16,0,0
	db        8,0,1,2,1,0,18,0,0,0,14,0,8,0,3,4
	db        0,0,0,0,3,0,89,16,0,0,8,0,2,0,10,0
	db        88,16,0,0,8,0,1,0,1,0,3,0,0,0,16,0
	db        1,2,3,0,3,4,0,0,87,16,0,0,117,0,0,0
	db        14,0,8,0,116,0,0,0,64,0,3,0,93,16,0,0
	db        8,0,2,0,10,0,92,16,0,0,8,0,1,0,1,0
	db        16,0,0,0,16,0,1,2,3,0,16,4,0,0,91,16
	db        0,0,0,0,0,0,14,0,8,0,116,0,0,0,0,0
	db        1,0,95,16,0,0,8,0,1,2,1,0,116,0,0,0
	db        14,0,8,0,116,0,0,0,0,0,1,0,97,16,0,0
	db        8,0,1,2,1,0,116,0,0,0,14,0,8,0,117,0
	db        0,0,0,0,1,0,99,16,0,0,8,0,1,2,1,0
	db        91,16,0,0,14,0,8,0,116,0,0,0,0,0,3,0
	db        101,16,0,0,16,0,1,2,3,0,91,16,0,0,91,16
	db        0,0,117,0,0,0,14,0,8,0,16,4,0,0,0,0
	db        1,0,103,16,0,0,8,0,1,2,1,0,91,16,0,0
	db        14,0,8,0,16,4,0,0,0,0,2,0,105,16,0,0
	db        12,0,1,2,2,0,16,4,0,0,91,16,0,0,14,0
	db        8,0,34,0,0,0,7,0,7,0,107,16,0,0,32,0
	db        1,2,7,0,34,0,0,0,87,16,0,0,34,0,0,0
	db        34,0,0,0,16,4,0,0,34,0,0,0,31,16,0,0
	db        14,0,8,0,34,0,0,0,7,0,0,0,109,16,0,0
	db        4,0,1,2,0,0,14,0,8,0,3,4,0,0,7,0
	db        1,0,111,16,0,0,8,0,1,2,1,0,3,4,0,0
	db        14,0,8,0,3,0,0,0,7,0,1,0,114,16,0,0
	db        8,0,2,0,10,0,55,16,0,0,8,0,1,2,1,0
	db        113,16,0,0,14,0,8,0,116,0,0,0,7,0,10,0
	db        120,16,0,0,8,0,2,0,10,0,117,16,0,0,28,0
	db        5,0,3,0,118,16,0,0,0,0,0,0,0,0,0,0
	db        0,0,0,0,0,0,171,0,0,0,12,0,60,0,4,2
	db        6,4,34,0,0,0,0,0,172,0,0,0,0,0,0,0
	db        0,0,242,241,6,4,3,4,0,0,0,0,173,0,0,0
	db        0,0,0,0,4,0,242,241,6,4,116,0,0,0,0,0
	db        174,0,0,0,0,0,0,0,8,0,8,0,2,0,10,0
	db        53,16,0,0,44,0,1,2,10,0,91,16,0,0,16,4
	db        0,0,116,16,0,0,116,16,0,0,116,0,0,0,34,0
	db        0,0,3,4,0,0,91,16,0,0,113,16,0,0,119,16
	db        0,0,14,0,8,0,34,0,0,0,7,0,2,0,122,16
	db        0,0,12,0,1,2,2,0,3,4,0,0,34,0,0,0
	db        14,0,8,0,116,0,0,0,7,0,2,0,124,16,0,0
	db        12,0,1,2,2,0,3,4,0,0,34,4,0,0,14,0
	db        8,0,34,0,0,0,7,0,2,0,126,16,0,0,12,0
	db        1,2,2,0,3,4,0,0,34,0,0,0,14,0,8,0
	db        128,16,0,0,0,0,3,0,131,16,0,0,8,0,2,0
	db        10,0,129,16,0,0,14,0,8,0,3,0,0,0,64,0
	db        3,0,130,16,0,0,16,0,1,2,3,0,116,0,0,0
	db        16,4,0,0,0,0,0,0,16,0,1,2,3,0,16,4
	db        0,0,16,4,0,0,116,0,0,0,14,0,8,0,66,16
	db        0,0,7,0,1,0,133,16,0,0,8,0,1,2,1,0
	db        91,16,0,0,14,0,8,0,116,0,0,0,7,0,1,0
	db        135,16,0,0,8,0,1,2,1,0,66,16,0,0,14,0
	db        8,0,73,16,0,0,7,0,2,0,137,16,0,0,12,0
	db        1,2,2,0,66,16,0,0,91,16,0,0,14,0,8,0
	db        116,0,0,0,7,0,2,0,139,16,0,0,12,0,1,2
	db        2,0,16,4,0,0,34,4,0,0
$$BTYPES	ends
$$BNAMES	segment byte public use32 'DEBNAM'
	db	7,'BytCopy'
	db	5,'bytes'
	db	3,'len'
	db	1,'i'
	db	3,'byt'
	db	3,'res'
	db	13,'BytToBStrCopy'
	db	5,'bytes'
	db	3,'len'
	db	3,'res'
	db	13,'BytToHStrCopy'
	db	5,'bytes'
	db	3,'len'
	db	1,'j'
	db	1,'i'
	db	4,'hlen'
	db	3,'res'
	db	14,'BStrToHStrCopy'
	db	4,'bstr'
	db	1,'j'
	db	1,'i'
	db	4,'hlen'
	db	4,'blen'
	db	3,'res'
	db	10,'IsSpaceStr'
	db	1,'s'
	db	8,'WCStrLen'
	db	2,'ws'
	db	1,'i'
	db	3,'len'
	db	12,'SubWCStrCopy'
	db	3,'str'
	db	3,'len'
	db	3,'res'
	db	9,'WCStrCopy'
	db	3,'Str'
	db	11,'WCToStrCopy'
	db	2,'wc'
	db	3,'res'
	db	1,'i'
	db	3,'len'
	db	12,'WCStrToLower'
	db	2,'st'
	db	1,'s'
	db	12,'WCStrToUpper'
	db	2,'st'
	db	1,'s'
	db	10,'SubStrCopy'
	db	3,'str'
	db	3,'len'
	db	3,'res'
	db	7,'StrCopy'
	db	3,'Str'
	db	10,'StrToLower'
	db	2,'st'
	db	1,'s'
	db	10,'StrToUpper'
	db	2,'st'
	db	1,'s'
	db	9,'GetArgLst'
	db	4,'args'
	db	1,'i'
	db	6,'argcnt'
	db	6,'arglst'
	db	10,'strstr_aux'
	db	2,'s1'
	db	2,'s2'
	db	1,'s'
	db	3,'res'
	db	2,'l2'
	db	10,'strchr_aux'
	db	1,'s'
	db	1,'c'
	db	1,'t'
	db	3,'res'
	db	11,'strrchr_aux'
	db	1,'s'
	db	1,'c'
	db	1,'t'
	db	3,'res'
	db	1,'l'
	db	11,'strcspn_aux'
	db	1,'s'
	db	6,'reject'
	db	1,'t'
	db	1,'i'
	db	1,'l'
	db	3,'res'
	db	10,'memcpy_aux'
	db	3,'dst'
	db	3,'src'
	db	1,'n'
	db	1,'i'
	db	10,'memcmp_aux'
	db	3,'dst'
	db	3,'src'
	db	1,'n'
	db	1,'i'
	db	10,'getcwd_aux'
	db	6,'buffer'
	db	7,'bufsize'
	db	3,'pwd'
	db	14,'GetSystemError'
	db	3,'txt'
	db	3,'buf'
	db	2,'rc'
	db	22,'GetSystemError_noalloc'
	db	6,'buffer'
	db	7,'bufsize'
	db	2,'rc'
	db	6,'runprg'
	db	3,'cmd'
	db	6,'cmdflg'
	db	20,'_PROCESS_INFORMATION'
	db	8,'hProcess'
	db	7,'hThread'
	db	11,'dwProcessId'
	db	10,'dwThreadId'
	db	13,'_STARTUPINFOA'
	db	2,'cb'
	db	10,'lpReserved'
	db	9,'lpDesktop'
	db	7,'lpTitle'
	db	3,'dwX'
	db	3,'dwY'
	db	7,'dwXSize'
	db	7,'dwYSize'
	db	13,'dwXCountChars'
	db	13,'dwYCountChars'
	db	15,'dwFillAttribute'
	db	7,'dwFlags'
	db	11,'wShowWindow'
	db	11,'cbReserved2'
	db	11,'lpReserved2'
	db	9,'hStdInput'
	db	10,'hStdOutput'
	db	9,'hStdError'
	db	3,'tmp'
	db	7,'ExitVal'
	db	11,'ProcessInfo'
	db	9,'StartInfo'
	db	18,'apply_fun_portable'
	db	1,'f'
	db	3,'cnt'
	db	4,'args'
	db	9,'apply_fun'
	db	1,'f'
	db	3,'cnt'
	db	4,'args'
	db	3,'arg'
	db	1,'i'
	db	7,'DL_open'
	db	6,'dlname'
	db	4,'flag'
	db	11,'HINSTANCE__'
	db	6,'unused'
	db	3,'dll'
	db	8,'DL_close'
	db	5,'dlhdl'
	db	9,'DL_symbol'
	db	5,'dlhdl'
	db	7,'symname'
	db	3,'res'
	db	8,'DL_error'
	db	16,'DL_error_noalloc'
	db	6,'buffer'
	db	7,'bufsize'
	db	8,'UserName'
	db	3,'dmy'
	db	3,'buf'
	db	20,'_SECURITY_ATTRIBUTES'
	db	7,'nLength'
	db	20,'lpSecurityDescriptor'
	db	14,'bInheritHandle'
	db	6,'size_t'
	db	9,'ptrdiff_t'
	db	7,'wchar_t'
	db	6,'wint_t'
	db	8,'wctype_t'
	db	6,'fpos_t'
	db	7,'va_list'
	db	6,'time_t'
	db	7,'clock_t'
	db	5,'dev_t'
	db	5,'ino_t'
	db	6,'mode_t'
	db	7,'nlink_t'
	db	5,'uid_t'
	db	5,'gid_t'
	db	5,'off_t'
	db	6,'_TCHAR'
	db	7,'_TSCHAR'
	db	7,'_TUCHAR'
	db	7,'_TXCHAR'
	db	5,'_TINT'
	db	5,'ULONG'
	db	6,'PULONG'
	db	6,'USHORT'
	db	7,'PUSHORT'
	db	5,'UCHAR'
	db	6,'PUCHAR'
	db	3,'PSZ'
	db	5,'DWORD'
	db	4,'BOOL'
	db	4,'BYTE'
	db	4,'WORD'
	db	5,'FLOAT'
	db	5,'PBYTE'
	db	6,'LPBYTE'
	db	5,'PWORD'
	db	6,'LPWORD'
	db	6,'PDWORD'
	db	7,'LPDWORD'
	db	6,'LPVOID'
	db	7,'LPCVOID'
	db	3,'INT'
	db	4,'UINT'
	db	14,'POINTER_64_INT'
	db	5,'PVOID'
	db	7,'PVOID64'
	db	4,'CHAR'
	db	5,'SHORT'
	db	4,'LONG'
	db	5,'WCHAR'
	db	6,'PWCHAR'
	db	5,'LPWCH'
	db	4,'PWCH'
	db	6,'NWPSTR'
	db	6,'LPWSTR'
	db	5,'PWSTR'
	db	5,'PCHAR'
	db	4,'LPCH'
	db	3,'PCH'
	db	5,'LPCCH'
	db	4,'PCCH'
	db	5,'NPSTR'
	db	5,'LPSTR'
	db	4,'PSTR'
	db	6,'LPCSTR'
	db	5,'PCSTR'
	db	5,'TCHAR'
	db	6,'PTCHAR'
	db	5,'TBYTE'
	db	6,'PTBYTE'
	db	5,'LPTCH'
	db	4,'PTCH'
	db	5,'PTSTR'
	db	6,'LPTSTR'
	db	7,'LPCTSTR'
	db	6,'HANDLE'
	db	7,'PHANDLE'
	db	5,'FCHAR'
	db	6,'FSHORT'
	db	5,'FLONG'
	db	7,'HRESULT'
	db	5,'CCHAR'
	db	4,'LCID'
	db	5,'PLCID'
	db	6,'LANGID'
	db	8,'LONGLONG'
	db	9,'DWORDLONG'
	db	3,'USN'
	db	7,'BOOLEAN'
	db	8,'PBOOLEAN'
	db	10,'KSPIN_LOCK'
	db	11,'PKSPIN_LOCK'
	db	13,'PACCESS_TOKEN'
	db	20,'PSECURITY_DESCRIPTOR'
	db	4,'PSID'
	db	11,'ACCESS_MASK'
	db	12,'PACCESS_MASK'
	db	27,'SECURITY_DESCRIPTOR_CONTROL'
	db	28,'PSECURITY_DESCRIPTOR_CONTROL'
	db	30,'SECURITY_CONTEXT_TRACKING_MODE'
	db	31,'PSECURITY_CONTEXT_TRACKING_MODE'
	db	20,'SECURITY_INFORMATION'
	db	21,'PSECURITY_INFORMATION'
	db	15,'EXECUTION_STATE'
	db	6,'WPARAM'
	db	6,'LPARAM'
	db	7,'LRESULT'
	db	4,'ATOM'
	db	8,'SPHANDLE'
	db	8,'LPHANDLE'
	db	7,'HGLOBAL'
	db	6,'HLOCAL'
	db	12,'GLOBALHANDLE'
	db	11,'LOCALHANDLE'
	db	7,'FARPROC'
	db	7,'HGDIOBJ'
	db	11,'HINSTANCE__'
	db	9,'HINSTANCE'
	db	7,'HMODULE'
	db	5,'HFILE'
	db	8,'COLORREF'
	db	10,'LPCOLORREF'
	db	20,'_SECURITY_ATTRIBUTES'
	db	19,'SECURITY_ATTRIBUTES'
	db	20,'PSECURITY_ATTRIBUTES'
	db	21,'LPSECURITY_ATTRIBUTES'
	db	20,'_PROCESS_INFORMATION'
	db	19,'PROCESS_INFORMATION'
	db	20,'PPROCESS_INFORMATION'
	db	21,'LPPROCESS_INFORMATION'
	db	13,'_STARTUPINFOA'
	db	12,'STARTUPINFOA'
	db	14,'LPSTARTUPINFOA'
	db	11,'STARTUPINFO'
	db	13,'LPSTARTUPINFO'
	db	17,'WIN_TRUST_SUBJECT'
	db	9,'LCSCSTYPE'
	db	13,'LCSGAMUTMATCH'
	db	11,'FXPT16DOT16'
	db	10,'FXPT2DOT30'
	db	5,'BCHAR'
	db	7,'COLOR16'
	db	4,'HDWP'
	db	13,'MENUTEMPLATEA'
	db	13,'MENUTEMPLATEW'
	db	12,'MENUTEMPLATE'
	db	15,'LPMENUTEMPLATEA'
	db	15,'LPMENUTEMPLATEW'
	db	14,'LPMENUTEMPLATE'
	db	10,'HDEVNOTIFY'
	db	11,'PHDEVNOTIFY'
	db	8,'HELPPOLY'
	db	6,'LCTYPE'
	db	7,'CALTYPE'
	db	5,'CALID'
	db	6,'REGSAM'
	db	9,'MMVERSION'
	db	8,'MMRESULT'
	db	12,'LPPATCHARRAY'
	db	10,'LPKEYARRAY'
	db	6,'FOURCC'
	db	5,'HPSTR'
	db	8,'MCIERROR'
	db	11,'MCIDEVICEID'
	db	12,'I_RPC_HANDLE'
	db	10,'RPC_STATUS'
	db	18,'RPC_BINDING_HANDLE'
	db	8,'handle_t'
	db	13,'RPC_IF_HANDLE'
	db	24,'RPC_AUTH_IDENTITY_HANDLE'
	db	16,'RPC_AUTHZ_HANDLE'
	db	17,'RPC_EP_INQ_HANDLE'
	db	11,'I_RPC_MUTEX'
	db	13,'RPC_NS_HANDLE'
	db	12,'FILEOP_FLAGS'
	db	15,'PRINTEROP_FLAGS'
	db	6,'u_char'
	db	7,'u_short'
	db	5,'u_int'
	db	6,'u_long'
	db	6,'SOCKET'
	db	8,'WSAEVENT'
	db	10,'LPWSAEVENT'
	db	11,'SERVICETYPE'
	db	5,'GROUP'
	db	6,'ALG_ID'
	db	10,'HCRYPTPROV'
	db	9,'HCRYPTKEY'
	db	10,'HCRYPTHASH'
	db	16,'HCRYPTOIDFUNCSET'
	db	17,'HCRYPTOIDFUNCADDR'
	db	9,'HCRYPTMSG'
	db	10,'HCERTSTORE'
	db	14,'HCERTSTOREPROV'
	db	4,'byte'
	db	7,'boolean'
	db	12,'NDR_CCONTEXT'
	db	14,'error_status_t'
	db	10,'RPC_BUFPTR'
	db	10,'RPC_LENGTH'
	db	15,'PMIDL_XMIT_TYPE'
	db	20,'RPC_SS_THREAD_HANDLE'
	db	7,'OLECHAR'
	db	8,'LPOLESTR'
	db	6,'DOUBLE'
	db	9,'ULONGLONG'
	db	5,'SCODE'
	db	8,'HCONTEXT'
	db	10,'CLIPFORMAT'
	db	13,'HMETAFILEPICT'
	db	4,'DATE'
	db	4,'BSTR'
	db	12,'VARIANT_BOOL'
	db	7,'VARTYPE'
	db	6,'PROPID'
	db	12,'LPCLIPFORMAT'
	db	13,'RPCOLEDATAREP'
	db	8,'HOLEMENU'
	db	6,'DISPID'
	db	8,'MEMBERID'
	db	8,'HREFTYPE'
	db	9,'SC_HANDLE'
	db	11,'LPSC_HANDLE'
	db	21,'SERVICE_STATUS_HANDLE'
	db	7,'SC_LOCK'
	db	7,'StdCPtr'
	db	6,'c_int8'
	db	7,'c_int16'
	db	7,'c_int32'
	db	7,'c_uint8'
	db	8,'c_uint16'
	db	8,'c_uint32'
	db	7,'c_int64'
	db	8,'c_uint64'
	db	5,'Abs_T'
	db	5,'Any_T'
	db	6,'c_byte'
	db	6,'c_word'
	db	4,'word'
	db	9,'c_bstring'
	db	8,'c_string'
	db	6,'wc_int'
	db	7,'wc_char'
	db	9,'wc_string'
	db	8,'PF_ERROR'
	db	5,'PCFUN'
	db	6,'DL_Hdl'
$$BNAMES	ends
	?debug	D "..\..\..\EXTERN\STYX\SRC\INC\mem_base.h" 11027 20005
	?debug	D "E:\usr\prj\Shacira\Extern\STYX\src\LIBBASE\syscbhdl.h" 10907 34658
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\imm.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\mcx.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\winsvc.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\oleauto.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\oaidl.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\msxml.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\servprov.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\oleidl.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\urlmon.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\cguid.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\objidl.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\unknwn.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\wtypes.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\rpcnsip.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\rpcndr.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\objbase.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\pshpack8.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\ole2.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\prsht.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\winspool.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\commdlg.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\wincrypt.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\mswsock.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\qos.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\winsock2.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\winperf.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\shellapi.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\rpcasync.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\rpcnterr.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\rpcnsi.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\rpcdcep.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\rpcdce.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\rpc.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\nb30.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\mmsystem.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\lzexpand.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\dlgs.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\ddeml.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\dde.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\cderr.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\winnetwk.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\winreg.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\winver.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\wincon.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\winnls.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\winuser.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\pshpack1.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\wingdi.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\winerror.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\winbase.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\pshpack2.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\poppack.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\pshpack4.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\winnt.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\windef.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\excpt.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\windows.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\wctype.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\wchar.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\fcntl.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\tchar.h" 9921 8224
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\dir.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\direct.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\sys/stat.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\sys/types.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\time.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\process.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\alloc.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\malloc.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\io.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\errno.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\stdarg.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\ctype.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\mem.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\string.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\search.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\stdlib.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\_nfile.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\_null.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\_defs.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\_stddef.h" 9803 8192
	?debug	D "E:\USR\BIN\CBUILD~1\INCLUDE\stdio.h" 9803 8192
	?debug	D "E:\usr\prj\Shacira\Extern\STYX\src\LIBBASE\styconf0.h" 11336 28532
	?debug	D "..\..\..\EXTERN\STYX\SRC\INC\sysbase0.h" 11824 30834
	?debug	D "E:\usr\prj\Shacira\Extern\STYX\src\LIBBASE\Sysbase1.c" 11824 29109
	end
