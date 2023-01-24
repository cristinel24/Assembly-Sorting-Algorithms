#include <iostream>
using namespace std;

void cocktailSort(int[], int);

int main()
{
    int v[] = { 3,5,12,54,12,12,65,7,0,-21,67,-65,-69,2,54,32,413,544,121,52452 };
    int v_size = sizeof(v) / sizeof(v[0]);

    const char output_type[] = "%d ";

    _asm {
        lea eax, v
        mov edi, v_size
        xor esi, esi

        push edi
        push eax
        call cocktailSort
        pop eax
        pop edi

        lea ecx, output_type

        _start_for_print :
        cmp esi, edi
            je _end_print
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

            _end_print :
    }
    return 0;
}

void cocktailSort(int a[], int n) {
    _asm {
        mov eax, [ebp + 8]

        xor ecx, ecx ///cl = swapped 
        mov cl, 1

        mov ebx, 0 ///ebx = start
        mov edx, [ebp + 12]
        dec edx ///edx = end

        _start_while:
            cmp cl, 1
            jne _end_while

            mov cl, 0

            mov esi, ebx
            _start_for:
                cmp esi, edx
                jge _end_for

                push ebx
                push ecx

                mov ebx, [eax + 4 * esi]
                mov ecx, [eax + 4 * esi + 4]

                cmp ebx, ecx
                jle _end_if

                mov [eax + 4 * esi], ecx
                mov [eax + 4 * esi + 4], ebx

                pop ecx
                pop ebx

                mov cl, 1
                inc esi
                jmp _start_for

                _end_if:
                    pop ecx
                    pop ebx
                    inc esi
                    jmp _start_for

            _end_for:
            cmp cl, 0
                je _end_while

                mov cl, 1
                dec edx

                mov esi, edx
                dec esi
                _start_for_1:
                    cmp esi, ebx
                    jl _end_for_1
                    
                    push ebx
                    push ecx

                    mov ebx, [eax + 4 * esi]
                    mov ecx, [eax + 4 * esi + 4]

                    cmp ebx, ecx
                    jle _end_if_1

                    mov [eax + 4 * esi + 4], ebx
                    mov [eax + 4 * esi], ecx

                    pop ecx
                    pop ebx

                    mov cl, 1
                    dec esi
                    jmp _start_for_1    

                    _end_if_1:
                        pop ecx
                        pop ebx
                        dec esi
                        jmp _start_for_1   

                _end_for_1:
                inc ebx
                jmp _start_while

        _end_while:
    }
}
