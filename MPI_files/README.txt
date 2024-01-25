Removed them to test other implementatioms: swap the current one with these to
be able to use MPI again
- Makefile has to be put in the root of the project
- .hpp in the include directory
- .cpp in the src directory

BEWARE
Remove frome the file names "MPI" at the end of each file name.
I added it to be able to recognize them, but they won't work with this names!
