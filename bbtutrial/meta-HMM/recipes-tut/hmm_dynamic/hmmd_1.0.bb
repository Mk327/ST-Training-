DESCRIPTION = "The hmm_dynamic recipe"
PR = "r1"
do_build () {
  gcc -c -FPIC  hmm.c
  gcc -shared -o libfoo.so hmm_pic.o
  gcc -o main main.c  
  LD_LIBRARY_PATH=./mylib ./main
}
