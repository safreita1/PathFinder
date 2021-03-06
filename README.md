# PathFinder

This project is an effort to develop the algorithmic tools necessary to analyze large networks in the context of two or more seed nodes. The first goal was to develop the core algorithms necessary for network connectivity analysis, followed by the creation of a web platform to facilitate easy access and intuitive interactions with the network visualizations.

This research was recently published in CIKM '17. Check out the paper on my [website](https://www.scottfreitas.com/).

![visual1](https://user-images.githubusercontent.com/16739132/32156581-930823f4-bcfb-11e7-9559-76d503e72551.jpg)

# How to Run:

The program can be run from the command line, however, it takes many variables. The suggested method of running it is to use the web platform at: [PathFinder](http://www.path-finder.io) 

If you want to run it locally, the instructions are detailed below:

(0) This program was built to run in a Linux Ubuntu environment and assumes that there exists a directory, '/path_finder_files', with two sub-folders 'user_adj_lists' and 'user_files'. To run in Windows, change the location of the output files in the source code to a directory of your choice. These folders are where the program output will be located.

Three files will be created each time the program is successfully run. (a) An adjacency list file containing edge pairs and (b) two DOT files for visualizing the network. 

(1) Compile using this (fill in the path location): g++ -o PathFinder /PathFinder/Source_Code/*.cpp -I /PathFinder/Header_Files/ -pthread -std=c++11 -O3

(2) Run program, this is an example query: ./PathFinder "Path to dataset here, leave quotes." KSSP Alin_Deutsch Mary_F._Fernandez -1 -1 -1 1 2 20 10 5 20 10 5 2 20 10 5 2 299315610694 true 2 12 -1 -1 -1 -1 -1 0 20 10 5 20 10 5 2 -1 -1 -1 -1 -1 false false

Below are the corresponding variables that define the input to the program, in order:

    'program': '/path_finder_files/programs/PathFinder',
    'networkLocation': '/path_finder_files/datasets/DBLP.txt',
    'algType': 'KSSP',
    'node1': '0',
    'node2': '13627',
    'node3': '-1',
    'node4': '-1',
    'node5': '-1',
    'numPaths': '3',
    'depthSSR1': '2',
    'numVerticesFirstIterationSSR1': '20',
    'numVerticesSubsequentIterationsSSR1': '20',
    'criticalVerticesNextIterationSSR1': '20',
    'numVerticesFirstIterationSSR2': '20',
    'numVerticesSubsequentIterationsSSR2': '30',
    'criticalVerticesNextIterationSSR2': '20',
    'depthSSR2': '2',
    'numVerticesFirstIterationCI': '20',
    'numVerticesSubsequentIterationsCI': '10',
    'criticalVerticesNextIterationCI': '5',
    'depthCI': '2',
    'sessionId': '299315610694',
    'useNameList': 'false',
    'colorSchemeFilter': '2',
    'nodeSizeFilter': '12',
    'removeNodes1': '-1',
    'removeNodes2': '-1',
    'removeNodes3': '-1',
    'removeNodes4': '-1',
    'removeNodes5': '-1',
    'edgeSchemeFilter': '0',
    'numVerticesFirstIterationSSR1MST': '20',
    'numVerticesSubsequentIterationsSSR1MST': '10',
    'criticalVerticesNextIterationSSR1MST': '5',
    'numVerticesFirstIterationCIMST': '20',
    'numVerticesSubsequentIterationsCIMST': '10',
    'criticalVerticesNextIterationCIMST': '5',
    'depthCIMST': '2',
    'removeEdges1': '-1',
    'removeEdges2': '-1',
    'removeEdges3': '-1',
    'removeEdges4': '-1',
    'removeEdges5': '-1',
    'searchReduction': 'false',
    'useKSSP': 'false',
    
Each of the variables has a defined range and number of types it takes, some of which depend on each other. Below are the possible ranges. Note: these are not being strictly defined but to be used as a reference point:

    'program': Path to PathFinder executable
    'networkLocation': Path to dataset
    'algType': 'KSSP' for K-Simple Shortest Paths algorithm or 'MST' for Minimum Spanning Tree algorithm
    'node1': Positive Integer, '-1' represents an empty value
    'node2': Positive Integer, '-1' represents an empty value
    'node3': Positive Integer, '-1' represents an empty value
    'node4': Positive Integer, '-1' represents an empty value
    'node5': Positive Integer, '-1' represents an empty value
    'numPaths': 1-15
    'depthSSR1': 2-4
    'numVerticesFirstIterationSSR1': 5, 10, 20, 30, 40, 60, 'all'
    'numVerticesSubsequentIterationsSSR1': 5, 10, 20, 30, 40, 60, 'all'
    'criticalVerticesNextIterationSSR1': 5, 10, 20, 30, 40, 60, 'all'
    'numVerticesFirstIterationSSR2': 5, 10, 20, 30, 40, 60, 'all'
    'numVerticesSubsequentIterationsSSR2': 5, 10, 20, 30, 40, 60, 'all'
    'criticalVerticesNextIterationSSR2': 5, 10, 20, 30, 40, 60, 'all'
    'depthSSR2': 1-4
    'numVerticesFirstIterationCI': 5, 10, 20, 30, 40, 60, 'all'
    'numVerticesSubsequentIterationsCI': 5, 10, 20, 30, 40, 60, 'all'
    'criticalVerticesNextIterationCI': 5, 10, 20, 30, 40, 60, 'all'
    'depthCI': 0-4
    'sessionId': Any positive integer
    'useNameList': true or false
    'colorSchemeFilter': 1-7
    'nodeSizeFilter': 2, 4, 6, 8, 10, 12
    'removeNodes1': Positive Integer, '-1' represents an empty value
    'removeNodes2': Positive Integer, '-1' represents an empty value
    'removeNodes3': Positive Integer, '-1' represents an empty value
    'removeNodes4': Positive Integer, '-1' represents an empty value
    'removeNodes5': Positive Integer, '-1' represents an empty value
    'edgeSchemeFilter': 0 or 1
    'numVerticesFirstIterationSSR1MST': 5, 10, 20, 30, 40, 60, 'all'
    'numVerticesSubsequentIterationsSSR1MST': 5, 10, 20, 30, 40, 60, 'all'
    'criticalVerticesNextIterationSSR1MST': 5, 10, 20, 30, 40, 60, 'all'
    'numVerticesFirstIterationCIMST': 5, 10, 20, 30, 40, 60, 'all'
    'numVerticesSubsequentIterationsCIMST': 5, 10, 20, 30, 40, 60, 'all'
    'criticalVerticesNextIterationCIMST': 5, 10, 20, 30, 40, 60, 'all'
    'depthCIMST': 0-4
    'removeEdges1': Positive Integer, '-1' represents an empty value
    'removeEdges2': Positive Integer, '-1' represents an empty value
    'removeEdges3': Positive Integer, '-1' represents an empty value
    'removeEdges4': Positive Integer, '-1' represents an empty value
    'removeEdges5': Positive Integer, '-1' represents an empty value
    'searchReduction': true or false
    'useKSSP': true or false
    
(3) Create a visualization using GraphViz in the Ubuntu environment the following way: /usr/gin/sfdp -Goverlap=false -Tpng 'DOT file (no quotes)' -o 'name of file.png (no quotes)' 

(4) Additional information on parameters can be found on the insutrctions page: [Instructions](http://www.path-finder.io/instructions.html). If more information on a variable is needed, please check the code.

# Datasets:

Pre-loaded datasets are from the [Stanford SNAP](http://snap.stanford.edu/data/index.html) collection, including: DBLP, Youtube and LiveJournal.

DBLP w/ names is the DBLP dataset which uses names instead of integers to represent nodes. Name information was taken from the DBLP webpage ([Uni Trier](http://dblp.uni-trier.de/faq/How+can+I+download+the+whole+dblp+dataset.html)) and modified for use in the PathFinder program.
