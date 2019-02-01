FOBJS = 

# Shared MKL libraries
YLIB = -L/usr/global/intel/mkl/11.0.0.079/lib/intel64 -Wl,-R/usr/global/intel/mkl/11.0.0.079/lib/intel64 -lmkl_rt -lmkl_intel_thread -lmkl_core -liomp5 -lpthread -lm 

# FFTW Library
XLIB = -L/usr/global/fftw/3.3.2/intel/double/lib/ -lfftw3_mpi -lfftw3
FLIB = -I/usr/global/fftw/3.3.2/intel/double/include/ -lpthread

# Needed C libraries
CLIB = -L/usr/global/intel/composer_xe/2013.0.079/composer_xe_2013.0.079/compiler/lib/intel64 -limf -lirc  

# Phase-field library
# Must change the name after "home" to your local username

PLIB = -L/gpfs/home/tuy123/group/MUPRO/Library/Update_Record_2016_07_14/Backup_Updated_Library/ -lpfMPI
ILIB = -I/gpfs/home/tuy123/group/MUPRO/Library/Update_Record_2016_07_14/Backup_Updated_Library/

#Please be sure to check your routine with both the -O0 option here and the 
# -O3 options here. 
#FCLAGS = $(LINK_FNL) -O3 -xSSE3 -mieee-fp -prec-div 
FCLAGS = $(LINK_FNL) -O3 -xSSE3 
#FCLAGS = -O0 -traceback -g

#if your subroutine is in a separate file add the file name here BEFORE library_subroutine_testing.f90
#Please rename the file "library_subroutine_testing" to something more specific.  
#Change the name here as well
SCR_F = Magnetic.f90

OBJS = $(SCR_F:.f90=.o) $(SCR_C:.c=.o)

Magnetic.exe: $(OBJS)  
	mpif90 -align rec16byte -align all $(FCLAGS) $(ILIB) $(FLIB) -o $@ $(FOBJS) $(OBJS) $(PLIB) $(XLIB) $(YLIB) $(CLIB)

%.o: %.f90  
	mpif90 -align rec16byte -align array64byte $(FCLAGS) $(FLIB) $(ILIB) -c -r8 $< $(YLIB) $(XLIB) $(PLIB) 

%.o: %.c
	mpicc $(FCLAGS) $(FLIB) -c $< $(XLIB) $(YLIB)

clean:  
	/bin/rm -f *.o *.mod *.exe *.dat fort.* *pbs.*
###  



