default rel

global function: function
global Trapeze: function
global Simpson: function

extern sqrt                                             
extern cos                                              
extern sin                                             

SECTION .text                          

function:; Function begin
        endbr64                                         
        push    rbp                                    
        mov     rbp, rsp                               
        sub     rsp, 16                               
        movsd   qword [rbp-8H], xmm0                    
        mov     dword [rbp-0CH], edi                    
        cmp     dword [rbp-0CH], 4                     
        ja      switchType         ; cases                         
        mov     eax, dword [rbp-0CH]                   
        lea     rdx, [rax*4]                            
        lea     rax, [rel swithcFunc]                       
        mov     eax, dword [rdx+rax]                    
        cdqe                                            
        lea     rdx, [rel swithcFunc]               
        add     rax, rdx 

        jmp     rax 

sinFunc:  mov     rax, qword [rbp-8H] 
        movq    xmm0, rax 
        call    sin   
        movq    rax, xmm0 
        jmp     switchType 

cosFunc:  mov     rax, qword [rbp-8H] 
        movq    xmm0, rax 
        call    cos   
        movq    rax, xmm0  
        jmp     switchType 

parabolaFunc:  movsd   xmm0, qword [rbp-8H] 
        mulsd   xmm0, xmm0 
        movq    rax, xmm0  
        jmp     switchType  

linFunc:  mov     rax, qword [rbp-8H] 
        jmp     switchType    

sqrtFunc:  mov     rax, qword [rbp-8H]  
        movq    xmm0, rax   
        call    sqrt  
        movq    rax, xmm0  
        jmp     switchType      

switchType:  
        movq    xmm0, rax 
        leave
        ret 

Trapeze:; Function begin
        endbr64       
        push    rbp        
        mov     rbp, rsp    
        sub     rsp, 64                
        movsd   qword [rbp-28H], xmm0              
        movsd   qword [rbp-30H], xmm1     
        mov     dword [rbp-34H], edi  
        movsd   xmm0, qword [rbp-30H] 
        subsd   xmm0, qword [rbp-28H]   
        movsd   xmm1, qword [rel retREsult]
        divsd   xmm0, xmm1      
        movsd   qword [rbp-8H], xmm0                 
        mov     edx, dword [rbp-34H]                 
        mov     rax, qword [rbp-28H]                   
        mov     edi, edx            
        movq    xmm0, rax                              
        call    function               
        movsd   qword [rbp-40H], xmm0                   
        mov     edx, dword [rbp-34H]    
        mov     rax, qword [rbp-30H]             
        mov     edi, edx                  
        movq    xmm0, rax                        
        call    function                            
        addsd   xmm0, qword [rbp-40H]   
        movsd   qword [rbp-10H], xmm0      
        mov     dword [rbp-14H], 1  
        jmp     getSum  

funcCalculation:  pxor    xmm0, xmm0     
        cvtsi2sd xmm0, dword [rbp-14H]               
        mulsd   xmm0, qword [rbp-8H]      
        addsd   xmm0, qword [rbp-28H]         
        movq    rax, xmm0                            
        mov     edx, dword [rbp-34H]        
        mov     edi, edx                    
        movq    xmm0, rax              
        call    function             
        addsd   xmm0, xmm0           
        movsd   xmm1, qword [rbp-10H]              
        addsd   xmm0, xmm1                        
        movsd   qword [rbp-10H], xmm0    
        add     dword [rbp-14H], 1   
getSum:  cmp     dword [rbp-14H], 99999         
        jle     funcCalculation                   
        movsd   xmm0, qword [rbp-8H]        
        movsd   xmm1, qword [rel ?_013]             
        divsd   xmm0, xmm1                          
        movsd   xmm1, qword [rbp-10H]        
        mulsd   xmm0, xmm1                         
        movsd   qword [rbp-10H], xmm0             
        movsd   xmm0, qword [rbp-10H]                 
        movq    rax, xmm0                             
        movq    xmm0, rax 
        leave 
        ret  


Simpson:; Function begin
        endbr64          
        push    rbp
        mov     rbp, rsp 
        sub     rsp, 64 
        movsd   qword [rbp-28H], xmm0  
        movsd   qword [rbp-30H], xmm1 
        mov     dword [rbp-34H], edi 
        movsd   xmm0, qword [rbp-30H]                  
        subsd   xmm0, qword [rbp-28H]  
        movsd   xmm1, qword [rel retREsult]  
        divsd   xmm0, xmm1            
        movsd   qword [rbp-8H], xmm0               
        mov     edx, dword [rbp-34H]               
        mov     rax, qword [rbp-28H]     
        mov     edi, edx           
        movq    xmm0, rax    
        call    function                            
        movsd   qword [rbp-40H], xmm0 
        mov     edx, dword [rbp-34H]  
        mov     rax, qword [rbp-30H]  
        mov     edi, edx          
        movq    xmm0, rax        
        call    function             
        addsd   xmm0, qword [rbp-40H]            
        movsd   qword [rbp-10H], xmm0    
        mov     dword [rbp-18H], 1   
        jmp     getSumSimpson   

?_009:  mov     eax, dword [rbp-18H]
        cdq                 
        shr     edx, 31 
        add     eax, edx    
        and     eax, 01H                   
        sub     eax, edx  
        add     eax, 1      
        add     eax, eax      
        mov     dword [rbp-14H], eax   
        pxor    xmm3, xmm3     
        cvtsi2sd xmm3, dword [rbp-14H]   
        movsd   qword [rbp-40H], xmm3  
        pxor    xmm0, xmm0           
        cvtsi2sd xmm0, dword [rbp-18H]  
        mulsd   xmm0, qword [rbp-8H]   
        addsd   xmm0, qword [rbp-28H]
        movq    rax, xmm0                  
        mov     edx, dword [rbp-34H]  
        mov     edi, edx  
        movq    xmm0, rax  
        call    function   
        mulsd   xmm0, qword [rbp-40H] 
        movsd   xmm1, qword [rbp-10H] 
        addsd   xmm0, xmm1      
        movsd   qword [rbp-10H], xmm0  
        add     dword [rbp-18H], 1    

funcCalculation1:  cmp     dword [rbp-18H], 99999  
        jle     ?_009        
        movsd   xmm0, qword [rbp-8H]
        movsd   xmm1, qword [rel ?_014]
        divsd   xmm0, xmm1         
        movsd   xmm1, qword [rbp-10H]    
        mulsd   xmm0, xmm1  
        movsd   qword [rbp-10H], xmm0   
        movsd   xmm0, qword [rbp-10H]   
        movq    rax, xmm0                   
        movq    xmm0, rax                           
        leave                                     
        ret                                             

SECTION .data   


SECTION .bss


SECTION .rodata 

swithcFunc:                                              
        dd sinFunc-$        
        dd cosFunc-$+4H   
        dd parabolaFunc-$+8H  
        dd linFunc-$+0CH   
        dd sqrtFunc-$+10H  

        dd swithcFunc-swithcFunc  

retResult:  dq 40F86A0000000000H   
  



