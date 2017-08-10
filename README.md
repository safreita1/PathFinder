# PathFinder

This research is an effort to develop visual-graphic interfaces for sense-making of large networks. The goal is to create an algorithmic model and prototype that will allow researchers to study and analyze the hidden patterns in a wide range of networks by identifying and characterizing communities and connectivity between a set of pre-marked nodes within large networks.

# How to Run:

The program can be run from the command line, however, it takes many variables. The suggested method of running it is to use the web platform at: path-finder.io

If you want to run it locally here is how:

(1) Compile using something similar to this (fill in the path location): g++ -o PathFinder /PathFinder/Source_Code/*.cpp -I /PathFinder/Header_Files/ -pthread -std=c++11 -O3

(2) ./PathFinder "Put path to dataset here, leave quotes." KSSP Alin_Deutsch Mary_F._Fernandez -1 -1 -1 1 2 20 10 5 20 10 5 2 20 10 5 2 299315610694 true 2 12 -1 -1 -1 -1 -1 0 20 10 5 20 10 5 2 0 -1 -1 -1 -1 -1

(3) The corresponding variables can be identified from looking at the code.

# Datasets:

Pre-loaded datasets are from the Stanford SNAP collection (http://snap.stanford.edu/data/index.html), including: DBLP, Youtube and LiveJournal.

DBLP w/ names is the DBLP dataset which uses names instead of integers to represent nodes. Name information was taken from the DBLP site (http://dblp.uni-trier.de/faq/How+can+I+download+the+whole+dblp+dataset.html) and modified for use in the PathFinder program.
