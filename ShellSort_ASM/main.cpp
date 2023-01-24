#include <iostream>
using namespace std;

void shellSort(int[], int);

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
        call shellSort
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
void shellSort(int a[], int n) {
    _asm {
        mov ebx, [ebp + 8]
        mov ecx, [ebp + 12]
        shr ecx, 1 ///ecx = gap

        _start_for:
            cmp ecx, 0
            jle _end_for

            mov esi, ecx
            _start_for_1:
                cmp esi, [ebp + 12]
                jge _end_for_1
                mov edx, [ebx + 4 * esi] ///edx=temp=a[i]
                
                mov edi, esi
                _start_for_2:
                    cmp edi, ecx
                    jl _end_for_2
                    mov eax, edi
                    sub eax, ecx ///edx=j-gap
                    mov eax, [ebx + 4 * eax] ///a[j-gap]
                    cmp eax, edx
                    jle _end_for_2

                    mov [ebx + 4 * edi], eax
                    sub edi, ecx
                    jmp _start_for_2
    
                _end_for_2:
                    mov [ebx + 4 * edi], edx
                    inc esi
                    jmp _start_for_1

            _end_for_1:
                shr ecx, 1
                jmp _start_for
    
        _end_for:
    }
}