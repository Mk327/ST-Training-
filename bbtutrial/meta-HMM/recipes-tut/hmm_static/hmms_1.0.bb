DESCRIPTION = "The hmm_static recipe"
PR = "r1"
do_build () {
  gcc -o hmm.o -c hmm.c
  ar -rs libfoo.a hmm.o
  gcc -c main.c 
  gcc -o main main.o 
}
