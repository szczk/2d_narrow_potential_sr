#! /bin/bash

# do generowania  kilka trajektorii do doktoratu
# o ile wszystko jest ustawione


# zeby byla kropka w wynikach 'seq' a nie przecinek
export LC_NUMERIC="en_US.UTF-8"


make generator


for alpha in 0.5 1.0 1.5 2.0 #$(seq -w 0.2 0.1 2.0)
  do
    ./generator.x --alpha $alpha --noise 2.0 --storage "results" --tmp "." --pt 2 --nt 1 --data_file_num 1 --n 5 
done 


