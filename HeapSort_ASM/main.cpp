#include <iostream>
using namespace std;

void heapsort(int[], int);
void insereazaAlTlea(int[], int, int);

int main()
{
    int v[] = { 43,12,6,1,0,-60,-4,45,132,-43,-2134 };
    int lg = sizeof(v) / sizeof(v[0]);

    const char output_type[] = "%d ";
    
    _asm {
        lea eax, v
        mov ebx, lg
        push ebx
        push eax
        call heapsort
        pop eax
        pop ebx

        xor esi, esi
        mov edi, ebx
        
        lea ecx, output_type

        _start_for_print:
            cmp esi, edi
            je _end_for_print

            mov ebx, [eax + 4 * esi]

            push eax
            push ebx
            push ecx
            call printf
            pop ecx
            add esp, 4
            pop eax

            inc esi
            jmp _start_for_print

        _end_for_print:
    }
   
    return 0;
}

void heapsort(int v[], int n) {
    _asm {
       mov esi, [ebp + 8]
       mov eax, [ebp + 12]
       mov edx, 0
       dec eax
       mov ecx, 2
       div ecx
       mov ecx, eax ///ecx=t=(n-1)/2

       _start_for:
           cmp ecx, 0
           jl _end_for

           mov edx, [ebp + 12]
           push ecx
           push edx
           push esi
           call insereazaAlTlea
           add esp, 8
               
           pop ecx
           dec ecx
           jmp _start_for

       _end_for:

       mov ecx, [ebp + 12]
       dec ecx ///ecx = r = (n-1)
        
       _start_while:
            cmp ecx,0
            jle _end_while
            
            mov eax, [esi]
            mov ebx, [esi + 4 * ecx]
            mov [esi + 4 * ecx], eax
            mov [esi], ebx

            mov ebx, 0
            push ebx
            push ecx
            push esi
            call insereazaAlTlea
            add esp, 4
            pop ecx
            add esp, 4

            dec ecx
            jmp _start_while

       _end_while:
    }
}

void insereazaAlTlea(int a[], int n, int t) {
    _asm {
        mov esi, [ebp + 8]
        mov ebx, [ebp + 16] // ebx = j = t
        mov ecx, 0          //ecx= heap = false
        
        _start_while_1:

            mov eax, ebx
            mov edx, 2
            mul edx
            inc eax

            cmp eax, [ebp + 12]
            jge _end_while_1

            cmp ecx, 0
            jne _end_while_1

            mov edi, eax ///edi = k = 2*j+1

            mov eax, [ebp + 12]
            dec eax

            cmp edi, eax
            jge _salt
            mov eax, [esi + 4 * edi]
            mov edx, [esi + 4 * edi + 4]
            cmp eax, edx
            jge _salt

            inc edi

            _salt:
                mov eax, [esi + 4 * ebx]
                mov edx, [esi + 4 * edi]
                cmp eax, edx
                jge _else_if

                mov [esi + 4 * ebx], edx
                mov [esi + 4 * edi], eax

                mov ebx, edi
                jmp _dupa_else
    
    
            _else_if:
                mov ecx, 1

            _dupa_else:
                jmp _start_while_1
      
        _end_while_1:
    }
}