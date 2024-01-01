#Q = {start,copy_a,to_left,clean_all,copy_b,one_to_left,two_to_right_first,multiply_b_first,multiply_b,two_to_right,finish_two,wi,wIl,wIle,wIleg,wIlega,wIlegal,wIlegal_,wIlegal_I,wIlegal_In,wIlegal_Inp,wIlegal_Inpu,wIlegal_Input}
#S = {a,b}
#G = {a,b,I,l,e,g,a,_,n,p,u,t}
#q0 = start
#B = _
#F = {finish_two}
#N = 2
;start: check if input meet requirement num(a) > 0
start a_ a_ ** copy_a
start b_ b_ ** to_left
start __ __ ** to_left

;copy_a: copy substring a of input string from tape1 to tape2
copy_a a_ aa rr copy_a
copy_a b_ b_ ** copy_b
copy_a __ __ ll to_left

;to_left: move tape1 and tape2 cursor to left
to_left ** __ ll to_left
to_left *_ __ ll to_left
to_left __ __ rr wi

;Illegal_Input
wi __ I_ r* wIl
wi *_ I_ r* wIl
wIl __ l_ r* wIle
wIl *_ l_ r* wIle
wIle __ e_ r* wIleg
wIle *_ e_ r* wIleg
wIleg __ g_ r* wIlega
wIleg *_ g_ r* wIlega
wIlega __ a_ r* wIlegal
wIlega *_ a_ r* wIlegal
wIlegal __ l_ r* wIlegal_
wIlegal *_ l_ r* wIlegal_
wIlegal_ __ __ r* wIlegal_I
wIlegal_ *_ __ r* wIlegal_I
wIlegal_I __ I_ r* wIlegal_In
wIlegal_I *_ I_ r* wIlegal_In
wIlegal_In __ n_ r* wIlegal_Inp
wIlegal_In *_ n_ r* wIlegal_Inp
wIlegal_Inp __ p_ r* wIlegal_Inpu
wIlegal_Inp *_ p_ r* wIlegal_Inpu
wIlegal_Inpu __ u_ r* wIlegal_Input
wIlegal_Inpu *_ u_ r* wIlegal_Input
wIlegal_Input __ t_ r* clean_all
wIlegal_Input *_ t_ r* clean_all

;clean_all: clean tape1 and tape2
clean_all ** __ rr clean_all
clean_all _* __ *r clean_all
clean_all *_ *_ r* clean_all

;copy_b: copy substring b of input string from tape1 to tape2
copy_b b_ bb rr copy_b
copy_b a_ a_ ** to_left
copy_b __ __ ll one_to_left


;one_to_left: move tape1 cursor to left most
one_to_left ** ** l* one_to_left
one_to_left _* _* r* multiply_b_first

;multiply_b_first
multiply_b_first *b c_ rl multiply_b
multiply_b_first _b c_ rl multiply_b
multiply_b *a *b *l two_to_right_first
multiply_b _a _b *l two_to_right_first
multiply_b *_ *_ lr finish_two
multiply_b __ __ lr finish_two

;multiply_b: move b to left, write c
multiply_b *b cb rl multiply_b
multiply_b _b cb rl multiply_b
multiply_b *a *b *l two_to_right_first
multiply_b _a _b *l two_to_right_first
multiply_b *_ *_ lr finish_two
multiply_b __ __ lr finish_two

;two_to_right_first:
two_to_right_first *a *a *r two_to_right
two_to_right_first _a _a *r two_to_right
two_to_right_first *_ *_ *r finish_two
two_to_right_first __ __ *r finish_two

;two_to_right: move tape2 cursor to right most
two_to_right ** ** *r two_to_right
two_to_right _* _* *r two_to_right
two_to_right *_ *_ *l multiply_b_first
two_to_right __ __ *l multiply_b_first

;finish_two: clean b in the tape2
finish_two *b __ rr finish_two
finish_two _b __ *r finish_two

