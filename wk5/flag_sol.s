.data
nrows: .word 6
ncols: .word 12
flag:  .byte '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#'
       .byte '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#'
       .byte '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'
       .byte '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'
       .byte '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#'
       .byte '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#'


.text
.globl main
   lw   $s2, nrows
   lw   $s3, ncols
   li   $s0, 0         # row = 0
loop1:                 
   beq  $s0, $s2, end_loop1
   li   $s1, 0         # col = 0
loop2:
   beq  $s1, $s3, end_loop2
   mul  $t0, $s0, $s3
   add  $t0, $t0, $s1  # convert [row][col] to byte offset
   lb   $a0, flag($t0)
   li   $v0, 11        # printf("%c", flag[row][col])
   syscall
   addi $s1, $s1, 1    # col++
   j    loop2
end_loop2:
   li   $a0, '\n'
   li   $v0, 11        # printf("\n")
   syscall
   addi $s0, $s0, 1    # row++
   j    loop1
end_loop1: