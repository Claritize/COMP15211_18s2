# Register usage:
#	- `a' is in $s0
#	- `a[0]' is in $s1
#	- `length' is in $s2
#	- `max_so_far' is in $t0
max:
	# prologue
	sw    $fp, -4($sp)
	la    $fp, -4($sp)
	sw    $ra, -8($sp)
	sw    $s0, -12($sp)
	sw    $s1, -16($sp)
	sw    $s2, -20($sp)
	addi  $sp, $sp, -24

	lw    $s1, ($a0)
	move  $s2, $a1

	# base case
max_base_case:
	# if (length == 1) return a[0];
	li    $t0, 1
	bgt   $a1, $t0, max_rec_case
	lw    $v0, ($a0)
	j     max_return

	# recursive case
max_rec_case:
	# int max_so_far = max(&a[1], length-1);
	addi  $a0, $a0, 4
	addi  $a1, $a1, -1
	jal   max
	move  $t0, $v0
	# return (a[0] > max_so_far) ? a[0] : max_so_far;
	ble   $s1, $t0, max_choice
	move  $v0, $s1
	j     max_return
max_else:
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