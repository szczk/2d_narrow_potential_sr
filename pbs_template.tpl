#!/bin/sh -f

###############################################################
#                                                             #
#    Bourne shell script for submitting a serial job to the   #
#    PBS queue using the qsub command.                        #
#                                                             #
###############################################################

#     Remarks: A line beginning with # is a comment.
#              A line beginning with #PBS is a PBS directive.
#              PBS directives must come first; any directives
#                 after the first executable statement are ignored.
#
   
##########################
#                        #
#   The PBS directives   #
#                        #
##########################

#          Set the name of the job (up to 15 characters, 
#          no blank spaces, start with alphanumeric character)

#PBS -N 2d_SR_a_${alpha}_s_${sigma}_nt_${nt}_pt_${pt}_${num}

#          By default, the standard output and error streams are sent
#          to files in the current working directory with names:
#              job_name.osequence_number  <-  output stream
#              job_name.esequence_number  <-  error stream
#          where job_name is the name of the job and sequence_number 
#          is the job number assigned when the job is submitted.
#          Use the directives below to change the files to which the
#          standard output and error streams are sent.

#    #PBS -o stdout_file
#    #PBS -e stderr_file

#PBS -j oe

#PBS -q l_long

#PBS -l walltime=01:00:00

#PBS -A "MNiSW/Zeus_lokalnie/UJ/052/2012"

# send mail when job is (a)borted, (b)begins, (e)nds
#PBS -m abe
#PBS -M krzysztof.sc@gmail.com

echo ------------------------------------------------------
echo -n 'Job is running on node '; cat $PBS_NODEFILE
echo ------------------------------------------------------
echo PBS: qsub is running on $PBS_O_HOST
echo PBS: originating queue is $PBS_O_QUEUE
echo PBS: executing queue is $PBS_QUEUE
echo PBS: working directory is $PBS_O_WORKDIR
echo PBS: execution mode is $PBS_ENVIRONMENT
echo PBS: job identifier is $PBS_JOBID
echo PBS: job name is $PBS_JOBNAME
echo PBS: node file is $PBS_NODEFILE
echo PBS: current home directory is $PBS_O_HOME
echo PBS: PATH = $PBS_O_PATH
echo ------------------------------------------------------

echo " running job... "

cd $PBS_O_HOME/2d_narrow_potential_sr


if [ ${USER} = "ufszczep" ];
then
  tmpdir=$SCRATCH
  storagedir=$STORAGE
  threads=1
fi 

# output=$storagedir/output
output=$SCRATCH
logs=$storagedir/logs

module add gcc 
# module add fftw
module add gsl
#module add libs/glibc/2.7

./generator.x --alpha ${alpha} --noise ${sigma} --storage "$SCRATCH/2d_NP_pt${pt}_D"  --tmp "$SCRATCH" --pt ${pt} --nt ${nt} --data_file_num ${num}  > $logs/SR_2d_a${alpha}_s${sigma}_nt_${nt}_pt${pt}_n${num}.log



# module add gnuplot

# export GDFONTPATH=`pwd`/fonts/
# export GNUPLOT_DEFAULT_GDFONT=LiberationSans-Regular

