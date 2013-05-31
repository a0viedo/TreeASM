global tree_create
global tree_create_int
global tree_create_double
global tree_create_string
global tree_deep_delete
global tree_add_child
global tree_print
global tree_prune
global tree_merge
global tree_last_children_pointer	
global tree_print_level

global es_bisiesto
global es_mayor_que_sesenta
global tiene_vocales


global sumar
global multiplicar
global intercalar

extern malloc
extern free
extern fprintf
extern fopen
extern fclose

%define NULL 0
%define TAM_TREE 20
%define TAM_NODO 16
%define TAM_dato_int 4
%define TAM_dato_double 8
%define TAM_puntero 8
%define TAM_value 8
%define offset_children 0
%define offset_value    8
%define offset_tipo     16
%define offset_element 0
%define offset_next    8
%define ENUM_int 8
%define ENUM_double 8
%define ENUM_string 8

section .data

fString: db `%s\0`
fStringSpace: db `%s \0`
formatoString: db `%s\n\0`
formatoDouble: db `%f\n\0`
formatoInteger: db `%d\n\0` 
nodeLabel: db `node: \0`
childNodeLabel: db `--> \0`
endTreeLabel: db `--------\0`
levelLabel: db `  \0`
append: db `a\0`
treeFirstLine: db `> %s\0`
; struct tree {
; 	struct list_node *children
; 	tree_value value
; 	tree_type type
; }

; struct list_node {
;	tree *element;
;	struct	list_node *next
;}

section .text
; ~ tree* tree_create(tree_value value, tree_type type)
tree_create:
	; RDI <- value
	; ESI <- type
	; Stack Frame
	push rbp ;alineada
	mov rbp, rsp

	push r12 ; desalineada
	push r13 ; alineada

	mov r12, rdi
	movsx r13, esi

	mov rdi, TAM_TREE ; parámetro de malloc
	call malloc ; resultado de malloc en rax

	mov [rax + offset_value], r12 ; seteo el valor
	mov [rax + offset_tipo], r13d ; seteo el tipo
	mov qword [rax + offset_children], NULL ; seteo los hijos en null

	pop r13
	pop r12
	pop rbp

	ret ; devuelvo el puntero al árbol en rax
;------------------------------------------------------------------------
; ~ tree* tree_create_int(int value)
tree_create_int:
	; EDI <- value
	; armo Stack Frame
	push rbp    ;alineada
	mov rbp, rsp

	mov esi, 0
	call tree_create
	pop rbp
	ret

; ~ tree* tree_create_double(double value)
tree_create_double:
	; XMM0 <- value
	; armo Stack Frame
	push rbp    ;alineada
	mov rbp, rsp

	mov esi, 1
	movq rdi, xmm0
	call tree_create

	pop rbp
	ret
;------------------------------------------------------------------------
; ~ tree* tree_create_string(char *str)
tree_create_string:
	; RDI <- value
	; armo Stack Frame
	push rbp    ;alineada
	mov rbp, rsp

	mov esi, 2
	call tree_create
	
	pop rbp
	ret
;------------------------------------------------------------------------
; ~ void tree_deep_delete(tree *self)
tree_deep_delete:
	; RDI <- self
	; armo Stack Frame
	push rbp    ;alineada
	mov rbp, rsp
	push r12 ; desa

	sub rsp,8 ; ali

	mov r12, rdi ; R12 <- *self
	mov rdi, [r12 + offset_children]
	cmp qword rdi, NULL
	je .checkeo ; si no tiene hijos paso a checkear si tengo que liberar memoria de su valor
	lea rdi, [r12 + offset_children]
	call list_node_deep_delete ; si tiene hijos, llamo a la función para eliminarlos
	jmp .checkeo
.libero_puntero_a_string:
	mov rdi, [r12 + offset_value]
	call free
	jmp .termina
.checkeo:
	cmp dword [r12 + offset_tipo], 2
	je .libero_puntero_a_string
