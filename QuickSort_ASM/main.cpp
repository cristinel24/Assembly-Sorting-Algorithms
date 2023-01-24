#include <iostream>
using namespace std;

void quickSort(int[], int, int);
int partition(int[], int, int);

int main()
{
    int v[] = { 3,5,12,54,12,12,65,7,0,-21,67,-65,-69,2,54,32,413,544,121,52452 };
    int v_size = sizeof(v) / sizeof(v[0]);

    const char output_type[] = "%d ";

    _asm {
        lea eax, v
        mov edi, v_size
        dec edi
        xor esi, esi

        push edi
        push esi
        push eax
        call quickSort
        pop eax
        pop esi
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
void quickSort(int a[], int low , int high) {
    _asm {
        mov esi, [ebp + 12]

        cmp esi, [ebp + 16]
        jge _end_if

            push [ebp + 16]
            push [ebp + 12]
            push [ebp + 8]
            call partition
            add esp, 12
            
            mov edi, eax

            push edi
            dec edi
            push edi
            push [ebp + 12]
            push [ebp + 8]
            call quickSort
            add esp, 12

            pop edi
            inc edi

            push [ebp + 16]
            push edi
            push [ebp + 8]
            call quickSort
            add esp, 12

        _end_if:
    }
}
int partition(int a[], int low, int high) {
    _asm {
        mov edx, [ebp + 8]
        mov ecx, [ebp + 16]
        mov ebx, [edx + 4 * ecx] ///ebx= pivot = a[high]

        mov esi, [ebp + 12]
        dec esi                 ///esi = i = low - 1

        mov edi, [ebp + 12]     ///edi = j = low

        _start_for:
            cmp edi, [ebp + 16]
            jge _end_for
            
            mov edx, [ebp + 8]
            mov edx, [edx + 4 * edi]    ///edx = a[j]

            cmp edx, ebx
            jge _end_if

            inc esi

            push eax
            push ecx

            mov edx, [ebp + 8]
            mov eax, [edx + 4 * esi]
            mov ecx, [edx + 4 * edi]
            mov [edx + 4 * esi], ecx
            mov [edx + 4 * edi], eax

            pop ecx
            pop eax

            _end_if:
                inc edi
                jmp _start_for

        _end_for:

        inc esi
        mov edi, [ebp + 16]
        mov edx, [ebp + 8]

        mov eax, [edx + 4 * esi] ///eax= a[i]
        mov ebx, [edx + 4 * edi]
        mov [edx + 4 * esi], ebx
        mov [edx + 4 * edi], eax

        mov eax, esi
    }
}