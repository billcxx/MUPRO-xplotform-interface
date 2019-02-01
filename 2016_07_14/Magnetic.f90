  module mod_mainMagnetic

    implicit none

	integer rank,process

    !system
	integer nx,ny,nz,nf,ns,k1,k2
    integer*8 kt
	real*8 lx,ly,lz,dx,dy,dz,dt0
    integer R(3), C(3), HN(2),lstart(3)
	integer Rn3,Rn2,Rn1
	integer Cn3,Cn2,Cn1
	integer Hn2,Hn1
	integer trans
	integer lstart3,lstart2,lstartR
    integer nn

    integer choiceIslandShape                   !island in-plane shape: 0-2d array in 'islandShape.in' 1-rectangular or 2-elliptical shape defined in the next line (only for nf=0 and ni3/=0)
	integer ni1,ni2,ni3,i1,i2,j1,j2             !# of grids along length, width, and depth of the magnetic island (only for nf=0; if nf=0 and ni3=0, the system is considered bulk; ni1 and ni2 only for choiceIslandShape=1,2 and ni3/=0)
    integer choiceGrainStruct                   !grain structure: 0-Euler angles array in 'eulerAng.in' 1-single crystal with specified Euler angles
    logical flagTransform                       !whether transformation between local and global coordinates is needed
    real*8 phiC,thetaC,psiC                     !Euler angles phi, theta and psi of the single crystal orientation (only for choiceGrainStruct=1)

    character*8 :: passfilename

    !material
    real*8,parameter :: pi = dacos(-1.d0)
    real*8,parameter :: mu0 = 4.d-7*pi          !vacuum permeability
    real*8,parameter :: eC0 = 1.6021766209d-19  !charge of electron
    real*8,parameter :: muB = 9.27400968d-24    !Bohr magneton
    real*8,parameter :: kB = 1.38064853d-23     !Boltzmann constant
    real*8,parameter :: l0 = 1.d-9              !length unit
    real*8 s0                                   !stress unit
    real*8 M0                                   !saturation magnetization
    real*8 gamma                                !electron gyromagnetic ratio
    real*8 alphaM                               !damping constant
    logical flagAnisotropy                      !whether to consider magnetocrystalline anisotropy
    integer choiceAnisotropy                    !type of magnetocrystalline anisotropy: 1-cubic 2-uniaxial (only for flagAnisotropy=true)
    real*8 kc1,kc2,kc3                          !magnetocrystalline anisotropy coefficient (only for flagAnisotropy=true; kc3 only for choiceAnisotropy=1)
    logical flagStrayField                      !whether to consider stray field
    logical flagPeriodic                        !periodic (or finite-size) magnetostatic boundary?
    real*8 muR(6)                               !(background) relative magnetic permeability = (1,1,1,0,0,0)
    real*8 ND(6)                                !demagnetizing factor N11, N22, N33, N23, N13, N12, depending on the macroscopic shape of the magnet (only for flagPeriodic=true)
    logical flagElastic                         !whether to consider magnetoelastic effect
    real*8 lam100,lam111                        !saturation magnetostriction (only for flagElastic=true)
    real*8 c11,c12,c44                          !elastic stiffness (Voigt) (only for flagElastic=true)
    real*8 cs11,cs12,cs44                       !elastic stiffness of substrate (Voigt) (only for flagElastic=true)
    real*8 C_in(21),CS(6,6)                     !elastic stiffness (Voigt)
    real*8 Csub_in(21),CU(6,6)                  !elastic stiffness of substrate(Voigt)
    real*8 AExch                                !magnetic exchange constant
    logical flagST                              !whether to consider spin torque
    integer choiceST                            !type of spin torque: 1-spin-orbit torque 2-Slonczewski spin-transfer torque 3-Zhang-Li spin-transfer torque (only for flagST=true)
    real*8 angleSH                              !spin Hall angle (only for flagST=true and choiceST=1)
    real*8 etaSP                                !spin polarization constant (only for flagST=true and choiceST=2)
    real*8 ksiSTT                               !degree of non-adiabaticity (only for flagST=true and choiceST=3)
    logical flagDMI                             !whether to consider DMI(Dzyaloshinskii-Moriya interaction)
    real*8 DDMI                                 !continuous effective DMI constant

    !magnetization, effective fields (driving forces), and energy densities
    real*8,allocatable,dimension(:,:,:,:),target :: magnt,hEff,hEffOut,hAni,hStr,hEla,hST,hThe,hExc,hDMI
    real*8,allocatable,dimension(:,:,:),target :: fTot,fExt,fAni,fStr,fEla,fExc,fDMI

    !arrays for stray field
    real*8,allocatable,dimension(:,:,:),target :: phiM_in,chargeM_in

    !arrays for mechAnical variables
    real*8,allocatable,dimension(:,:,:,:),target :: eta,e,u
    real*8,allocatable,dimension(:,:,:,:),target :: s,elast
    real*8,allocatable,dimension(:,:,:,:,:) :: cGlob                      !elastic stiffness array
    real*8,allocatable,dimension(:,:,:,:,:,:,:) :: CS_standard,cGlob_standard

    !arrays for magnet shape
    real*8,allocatable,dimension(:,:,:) :: oMag,oSub,totalSize
    real*8,allocatable,dimension(:,:) :: oMag2d,oMag2d_glob

    !arrays for polycrystal grain structure
    real*8,allocatable,dimension(:,:,:) :: phiPolyC,thetaPolyC,psiPolyC   !Euler angles phi, theta and psi of the polycrystal orientation
    real*8,allocatable,dimension(:,:,:,:,:),target :: PolyTR              !array of the transformation matrix from the local to global coordinates

    !arrays for spin torque
    real*8,allocatable,dimension(:,:,:) :: angleST                        !spin torque angle

    !simulation parameters, external fields and conditions
    integer choiceHExt                          !external magnetic field: 0-array in 'hExt.in' with linear interpolations 1-DC & AC components
    real*8,allocatable :: hExt(:,:)             !applied magnetic field sequence
    real*8 hdc(3)                               !DC component of external magnetic field (only for choiceHExt=1)
    real*8 hac(3)                               !peak amplitude of AC component of external magnetic field (only for choiceHExt=1)
    real*8 frequency                            !frequency of AC component of external magnetic field(only for choiceHExt=1)
    logical flagConstrained                     !strain (or stress) elastic boundary condition? (only for bulk, i.e. nf=0 and ni3=0, and flagElastic=true)
    real*8 exx,eyy,exy                          !in-plane substrate/applied strains/stress (only for flagElastic=true)
    real*8 ezz,exz,eyz                          !out-of-plane applied strains/stress (only for bulk, i.e. nf=0 and ni3=0, and flagElastic=true)
    real*8 sTotapp(6)                           !applied strains/stress (only for bulk)
    logical flagElasticInhomo                   !whether to consider elastic stiffness inhomogeneity
    logical elasCondChange                      
    integer recursL                             !recursion limit for iterative elastic solver (only when the elastic stiffness of the system is inhomogeneous)
    real*8 toler                                !tolerance of convergence for iterative elastic solver (only when the elastic stiffness of the system is inhomogeneous)
    real*8,target :: jElect(3)                  !spin-polarized electric current density (only for flagST=true)
    real*8 mFixed(3)                            !fixed magnetization in the fixed layer in a spin torque structure (unitless) (only for flagST=true)
    real*8 lFree                                !thickness of free layers in a spin torque structure (only for flagST=true)
    real*8 constST                              
    logical flagThermalFluc                     !whether to consider thermal fluctuation
    real*8 temperature                          !temperature (K) (only for flaghermalFluc=true)
    real*8 varHT   !                            
    real*8 dt                                   !time per evolution step
    integer*8 kt0,ktMax                         !starting time step #; finishing time step #
    integer*8 ktOutTable,ktOutDist              !output step interval for data table; output step interval for spatial distribution
    integer choiceInitialM                      !initial m distribution: 0-'magnt.in' 1-random orientation 2-specified uniform orientation 3-specified vortex domain ('magnt.in' can be copied from output files 'magnt.*.dat')
    real*8 AxisInitialM(3),axisSize             !axis of a uniform orientation, or a vortex domain, for the initial m distribution (only for choiceInitialM=2,3)

    real*8 fmag                                 !volume fraction of the magnetic phase in the system
    real*8 mAvg(3)                              !average magnetization
    real*8 hEffAvg(3),hAniAvg(3),hStrAvg(3),hElaAvg(3),hSTAvg(3),hTheAvg(3),hExcAvg(3),hDMIAvg(3)
    real*8 fTotAvg,fExtAvg,fAniAvg,fStrAvg,fElaAvg,fExcAvg,fDMIAvg
    real*8 eAvg(6),etaAvg(6),sAvg(6)            !average strain and stress

    integer choiceLLGSolver                     !type of LLGSolver: 1-implicit Gauss-Seidel using Fourier spectral 2-explicit rk4
    logical flagExplicitDMI                     !whether to explicitly evaluate DMI field using FDM in implicit Gauss-Seidel LLG solver (only for flagDMI=true and choiceLLGSolver=1)
    integer,parameter :: solverFourierSpectrum = 1, solverExpRK4 = 2
    logical isThermalFieldCalc

    !output choices                             
    logical flagOutH                            !whether to output distribution of effective fields
    logical flagOutE                            !whether to output distribution of energy densities
    logical flagOutS                            !whether to output distribution of eigenstrain, strain, and stress (only for flagElastic=true)

  end module



  subroutine initMPI()

    use mod_interfaces
    use mod_mainMagnetic
    implicit none

    integer :: n
    call MPI_INIT(ierr)
    call MPI_comm_size(MPI_COMM_WORLD,process,ierr)
    call MPI_comm_rank(MPI_comm_world,rank,ierr)

