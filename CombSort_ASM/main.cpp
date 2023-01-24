#include <iostream>
using namespace std;

void combSort(int[], int);
int getNextGap(int);

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
        call combSort
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
int getNextGap(int gap) {
    _asm {
        mov eax, [ebp + 8]
        xor edx, edx
        mov ecx, 10
        mul ecx
        mov ecx, 13
        div ecx

        cmp eax, 1
        jge _return
        mov eax, 1

        _return:
    }
}

void combSort(int a[], int n) {
    _asm {
        mov eax, [ebp + 12] ///eax = gap
        mov bl, 1 

        _start_while:
            cmp eax, 1
            jne _ok
            cmp bl, 1
            jne _end_while
            _ok:

            push eax
            call getNextGap
            add esp, 4

            mov bl, 0

            mov edx, [ebp + 12]
            sub edx, eax
            xor esi, esi
            
            _start_for:
                cmp esi, edx
                jge _end_for

                push eax
                push ebx
                push ecx
                mov ecx, [ebp + 8]
                mov eax, [ecx + 4 * esi]
                mov ebx, [ecx + 4 * esi + 4]

                cmp eax, ebx
                jle _end_if
                mov [ecx + 4 * esi], ebx
                mov [ecx + 4 * esi + 4], eax
                pop ecx
                pop ebx
                pop eax
                mov bl, 1
                inc esi
                jmp _start_for

                _end_if:
                    pop ecx
                    pop ebx
                    pop eax
                    inc esi
                    jmp _start_for


    
            _end_for:
                jmp _start_while

        _end_while:
    }
}