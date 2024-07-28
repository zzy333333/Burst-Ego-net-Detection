## For Disjoint Interval Setting

```

g++ exact_main.cpp graph.cpp exact.cpp -o DisBurstExact -O2

g++ approximate_main.cpp graph.cpp sample.cpp recalculate.cpp -o DisBurstApp -O2

```

## For Sliding Window Setting

```

g++ exact_main.cpp graph.cpp exact.cpp -o SldBurstExact -O2

g++ exact_main.cpp graph.cpp thinkd.cpp -o ThinkD -O2

g++ parallel_main.cpp graph.cpp parallel.cpp -fopenmp -o SldBurstPara -O2

```
