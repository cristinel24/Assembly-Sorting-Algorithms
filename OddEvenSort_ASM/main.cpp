#include <iostream>
using namespace std;

void oddEvenSort(int [], int);

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
        call oddEvenSort
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
void oddEvenSort(int a[], int n) {
    _asm {
        xor ecx, ecx
        mov edx, [ebp + 8]
        
        _start_while:
            cmp cl, 1
            je _end_while
            
            mov cl, 1

            mov esi, 1
            mov ebx, [ebp + 12]
            sub ebx, 2

            _start_for:
                cmp esi, ebx
                jg _end_for
                
                mov eax, [edx + 4 * esi]
                mov edi, [edx + 4 * esi + 4]

                cmp eax, edi
                jle _end_if

                mov [edx + 4 * esi + 4], eax
                mov [edx + 4 * esi], edi
                mov cl, 0

                _end_if:
                add esi, 2
                jmp _start_for
    
    
            _end_for:

            xor esi, esi
            mov ebx, [ebp + 12]
            sub ebx, 2

            _start_for_1:
                    cmp esi, ebx
                    jg _end_for_1

                    mov eax, [edx + 4 * esi]
                    mov edi, [edx + 4 * esi + 4]

                    cmp eax, edi
                    jle _end_if_1

                    mov [edx + 4 * esi + 4], eax
                    mov [edx + 4 * esi], edi
                    mov cl, 0

                    _end_if_1:
                    add esi, 2
                    jmp _start_for_1


           _end_for_1:
                jmp _start_while

        _end_while:
    }
}