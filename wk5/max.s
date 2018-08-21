# Register usage:
#	- `a' is in $a0
#	- `length' is in $a1
#	- `max_so_far' is in $v0

.text
.globl main
max:
	# prologue
	sw    $fp, -4($sp)
	la    $fp, -4($sp)
	sw    $ra, -8($sp)
	sw    $s0, -12($sp)
	sw    $s1, -16($sp)
	sw    $s2, -20($sp)
	addi  $sp, $sp, -24

	lw    $s1, ($a0) #storing the first item in array

	# base case
max_base_case:
	# if (length == 1) return a[0];

	
	# recursive case
max_rec_case:
	# int max_so_far = max(&a[1], length-1);

#else statement
return_max:
	
max_return:
	# epilogue
	lw    $s2, -16($fp)
	lw    $s1, -12($fp)
	lw    $s0, -18($fp)
	lw    $ra, -4($fp)
	lw    $fp, ($fp)
	la    $sp, 4($fp)
	j     $ra