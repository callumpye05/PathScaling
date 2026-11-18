set -e 


for vertices in 1000, 2000, 4000; do 
    ./bench_matrix "$vertices" 
done
