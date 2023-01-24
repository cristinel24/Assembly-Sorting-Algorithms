#include <iostream>
using namespace std;

void mergeSort(int[], int[], int, int);
void interclasare(int[], int[], int, int);

int main()
{
    int v[] = { 3,5,12,54,12,12,65,7,0,-21,67,-65,-69,2,54,32,413,544,121,52452 };
    int v_size = sizeof(v) / sizeof(v[0]);
    int* b = new int[v_size] {};

    const char output_type[] = "%d "; 

    _asm {
        mov edi, v_size
        dec edi
        xor esi, esi
        
        mov ebx, b
        lea eax, v

        push edi
        push esi
        push ebx
        push eax
        call mergeSort
        pop eax
        pop ebx
        pop esi
        pop edi
        inc edi

        lea ecx, output_type

        _start_for_print:
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

    delete b;

    return 0;
}

void mergeSort(int a[], int b[], int st, int dr) {
    _asm {
        mov esi, [ebp + 16]
        mov edi, [ebp + 20]

        cmp esi, edi
        jge _end_if

        mov eax, esi
        add eax, edi
        shr eax, 1

        push eax
        push esi
        push [ebp + 12]
        push [ebp + 8]
        call mergeSort
        add esp, 8
        pop esi
        pop eax

        push edi
        inc eax
        push eax
        push[ebp + 12]
        push[ebp + 8]
        call mergeSort
        add esp, 8
        pop eax
        pop edi

        push edi
        push esi
        push[ebp + 12]
        push[ebp + 8]
        call interclasare
        add esp, 8
        pop esi
        pop edi

        _end_if:
    }
}

void interclasare(int a[], int b[], int st, int dr) {
    _asm {
        mov eax, [ebp + 16]
        add eax, [ebp + 20]
        shr eax, 1 // eax = mij 

        mov esi, [ebp + 16] ///esi = i = st
        mov ecx ,esi ///ecx = k = st

        push eax
        inc eax
        mov edi, eax /// edi = j = mij + 1
        pop eax

        _start_while:
            
            cmp esi, eax
            jg _end_while
            cmp edi, [ebp + 20]
            jg _end_while
            push eax
            mov ebx, [ebp + 8]
            mov eax, [ebx + 4 * esi] //eax = a[i]
            mov ebx, [ebx + 4 * edi] //ebx = a[j]
       
            mov edx, [ebp + 12]    
            //mov edx, [edx + 4 * ecx] ///edx = b[k]

            cmp eax, ebx
            jge _else
            mov [edx + 4 * ecx], eax
            inc esi
            inc ecx
            pop eax
            jmp _start_while

            _else:
                mov [edx + 4 * ecx], ebx
                inc edi
                inc ecx
                pop eax
                jmp _start_while

        _end_while:

        mov eax, [ebp + 16]
        add eax, [ebp + 20]
        shr eax, 1 // eax = mij 

        mov edx, [ebp + 12]    

        _start_while_1:
            cmp esi, eax
            jg _end_while_1

            mov eax, [ebp + 8]
            mov eax, [eax + 4 * esi] //eax = a[i]

            mov [edx + 4 * ecx], eax
            inc ecx
            inc esi
            jmp _start_while_1

        _end_while_1:

        mov ebx, [ebp + 8]
        
        _start_while_2:
            cmp edi, [ebp + 20]
            jg _end_while_2

           
            mov eax, [ebx + 4 * edi] //eax = a[j]

            mov [edx + 4 * ecx], eax
            inc ecx
            inc edi
            jmp _start_while_2

        _end_while_2:        

        mov eax, [ebp + 8]
        mov ebx, [ebp + 12]

        mov esi, [ebp + 16]
        mov edi, [ebp + 20]

        _start_for:
            cmp esi, edi
            jg _end_for
            mov ecx, [eax + 4 * esi]
            mov edx, [ebx + 4 * esi]
            mov [eax + 4 * esi], edx
            mov [ebx + 4 * esi], ecx
            inc esi
            jmp _start_for

        _end_for:
            
    }
}