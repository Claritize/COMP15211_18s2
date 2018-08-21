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
	li    $t0, 1 #load 1 into register for comparison
	bgt   $a1, $t0, max_rec_case #if current length > 1 then call recursive
	lw    $v0, ($a0) #otherwise end of recursion and store first value into return
	j     max_return #jump to return code

	# recursive case
max_rec_case:
	# int max_so_far = max(&a[1], length-1);
	addi  $a0, $a0, 4 #add 4bytes to array pointer
	addi  $a1, $a1, -1 #subtract 1 from the length
	jal   max #call recursive
	move  $t0, $v0 #store the return value into temp register
	# return (a[0] > max_so_far) ? a[0] : max_so_far;
	ble   $s1, $t0, return_max #if current value is smaller than return value, we use return value
	move  $v0, $s1 #otherwise we return the current head
	j     max_return #jump to stack restoration to skip the else statement

#else statement
return_max:
	move  $v0, $t0
max_return:
	# epilogue
	lw    $s2, -16($fp)
	lw    $s1, -12($fp)
	lw    $s0, -18($fp)
	lw    $ra, -4($fp)
	lw    $fp, ($fp)
	la    $sp, 4($fp)
	j     $ra