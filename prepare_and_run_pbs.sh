#! /bin/bash

#cd ~/mean_passages2/
# module add gcc/4.5.3
# make

#if [ ${USER} = "ufszczep" ];
#then
#module add gcc/4.5.3
#module add fftw

#make -f makefile_zeus
#else
#make
#fi


#rm *.png
#rm *.txt
touch jobs_ids.txt

tmpdir="/tmp/"
storagedir="./data"
# /mnt/lustre/scratch/people/ufszczep/
# /storage/ufszczep/

if [ ${USER} = "ufszczep" ];
then
  tmpdir="\/mnt\/lustre\/scratch2\/people\/ufszczep\/"
# storagedir="\/storage\/ufszczep\/"
  storagedir="\/mnt\/lustre\/scratch2\/people\/ufszczep\/output\/"

  threads=1
fi 

echo "tmp dir: '$tmpdir'"
echo "storage dir: '$storagedir'"


echo "\n"

# zeby byla kropka w wynikach 'seq' a nie przecinek
export LC_NUMERIC="en_US.UTF-8"




for nt in 1
 do
  for pt in 2
   do
     for alpha in 1.6 #$(seq -w 0.2 0.1 2.0)
      do
      for sigma in 2 4 6 #$(seq -w 0.1 0.02 1.0)
         do
          for num in 1 #$(seq 1 10)
           do
              echo "alpha = $alpha, sigma = $sigma, nt = $nt, pt = $pt n = $num"
              file="a_"$alpha"_s_"$sigma"_nt_"$nt"_pt_"$pt"_"$num".pbs"
                if [ ${USER} = "ufszczep" ];
                then
                    cat pbs_template.tpl | sed -e "s/\${tmp}/$tmpdir/g" -e "s/\${storage}/$storagedir/g" -e "s/\${alpha}/$alpha/g" -e "s/\${sigma}/$sigma/g" -e "s/\${nt}/$nt/g" -e "s/\${pt}/$pt/g" -e "s/\${num}/$num/g" > $file
                    qsub -f $file >> jobs_ids.txt
                else
                    ./generator.x --alpha $alpha --noise $sigma --storage "$storagedir" --tmp "$tmpdir" --pt $pt --nt $nt --data_file_num $num
                fi 
           done
         done
       done 
    done
done



#text=$(tr '\n' ':' <jobs_ids.txt)

#qsub -W depend=afterok:$text  -f "plot_job.pbs"

# 0.5 0.7 0.9 1.1 1.3 1.4 1.5 1.6 1.7 1.8 1.9 2.0 2.1 2.2 2.3 2.4 2.5 2.6 2.7 2.8 2.9 3.0 3.1 3.2 3.3 3.4 3.5 3.6 3.7 3.8 3.9 4.0 4.1 4.2 4.3 4.4 4.5
