#include <iostream>
using namespace std;

int findMax(int [], int);
void flip(int[], int);
void pancakeSort(int arr[], int);

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
        call pancakeSort
        pop eax
        pop edi

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
void flip(int a[], int i) {
    _asm {
        mov eax, [ebp + 8]
        xor esi, esi
        mov edi, [ebp + 12]

        _start_while:
            cmp esi, edi
            jge _end_while

            mov ecx, [eax + 4 * esi]
            mov ebx, [eax + 4 * edi]

            mov [eax + 4 * esi], ebx
            mov [eax + 4 * edi], ecx

            inc esi
            dec edi
            jmp _start_while

        _end_while:
    }
}

int findMax(int a[], int n) {
    _asm {
        xor eax, eax
        xor esi, esi
        mov edx, [ebp + 8]
        
        _start_for:
            cmp esi, [ebp + 12]
            jge _end_for

            mov ebx, [edx + 4 * esi]
            mov ecx, [edx + 4 * eax]

            cmp ebx, ecx
            jle _end_if

            mov eax, esi

            _end_if:
            inc esi
            jmp _start_for

        _end_for:
    }
}

void pancakeSort(int a[], int n) {
    _asm {
        mov esi, [ebp + 12]

        _start_for:
            cmp esi, 1
            jle _end_for

            push esi
            push [ebp + 8]
            call findMax
            add esp, 4
            pop esi

            mov ebx, esi
            dec ebx

            cmp eax, ebx
            je _end_if

            push eax
            push [ebp + 8]
            call flip
            add esp, 4
            pop eax

            push ebx
            push [ebp + 8]
            call flip
            add esp, 4
            pop ebx

            _end_if:
                dec esi
                jmp _start_for
    
        _end_for:
    }
}