.termina:
	mov rdi, r12
	call free ; libero la memoria del propio árbol
	add rsp, 8
	pop r12
	pop rbp	
	ret
;------------------------------------------------------------------------
; ~ auxiliar
; ~ int tree_children_count(tree *self)
tree_children_count:
	push rbp    ;alineada
	mov rbp, rsp

	xor rax, rax
	mov rsi, [rdi + offset_children]
.proximo:
	cmp qword rsi, NULL
	je .termina
	mov rsi, [rsi + offset_next] ; RSI <- proximo
	inc rax ; incremento el contador
	jmp .proximo

.termina:	
	pop rbp
	ret


;------------------------------------------------------------------------
; ~ auxiliar
; ~ retorna un puntero al puntero final (el que apunta a null)
;list_node_p* tree_last_children_pointer(tree *self)
tree_last_children_pointer:
	; RDI <- self
	; armo Stack Frame
	push rbp    ;alineada
	mov rbp, rsp

	mov rax, [rdi + offset_children] ; asume que tiene al menos un hijo, ojo
.ciclo:
	mov rsi, [rax + offset_next]
	cmp qword rsi, NULL
	je .termina
	mov rax, rsi
	jmp .ciclo
.termina:
	pop rbp
	ret
;------------------------------------------------------------------------
; ~ void tree_add_child(tree *self, tree *child)
tree_add_child:
	; RDI <- self
	; RSI <- child
	; armo Stack Frame
	push rbp    ;alineada
	mov rbp, rsp
	
	push r13 ; desa
	push r14 ; ali
	push r15 ; desa
	sub rsp, 8 ; ali
	
	mov r13, rdi ; R13 <- RDI <- self
	mov r14, rsi ; R14 <- RSI <- child

	mov rdi, TAM_NODO
	call malloc ; posición inicial de la memoria que pedí en rax

	mov qword [rax + offset_next], NULL ; el próximo del nuevo nodo tiene que apuntar a NULL
	mov [rax + offset_element], r14 ; seteo el elemento del nuevo nodo a que apunte al tree child

	mov r15, rax ; paso a r15 donde empieza la memoria del nodo que pedí

	cmp qword [r13 + offset_children], NULL ; checkeo si el padre ya tiene hijos
	jne .obtenerElUltimo ; si tiene, agrego al final
	mov [r13 + offset_children], rax ; si no tiene, hago que apunte al nodo que creé
	jmp .termina
.obtenerElUltimo:
	mov rdi, r13
	call tree_last_children_pointer	; busco el último	
	mov [rax + offset_next], r15 ; al último le agrego el nodo que cré
.termina:
	add rsp, 8
	pop r15
	pop r14
	pop r13	
	pop rbp
	ret
;------------------------------------------------------------------------
tree_print_value:
	; RDI <- *self
	; RSI <- *file
	; armo Stack Frame
	push rbp    ;alineada
	mov rbp, rsp

	mov rcx, rsi

	mov esi, [rdi + offset_tipo]
	cmp esi, 1 ; me fijo si es tipo Double
	je .esDouble
	cmp esi, 2 ; me fijo si es string
	je .esString
	mov edx, [rdi + offset_value] ; muevo el valor a la parte baja de rsi ya que es un integer
	mov rsi, formatoInteger
	jmp .imprimir
.esDouble:
	movq xmm0, [rdi + offset_value]
	mov rsi, formatoDouble
	mov qword rax, 1 ; si RAX no está en 1, esto explota
	jmp .imprimir
.esString:
	mov rdx, [rdi + offset_value]
	mov rsi, formatoString
.imprimir: 
	mov rdi, rcx
	call fprintf
	
	pop rbp
	ret
;------------------------------------------------------------------------
; ~ auxiliar
; ~ void tree_print_value_at_level(tree* self, FILE *file, int level)
tree_print_value_at_level:
	; RDI <- self
	; RSI <- file
	; EDX <- level
	; armo Stack Frame
	push rbp    ;alineada
	mov rbp, rsp

	ret
