# PathFinder

This research is an effort to develop visual-graphic interfaces for sense-making of large networks. The goal is to create an algorithmic model and prototype that will allow researchers to study and analyze the hidden patterns in a wide range of networks by identifying and characterizing communities and connectivity between a set of pre-marked nodes within large networks.

# How to Run:

The program can be run from the command line, however, it takes many variables. The suggested method of running it is to use the web platform at: [Path Finder](www.path-finder.io) 

If you want to run it locally here is how:

(1) Compile using this (fill in the path location): g++ -o PathFinder /PathFinder/Source_Code/*.cpp -I /PathFinder/Header_Files/ -pthread -std=c++11 -O3

(2) Run program, this is an example query: ./PathFinder "Path to dataset here, leave quotes." KSSP Alin_Deutsch Mary_F._Fernandez -1 -1 -1 1 2 20 10 5 20 10 5 2 20 10 5 2 299315610694 true 2 12 -1 -1 -1 -1 -1 0 20 10 5 20 10 5 2 0 -1 -1 -1 -1 -1 false

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
    
(3) Additional information on parameters can be found on the insutrctions page: [Instructions](http://www.path-finder.io/instructions.html). If more information on a variable is needed, please check the code.

# Datasets:

Pre-loaded datasets are from the [Stanford SNAP](http://snap.stanford.edu/data/index.html) collection, including: DBLP, Youtube and LiveJournal.

DBLP w/ names is the DBLP dataset which uses names instead of integers to represent nodes. Name information was taken from the DBLP webpage ([Uni Trier](http://dblp.uni-trier.de/faq/How+can+I+download+the+whole+dblp+dataset.html)) and modified for use in the PathFinder program.
