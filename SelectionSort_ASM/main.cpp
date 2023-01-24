#include <iostream>
using namespace std;

void selectionSort(int[], int);

int main()
{
    int v[] = { 3,5,12,54,12,12,65,7,0,-21,67,-65,-69,2,54,32,413,544,121,52452 };
    int v_size = sizeof(v) / sizeof(v[0]);

    const char output_type[] = "%d ";

    _asm {
        xor esi, esi
        mov edi, v_size
        lea eax, v
        push edi
        push eax
        call selectionSort
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

       _end_print:
    }

    return 0;
}
void selectionSort(int a[], int n) {
    _asm {
        mov edx, [ebp + 8]
        xor esi, esi
        mov ecx, [ebp + 12]
        dec ecx

        _start_for:
            cmp esi, ecx
            jge _end_for
            mov ebx, esi ///ebx= min_idx
            
            mov edi, esi
            inc edi

            _start_for_1:
                cmp edi, [ebp + 12]
                jge _end_for_1
                
                push ecx
                mov eax, [edx + 4 * edi]
                mov ecx, [edx + 4 * ebx]

                cmp eax, ecx
                jge _reia_for
                
                pop ecx
                mov ebx, edi
                inc edi
                jmp _start_for_1

            _reia_for:
                pop ecx
                inc edi
                jmp _start_for_1
                
            _end_for_1:
                cmp ebx, esi
                je _end_if
                push ecx
                mov eax, [edx + 4 * ebx]
                mov ecx, [edx + 4 * esi]
                mov [edx + 4 * ebx], ecx
                mov [edx + 4 * esi], eax
                pop ecx

            _end_if:
                inc esi
                jmp _start_for

        _end_for:
    }
}