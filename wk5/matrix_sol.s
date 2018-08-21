.text
.globl main
change:
   # params:    nrows is $a0, ncols is $a1, &M is $a2, factor is $a3
   # registers: row is $s0, col is $s1

   # set up stack frame
   sw   $fp, -4($sp)
   la   $fp, -4($sp)
   sw   $ra, -4($fp)
   sw   $s0, -8($fp)
   sw   $s1, -12($fp)
   addi $sp, $sp, -16

   li   $t4, 4           # sizeof(int)
   li   $s0, 0
loop1:                   # for (int row = 0; row < nrows; row++)
   bge  $s0, $a0, end1
   li   $s1, 0
loop2:                   # for (int col = 0; col < ncols; col++)
   bge  $s1, $a1, end2

   # get &M[row][col]
   mul  $t0, $s0, $a1
   mul  $t0, $t0, $t4    # offset of M[row]  (#bytes)
   mul  $t1, $s1, $t4    # offset within M[row]  (#bytes)
   add  $t0, $t0, $t1    # offset of M[row][col] (#bytes)
   add  $t0, $t0, $a2    # &M[row][col]

   lw   $t1, ($t0)
   mul  $t1, $t1, $a3
   sw   $t1, ($t0)       # M[row][col] = factor * M[row][col]

   addi $s1, $s1, 1
   j    loop2
end2:
   addi $s0, $s0, 1
   j    loop1
end1:

   # clean up stack frame
   lw   $ra, -4($fp)
   lw   $s0, -8($fp)
   lw   $s1, -12($fp)
   la   $sp, 4($fp)
   lw   $fp, ($fp)