;------------------------------------------------------------------------
print_spaces:
	; recibe un int en EDI
	; RSI <- *file
	push rbp    ;alineada
	mov rbp, rsp

	push r12 ; desa
	push rbx ; ali	

	mov r12, rsi
	movsx rbx, edi
	
	cmp rbx, 0
	jne .imprime_espacio
	jmp .imprime_label ; cero espacios, imprime el label directamente

.imprime_espacio:
	mov rdx, levelLabel
	mov rsi, fString
	mov rdi, r12
	call fprintf ; imprimo dos espacios
	dec rbx
	cmp qword rbx, NULL
	jne .imprime_espacio	

.imprime_label:	
	mov rdx, childNodeLabel
	mov rsi, fString 
	mov rdi, r12
	call fprintf ; imprimo label

.termina:
	pop rbx
	pop r12
	pop rbp
	ret
;------------------------------------------------------------------------
tree_print_level_aux:
	; RDI <- *self
	; ESI <- level
	; RDX <- *file
	; armo Stack Frame
	push rbp    ;alineada
	mov rbp, rsp

	push r12 ; desa
	push r13 ; ali

	mov r12, rdi ; R12 <- *self
	mov r13, rdx ; R13 <- *file

	movsx rdi, esi ; EDI <- EDX
	mov rsi, r13
	call print_spaces

	mov rdx, nodeLabel
	mov rsi, fString
	mov rdi, r13
	call fprintf ; imprimo la parte que dice node

	mov rdi, r12
	mov rsi, r13
	call tree_print_value ; imprimo el valor

	pop r13
	pop r12
	pop rbp
	ret
;------------------------------------------------------------------------
; ~ auxiliar
; ~ void tree_print_level(tree *self, FILE *file, int level)
tree_print_level:
	; RDI <- *self
	; RSI <- *file
	; EDX <- level
	; armo Stack Frame
	push rbp    ;alineada
	mov rbp, rsp

	push r12 ; desa
	push r13 ; ali
	push r14 ; desa	
	push r15 ; ali
	
	mov r13, rdi ; R13 <- *self
	mov r12, rsi ; R12 <- *file
	movsx r15, edx ; R15 <- level

	mov r13, [r13 + offset_children]
	cmp qword r13, NULL ; checkeo si tiene hijos
	je .termina ; si no tiene termina

.proximo:
	mov r14, [r13 + offset_element] ; en r14 está el elemento 

	mov rdi, r14 
	mov rsi, r15
	mov rdx, r12
	call tree_print_level_aux ; imprimo el árbol que estoy recorriendo

	mov rax, [r14 + offset_children] 
	cmp qword rax, NULL ; me fijo si tiene nietos
	jne .tiene_nietos

.checkeo_por_ultimo:
	mov r13, [r13 + offset_next] 
	cmp qword r13, NULL ; me fijo si el próximo es null
	je .termina ; si es null entonces es el último, por lo tanto termino
	jmp .proximo		

.tiene_nietos:
	lea rdi, [r14 + offset_children]
	inc r15 ; incremento el nivel ya que voy a hacer recursion
	mov rsi, r12
	mov rdx, r15
	call tree_print_level ; recursion hacia el nivel inferior de sus hijos
	dec r15 ; decremento para seguir imprimiendo los hijos al mismo nivel
	jmp .checkeo_por_ultimo

.termina:	
	pop r15	
	pop r14
	pop r13
	pop r12
	pop rbp
	ret