4002  format("Hello, I am processor ",i3," of ",i2)
    do n = 0,process-1
      call MPI_Barrier(MPI_Comm_world,ierr)
      if(rank==n) then
        print 4002, rank,process-1
      endif
    enddo
    call sleep (1)

    call MPI_Barrier(MPI_Comm_world,ierr)

  end subroutine



  subroutine inputParameters()

    use mod_interfaces
    use mod_mainMagnetic
    implicit none

    if (rank==0) then

      open(unit = 1, file = "parameter.in")
      read(1,*),lx,ly,lz
      read(1,*),nx,ny,nz
      read(1,*),ns,nf
      read(1,*),choiceIslandShape
      read(1,*),ni1,ni2,ni3
      read(1,*),choiceGrainStruct
      read(1,*),phiC,thetaC,psiC
      read(1,*),M0,gamma,alphaM
      read(1,*),flagAnisotropy
      read(1,*),choiceAnisotropy
      read(1,*),kc1,kc2,kc3
      read(1,*),flagStrayField
      read(1,*),flagPeriodic
      read(1,*),ND(1),ND(2),ND(3)
      read(1,*),ND(4),ND(5),ND(6)
      read(1,*),choiceHExt
      read(1,*),hdc(1),hdc(2),hdc(3)
      read(1,*),hac(1),hac(2),hac(3)
      read(1,*),frequency
      read(1,*),AExch
      read(1,*),flagElastic
      read(1,*),lam100,lam111
      read(1,*),c11,c12,c44
      read(1,*),cs11,cs12,cs44
      read(1,*),flagConstrained
      read(1,*),exx,eyy,exy
      read(1,*),ezz,exz,eyz
      read(1,*),recursL,toler
      read(1,*),flagST
      read(1,*),choiceST
      read(1,*),angleSH
      read(1,*),etaSP
      read(1,*),ksiSTT
      read(1,*),jElect(1),jElect(2),jElect(3)
      read(1,*),mFixed(1),mFixed(2),mFixed(3)
      read(1,*),flagDMI
      read(1,*),DDMI
      read(1,*),flagThermalFluc
      read(1,*),temperature
      read(1,*),choiceLLGSolver
      read(1,*),dt
      read(1,*),kt0,ktMax
      read(1,*),ktOutTable,ktOutDist
      read(1,*),choiceInitialM
      read(1,*),AxisInitialM(1),AxisInitialM(2),AxisInitialM(3)
      read(1,*),flagOutH,flagOutE
      read(1,*),flagOutS
      close(1)

      flagTransform = .true.
      if(choiceGrainStruct==1 .and. dmax1(dabs(phiC),dabs(thetaC),dabs(psiC))<=1.e-8) flagTransform = .false.

      flagElasticInhomo = .true.
      if(choiceGrainStruct==1 .and. &                                                                 !single crystal .and.
          (nf==0.and.ni3==0 .or. &                                                                    !(bulk .or.
           nf/=0.and.(dmax1(dabs(cs11/c11-1.d0),dabs(cs12/c12-1.d0),dabs(cs44/c44-1.d0))<=1.e-8))) &  !thin film with same stiffness in film and substrate)
      flagElasticInhomo = .false.

    endif

    call MPI_Barrier(MPI_COMM_WORLD,ierr)

  end subroutine



  subroutine init()

    use mod_interfaces
    use mod_mainMagnetic
    implicit none

    integer :: i,j,k,l,m,n
    real*8 :: R3(6)                   !adding the iterative variables
    call MPI_Barrier(MPI_Comm_world,ierr)

    call MPI_Bcast(lx,               1,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(ly,               1,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(lz,               1,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(nx,               1,   MPI_integer, 0,MPI_Comm_World,ierr)
    call MPI_Bcast(ny,               1,   MPI_integer, 0,MPI_Comm_World,ierr)
    call MPI_Bcast(nz,               1,   MPI_integer, 0,MPI_Comm_World,ierr)
    call MPI_Bcast(ns,               1,   MPI_integer, 0,MPI_Comm_World,ierr)
    call MPI_Bcast(nf,               1,   MPI_integer, 0,MPI_Comm_World,ierr)
    call MPI_Bcast(choiceIslandShape,1,   MPI_integer, 0,MPI_Comm_World,ierr)
    call MPI_Bcast(ni1,              1,   MPI_integer, 0,MPI_Comm_World,ierr)
    call MPI_Bcast(ni2,              1,   MPI_integer, 0,MPI_Comm_World,ierr)
    call MPI_Bcast(ni3,              1,   MPI_integer, 0,MPI_Comm_World,ierr)
    call MPI_Bcast(choiceGrainStruct,1,   MPI_integer, 0,MPI_Comm_World,ierr)
    call MPI_Bcast(phiC,             1,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(thetaC,           1,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(psiC,             1,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(M0,               1,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(gamma,            1,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(alphaM,           1,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(flagAnisotropy,   1,   MPI_logical, 0,MPI_Comm_World,ierr)
    call MPI_Bcast(choiceAnisotropy, 1,   MPI_integer, 0,MPI_Comm_World,ierr)
    call MPI_Bcast(kc1,              1,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(kc2,              1,   MPI_real8,   0,MPI_Comm_World,ierr)
	call MPI_Bcast(kc3,              1,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(flagStrayField,   1,   MPI_logical, 0,MPI_Comm_World,ierr)
    call MPI_Bcast(flagPeriodic,     1,   MPI_logical, 0,MPI_Comm_World,ierr)
    call MPI_Bcast(ND,               6,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(choiceHExt,       1,   MPI_integer, 0,MPI_Comm_World,ierr)
    call MPI_Bcast(hdc,              3,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(hac,              3,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(frequency,        1,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(AExch,            1,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(flagElastic,      1,   MPI_logical, 0,MPI_Comm_World,ierr)
    call MPI_Bcast(lam100,           1,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(lam111,           1,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(c11,              1,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(c12,              1,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(c44,              1,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(cs11,             1,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(cs12,             1,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(cs44,             1,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(flagConstrained,  1,   MPI_logical, 0,MPI_Comm_World,ierr)
    call MPI_Bcast(exx,              1,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(eyy,              1,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(exy,              1,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(ezz,              1,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(exz,              1,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(eyz,              1,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(recursL,          1,   MPI_integer, 0,MPI_Comm_World,ierr)
    call MPI_Bcast(toler,            1,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(flagST,           1,   MPI_logical, 0,MPI_Comm_World,ierr)
    call MPI_Bcast(choiceST,         1,   MPI_integer, 0,MPI_Comm_World,ierr)
    call MPI_Bcast(angleSH,          1,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(etaSP,            1,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(ksiSTT,           1,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(jElect,           3,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(mFixed,           3,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(flagDMI,          1,   MPI_logical, 0,MPI_Comm_World,ierr)
    call MPI_Bcast(DDMI,             1,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(flagThermalFluc,  1,   MPI_logical, 0,MPI_Comm_World,ierr)
    call MPI_Bcast(temperature,      1,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(choiceLLGSolver,  1,   MPI_integer, 0,MPI_Comm_World,ierr)
    call MPI_Bcast(dt,               1,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(kt0,              1,   MPI_integer8,0,MPI_Comm_World,ierr)
    call MPI_Bcast(ktMax,            1,   MPI_integer8,0,MPI_Comm_World,ierr)
    call MPI_Bcast(ktOutTable,       1,   MPI_integer8,0,MPI_Comm_World,ierr)
    call MPI_Bcast(ktOutDist,        1,   MPI_integer8,0,MPI_Comm_World,ierr)
    call MPI_Bcast(choiceInitialM,   1,   MPI_integer, 0,MPI_Comm_World,ierr)
    call MPI_Bcast(AxisInitialM,     3,   MPI_real8,   0,MPI_Comm_World,ierr)
    call MPI_Bcast(flagOutH,         1,   MPI_logical, 0,MPI_Comm_World,ierr)
    call MPI_Bcast(flagOutE,         1,   MPI_logical, 0,MPI_Comm_World,ierr)
    call MPI_Bcast(flagOutS,         1,   MPI_logical, 0,MPI_Comm_World,ierr)
    call MPI_Bcast(flagTransform,    1,   MPI_logical, 0,MPI_Comm_World,ierr)
    call MPI_Bcast(flagElasticInhomo,1,   MPI_logical, 0,MPI_Comm_World,ierr)

    call MPI_Barrier(MPI_Comm_world,ierr)

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! set up system size !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    nn = nx * ny * nz

    dx=lx/real(nx)
    dy=ly/real(ny)
    dz=lz/real(nz)

    k1 = ns + 1
    k2 = ns + nf
    if (nf==0) then
      if (ni3==0) then
        k1 = 1
        k2 = nz
      else
        k1 = ns + 1
        k2 = ns + ni3
      endif
    endif

    kt = kt0

	call simSizeDeclare(nx,ny,nz,ns,nf,lx,ly,lz,kt_in=kt)

    call MPI_Barrier(MPI_COMM_WORLD,ierr)

    call fourier_mpi_setup(R,C,HN,lstart,trans)

    Rn1 = R(1);Rn2 = R(2); Rn3 = R(3)
    Cn1 = C(1);Cn2 = C(2); Cn3 = C(3)
    Hn1 = HN(1);Hn2 = HN(2)
    lstartR = lstart(1); lstart2 = lstart(2); lstart3 = lstart(3)

    call MPI_Barrier(MPI_COMM_WORLD,ierr)
 
    call setup_msolve_general

    call random_seed()

    call MPI_Barrier(MPI_COMM_WORLD,ierr)

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! non-dimensionalization !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    s0 = 1.e9

    phiC    = phiC    * pi/180.d0
    thetaC  = thetaC  * pi/180.d0
    psiC    = psiC    * pi/180.d0

    AExch = AExch/(mu0*M0**2*l0**2)

    kc1 = kc1 / (mu0*M0**2)
    kc2 = kc2 / (mu0*M0**2)
	kc3 = kc3 / (mu0*M0**2)

    muR(1:3) = 1.
    muR(4:6) = 0.

    C_in(1)=c11;  C_in(2)=c12;  C_in(3) =c12;  C_in(4) = 0.;  C_in(5) = 0.;  C_in(6) = 0.   !cubic anisotropy only
                  C_in(7)=c11;  C_in(8) =c12;  C_in(9) = 0.;  C_in(10)= 0.;  C_in(11)= 0.
                                C_in(12)=c11;  C_in(13)= 0.;  C_in(14)= 0.;  C_in(15)= 0.
                                               C_in(16)=c44;  C_in(17)= 0.;  C_in(18)= 0.
                                                              C_in(19)=c44;  C_in(20)= 0.
                                                                             C_in(21)=c44
    C_in = C_in / s0

    Csub_in(1)=cs11;  Csub_in(2)=cs12;  Csub_in(3) =cs12;  Csub_in(4) = 0.;  Csub_in(5) = 0.;  Csub_in(6) = 0.   !cubic anisotropy only
                      Csub_in(7)=cs11;  Csub_in(8) =cs12;  Csub_in(9) = 0.;  Csub_in(10)= 0.;  Csub_in(11)= 0.
                                        Csub_in(12)=cs11;  Csub_in(13)= 0.;  Csub_in(14)= 0.;  Csub_in(15)= 0.
                                                           Csub_in(16)=cs44; Csub_in(17)= 0.;  Csub_in(18)= 0.
                                                                             Csub_in(19)=cs44; Csub_in(20)= 0.
                                                                                               Csub_in(21)=cs44
    Csub_in = Csub_in / s0

	if(nf==0.and.ni3==0.and..not.flagConstrained) then
      exx = exx / s0
      eyy = eyy / s0
      ezz = ezz / s0
      exy = exy / s0
      exz = exz / s0
      eyz = eyz / s0
	endif

    sTotapp(1)=exx;   sTotapp(2)=eyy;   sTotapp(3)=ezz
	sTotapp(4)=eyz;   sTotapp(5)=exz;   sTotapp(6)=exy
    if(ni3/=0) sTotapp(3:5)=0.d0

	elasCondChange = .true.

    DDMI = DDMI / (mu0 * M0**2 * l0)
    if(.not.flagDMI) DDMI=0.d0

    flagExplicitDMI = .true.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! allocate and initiate arrays !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    allocate(magnt(Rn3,Rn2,Rn1,3));                  magnt=0.
    allocate(hEff(Rn3,Rn2,Rn1,3));                   hEff=0.
    allocate(hEffOut(Rn3,Rn2,Rn1,3));                hEffOut=0.
    allocate(hAni(Rn3,Rn2,Rn1,3));                   hAni=0.
    allocate(hStr(Rn3,Rn2,Rn1,3));                   hStr=0.
    allocate(hEla(Rn3,Rn2,Rn1,3));                   hEla=0.
    allocate(hST(Rn3,Rn2,Rn1,3));                    hST=0.
    allocate(hThe(Rn3,Rn2,Rn1,3));                   hThe=0.
    allocate(hExc(Rn3,Rn2,Rn1,3));                   hExc=0.
    allocate(hDMI(Rn3,Rn2,Rn1,3));                   hDMI=0.

    allocate(fTot(Rn3,Rn2,Rn1));                     fTot=0.
    allocate(fExt(Rn3,Rn2,Rn1));                     fExt=0.
    allocate(fAni(Rn3,Rn2,Rn1));                     fAni=0.
    allocate(fStr(Rn3,Rn2,Rn1));                     fStr=0.
    allocate(fEla(Rn3,Rn2,Rn1));                     fEla=0.
    allocate(fExc(Rn3,Rn2,Rn1));                     fExc=0.
    allocate(fDMI(Rn3,Rn2,Rn1));                     fDMI=0.

    allocate(phiM_in(Rn3,Rn2,Rn1));                  phiM_in=0.
    allocate(chargeM_in(Rn3,Rn2,Rn1));               chargeM_in=0.

    if(flagElastic) then
      allocate(eta(Rn3,Rn2,Rn1,6));                  eta=0.
      allocate(e(Rn3,Rn2,Rn1,6));                    e=0.
      allocate(u(Rn3,Rn2,Rn1,6));                    u=0.
      allocate(s(Rn3,Rn2,Rn1,6));                    s=0.
      allocate(elast(Rn3,Rn2,Rn1,3));                elast=0.
      allocate(cGlob(6,6,Rn3,Rn2,Rn1));              cGlob=0.
      allocate(CS_standard(3,3,3,3,Rn3,Rn2,Rn1));    CS_standard=0.
      allocate(cGlob_standard(3,3,3,3,Rn3,Rn2,Rn1)); cGlob_standard=0.
    endif

    allocate(angleST(Rn3,Rn2,Rn1));                  angleST=0.

    allocate(oMag(Rn3,Rn2,Rn1));                     oMag=0.
    allocate(oSub(Rn3,Rn2,Rn1));                     oSub=0.
    allocate(totalSize(Rn3,Rn2,Rn1));                totalSize=0.

    if(flagTransform) then
      allocate(phiPolyC(Rn3,Rn2,Rn1));               phiPolyC=0.
      allocate(thetaPolyC(Rn3,Rn2,Rn1));             thetaPolyC=0.
      allocate(psiPolyC(Rn3,Rn2,Rn1));               psiPolyC=0.
      allocate(PolyTR(3,3,Rn3,Rn2,Rn1));             PolyTR=0.
    endif

    call MPI_Barrier(Mpi_Comm_world,ierr)

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! magnet shape !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	if(nf==0 .and. ni3.ne.0) then   !island
      if(choiceIslandShape==0) then
        allocate(oMag2d_glob(Rn2,nx));        oMag2d_glob=0.
        allocate(oMag2d(Rn2,Rn1));            oMag2d=0.

        if(rank==0) then
          open(unit = 2, file = "islandShape.in")
          do k=1,nx*Rn2
            read (2,*) i,j,oMag2d_glob(j,i)
          enddo
        endif

        call MPI_Bcast(oMag2d_glob,Rn2*nx,MPI_real8,0,MPI_Comm_World,ierr)
        call MPI_Barrier(MPI_COMM_WORLD,ierr)
        if (Rn1>0) oMag2d = oMag2d_glob(:,lstartR+1:lstartR+Rn1)
        oMag2d = dmax1(dmin1(oMag2d,1.d0),0.d0)

        do i=k1,k2
          where(oMag2d>0.5) oMag(i,:,:)=1.d0
        enddo

      elseif (choiceIslandShape==1) then
        j1 = ((ny + 1)-(ni2 - 1)) /2
        j2 = ((ny + 1)+(ni2 - 1)) /2
        i1 = max(((nx + 1)-(ni1 - 1))/2 - lstartR, 1)
        i2 = min(((nx + 1)+(ni1 - 1))/2 - lstartR, Rn1)
        oMag(k1:k2,j1:j2,i1:i2)=1.

      elseif (choiceIslandShape==2) then
        do i=1,Rn1
        do j=1,Rn2
          if( ((i+lstartR-(1+nx)/2.)/(ni1/2.))**2 + ((j-(1+ny)/2.)/(ni2/2.))**2 <= 1.) oMag(k1:k2,j,i)=1.
        enddo
        enddo

      endif

    else   !bulk or thin film
      oMag(k1:k2,:,:)=1.

    endif

    if(k1>1) oSub(1:k1-1,:,:)=1.

    R3(4) = sum(oMag)
    call MPI_Reduce(R3(4),fmag,4,MPI_Real8,MPI_SUM,0,MPI_COMM_WORLD,ierr)
    fmag = fmag / nn

    passfilename = 'oMag'
    call outputxN_P(passfilename,oMag(:,:,:))

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! transformation matrix array !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    if(flagTransform) then
      if (choiceGrainStruct==0) then
        passfilename = 'eulerAng'
        call inputxN_P(passfilename,phiPolyC,thetaPolyC,psiPolyC)
        phiPolyC    = phiPolyC    * pi/180.d0
        thetaPolyC  = thetaPolyC  * pi/180.d0
        psiPolyC    = psiPolyC    * pi/180.d0

      elseif (choiceGrainStruct==1) then
        phiPolyC    = phiC
        thetaPolyC  = thetaC
        psiPolyC    = psiC
      endif
    endif

    if(flagTransform) call polyCrystalEulerAngles(phiPolyC,thetaPolyC,psiPolyC,PolyTR)

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! elastic stiffness calculation !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    if(flagElastic) then
      CS(1,1)=C_in(1); CS(1,2)=C_in(2); CS(1,3)=C_in(3);  CS(1,4)=C_in(4);  CS(1,5)=C_in(5);  CS(1,6)=C_in(6)
                       CS(2,2)=C_in(7); CS(2,3)=C_in(8);  CS(2,4)=C_in(9);  CS(2,5)=C_in(10); CS(2,6)=C_in(11)
                                        CS(3,3)=C_in(12); CS(3,4)=C_in(13); CS(3,5)=C_in(14); CS(3,6)=C_in(15)
                                                          CS(4,4)=C_in(16); CS(4,5)=C_in(17); CS(4,6)=C_in(18)
                                                                            CS(5,5)=C_in(19); CS(5,6)=C_in(20)
                                                                                              CS(6,6)=C_in(21)
      do i = 1,6
      do j = i,6
        CS(j,i) = CS(i,j)
      enddo
      enddo

      CU(1,1)=Csub_in(1); CU(1,2)=Csub_in(2); CU(1,3)=Csub_in(3);  CU(1,4)=Csub_in(4);  CU(1,5)=Csub_in(5);  CU(1,6)=Csub_in(6)
                          CU(2,2)=Csub_in(7); CU(2,3)=Csub_in(8);  CU(2,4)=Csub_in(9);  CU(2,5)=Csub_in(10); CU(2,6)=Csub_in(11)
                                              CU(3,3)=Csub_in(12); CU(3,4)=Csub_in(13); CU(3,5)=Csub_in(14); CU(3,6)=Csub_in(15)
                                                                   CU(4,4)=Csub_in(16); CU(4,5)=Csub_in(17); CU(4,6)=Csub_in(18)
                                                                                        CU(5,5)=Csub_in(19); CU(5,6)=Csub_in(20)
                                                                                                             CU(6,6)=Csub_in(21)
  
      do i = 1,6
      do j = i,6
        CU(j,i) = CU(i,j)
      enddo
      enddo

      if(flagTransform) then

        do i = 1,3
        do j = 1,3
        do k = 1,3
        do l = 1,3
          IF (i == j) m = i
          IF ((i == 2 .AND. j == 3) .OR. ( i == 3 .AND. j == 2)) m = 4
          IF ((i == 1 .AND. j == 3) .OR. ( i == 3 .AND. j == 1)) m = 5
          IF ((i == 1 .AND. j == 2) .OR. ( i == 2 .AND. j == 1)) m = 6
          IF (k == l) n = k
          IF ((k == 2 .AND. l == 3) .OR. ( k == 3 .AND. l == 2)) n = 4
          IF ((k == 1 .AND. l == 3) .OR. ( k == 3 .AND. l == 1)) n = 5
          IF ((k == 1 .AND. l == 2) .OR. ( k == 2 .AND. l == 1)) n = 6
          CS_standard(i,j,k,l,:,:,:) = CS(m,n) * oMag + CU(m,n) * oSub
        enddo
        enddo
        enddo
        enddo

        call tensor_rotate_variable(CS_standard,cGlob_standard,"F")

        do i = 1,3
        do j = 1,3
        do k = 1,3
        do l = 1,3
          IF (i == j) m = i
          IF ((i == 2 .AND. j == 3) .OR. ( i == 3 .AND. j == 2)) m = 4
          IF ((i == 1 .AND. j == 3) .OR. ( i == 3 .AND. j == 1)) m = 5
          IF ((i == 1 .AND. j == 2) .OR. ( i == 2 .AND. j == 1)) m = 6
          IF (k == l) n = k
          IF ((k == 2 .AND. l == 3) .OR. ( k == 3 .AND. l == 2)) n = 4
          IF ((k == 1 .AND. l == 3) .OR. ( k == 3 .AND. l == 1)) n = 5
          IF ((k == 1 .AND. l == 2) .OR. ( k == 2 .AND. l == 1)) n = 6
          cGlob(m,n,:,:,:) = cGlob_standard(i,j,k,l,:,:,:)
        enddo
        enddo
        enddo
        enddo

      else   !flagTransform

        do i=1,6
        do j=1,6
          cGlob(i,j,:,:,:) = CS(i,j) * oMag + CU(i,j) * oSub
        enddo
        enddo

      endif   !flagTransform

      passfilename = 'cGlob'
      call outputxN_P(passfilename,cGlob(1,1,:,:,:),cGlob(1,2,:,:,:),cGlob(4,4,:,:,:))

    endif   !flagElastic

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! spin torque !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    if (flagST) then
      lFree = (k2-k1+1) * dz * l0
      constST = muB/(gamma*M0**2*eC0*lFree)*jElect(3)
    endif

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! thermal fluctuation !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    if(flagThermalFluc) varHT = dsqrt(2.d0 * alphaM * kB * temperature / (mu0 * M0 * gamma * dx*dy*dz * l0**3 * dt)) / M0

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! initial magnetization !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    if (choiceInitialM==0) then
      passfilename = 'magnt'
      call inputxN_P(passfilename,magnt(:,:,:,1),magnt(:,:,:,2),magnt(:,:,:,3))

    elseif (choiceInitialM==1) then
      call random_number(magnt(:,:,:,:))
      magnt = magnt - 0.5
      totalSize = dsqrt(magnt(:,:,:,1)**2 + magnt(:,:,:,2)**2 + magnt(:,:,:,3)**2)
      magnt(:,:,:,1) = magnt(:,:,:,1) / totalSize * oMag
      magnt(:,:,:,2) = magnt(:,:,:,2) / totalSize * oMag
      magnt(:,:,:,3) = magnt(:,:,:,3) / totalSize * oMag

    elseif (choiceInitialM==2) then
      axisSize = dsqrt(axisInitialM(1)**2+axisInitialM(2)**2+axisInitialM(3)**2)
      if(axisSize<1.d-24) then
        axisInitialM(1)=0.d0
        axisInitialM(2)=0.d0
        axisInitialM(3)=1.d0
      else
        axisInitialM = axisInitialM/axisSize
      endif

      magnt(:,:,:,1) = axisInitialM(1) * oMag
      magnt(:,:,:,2) = axisInitialM(2) * oMag
      magnt(:,:,:,3) = axisInitialM(3) * oMag

    elseif (choiceInitialM==3) then
      axisSize = dsqrt(axisInitialM(1)**2+axisInitialM(2)**2+axisInitialM(3)**2)
      if(axisSize<1.d-24) then
        axisInitialM(1)=0.d0
        axisInitialM(2)=0.d0
        axisInitialM(3)=1.d0
      else
        axisInitialM = axisInitialM/axisSize
      endif

      do i=1,Rn1
      do j=1,Rn2
      do k=1,Rn3
        magnt(k,j,i,1) = (j        -(1+ny)/2.)*dy*axisInitialM(3) - (k        -(1+nz)/2.)*dz*axisInitialM(2)
        magnt(k,j,i,2) = (k        -(1+nz)/2.)*dz*axisInitialM(1) - (i+lstartR-(1+nx)/2.)*dx*axisInitialM(3)
        magnt(k,j,i,3) = (i+lstartR-(1+nx)/2.)*dz*axisInitialM(2) - (j        -(1+ny)/2.)*dy*axisInitialM(1)
      enddo
      enddo
      enddo
      totalSize = dsqrt(magnt(:,:,:,1)**2 + magnt(:,:,:,2)**2 + magnt(:,:,:,3)**2)
      where(totalSize<1.d-12)
        magnt(:,:,:,1)=axisInitialM(1)
        magnt(:,:,:,2)=axisInitialM(2)
        magnt(:,:,:,3)=axisInitialM(3)
      endwhere

      magnt(:,:,:,1) = magnt(:,:,:,1) / totalSize * oMag
      magnt(:,:,:,2) = magnt(:,:,:,2) / totalSize * oMag
      magnt(:,:,:,3) = magnt(:,:,:,3) / totalSize * oMag

    endif

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! external field sequence !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    allocate(hExt(3,0:ktMax));   hExt=0.

    if (choiceHExt==0) then
      if(rank==0) open(unit = 3, file = "hExt.in")
      if(rank==0) read (3,*) n
      call MPI_Bcast(n,1,MPI_integer,0,MPI_Comm_World,ierr)
      call MPI_Barrier(MPI_COMM_WORLD,ierr)
      i=0
      do k=1,n
        if(rank==0) read (3,*) j,hExt(1,j),hExt(2,j),hExt(3,j)
        call MPI_Bcast(j,        1,MPI_integer,0,MPI_Comm_World,ierr)
        call MPI_Bcast(hExt(1,j),1,MPI_real8,  0,MPI_Comm_World,ierr)
        call MPI_Bcast(hExt(2,j),1,MPI_real8,  0,MPI_Comm_World,ierr)
        call MPI_Bcast(hExt(3,j),1,MPI_real8,  0,MPI_Comm_World,ierr)
        call MPI_Barrier(MPI_COMM_WORLD,ierr)
		if (k==1) hExt(:,0) = hExt(:,j)
        do l=i+1,j-1
          hExt(:,l) = (hExt(:,i)*(j-l) + hExt(:,j)*(l-i)) / real(j-i)
        enddo
        i=j
      enddo
      do l=j,ktMax
        hExt(:,l) = hExt(:,j)
      enddo

    elseif (choiceHExt==1) then
      if (hac(1)==0. .and. hac(2)==0. .and. hac(3)==0.) then
		hExt(1,:) = hdc(1);   hExt(2,:) = hdc(2);   hExt(3,:) = hdc(3)
      else
        do k=0,ktMax
		  hExt(:,k) = hdc + hac * dsin(2*pi*frequency*k*dt)
		enddo
      endif

    endif

    if(rank==0) then
      open(unit = 11, file = "hExt.dat")
      write(11,'("    Step#   External magnetic field (A/m)")')
	  do i = kt0,ktMax
        write(11,1001)i,hExt(1,i),hExt(2,i),hExt(3,i)
      enddo
    endif

1001  format(i10,30es16.7e3)

    hExt = hExt / M0

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! call set-up routines !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    call LLG_setup(magnt,hEff,hExc,hDMI,fExc,fDMI,oMag,dt*gamma*M0/(1+alphaM**2),alphaM,AExch,DDMI,flagExplicitDMI)

    if(flagAnisotropy) call magneticAnisotropy_setup(magnt,hAni,fAni,oMag,choiceAnisotropy,kc1,kc2,kc3)

    if(flagStrayField) call strayField_setup(flagPeriodic,muR,ND,magnt,chargeM_in,phiM_in,hStr,fStr)

    if(flagElastic) then
      call magnetoElastic_setup(magnt,hEla,M0,lam100,lam111,s0,C_in,oMag)
      if(flagElasticInhomo) then; call iterativeElastic_setup(eta,e,u,s,elast,fEla,cGlob_in=cGlob)
      else;                       call elastic_setup(eta,e,u,s,elast,fEla,C_in); endif
    endif

    if(flagST.and.choiceST==3) call STTZhangLi_setup(magnt,hST,oMag,jElect,ksiSTT,M0,gamma)
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! prepare for output !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    if(rank==0) then

      open(unit = 13, file = "avMagntz.dat")
      write(13,'("    Step#   Average magnetization (unitless)")')

      open(unit = 14, file = "avhEff.dat")
      write(14,'("    Step#   Average effective field (A/m)                   External magnetic field (A/m)                   &
                              Average stray field (A/m)                       Average anisotropy field (A/m)                  &
                              Average magnetoelastic field (A/m)              Average exchange field (A/m)                    &
                              Average DMI field (A/m)                         Average spin torque field (A/m)                 &
                              Average thermal fluctuation field (A/m)")')

      open(unit = 17, file = "avEnergy.dat")
      write(17,'("    Step#   Total           External        Anisotropy      Stray field     Magnetoelastic  Exchange        DMI (J/m^3)")')

      if(flagElastic) then
        open(unit = 15, file = "avStrain.dat")
        write(15,'("    Step#   Average strain (unitless)                                                                             Average eigenstrain (unitless)")')

        open(unit = 16, file = "avStress.dat")
        write(16,'("    Step#   Average stress (Pa)")')
      endif

    endif

    call MPI_Barrier(MPI_COMM_WORLD,ierr)

  end subroutine



  subroutine getHeff()

    use mod_interfaces
    use mod_mainMagnetic
    implicit none

    integer :: i,j,k
    real*8 gaussDistribution

    if(flagAnisotropy) then
      if(flagTransform) then;     call polyMagneticAnisotropy
      else;                       call magneticAnisotropy; endif
    endif

    if(flagStrayField) call strayField

    if(flagElastic) then
      if(flagTransform) then;     call polyMagneticEigenstrain
      else;                       call magneticEigenstrain; endif
      if(flagElasticInhomo) then; call iterativeElasticSolve(flagConstrained,sTotapp,exx,eyy,exy,elasCondChange,toler,recursL)
      else;                       call elasticSolve(flagConstrained,sTotapp,exx,eyy,exy); endif
      if(flagTransform) then;     call polyMagnetoElasticDrivingForce
      else;                       call magnetoElasticDrivingForce; endif
    endif

    call MPI_Barrier(MPI_COMM_WORLD,ierr)

    if(flagST) then
      Selectcase(choiceST)
      case(1)
        hST(:,:,:,1) = (magnt(:,:,:,2)*mFixed(3) - magnt(:,:,:,3)*mFixed(2)) * constST * angleSH
        hST(:,:,:,2) = (magnt(:,:,:,3)*mFixed(1) - magnt(:,:,:,1)*mFixed(3)) * constST * angleSH
        hST(:,:,:,3) = (magnt(:,:,:,1)*mFixed(2) - magnt(:,:,:,2)*mFixed(1)) * constST * angleSH
      case(2)
        angleST = 1.d0 / (-4.d0 + 0.25d0*((1.d0+etaSP)/dsqrt(etaSP))**3 &
                            * (3.d0+magnt(:,:,:,1)*mFixed(1)+magnt(:,:,:,2)*mFixed(2)+magnt(:,:,:,3)*mFixed(3)))
        hST(:,:,:,1) = (magnt(:,:,:,2)*mFixed(3) - magnt(:,:,:,3)*mFixed(2)) * constST * angleST
        hST(:,:,:,2) = (magnt(:,:,:,3)*mFixed(1) - magnt(:,:,:,1)*mFixed(3)) * constST * angleST
        hST(:,:,:,3) = (magnt(:,:,:,1)*mFixed(2) - magnt(:,:,:,2)*mFixed(1)) * constST * angleST
      case(3)
        call STTZhangLi
      endselect

    endif

    if(flagThermalFluc.and.isThermalFieldCalc==0) then
      do i=1,Rn1
      do j=1,Rn2
      do k=1,Rn3
        HThe(k,j,i,1)=gaussDistribution(0.,varHT)
        HThe(k,j,i,2)=gaussDistribution(0.,varHT)
        HThe(k,j,i,3)=gaussDistribution(0.,varHT)
      enddo
      enddo
      enddo
      isThermalFieldCalc=1
    endif

    if(choiceLLGSolver==solverExpRK4 .or. flagExplicitDMI) call magneticExchange

    do i=1,3
      Selectcase(choiceLLGSolver)
      case(solverFourierSpectrum)
        hEff(:,:,:,i) = hExt(i,kt) + hAni(:,:,:,i) + hStr(:,:,:,i) + hEla(:,:,:,i) + hST(:,:,:,i) + hThe(:,:,:,i)
        if(flagExplicitDMI) hEff(:,:,:,i) = hEff(:,:,:,i) + hDMI(:,:,:,i)
      case(solverExpRK4)
        hEff(:,:,:,i) = hExt(i,kt) + hAni(:,:,:,i) + hStr(:,:,:,i) + hEla(:,:,:,i) + hST(:,:,:,i) + hThe(:,:,:,i) + hExc(:,:,:,i) + hDMI(:,:,:,i)
      endselect
    enddo

    if (mod(kt,ktOutTable)==0.or.mod(kt,ktOutDist)==0.or.kt==kt0.or.kt==ktMax) then
      Selectcase(choiceLLGSolver)
      case(solverFourierSpectrum)
        if(flagExplicitDMI) then
          hEffOut = hEff + hExc
        else
          call magneticExchange
          hEffOut = hEff + hExc + hDMI
        endif
      case(solverExpRK4)
        hEffOut = hEff
      endselect
      fExt = -( magnt(:,:,:,1)*hExt(1,kt) + magnt(:,:,:,2)*hExt(2,kt) + magnt(:,:,:,3)*hExt(3,kt) )
      fTot = fExt + fAni + fStr + fEla*s0/(mu0*M0**2) + fExc + fDMI
    endif

    call MPI_Barrier(MPI_COMM_WORLD,ierr)

  end subroutine



  subroutine outputDataTable()

    use mod_interfaces
    use mod_mainMagnetic
    implicit none

    integer :: i,j,k
    real*8 :: R3(6)

    do i=1,3;   R3(i) = sum(magnt(:,:,:,i));   enddo
    call MPI_Reduce(R3(1:3),mAvg,3,MPI_Real8,MPI_SUM,0,MPI_COMM_WORLD,ierr)

    do i=1,3;   R3(i) = sum(hEffOut(:,:,:,i)*oMag);   enddo
    call MPI_Reduce(R3(1:3),hEffAvg,3,MPI_Real8,MPI_SUM,0,MPI_COMM_WORLD,ierr)

    do i=1,3;   R3(i) = sum(hAni(:,:,:,i)*oMag);   enddo
    call MPI_Reduce(R3(1:3),hAniAvg,3,MPI_Real8,MPI_SUM,0,MPI_COMM_WORLD,ierr)

    do i=1,3;   R3(i) = sum(hStr(:,:,:,i)*oMag);   enddo
    call MPI_Reduce(R3(1:3),hStrAvg,3,MPI_Real8,MPI_SUM,0,MPI_COMM_WORLD,ierr)

    do i=1,3;   R3(i) = sum(hEla(:,:,:,i)*oMag);   enddo
    call MPI_Reduce(R3(1:3),hElaAvg,3,MPI_Real8,MPI_SUM,0,MPI_COMM_WORLD,ierr)

    do i=1,3;   R3(i) = sum(hExc(:,:,:,i)*oMag);   enddo
    call MPI_Reduce(R3(1:3),hExcAvg,3,MPI_Real8,MPI_SUM,0,MPI_COMM_WORLD,ierr)

    do i=1,3;   R3(i) = sum(hDMI(:,:,:,i)*oMag);   enddo
    call MPI_Reduce(R3(1:3),hDMIAvg,3,MPI_Real8,MPI_SUM,0,MPI_COMM_WORLD,ierr)

    do i=1,3;   R3(i) = sum(hST(:,:,:,i)*oMag);   enddo
    call MPI_Reduce(R3(1:3),hSTAvg,3,MPI_Real8,MPI_SUM,0,MPI_COMM_WORLD,ierr)

    do i=1,3;   R3(i) = sum(hThe(:,:,:,i)*oMag);   enddo
    call MPI_Reduce(R3(1:3),hTheAvg,3,MPI_Real8,MPI_SUM,0,MPI_COMM_WORLD,ierr)


    R3(1) = sum(fTot)
    call MPI_Reduce(R3(1),fTotAvg,1,MPI_Real8,MPI_SUM,0,MPI_COMM_WORLD,ierr)

    R3(1) = sum(fExt)
    call MPI_Reduce(R3(1),fExtAvg,1,MPI_Real8,MPI_SUM,0,MPI_COMM_WORLD,ierr)

    R3(1) = sum(fAni)
    call MPI_Reduce(R3(1),fAniAvg,1,MPI_Real8,MPI_SUM,0,MPI_COMM_WORLD,ierr)

    R3(1) = sum(fStr)
    call MPI_Reduce(R3(1),fStrAvg,1,MPI_Real8,MPI_SUM,0,MPI_COMM_WORLD,ierr)

    R3(1) = sum(fExc)
    call MPI_Reduce(R3(1),fExcAvg,1,MPI_Real8,MPI_SUM,0,MPI_COMM_WORLD,ierr)

    R3(1) = sum(fDMI)
    call MPI_Reduce(R3(1),fDMIAvg,1,MPI_Real8,MPI_SUM,0,MPI_COMM_WORLD,ierr)

    if(flagElastic) then
      do i=1,6;   R3(i) = sum(e(:,:,:,i)*oMag);   enddo
      call MPI_Reduce(R3,eAvg,6,MPI_Real8,MPI_SUM,0,MPI_COMM_WORLD,ierr)
  
      do i=1,6;   R3(i) = sum(eta(:,:,:,i)*oMag);   enddo
      call MPI_Reduce(R3,etaAvg,6,MPI_Real8,MPI_SUM,0,MPI_COMM_WORLD,ierr)
  
      do i=1,6;   R3(i) = sum(s(:,:,:,i)*oMag);     enddo
      call MPI_Reduce(R3,sAvg,6,MPI_Real8,MPI_SUM,0,MPI_COMM_WORLD,ierr)

      R3(1) = sum(fEla)
      call MPI_Reduce(R3(1),fElaAvg,1,MPI_Real8,MPI_SUM,0,MPI_COMM_WORLD,ierr)
    endif

    if(rank==0) then
      mAvg    = mAvg    / (nn * fmag)
      hEffAvg = hEffAvg / (nn * fmag)
      hAniAvg = hAniAvg / (nn * fmag)
      hStrAvg = hStrAvg / (nn * fmag)
      hElaAvg = hElaAvg / (nn * fmag)
      hSTAvg  = hSTAvg  / (nn * fmag)
      hTheAvg = hTheAvg / (nn * fmag)

      fTotAvg = fTotAvg / (nn * fmag)
      fExtAvg = fExtAvg / (nn * fmag)
      fAniAvg = fAniAvg / (nn * fmag)
      fStrAvg = fStrAvg / (nn * fmag)
      fElaAvg = fElaAvg / (nn * fmag)
      fExcAvg = fExcAvg / (nn * fmag)
      fDMIAvg = fDMIAvg / (nn * fmag)

      eAvg    = eAvg    / (nn * fmag)
      etaAvg  = etaAvg  / (nn * fmag)
      sAvg    = sAvg    / (nn * fmag)

      write(13,1001)kt,mAvg(1),mAvg(2),mAvg(3)
      write(14,1001)kt,hEffAvg(1)*M0,hEffAvg(2)*M0,hEffAvg(3)*M0, &
                       hExt(1,kt)*M0,hExt(2,kt)*M0,hExt(3,kt)*M0,   hStrAvg(1)*M0,hStrAvg(2)*M0,hStrAvg(3)*M0, &
                       hAniAvg(1)*M0,hAniAvg(2)*M0,hAniAvg(3)*M0,   hElaAvg(1)*M0,hElaAvg(2)*M0,hElaAvg(3)*M0, &
                       hExcAvg(1)*M0,hExcAvg(2)*M0,hExcAvg(3)*M0,   hDMIAvg(1)*M0,hDMIAvg(2)*M0,hDMIAvg(3)*M0, &
                       hSTAvg(1)*M0, hSTAvg(2)*M0, hSTAvg(3)*M0,    hTheAvg(1)*M0,hTheAvg(2)*M0,hTheAvg(3)*M0
      write(17,1001)kt,fTotAvg*mu0*M0**2, fExtAvg*mu0*M0**2, fAniAvg*mu0*M0**2, fStrAvg*mu0*M0**2, fElaAvg*s0 &
  		              ,fExcAvg*mu0*M0**2, fDMIAvg*mu0*M0**2
      if(flagElastic) write(15,1001)kt,eAvg(1),eAvg(2),eAvg(3),eAvg(4),eAvg(5),eAvg(6) &
                                      ,etaAvg(1),etaAvg(2),etaAvg(3),etaAvg(4),etaAvg(5),etaAvg(6)
      if(flagElastic) write(16,1001)kt,sAvg(1)*s0,sAvg(2)*s0,sAvg(3)*s0,sAvg(4)*s0,sAvg(5)*s0,sAvg(6)*s0
    endif

1001  format(i10,30es16.7e3)

    call MPI_Barrier(MPI_COMM_WORLD,ierr)

  end subroutine



  subroutine outputSpatialDistribution()

    use mod_interfaces
    use mod_mainMagnetic
    implicit none

    passfilename = 'magnt'
    call outputxN_P(passfilename,magnt(:,:,:,1),magnt(:,:,:,2),magnt(:,:,:,3))

    if(flagOutH) then
      passfilename = 'hEff'
      call outputxN_P(passfilename,hEffOut(:,:,:,1)*M0,hEffOut(:,:,:,2)*M0,hEffOut(:,:,:,3)*M0)

      passfilename = 'hStray'
      if(flagStrayField) call outputxN_P(passfilename,hStr(:,:,:,1)*M0,hStr(:,:,:,2)*M0,hStr(:,:,:,3)*M0)

      passfilename = 'hAnis'
      if(flagAnisotropy) call outputxN_P(passfilename,hAni(:,:,:,1)*M0,hAni(:,:,:,2)*M0,hAni(:,:,:,3)*M0)

      passfilename = 'hElas'
      if(flagElastic) call outputxN_P(passfilename,hEla(:,:,:,1)*M0,hEla(:,:,:,2)*M0,hEla(:,:,:,3)*M0)

      passfilename = 'hST'
      if(flagST) call outputxN_P(passfilename,hST(:,:,:,1)*M0,hST(:,:,:,2)*M0,hST(:,:,:,3)*M0)

      passfilename = 'hTher'
      if(flagThermalFluc) call outputxN_P(passfilename,hThe(:,:,:,1)*M0,hThe(:,:,:,2)*M0,hThe(:,:,:,3)*M0)

      passfilename = 'hExch'
      call outputxN_P(passfilename,hExc(:,:,:,1)*M0,hExc(:,:,:,2)*M0,hExc(:,:,:,3)*M0)

      passfilename = 'hDMI'
      if(flagDMI) call outputxN_P(passfilename,hDMI(:,:,:,1)*M0,hDMI(:,:,:,2)*M0,hDMI(:,:,:,3)*M0)
    endif

    if(flagOutE) then
      passfilename = 'fTotal'
      call outputxN_P(passfilename,fTot*mu0*M0**2)

      passfilename = 'fStray'
      if(flagStrayField) call outputxN_P(passfilename,fStr*mu0*M0**2)

      passfilename = 'fAnis'
      if(flagAnisotropy) call outputxN_P(passfilename,fAni*mu0*M0**2)

      passfilename = 'fElas'
      if(flagElastic) call outputxN_P(passfilename,fEla*s0)

      passfilename = 'fExch'
      call outputxN_P(passfilename,fExc*mu0*M0**2)

      passfilename = 'fDMI'
      if(flagDMI) call outputxN_P(passfilename,fDMI*mu0*M0**2)
    endif

    if(flagOutS.and.flagElastic) then
      passfilename = 'eigStn'
      call outputxN_P(passfilename,eta(:,:,:,1),eta(:,:,:,2),eta(:,:,:,3),eta(:,:,:,4),eta(:,:,:,5),eta(:,:,:,6))

      passfilename = 'strain'
      call outputxN_P(passfilename,e(:,:,:,1),e(:,:,:,2),e(:,:,:,3),e(:,:,:,4),e(:,:,:,5),e(:,:,:,6))

      passfilename = 'stress'
      call outputxN_P(passfilename,s(:,:,:,1)*s0,s(:,:,:,2)*s0,s(:,:,:,3)*s0,s(:,:,:,4)*s0,s(:,:,:,5)*s0,s(:,:,:,6)*s0)
    endif

    call MPI_Barrier(MPI_COMM_WORLD,ierr)

  end subroutine



  subroutine finalize()

    use mod_interfaces
    use mod_mainMagnetic
    implicit none

    if(rank==0) then
      close(13)
      close(14)
      close(17)
      if(flagElastic) close(15)
      if(flagElastic) close(16)
    endif

	  print *, "Finished program on Rank ",rank

    call MPI_finalize(ierr)

  end subroutine



  subroutine FourierSpectrum_LLG()

    use mod_interfaces
    use mod_mainMagnetic
    implicit none

    call getHeff()
!!!!!(output data table)!!!!!
    if (mod(kt,ktOutTable)==0.or.kt==kt0.or.kt==ktMax) then
      call outputDataTable()
    endif
    call MPI_Barrier(MPI_COMM_WORLD,ierr)
!!!!!(end of data table output)!!!!!
!!!!!(output spatial distribution)!!!!!
    if (mod(kt,ktOutDist)==0.or.kt==kt0.or.kt==ktMax) then
      call outputSpatialDistribution()
    endif
    call MPI_Barrier(MPI_COMM_WORLD,ierr)
!!!!!(end of spatial distribution output)!!!!!
    call LLG_solver

    call MPI_Barrier(MPI_COMM_WORLD,ierr)

  end subroutine



  subroutine ExpRK4_LLG()             !extended framework of explicit RK4 solver

    use mod_interfaces
    use mod_mainMagnetic
    implicit none

    integer i,j,k,period   !if there is some variable that uses the same name as "period", you can change this one since it appears only here
    real*8 dtReduced
    real*8,parameter :: dtCoeff(4)=[0.5d0, 0.5d0, 1.0d0, 0.0d0], dMdtCoeff(4)=[1.0d0/6.0d0, 1.0d0/3.0d0, 1.0d0/3.0d0, 1.0d0/6.0d0]
    real*8,allocatable :: magnt0(:,:,:,:),McH(:,:,:,:), dMdt(:,:,:,:,:)

    allocate (magnt0(Rn3,Rn2,Rn1,3));   magnt0=0.0d0
    allocate (McH(Rn3,Rn2,Rn1,3));      McH=0.0d0
    allocate (dMdt(Rn3,Rn2,Rn1,3,4));      dMdt=0.0d0

    dtReduced = dt*gamma*M0/(1+alphaM**2)
    magnt0=magnt
    do period=1,4
      call getHeff()

      if(period==1) then   !output
        !!!!!(output data table)!!!!!
        if (mod(kt,ktOutTable)==0.or.kt==kt0.or.kt==ktMax) then
          call outputDataTable()
        endif
        call MPI_Barrier(MPI_COMM_WORLD,ierr)
        !!!!!(end of data table output)!!!!!
        !!!!!(output spatial distribution)!!!!!
        if (mod(kt,ktOutDist)==0.or.kt==kt0.or.kt==ktMax) then
          call outputSpatialDistribution()
        endif
        call MPI_Barrier(MPI_COMM_WORLD,ierr)
        !!!!!(end of spatial distribution output)!!!!!
      end if

      call mpi_barrier(Mpi_comm_world,ierr)
      McH(:,:,:,1) = magnt(:,:,:,2)*hEff(:,:,:,3) - magnt(:,:,:,3)*hEff(:,:,:,2)
      McH(:,:,:,2) = magnt(:,:,:,3)*hEff(:,:,:,1) - magnt(:,:,:,1)*hEff(:,:,:,3)
      McH(:,:,:,3) = magnt(:,:,:,1)*hEff(:,:,:,2) - magnt(:,:,:,2)*hEff(:,:,:,1)

      dMdt(:,:,:,1,period) = -McH(:,:,:,1) - alphaM*(magnt(:,:,:,2)*McH(:,:,:,3) - magnt(:,:,:,3)*McH(:,:,:,2))
      dMdt(:,:,:,2,period) = -McH(:,:,:,2) - alphaM*(magnt(:,:,:,3)*McH(:,:,:,1) - magnt(:,:,:,1)*McH(:,:,:,3))
      dMdt(:,:,:,3,period) = -McH(:,:,:,3) - alphaM*(magnt(:,:,:,1)*McH(:,:,:,2) - magnt(:,:,:,2)*McH(:,:,:,1))

      magnt(:,:,:,:) = magnt0(:,:,:,:) + dtCoeff(period) * dMdt(:,:,:,:,period) * dtReduced
      call mpi_barrier(Mpi_comm_world,ierr)

    end do

    magnt = magnt0
    do period=1,4
      magnt(:,:,:,:) = magnt(:,:,:,:) + dMdtCoeff(period) * dMdt(:,:,:,:,period) * dtReduced
    end do
    call mpi_barrier(Mpi_comm_world,ierr)

    deallocate(magnt0)
    deallocate(McH)
    deallocate(dMdt)

    call MPI_Barrier(MPI_COMM_WORLD,ierr)

  end subroutine



  program main

    use mod_interfaces
    use mod_mainMagnetic
    implicit none

    integer i,j,k

    call initMPI()
    call inputParameters()
    call init()

    do kt = kt0 , ktMax                     !cuz we can't detach the output module from the solver(maybe we can do in the future), the output code is merged into the solvers
      isThermalFieldCalc=0
      Selectcase(choiceLLGSolver)
      case(solverFourierSpectrum)
        call FourierSpectrum_LLG()
      case(solverExpRK4)
        call ExpRK4_LLG()
      endselect
    enddo   !kt=0,ktMax, end of magnetization evolution

    call mpi_barrier(Mpi_comm_world,ierr)
    call finalize()

  end program