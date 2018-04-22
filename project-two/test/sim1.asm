Set R1, #30.0 --angle of inclined plane
--convert to radians
Set R2, #3.14159265 --pi
Fmul R1, R1, R2
Set R2, #180.0
Fdiv R1, R1, R2
--compute equation
Cos R2, R1
Set R3, #0.4
FMul R2, R2, R3
Sin R1, R1
Fadd R1, R1, R2
Set R2, #100.0 --mass of crate
Fmul R1, R1, R2
Set R2, #9.81 --acceleration of gravity
Fmul R1, R1, R2
Get R1