#include <iostream>
using namespace std;

void bogoSort(int[], int);
bool isSorted(int[], int);
void shuffle(int[], int);

int main()
{
    int v[] = { 3,5,65,7,0,-21,67,-65,-69, 70, 24, 21, 15, 23};
    int v_size = sizeof(v) / sizeof(v[0]);

    const char output_type[] = "%d ";

    _asm {
        xor esi, esi
        mov edi, v_size
        lea eax, v
        push edi
        push eax
        call bogoSort
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
void bogoSort(int a[], int n) {
    _asm {
    _start_while:
        xor eax, eax
        push [ebp + 12]
        push [ebp + 8]
        call isSorted
        add esp, 8
        cmp al, 0
        jne _end
        push [ebp + 12]
        push [ebp + 8]
        call shuffle
        add esp, 8
        jmp _start_while

    _end:
    }
}
bool isSorted(int a[], int n) {
    _asm {
        mov eax, [ebp + 8]
        mov edi, [ebp + 12]

        _start_while_1:
            dec edi
            cmp edi, 1
            jl _return_true
            mov ebx, [eax + 4 * edi]
            cmp ebx,  [eax + 4 * edi - 4]
            jge _start_while_1

            mov al, 0
            jmp _end_1


        _return_true:
            mov al, 1

        _end_1:
    
    }
}
void shuffle(int a[], int n) {
    _asm {
        xor esi, esi
        mov edi, [ebp + 8]
        mov ecx, [ebp + 12]

        _start_for:
            cmp esi, ecx
            jge _end_for

            call rand
            xor edx, edx
            mov ecx, [ebp + 12]
            div ecx

            push ecx

            mov ebx, [edi + 4 * esi]
            mov ecx, [edi + 4 * edx]
            mov [edi + 4 * edx], ebx
            mov [edi + 4 * esi], ecx

            pop ecx

            inc esi
            jmp _start_for


        _end_for:
    }
}