;------------------------------------------------------------------------
; ~ void tree_print(tree *self, char* extra, char *archivo)
tree_print:
	; RDI <- *self
	; RSI <- *extra
	; RDX <- *archivo
	; armo Stack Frame
	push rbp    ;alineada
	mov rbp, rsp

	push r12 ; desa
	push r13 ; ali
	push r14 ; desa
	push r15 ; ali


	mov r12, rdi ; R12 <- *self
	mov r13, rsi ; R13 <- *extra

	mov rdi, rdx
	mov rsi, append	
	call fopen
		
	mov r15, rax

	mov rdi, r15
	mov rsi, formatoString
	mov rdx, r13
	call fprintf ; imprimo el extra
	
	mov rdx, nodeLabel
	mov rsi, treeFirstLine
	mov rdi, r15
	call fprintf ; imprimo la parte del padre

	mov rdi, r12
	mov rsi, r15
	call tree_print_value ; imprimo el valor del padre
	
	mov rdi, r12
	mov rsi, r15
	xor rdx, rdx
	mov rdx, 0
	call tree_print_level ; imprimo el resto

	mov rdx, endTreeLabel
	mov rsi, formatoString
	mov rdi, r15
	call fprintf ; imprimo linea final

	mov rdi, r15
	call fclose ; cierro el stream	

	pop r15	
	pop r14
	pop r13
	pop r12
	pop rbp
	ret


;------------------------------------------------------------------------
; ~ auxiliar
; ~ void list_node_deep_delete(list_node **node_pointer)
list_node_deep_delete:
	; RDI node_pointer
	; armo Stack Frame
	push rbp    ;alineada
	mov rbp, rsp

	push r13 ; desa
	push r14 ; ali

	mov r13, [rdi] ; R13 <- node_pointer
	
.proximo:
	cmp qword r13, NULL
	je .termina
	mov r14, [r13 + offset_element] 
	mov rsi, [r14 + offset_children] 
	cmp qword rsi, NULL ; checkeo si tiene nietos
	jne .tieneNietos

.libero_memoria:
	cmp dword [r14 + offset_tipo], 2 ; checkeo si el tipo es string
	je .elimino_puntero_a_string ; si es del tipo string, entonces tengo que liberar la memoria de su puntero a char
.elimino_nodo_y_arbol:
	mov rdi, r14 
	call free  ;libero la memoria del arbol
	mov r14, [r13 + offset_next]

	mov rdi, r13 
	call free ;libero la memoria del nodo

	cmp qword r14, NULL ; checkeo si el próximo es null
	je .termina ; entonces termino
	
	mov r13, r14
	jmp .proximo		

.elimino_puntero_a_string:
	mov rdi, [r14 + offset_value]
	call free
	jmp .elimino_nodo_y_arbol

.tieneNietos:
	lea rdi, [r14 + offset_children]
	call list_node_deep_delete ; recursion hacia el nivel inferior de sus hijos
	jmp .libero_memoria

.termina:	
	pop r14
	pop r13
	pop rbp
	ret

;------------------------------------------------------------------------
; ~ void tree_prune(tree *self, tree_bool_method method)
tree_prune:
	; RDI <- *self
	; RSI <- method
	push rbp
	mov rbp, rsp

	push r12
	push r13
	push r14
	push r15
	push rbx

	sub rsp, 8

	xor r15, r15
	mov r12, rdi ; R12 <- *self NO LO USO
	mov r13, rsi ; R13 <- method

	mov r14, [r12 + offset_children]
	cmp qword r14, NULL ; checkeo si no tiene hijos
	je .termina ; si no tiene, entonces termino
.proximo:
	mov rdi, [r14 + offset_element]
	mov rbx, [r14 + offset_next]
	call r13 ; evaluo el método que me devuelve bool
	cmp eax, 0
	je .recursion ; si es falso, hago recursión
	
	mov rdi, [r14 + offset_element]
	call tree_deep_delete ; si no es falso, elimino ese arbol y sus hijos

	cmp qword r15, NULL
	je .esElPrimerNodo

	mov [r15 + offset_next], rbx ; uno el nodo anterior con el siguiente al eliminado

	mov rdi, r14
	call free  ;libero el nodo del arbol eliminado

.checkeoSiEsElUltimo:
	cmp qword rbx, NULL
	je .termina

	mov r14, rbx
	jmp .proximo

