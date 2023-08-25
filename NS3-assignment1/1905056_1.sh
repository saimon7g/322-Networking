#!/bin/bash

./ns3 run "scratch/1905056_1.cc --numNode=20 --numFlow=10 --numPacketperSecond=100 --coverageArea=2 --verbose=false --tracing=true --variable_param=1"
./ns3 run "scratch/1905056_1.cc --numNode=40 --numFlow=20 --numPacketperSecond=100 --coverageArea=2 --verbose=false --tracing=true --variable_param=1"
./ns3 run "scratch/1905056_1.cc --numNode=60 --numFlow=30 --numPacketperSecond=100 --coverageArea=2 --verbose=false --tracing=true --variable_param=1"
./ns3 run "scratch/1905056_1.cc --numNode=80 --numFlow=40 --numPacketperSecond=100 --coverageArea=2 --verbose=false --tracing=true --variable_param=1"
./ns3 run "scratch/1905056_1.cc --numNode=100 --numFlow=50 --numPacketperSecond=100 --coverageArea=2 --verbose=false --tracing=true --variable_param=1"

gnuplot -e "set terminal pngcairo enhanced font 'arial,10' fontscale 1.0 size 800,600;
            set output 'scratch/node_vs_throughput.png';
            set title 'node vs throughput graph';
            set xlabel 'node';
            set ylabel 'throughput';
            plot 'scratch/throughput.dat' using 1:2 with lines title 'wiegweuifwweuif';"

gnuplot -e "set terminal pngcairo enhanced font 'arial,10' fontscale 1.0 size 800,600;
            set output 'scratch/node_vs_deliveryratio.png';
            set title 'node vs throughput graph';
            set xlabel 'node';
            set ylabel 'throughput';
            plot 'scratch/delivery_ratio.dat' using 1:2 with lines title 'wiegweuifwweuif';"

rm -if  scratch/throughput.dat
rm -if  scratch/delivery_ratio.dat



./ns3 run "scratch/1905056_1.cc --numNode=40 --numFlow=10 --numPacketperSecond=100 --coverageArea=2 --verbose=false --tracing=true --variable_param=2"
./ns3 run "scratch/1905056_1.cc --numNode=40 --numFlow=20 --numPacketperSecond=100 --coverageArea=2 --verbose=false --tracing=true --variable_param=2"
./ns3 run "scratch/1905056_1.cc --numNode=40 --numFlow=30 --numPacketperSecond=100 --coverageArea=2 --verbose=false --tracing=true --variable_param=2"
./ns3 run "scratch/1905056_1.cc --numNode=40 --numFlow=40 --numPacketperSecond=100 --coverageArea=2 --verbose=false --tracing=true --variable_param=2"
./ns3 run "scratch/1905056_1.cc --numNode=40 --numFlow=50 --numPacketperSecond=100 --coverageArea=2 --verbose=false --tracing=true --variable_param=2"

gnuplot -e "set terminal pngcairo enhanced font 'arial,10' fontscale 1.0 size 800,600;
            set output 'scratch/flow_vs_throughput.png';
            set title 'flow vs throughput graph';
            set xlabel 'flow';
            set ylabel 'throughput';
            plot 'scratch/throughput.dat' using 1:2 with lines title 'wiegweuifwweuif';"

gnuplot -e "set terminal pngcairo enhanced font 'arial,10' fontscale 1.0 size 800,600;
            set output 'scratch/flow_vs_deliveryratio.png';
            set title 'flow vs throughput graph';
            set xlabel 'flow';
            set ylabel 'throughput';
            plot 'scratch/delivery_ratio.dat' using 1:2 with lines title 'wiegweuifwweuif';"

rm -if  scratch/throughput.dat
rm -if  scratch/delivery_ratio.dat

./ns3 run "scratch/1905056_1.cc --numNode=40 --numFlow=30 --numPacketperSecond=100 --coverageArea=2 --verbose=false --tracing=true --variable_param=3"
./ns3 run "scratch/1905056_1.cc --numNode=40 --numFlow=30 --numPacketperSecond=200 --coverageArea=2 --verbose=false --tracing=true --variable_param=3"
./ns3 run "scratch/1905056_1.cc --numNode=40 --numFlow=30 --numPacketperSecond=300 --coverageArea=2 --verbose=false --tracing=true --variable_param=3"
./ns3 run "scratch/1905056_1.cc --numNode=40 --numFlow=30 --numPacketperSecond=400 --coverageArea=2 --verbose=false --tracing=true --variable_param=3"
./ns3 run "scratch/1905056_1.cc --numNode=40 --numFlow=30 --numPacketperSecond=500 --coverageArea=2 --verbose=false --tracing=true --variable_param=3"

gnuplot -e "set terminal pngcairo enhanced font 'arial,10' fontscale 1.0 size 800,600;
            set output 'scratch/packetpersecond_vs_throughput.png';
            set title 'packetpersecond vs throughput graph';
            set xlabel 'packetpersecond';
            set ylabel 'throughput';
            plot 'scratch/throughput.dat' using 1:2 with lines title 'wiegweuifwweuif';"

gnuplot -e "set terminal pngcairo enhanced font 'arial,10' fontscale 1.0 size 800,600;
            set output 'scratch/packetpersecond_vs_deliveryratio.png';
            set title 'packetpersecond vs throughput graph';
            set xlabel 'packetpersecond';
            set ylabel 'throughput';
            plot 'scratch/delivery_ratio.dat' using 1:2 with lines title 'wiegweuifwweuif';"

rm -if  scratch/throughput.dat
rm -if  scratch/delivery_ratio.dat

./ns3 run "scratch/1905056_1.cc --numNode=40 --numFlow=30 --numPacketperSecond=100 --coverageArea=1 --verbose=false --tracing=true --variable_param=4"
./ns3 run "scratch/1905056_1.cc --numNode=40 --numFlow=30 --numPacketperSecond=100 --coverageArea=2 --verbose=false --tracing=true --variable_param=4"
./ns3 run "scratch/1905056_1.cc --numNode=40 --numFlow=30 --numPacketperSecond=100 --coverageArea=3 --verbose=false --tracing=true --variable_param=4"
./ns3 run "scratch/1905056_1.cc --numNode=40 --numFlow=30 --numPacketperSecond=100 --coverageArea=4 --verbose=false --tracing=true --variable_param=4"
./ns3 run "scratch/1905056_1.cc --numNode=40 --numFlow=30 --numPacketperSecond=100 --coverageArea=5 --verbose=false --tracing=true --variable_param=4"

gnuplot -e "set terminal pngcairo enhanced font 'arial,10' fontscale 1.0 size 800,600;
            set output 'scratch/coveragearea_vs_throughput.png';
            set title 'coveragearea vs throughput graph';
            set xlabel 'coveragearea';
            set ylabel 'throughput';
            plot 'scratch/throughput.dat' using 1:2 with lines title 'wiegweuifwweuif';"

gnuplot -e "set terminal pngcairo enhanced font 'arial,10' fontscale 1.0 size 800,600;
            set output 'scratch/coveragearea_vs_deliveryratio.png';
            set title 'coveragearea vs delivery ratio graph';
            set xlabel 'coveragearea';
            set ylabel 'delivery ratio';
            plot 'scratch/delivery_ratio.dat' using 1:2 with lines title 'wiegweuifwweuif';"

rm -if  scratch/throughput.dat
rm -if  scratch/delivery_ratio.dat

    










