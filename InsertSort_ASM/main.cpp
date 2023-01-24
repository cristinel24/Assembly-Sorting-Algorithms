#include <iostream>
using namespace std;

void insertSort(int[], int);

int main()
{
    int v[] = { 3,5,12,54,12,12,65,7,0,-21,67,-65,-69,2,54,32,413,544,121,52452 };
    int v_size = sizeof(v) / sizeof(v[0]);

    const char output_type[] = "%d ";

    _asm {
        lea eax, v
        mov esi, v_size

        push esi
        push eax
        call insertSort
        pop eax
        pop esi

        lea ecx, output_type
        mov edi, esi
        xor esi, esi
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

void insertSort(int a[], int n) {
    _asm {
        mov esi, 1

        mov eax, [ebp + 8]

        _start_for:
            cmp esi, [ebp + 12]
            jge _end_for

            mov ebx, [eax + 4 * esi] ///ebx = temp = a[i]
            mov edi, esi
            dec edi ///edi = j = i - 1

            _start_while:
                cmp edi, 0
                jl _end_while
                mov ecx, [eax + 4 * edi] ///ecx = a[j]
                cmp ecx, ebx
                jle _end_while

                push edi
                inc edi
                mov [eax + 4 * edi], ecx
                pop edi
                dec edi
                jmp _start_while
    
            _end_while:
                inc edi
                mov ecx, [eax + 4 * edi]
                cmp ecx, ebx
                je _end_if
                mov [eax + 4 * edi], ebx
            
            _end_if:
                inc esi
                jmp _start_for

        _end_for:
    }
}