.esElPrimerNodo:
	mov [r12 + offset_children], rbx ; uno el arbol padre con el nodo siguiente al eliminado
	mov rdi, r14
	call free  ;libero el nodo del arbol eliminado
	jmp .checkeoSiEsElUltimo
		
.recursion:
	mov r15, r14
	mov rdi, [r14 + offset_element]
	mov rsi, r13
	call tree_prune
	jmp .checkeoSiEsElUltimo

.termina:
	add rsp, 8
	pop rbx
	pop r15
	pop r14
	pop r13
	pop r12
	pop rbp
	ret
;------------------------------------------------------------------------
; ~ auxiliar
; ~ void tree_shallow_delete(tree *self)
tree_shallow_delete:
	; RDI <- self
	; armo Stack Frame
	push rbp    ;alineada
	mov rbp, rsp

	push r12 ; desa
	push r13 ; ali

	mov r12, rdi
	mov r13, r12 
	mov rdi, [rdi + offset_children] 
	cmp qword rdi, NULL
	je .termina

.proximo:
	mov r12, [rdi + offset_next] ; uso r12 ya que al hacer una llamada, perdería cualquier registro que necesariamente tenga que pushear
	call free ;libero la memoria del nodo
	cmp qword r12, NULL ; checkeo si el próximo es null
	je .termina ; si es null entonces termino
	mov rdi, r12 
	jmp .proximo		

.termina:	
	mov rdi, r13
	call free

	pop r13
	pop r12
	pop rbp
	ret

;------------------------------------------------------------------------
; ~ auxiliar
; ~ void list_node_shallow_delete(list_node **node_pointer)
list_node_shallow_delete:
	; RDI <- node_pointer
	ret

;------------------------------------------------------------------------
; ~ auxiliar
; ~ void merge(tree *parent, list_node **node_pointer, tree_value_method value_method)
merge:
	; RDI <- parent
	; RSI <- node_pointer
	; RDX <- value_method
	; armo Stack Frame
	push rbp
	mov rbp, rsp

	push r12
	push r13
	push r14
	push r15
	push rbx
	sub rsp, 8

	mov r12, rdi ; R12 <- *parent
	mov r13, [rsi] ; RSI <- *node_pointer
	mov r14, rdx ; RDX <- value_method

	mov rdi, r13
	call tree_children_count ; cuento la cantidad de hijos que tiene

	mov r15, rax
	cmp qword r15, NULL ; checkeo si tiene hijos
	je .termina ; si no tiene termino
	mov rbx, [r13 + offset_children]

.proximo: 
	mov rsi, [rbx + offset_element]

	mov rdi, r12 
	call tree_add_child ; agrego el hijo al padre

	dec r15
	mov rbx, [rbx + offset_next]
	cmp qword rbx, NULL ; checkeo si el próximo es null
	je .termina ; si es null termino
	jmp .proximo

.termina:
	mov rdi, r12
	mov rsi, r13
	call r14 ; llamo a la función que me devuelve un valor

	mov [r12 + offset_value], rax ; se lo seteo al padre

	mov rdi, r13
	call tree_shallow_delete ; elimino los nodos de los hijos que moví

	add rsp, 8
	pop rbx
	pop r15
	pop r14
	pop r13
	pop r12
	pop rbp
	ret

;------------------------------------------------------------------------
; ~ tree* tree_merge(tree *self, tree_bool_method test_method, tree_value_method value_method)
tree_merge:
	; RDI <- self
	; RSI <- test_method
	; RDX <- value_method
	push rbp    ;alineada
	mov rbp, rsp

	%define nodoAnterior [rbp - 48]

	push rbx ; desa
	push r12 ; ali
	push r13 ; desa
	push r14 ; ali
	push r15 ; desa

	sub rsp, 8 ; ali
	mov qword nodoAnterior, NULL ; inicializo variable en null

	mov r12, rdi ; R12 <- *self
	mov r13, rsi ; R13 <- test_method
	mov r14, rdx ; R14 <- value_method

	call tree_children_count ; cuento cuantos hijos tiene
	mov r15, rax
	
	mov rbx, [r12 + offset_children]	
	cmp qword rbx, NULL ; checkeo si tiene hijos
	je .termina ; si no tiene, termino
