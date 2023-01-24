#include <iostream>
using namespace std;

void stoogeSort(int[], int, int);

int main()
{
    int v[] = { 3,5,12,54,12,12,65,7,0,-21,67,-65,-69,2,54,32,413,544,121,52452 };
    int v_size = sizeof(v) / sizeof(v[0]);

    const char output_type[] = "%d ";

    _asm {
        lea eax, v
        mov edi, v_size
        xor esi, esi
        dec edi

        push edi
        push esi
        push eax
        call stoogeSort
        pop eax
        add esp, 8

        xor esi, esi
        mov edi, v_size

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
void stoogeSort(int a[], int l, int h) {
    _asm {
        mov esi, [ebp + 12]
        mov edi, [ebp + 16]

        cmp esi, edi
        jge _end

        mov eax, [ebp + 8]

        mov ebx, [eax + 4 * esi]
        mov ecx, [eax + 4 * edi]
        cmp ebx, ecx
        jle _end_if

        mov [eax + 4 * edi], ebx
        mov [eax + 4 * esi], ecx

        _end_if:

        mov eax, edi
        sub eax, esi
        inc eax
        
        cmp eax, 2
        jle _end_if_1

        xor edx, edx
        mov ecx, 3
        div ecx

        mov ecx, eax ///ecx = t 

        mov ebx, [ebp + 16]
        sub ebx, ecx ///ebx=h-t
        push ecx
        push ebx
        push esi
        push [ebp + 8]
        call stoogeSort
        pop eax
        pop esi
        pop ebx
        pop ecx

        mov ebx, [ebp + 12]
        add ebx, ecx //ebx=l+t
        push ecx
        push edi
        push ebx
        push [ebp + 8]
        call stoogeSort
        pop eax
        pop ebx
        pop edi
        pop ecx

        mov ebx, [ebp + 16]
        sub ebx, ecx ///ebx=h-t
        push ecx
        push ebx
        push esi
        push [ebp + 8]
        call stoogeSort
        pop eax
        pop esi
        pop ebx
        pop ecx

    _end_if_1:

     _end:
    }
}