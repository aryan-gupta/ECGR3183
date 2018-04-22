Set R1, #30 --angle of inclined plane
--convert to radians
Set R2, #3 --pi
Fmul R1, R1, R2
Set R2, #180
Fdiv R1, R1, R2
--compute equation
Cos R2, R1
Set R3, #1
FMul R2, R2, R3
Sin R1, R1
Fadd R1, R1, R2
Set R2, #100 --mass of crate
Fmul R1, R1, R2
Set R2, #10 --acceleration of gravity
Fmul R1, R1, R2
Get R1