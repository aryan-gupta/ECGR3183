Set R1, #4.0
Set R2, #2.0 --a
Fmul R1, R1, R2
Set R3, #2.0 --c
Fmul R1, R1, R3
Set R3, #5.0 --b
Pow R4, R3, #2
Fsub R1, R4, R1
Sqrt R1, R1
Fneg R3, R3
Fadd R0, R3, R1
Fsub R1, R3, R1
Set R3, #2
Fmul R2, R2, R3
Fdiv R0, R0, R2
Get R0
Fdiv R1, R1, R2
Get R1