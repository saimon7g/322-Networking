#!/bin/bash
#!/bin/bash

./ns3 run "scratch/1905056_2.cc --numNode=20 --numFlow=10 --numPacketperSecond=100 --speedOfNodes=2 --verbose=false --tracing=true"
./ns3 run "scratch/1905056_2.cc --numNode=40 --numFlow=20 --numPacketperSecond=100 --speedOfNodes=2 --verbose=false --tracing=true"
./ns3 run "scratch/1905056_2.cc --numNode=60 --numFlow=30 --numPacketperSecond=100 --speedOfNodes=2 --verbose=false --tracing=true"
./ns3 run "scratch/1905056_2.cc --numNode=80 --numFlow=40 --numPacketperSecond=100 --speedOfNodes=2 --verbose=false --tracing=true"
./ns3 run "scratch/1905056_2.cc --numNode=100 --numFlow=50 --numPacketperSecond=100 --speedOfNodes=2 --verbose=false --tracing=true"

gnuplot -e "set terminal pngcairo enhanced font 'arial,10' fontscale 1.0 size 800,600;
            set output 'scratch/node_vs_throughput_2.png';
            set title 'node vs throughput graph';
            set xlabel 'node';
            set ylabel 'throughput';
            plot 'scratch/throughput_2.dat' using 1:2 with lines title 'wiegweuifwweuif';"

gnuplot -e "set terminal pngcairo enhanced font 'arial,10' fontscale 1.0 size 800,600;
            set output 'scratch/node_vs_deliveryratio_2.png';
            set title 'node vs throughput graph';
            set xlabel 'node';
            set ylabel 'throughput';
            plot 'scratch/delivery_ratio.dat' using 1:2 with lines title 'wiegweuifwweuif';"

rm -if  scratch/throughput_2.dat
rm -if  scratch/delivery_ratio_2.dat



./ns3 run "scratch/1905056_2.cc --numNode=40 --numFlow=10 --numPacketperSecond=100 --speedOfNodes=2 --verbose=false --tracing=true"
./ns3 run "scratch/1905056_2.cc --numNode=40 --numFlow=20 --numPacketperSecond=100 --speedOfNodes=2 --verbose=false --tracing=true"
./ns3 run "scratch/1905056_2.cc --numNode=40 --numFlow=30 --numPacketperSecond=100 --speedOfNodes=2 --verbose=false --tracing=true"
./ns3 run "scratch/1905056_2.cc --numNode=40 --numFlow=40 --numPacketperSecond=100 --speedOfNodes=2 --verbose=false --tracing=true"
./ns3 run "scratch/1905056_2.cc --numNode=40 --numFlow=50 --numPacketperSecond=100 --speedOfNodes=2 --verbose=false --tracing=true"

gnuplot -e "set terminal pngcairo enhanced font 'arial,10' fontscale 1.0 size 800,600;
            set output 'scratch/flow_vs_throughput_2.png';
            set title 'flow vs throughput graph';
            set xlabel 'flow';
            set ylabel 'throughput';
            plot 'scratch/throughput_2.dat' using 1:2 with lines title 'wiegweuifwweuif';"

gnuplot -e "set terminal pngcairo enhanced font 'arial,10' fontscale 1.0 size 800,600;
            set output 'scratch/flow_vs_deliveryratio_2.png';
            set title 'flow vs throughput graph';
            set xlabel 'flow';
            set ylabel 'throughput';
            plot 'scratch/delivery_ratio_2.dat' using 1:2 with lines title 'wiegweuifwweuif';"

rm -if  scratch/throughput_2.dat
rm -if  scratch/delivery_ratio_2.dat

./ns3 run "scratch/1905056_2.cc --numNode=40 --numFlow=30 --numPacketperSecond=100 --speedOfNodes=2 --verbose=false --tracing=true"
./ns3 run "scratch/1905056_2.cc --numNode=40 --numFlow=30 --numPacketperSecond=200 --speedOfNodes=2 --verbose=false --tracing=true"
./ns3 run "scratch/1905056_2.cc --numNode=40 --numFlow=30 --numPacketperSecond=300 --speedOfNodes=2 --verbose=false --tracing=true"
./ns3 run "scratch/1905056_2.cc --numNode=40 --numFlow=30 --numPacketperSecond=400 --speedOfNodes=2 --verbose=false --tracing=true"
./ns3 run "scratch/1905056_2.cc --numNode=40 --numFlow=30 --numPacketperSecond=500 --speedOfNodes=2 --verbose=false --tracing=true"

gnuplot -e "set terminal pngcairo enhanced font 'arial,10' fontscale 1.0 size 800,600;
            set output 'scratch/packetpersecond_vs_throughput_2.png';
            set title 'packetpersecond vs throughput graph';
            set xlabel 'packetpersecond';
            set ylabel 'throughput';
            plot 'scratch/throughput_2.dat' using 1:2 with lines title 'wiegweuifwweuif';"

gnuplot -e "set terminal pngcairo enhanced font 'arial,10' fontscale 1.0 size 800,600;
            set output 'scratch/packetpersecond_vs_deliveryratio_2.png';
            set title 'packetpersecond vs throughput graph';
            set xlabel 'packetpersecond';
            set ylabel 'throughput';
            plot 'scratch/delivery_ratio_2.dat' using 1:2 with lines title 'wiegweuifwweuif';"

rm -if  scratch/throughput_2.dat
rm -if  scratch/delivery_ratio_2.dat

./ns3 run "scratch/1905056_2.cc --numNode=40 --numFlow=30 --numPacketperSecond=100 --speedOfNodes=1 --verbose=false --tracing=true"
./ns3 run "scratch/1905056_2.cc --numNode=40 --numFlow=30 --numPacketperSecond=100 --speedOfNodes=2 --verbose=false --tracing=true"
./ns3 run "scratch/1905056_2.cc --numNode=40 --numFlow=30 --numPacketperSecond=100 --speedOfNodes=3 --verbose=false --tracing=true"
./ns3 run "scratch/1905056_2.cc --numNode=40 --numFlow=30 --numPacketperSecond=100 --speedOfNodes=4 --verbose=false --tracing=true"
./ns3 run "scratch/1905056_2.cc --numNode=40 --numFlow=30 --numPacketperSecond=100 --speedOfNodes=5 --verbose=false --tracing=true"

gnuplot -e "set terminal pngcairo enhanced font 'arial,10' fontscale 1.0 size 800,600;
            set output 'scratch/speedOfNodes_vs_throughput_2.png';
            set title 'speedOfNodes vs throughput graph';
            set xlabel 'speedOfNodes';
            set ylabel 'throughput';
            plot 'scratch/throughput_2.dat' using 1:2 with lines title 'wiegweuifwweuif';"

gnuplot -e "set terminal pngcairo enhanced font 'arial,10' fontscale 1.0 size 800,600;
            set output 'scratch/speedOfNodes_vs_deliveryratio_2.png';
            set title 'speedOfNodes vs delivery ratio graph';
            set xlabel 'speedOfNodes';
            set ylabel 'delivery ratio';
            plot 'scratch/delivery_ratio_2.dat' using 1:2 with lines title 'wiegweuifwweuif';"

rm -if  scratch/throughput_2.dat
rm -if  scratch/delivery_ratio_2.dat
