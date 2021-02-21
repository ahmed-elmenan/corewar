    
.name           "champion executable"#commentaire
.comment        "men neyytk
 bag
 hi
 terb
 e7n
 i ?    "    #;dfdf#wa33333
 
tirf: ld	%0, r16
	zjmp %:tirb
	live	%42


lqsd:    	
	add	r3,r4,r3
    sti	r1,r1,%1
    ld	%1,r5
	ld	%0,r11
	ld	%4,r3
sti:	live	%42
	fork  %:tirf  
	live	%742
	sub	r3,r5,r3
	zjmp	%:tirop
	ld	%0,r11
					fork	%:tirf
#	and r10,  R2,%2 
	live	%42
	sti r10,%-510,%0
	sti r10,%-404,%0
	sti	r10,%-303,%0
				sti	r10,%-202,%0
	ld	%0,r11
	zjmp	%:tirf

tirop:	ld	%368,r2
ld	%0,r3
	ld	%4,r4

tirb:	live	%1
	sti	r10,%-510,r2
			sti	r10,%-510,r3
	add	r4,r5,r4
	add	r3,r4,r3
	sub	r2, r4,  r2
	zjmp	%:tirop
			ld	%0,r11
	zjmp	%:entree
	zjmp	%:tirb