.proximo:
	mov rdi,[rbx + offset_element]
	call r13 ; llamo a test_method

	cmp qword rax, 0
	je .recursion ; si me dió false, hago recursión

	mov rdi, r12
	lea rsi, [rbx + offset_element]
	mov rdx, r14
	call merge ; de lo contrario, mergeo

	cmp qword nodoAnterior, NULL
	je .esElPrimerNodo

	mov rdi, rbx
	mov rbx, [rbx + offset_next] ; me muevo al siguiente nodo
	mov rsi, nodoAnterior
	mov [rsi + offset_next], rbx ; uno el anterior(de antes de moverme) con el siguiente(también)
	call free ;libero memoria del nodo

.checkeoSiEsElUltimo:
	dec r15
	jnz .proximo
	jmp .termina

.recursion:
	mov nodoAnterior, rbx
	mov rsi, r13
	mov rdx, r14
	mov rdi, [rbx + offset_element]
	call tree_merge
	mov rbx, [rbx + offset_next] ; me muevo al siguiente nodo
	jmp .checkeoSiEsElUltimo

.esElPrimerNodo:
	mov rdi, rbx
	mov rbx, [rbx + offset_next]
	mov [r12 + offset_children], rbx
	call free
	jmp .checkeoSiEsElUltimo	
.termina:
	
	add rsp, 8
	pop r15
	pop r14
	pop r13
	pop r12
	pop rbx
	pop rbp
	ret
;------------------------------------------------------------------------
; ~ boolean es_bisiesto(tree *t);
es_bisiesto:
	; RDI <- t
	push rbp    ;alineada
	mov rbp, rsp

	push r12 ; desa, pero no hago ninguna call

	mov esi, [rdi + offset_value]
	movsx r12, esi

	xor rdx, rdx
	mov rax, r12
	mov qword rsi, 4
	div rsi
	
	cmp rdx, 0
	je .divisiblePor4
	mov qword rax, 0
	jmp .termina
.divisiblePor4:
	xor rdx, rdx
	mov rax, r12
	mov qword rsi, 100
	div rsi
	cmp rdx, 0
	jne .esBisiesto
	xor rdx, rdx
	mov rax, r12
	mov qword rsi, 400
	div rsi
	cmp rdx, 0
	je .esBisiesto
	xor rax,rax
	jmp .termina
.esBisiesto:
	mov qword rax, 1
.termina:
	pop r12
	pop rbp
	ret

;------------------------------------------------------------------------
; ~ boolean es_mayor_que_sesenta(tree *t);
es_mayor_que_sesenta:
	; RDI <- t
	push rbp    ;alineada
	mov rbp, rsp

	xor rax,rax
	movq xmm0, [rdi + offset_value]

	mov rsi, 60
	cvtsi2sd xmm1, rsi ; convierto el 60 a double

	cmpsd xmm1, xmm0, 001b ; comparo si 60 es menor que el valor del árbol
	movq rax, xmm1

	and rax, 0000000000000001H ; elimino todo menos el primer bit
	pop rbp
	ret

;------------------------------------------------------------------------
; ~ boolean tiene_vocales(tree *t);
tiene_vocales:
	; RDI <- t
	push rbp    ;alineada
	mov rbp, rsp

	push rbx
	xor rax, rax
	mov rdi, [rdi + offset_value]
	
	xor rsi, rsi
.busco_vocales:
	mov bl, [rdi + rsi] ;
	
	cmp bl, 'a'
	je .tiene_vocales
	cmp bl, 'e'
	je .tiene_vocales
	cmp bl, 'i'
	je .tiene_vocales
	cmp bl, 'o'
	je .tiene_vocales
	cmp bl, 'u'
	je .tiene_vocales

	cmp bl, 0
	je .termina
	add rsi, 1
	jmp .busco_vocales

