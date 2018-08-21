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



   # clean up stack frame
   lw   $ra, -4($fp)
   lw   $s0, -8($fp)
   lw   $s1, -12($fp)
   la   $sp, 4($fp)
   lw   $fp, ($fp)