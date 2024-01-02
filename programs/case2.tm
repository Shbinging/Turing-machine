#Q = {start,copy_u,handle_c,two_to_left,compare_u,false_clean,false_clean_to_head,true_clean,true_clean_to_head,true_t,true_tr,true_tru,true_true,false_f,false_fa,false_fal,false_fals,false_false,finish}

#S = {a,b,c}

#G = {a,b,c,_,f,l,s,e,t,r,u,e}

#q0 = start

#B = _

#F = {true_true}

#N = 2

;start:
start __ __ ** false_f
start a_ a_ ** copy_u
start b_ b_ ** copy_u
start c_ c_ ** handle_c

;copy_u
copy_u a_ aa rr copy_u
copy_u b_ bb rr copy_u
copy_u c_ c_ ** handle_c
copy_u __ __ ** false_clean

;handle_c
handle_c c_ c_ *l two_to_left

;two_to_left
two_to_left ** ** *l two_to_left
two_to_left *_ *_ rr compare_u

;compare_u
compare_u __ __ ll true_clean
compare_u aa aa rr compare_u
compare_u bb bb rr compare_u
compare_u ab ab ** false_clean
compare_u ba ba ** false_clean
compare_u a_ a_ ** false_clean
compare_u b_ b_ ** false_clean
compare_u _a _a ** false_clean
compare_u _b _b ** false_clean

;false_clean
false_clean __ __ ll false_clean_to_head
false_clean ** ** rr false_clean
false_clean *_ *_ r* false_clean
false_clean _* _* *r false_clean

;true_clean
true_clean __ __ ll true_clean_to_head
true_clean ** ** rr true_clean
true_clean *_ *_ r* true_clean
true_clean _* _* *r true_clean

;false_clean_to_head
false_clean_to_head __ __ rr false_f
false_clean_to_head ** __ ll false_clean_to_head
false_clean_to_head *_ __ l* false_clean_to_head
false_clean_to_head _* __ *l false_clean_to_head

;true_clean_to_head
true_clean_to_head __ __ rr true_t
true_clean_to_head ** __ ll true_clean_to_head
true_clean_to_head *_ __ l* true_clean_to_head
true_clean_to_head _* __ *l true_clean_to_head

;true_t
true_t __ t_ r* true_tr

;true_tr
true_tr __ r_ r* true_tru

;true_tru
true_tru __ u_ r* true_true

;true_true
true_true __ e_ r* finish

;false_f
false_f __ f_ r* false_fa

;false_fa
false_fa __ a_ r* false_fal

;false_fal
false_fal __ l_ r* false_fals

;false_fals
false_fals __ s_ r* false_false

;false_false
false_false __ e_ r* finish