.tiene_vocales:
	add eax, 1
.termina:
	pop rbx
	pop rbp
	ret

;------------------------------------------------------------------------
; ~ tree_value sumar(tree* padre, tree *hijo);
sumar:
	; RDI <- padre
	; RSI <- hijo
	push rbp    ;alineada
	mov rbp, rsp

	xor rax,rax ; limpio RAX
	mov eax, [rdi + offset_value]
	mov edi, [rsi + offset_value]
	add eax, edi
	
	pop rbp
	ret

;------------------------------------------------------------------------
; ~ tree_value multiplicar(tree* padre, tree *hijo);
multiplicar:
	; RDI <- padre
	; RSI <- hijo
	push rbp    ;alineada
	mov rbp, rsp

	movq xmm0, [rdi + offset_value]
	movq xmm1, [rsi + offset_value] 
	mulsd xmm0, xmm1
	movq rax, xmm0

	pop rbp
	ret
;------------------------------------------------------------------------
; ~ tree_value intercalar(tree* padre, tree *hijo);
intercalar:
	; RDI <- padre
	; RSI <- hijo
	push rbp    ;alineada
	mov rbp, rsp

	push r12
	push r13
	push r14
	push r15
	push rbx

	sub rsp, 8

	mov r12, [rdi + offset_value]
	mov r13, [rsi + offset_value]
	
	mov rdi, r13
	call str_len
	mov r15, rax ; longitud de la cadena de hijo en rsi

	mov rdi, r12
	call str_len ; es mi función por lo tanto estoy seguro que puedo contar con los registros que utilizo
	mov rbx, rax ; ; longitud de la cadena de padre en rdi

	cmp rbx, r15
	mov rax, rbx
	jg .init
	mov rax, r15 ; en rax me quedo con el mayor length de ambos árboles

.init:
	mov r14, rax
	mov rdi, rax
	inc rdi ; str_len + 1
	call malloc ; pido memoria para la memoria donde voy a guardar el resultado

	mov rcx, r14
	mov r14, rax
	xor r8,r8 ; inicializo contador
.ciclo:
	cmp qword r8, rbx ; comparo contra la longitud de la cadena del padre
	je .completo_con_hijo
	cmp qword r8, r15 ; comparo contra la longitud de la cadena del hijo
	je .completo_con_padre

	xor rdx, rdx
	mov rax, r8
	mov rdi, 2
	div rdi
	cmp rdx, 0 ; checkeo si es par
	je .corresponde_char_de_padre ; es divisible por 2, luego es par y le corresponde el char al padre
	
	mov al, [r13 + r8]
	jmp .sigue_ciclo
.corresponde_char_de_padre:
	mov al, [r12 + r8]
.sigue_ciclo:
	mov [r14 + r8], al
	cmp r8, rcx
	jge .termina
	inc r8
	jmp .ciclo

.completo_con_padre:
	mov rsi, r12
	jmp .completo
.completo_con_hijo:
	mov rsi, r13
.completo:
	mov al, [rsi + r8]
	mov [r14 + r8], al
	cmp r8, rcx
	je .termina
	inc r8
	jmp .completo
	
.termina:
	mov al, NULL
	mov [r14 + r8], al ; agrego caracter nulo
	mov rdi, r12
	call free ; libero la memoria del valor del árbol que recibo
	mov rdi, r13
	call free ; libero la memoria del valor del árbol que recibo
	mov rax, r14
	add rsp, 8

	pop rbx
	pop r15
	pop r14
	pop r13
	pop r12
	pop rbp
	ret


str_len:
	
	mov rcx, 0
.ciclo:
	cmp byte [rdi + rcx], NULL
	je .termina
	inc rcx
	jmp .ciclo
.termina:
	mov rax, rcx
	ret

	


