#include <iostream>
using namespace std;

void bubbleSort(int[], int);

int main()
{
    int v[] = { 3,5,12,54,12,12,65,7,0,-21,67,-65,-69,2,54,32,413,544,121,52452 };
    int v_size = sizeof(v) / sizeof(v[0]);

    const char output_type[] = "%d ";

    _asm {
        lea eax, v
        mov edi, v_size
        push edi
        push eax
        call bubbleSort
        pop eax
        pop edi
    
        xor esi, esi

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
void bubbleSort(int a[], int n) {
    _asm {
        xor esi, esi
        mov ecx, [ebp + 12]
        dec ecx /// ecx = n -1
        
        mov eax, [ebp + 8]

        _start_for:
            cmp esi, ecx
            jge _end_for

            xor edi, edi
            mov ebx, ecx
            sub ebx, esi ///ebx= n - i - 1
            
            _start_for_1:
                cmp edi, ebx
                jge _end_for_1

                push ecx
                push edx

                mov ecx,[eax + 4 * edi]
                mov edx,[eax + 4 * edi + 4]

                cmp ecx, edx
                jle _end_if

                mov [eax + 4 * edi + 4], ecx
                mov [eax + 4 * edi], edx
                pop edx
                pop ecx
                inc edi
                jmp _start_for_1

            _end_if:
                pop edx
                pop ecx
                inc edi
                jmp _start_for_1

        _end_for_1:
            inc esi
            jmp _start_for

        _end_for:
    }
}