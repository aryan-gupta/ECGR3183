Set R0, #2.3 --m1
Set R1, #5.7 --m2
Fmul R0, R0, R1
Set R1, #13.2 --r
Pow R1, R1, #2
Fdiv R0, R0, R1
Set R1, #6.673E-11 --gravitational constant
Fmul R0, R0, R1
Get R0